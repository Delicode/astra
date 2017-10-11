// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.
#include <stdio.h>
#include <string.h>
#include <astra/capi/astra.h>
#include <astra/capi/streams/image_types.h>
#include <astra/capi/streams/infrared_capi.h>
#include <astra/capi/streams/image_capi.h>
#include <key_handler.h>

void print_ir(astra_infraredframe_t irFrame)
{
    astra_image_metadata_t metadata;
    uint8_t* irData;

    size_t irByteLength;

    astra_infraredframe_get_data_ptr(irFrame, &irData, &irByteLength);

    astra_infraredframe_get_metadata(irFrame, &metadata);

    int width = metadata.width;
    int height = metadata.height;
    size_t index = ((width * (height / 2)) + (width / 2));

    astra_frame_index_t frameIndex;
    astra_infraredframe_get_frameindex(irFrame, &frameIndex);

    uint8_t middle = irData[index];
    printf("ir frameIndex: %d, data %d\n", frameIndex, (int)middle);
}


int main(int argc, char* argv[])
{
    set_key_handler();

    astra_initialize();

    astra_streamsetconnection_t sensor;

    astra_streamset_open("device/default", &sensor);

    astra_reader_t reader;
    astra_reader_create(sensor, &reader);


    astra_infraredstream_t irStream;
    astra_reader_get_infraredstream(reader, &irStream);

    astra_reader_get_infraredstream(reader, &irStream);

    astra_result_token_t token;
    size_t count = 0;
    astra_imagestream_t imgstream = (astra_imagestream_t)irStream;
    astra_imagestream_request_modes(imgstream, &token, &count);

    astra_imagestream_mode_t allmodes[100];
    memset(allmodes, 0, sizeof(allmodes));

    if (count > 100)
        count = 100;

    astra_imagestream_get_modes_result(imgstream, token, allmodes, count);

    int selected_mode_index = -1;

    int desired_width = 1280;
    int desired_height = 1024;
    int desired_fps = 30;
    int desired_pixelformat = ASTRA_PIXEL_FORMAT_GRAY16;

    unsigned int i;
    for (i = 0; i < count; i++)
    {
        astra_imagestream_mode_t* t = &allmodes[i];
        if (allmodes[i].width == desired_width
                && allmodes[i].height == desired_height
                && allmodes[i].fps == desired_fps
                && allmodes[i].pixelFormat == desired_pixelformat)
        {
            selected_mode_index = i;
        }

        fprintf(stderr, "fps: %d, id: %d, width: %d, height: %d, format: %d\n", (int)t->fps, (unsigned int)t->id, t->width, t->height, t->pixelFormat);
    }

    if (selected_mode_index == -1)
    {
        fprintf(stderr, "did not find desired video mode\n");
        return 0;
    }

    astra_imagestream_mode_t used_videomode = allmodes[selected_mode_index];

    int rc = astra_imagestream_set_mode(imgstream, &used_videomode);
    if (rc != ASTRA_STATUS_SUCCESS)
    {
        fprintf(stderr, "Failed setting video mode %d\n", rc);
        return 0;
    }

    astra_stream_start(irStream);

    astra_frame_index_t lastFrameIndex = -1;

    do
    {
        astra_temp_update();

        astra_reader_frame_t frame;
        astra_status_t rc = astra_reader_open_frame(reader, 0, &frame);

        if (rc == ASTRA_STATUS_SUCCESS)
        {
            astra_infraredframe_t irFrame;
            astra_frame_get_infraredframe(frame, &irFrame);

            astra_frame_index_t newFrameIndex;
            astra_infraredframe_get_frameindex(irFrame, &newFrameIndex);

            if (lastFrameIndex == newFrameIndex)
            {
                printf("duplicate frame index: %d\n", lastFrameIndex);
            }
            lastFrameIndex = newFrameIndex;

            print_ir(irFrame);

            astra_reader_close_frame(&frame);
        }

    } while (shouldContinue);

    astra_reader_destroy(&reader);
    astra_streamset_close(&sensor);

    astra_terminate();
}
