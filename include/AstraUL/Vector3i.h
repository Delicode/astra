#ifndef VECTOR3I_H
#define VECTOR3I_H

#include <cmath>
#include <AstraUL/skul_ctypes.h>

namespace astra {

    struct Vector3i : public astra_vector3i_t
    {
        Vector3i()
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }

        Vector3i(const astra_vector3i_t& v)
        {
            *this = v;
        }

        Vector3i& operator=(const astra_vector3i_t& rhs)
        {
            ::astra_vector3i_t::x = rhs.x;
            ::astra_vector3i_t::y = rhs.y;
            ::astra_vector3i_t::z = rhs.z;

            return *this;
        }

        Vector3i(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        inline operator ::astra_vector3i_t*() { return this; }
        inline operator const ::astra_vector3i_t*() const { return this; }

        float length() const;
        int length_squared() const;
        int dot(const Vector3i& v) const;

        Vector3i cross(const Vector3i& v) const;

        static Vector3i normalize(Vector3i v);

        static inline Vector3i zero();

        friend bool operator==(const Vector3i& lhs, const Vector3i& rhs);
        friend bool operator!=(const Vector3i& lhs, const Vector3i& rhs);

        bool is_zero() const;

        Vector3i& operator+=(const Vector3i& rhs);
        Vector3i& operator-=(const Vector3i& rhs);
        Vector3i& operator*=(const float& rhs);
        Vector3i& operator/=(const float& rhs);

        friend Vector3i operator+(const Vector3i& lhs, const Vector3i& rhs);
        friend Vector3i operator-(const Vector3i& lhs, const Vector3i& rhs);
        friend Vector3i operator*(const Vector3i& lhs, const float& rhs);
        friend Vector3i operator*(const float& lhs, const Vector3i& rhs);
        friend Vector3i operator/(const Vector3i& lhs, const float& rhs);

        Vector3i operator-();
    };

    inline float Vector3i::length() const
    {
        return std::sqrtf(x * x + y * y + z * z);
    }

    inline int Vector3i::length_squared() const
    {
        return x * x + y * y + z * z;
    }

    inline int Vector3i::dot(const Vector3i& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    inline Vector3i Vector3i::cross(const Vector3i& v) const
    {
        return Vector3i(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }

    inline Vector3i Vector3i::normalize(Vector3i v)
    {
        double length = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
        if (length < 1e-9)
        {
            return Vector3i(0, 0, 0);
        }
        else
        {
            return Vector3i(
                static_cast<std::int32_t>(v.x / length),
                static_cast<std::int32_t>(v.y / length),
                static_cast<std::int32_t>(v.z / length));
        }
    }

    inline bool Vector3i::is_zero() const
    {
        Vector3i zero;
        return *this == zero;
    }

    inline Vector3i& Vector3i::operator+=(const Vector3i& rhs)
    {
        this->x = this->x + rhs.x;
        this->y = this->y + rhs.y;
        this->z = this->z + rhs.z;
        return *this;
    }

    inline Vector3i& Vector3i::operator-=(const Vector3i& rhs)
    {
        this->x = this->x - rhs.x;
        this->y = this->y - rhs.y;
        this->z = this->z - rhs.z;
        return *this;
    }

    inline Vector3i& Vector3i::operator*=(const float& rhs)
    {
        this->x = this->x * rhs;
        this->y = this->y * rhs;
        this->z = this->z * rhs;
        return *this;
    }

    inline Vector3i& Vector3i::operator/=(const float& rhs)
    {
        this->x = static_cast<std::int32_t>(this->x / rhs);
        this->y = static_cast<std::int32_t>(this->y / rhs);
        this->z = static_cast<std::int32_t>(this->z / rhs);
        return *this;
    }

    inline Vector3i Vector3i::operator-()
    {
        return Vector3i(-this->x, -this->y, -this->z);
    }

    inline bool operator==(const Vector3i& lhs, const Vector3i& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }

    inline bool operator!=(const Vector3i& lhs, const Vector3i& rhs)
    {
        return !(lhs == rhs);
    }

    inline Vector3i operator+(const Vector3i& lhs, const Vector3i& rhs)
    {
        return Vector3i(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    inline Vector3i operator-(const Vector3i& lhs, const Vector3i& rhs)
    {
        return Vector3i(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    inline Vector3i operator*(const Vector3i& lhs, const float& rhs)
    {
        return Vector3i(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }

    inline Vector3i operator*(const float& lhs, const Vector3i& rhs)
    {
        return rhs * lhs;
    }

    inline Vector3i operator/(const Vector3i& lhs, const float& rhs)
    {
        return Vector3i(
            static_cast<std::int32_t>(lhs.x / rhs),
            static_cast<std::int32_t>(lhs.y / rhs),
            static_cast<std::int32_t>(lhs.z / rhs));
    }

    inline Vector3i Vector3i::zero()
    {
        Vector3i zero;
        return zero;
    }
}

#endif /* VECTOR3I_H */
