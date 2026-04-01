//
// Created by LEI XU on 5/13/19.
//
#pragma once
#ifndef RAYTRACING_VECTOR_H
#define RAYTRACING_VECTOR_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <immintrin.h>

class Vector3f {
public:
    float x, y, z;

    Vector3f() : x(0), y(0), z(0) {
    }

    Vector3f(float xx) : x(xx), y(xx), z(xx) {
    }

    Vector3f(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {
    }

    Vector3f operator *(const float &r) const {
        __m128 v = _mm_set_ps(z, y, x, 0);
        __m128 vr = _mm_mul_ps(v, _mm_set1_ps(r));

        float xr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        float yr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));
        float zr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 3, 3, 3)));

        return Vector3f(xr, yr, zr);
    }

    Vector3f operator /(const float &r) const {
        __m128 v = _mm_set_ps(z, y, x, 0);
        __m128 vr = _mm_div_ps(v, _mm_set1_ps(r));

        float xr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        float yr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));
        float zr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 3, 3, 3)));

        return Vector3f(xr, yr, zr);
    }

    float norm() {
        __m128 v1 = _mm_set_ps(z, y, x, 0);

        __m128 dp = _mm_dp_ps(v1, v1, 0xFF);
        float sun = _mm_cvtss_f32(dp);
        return sqrtf(sun);
    }

    Vector3f normalized() {
        float n = norm();
        return Vector3f(x / n, y / n, z / n);
    }

    Vector3f operator *(const Vector3f &r) const {
        __m128 v1 = _mm_set_ps(z, y, x, 0);
        __m128 vr = _mm_set_ps(r.z, r.y, r.x, 0);
        vr = _mm_mul_ps(v1, vr);

        float xr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        float yr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));
        float zr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 3, 3, 3)));

        return Vector3f(xr, yr, zr);
    }

    Vector3f operator -(const Vector3f &r) const {
        __m128 v1 = _mm_set_ps(z, y, x, 0);
        __m128 vr = _mm_set_ps(r.z, r.y, r.x, 0);
        vr = _mm_sub_ps(v1, vr);

        float xr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        float yr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));
        float zr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 3, 3, 3)));

        return Vector3f(xr, yr, zr);
    }

    Vector3f operator +(const Vector3f &r) const {
        __m128 v1 = _mm_set_ps(z, y, x, 0);
        __m128 vr = _mm_set_ps(r.z, r.y, r.x, 0);
        vr = _mm_add_ps(v1, vr);

        float xr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        float yr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));
        float zr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 3, 3, 3)));

        return Vector3f(xr, yr, zr);
    }

    Vector3f operator -() const {
        __m128 v = _mm_set_ps(z, y, x, 0);
        __m128 vr = _mm_mul_ps(v, _mm_set1_ps(-1.0f));

        float xr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        float yr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));
        float zr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 3, 3, 3)));

        return Vector3f(xr, yr, zr);
    }

    Vector3f &operator +=(const Vector3f &v) {
        __m128 v1 = _mm_set_ps(z, y, x, 0);
        __m128 vr = _mm_set_ps(v.z, v.y, v.x, 0);
        vr = _mm_add_ps(v1, vr);

        x = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        y = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));
        z = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 3, 3, 3)));

        return *this;
    }

    friend Vector3f operator *(const float &r, const Vector3f &v) {
        __m128 v1 = _mm_set_ps(v.z, v.y, v.x, 0);
        __m128 vr = _mm_mul_ps(v1, _mm_set1_ps(r));

        float xr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        float yr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));
        float zr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 3, 3, 3)));

        return Vector3f(xr, yr, zr);
    }

    friend std::ostream &operator <<(std::ostream &os, const Vector3f &v) {
        return os << v.x << ", " << v.y << ", " << v.z;
    }

    double operator[](int index) const;

    double &operator[](int index);


    static Vector3f Min(const Vector3f &p1, const Vector3f &p2) {
        return Vector3f(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                        std::min(p1.z, p2.z));
    }

    static Vector3f Max(const Vector3f &p1, const Vector3f &p2) {
        return Vector3f(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                        std::max(p1.z, p2.z));
    }
};

inline double Vector3f::operator[](int index) const {
    return (&x)[index];
}


class Vector2f {
public:
    Vector2f() : x(0), y(0) {
    }

    Vector2f(float xx) : x(xx), y(xx) {
    }

    Vector2f(float xx, float yy) : x(xx), y(yy) {
    }

    Vector2f operator *(const float &r) const {
        __m128 v1 = _mm_set_ps(0, y, x, 0);
        __m128 vr = _mm_set_ps(0, r, r, 0);
        vr = _mm_mul_ps(v1, vr);

        float xr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        float yr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));

        return Vector2f(xr, yr);
    }

    Vector2f operator +(const Vector2f &v) const {
        __m128 v1 = _mm_set_ps(0, y, x, 0);
        __m128 vr = _mm_set_ps(0, v.y, v.x, 0);
        vr = _mm_add_ps(v1, vr);

        float xr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(1, 1, 1, 1)));
        float yr = _mm_cvtss_f32(_mm_shuffle_ps(vr, vr, _MM_SHUFFLE(2, 2, 2, 2)));

        return Vector2f(xr, yr);
    }

    float x, y;
};

inline Vector3f lerp(const Vector3f &a, const Vector3f &b, const float &t) {
    return a * (1 - t) + b * t;
}

inline Vector3f normalize(Vector3f v) {
    return v.normalized();
}

inline float dotProduct(const Vector3f &a, const Vector3f &b) {
    __m128 v1 = _mm_set_ps(a.z, a.y, a.x, 0);
    __m128 v2 = _mm_set_ps(b.z, b.y, b.x, 0);
    v2 = _mm_dp_ps(v1, v2, 0xFF);
    return _mm_cvtss_f32(v2);
}

inline Vector3f crossProduct(const Vector3f &a, const Vector3f &b) {
    return Vector3f(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}


#endif //RAYTRACING_VECTOR_H
