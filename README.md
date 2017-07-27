This fork of the astra API has a few fixes

* Fixes C++11/14 compiling problems
* Removes the lisp preprocessor step from the build pipeline. Clisp hasn't been updated since 2010 and it was removed from most debian based distros in 2014
    * Compiling clisp is extremely difficult and it doesn't do anything for regular users of the API

To build on Debian

* git clone thisrepo
* git submodule init
* git submodule update
* build libusb from https://github.com/libusb/libusb
    * requires autotools stuff and libtool
    * sh autogen.sh, ./configure, make, sudo make install
* build OpenNI2 from https://github.com/occipital/OpenNI2
    * Requires openjdk-8-jre openjdk-8-jdk freeglut3-dev
    * run make
    * export OPENNI2_REDIST=/home/user/OpenNI2/Bin/x64-release
* libsfml-dev from the repos
* mkdir build && cmake .. && make -j 5

