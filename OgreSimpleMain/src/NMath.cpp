#include "NMath.h"

#include <string.h>
#include <math.h>
#include <algorithm>

//#include "MapTypes.h"

using std::swap;

namespace OgreSimple
{
    Vector2 Vector2::operator+(const Vector2& rhs) const
    {
        return Vector2(x + rhs.x, y + rhs.y);
    }

    Vector2 Vector2::operator-(const Vector2& rhs) const
    {
        return Vector2(x - rhs.x,y - rhs.y);
    }

    Vector2 Vector2::operator*(float s) const
    {
        return Vector2(x * s, y * s);
    }

    Vector2& Vector2::operator+=(const Vector2& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    float Vector2::Dot(const Vector2& rhs) const
    {
        return x * rhs.x + y * rhs.y;
    }

    void Vector2::Normalize(void)
    {
        float length = sqrt(x * x + y * y);

        // do nothing for a zero vector
        if (length > EPSILON)
        {
            length = 1.0f / length;
            x *= length;
            y *= length;
        }
    }

    Vector2 Vector2::Normalization(void) const
    {
        float length = sqrt(x * x + y * y);

        // do nothing for a zero vector
        if (length > EPSILON)
        {
            length = 1.0f / length;

            return Vector2(x * length, y * length);
        }
        else
        {
            return *this;
        }
    }

    bool Vector3::operator==(const Vector3& rhs) const
    {
        return !(*this != rhs);
    }
    bool Vector3::operator!=(const Vector3& rhs) const
    {
        return ((x != rhs.x) || (y != rhs.y) || (z != rhs.z));
    }

    Vector3 Vector3::operator+(const Vector3& rhs) const
    {
        return Vector3(x + rhs.x,
                    y + rhs.y,
                    z + rhs.z
                    );
    }

    Vector3 Vector3::operator-(const Vector3& rhs) const
    {
        return Vector3(x - rhs.x,
                    y - rhs.y,
                    z - rhs.z
                    );
    }

    Vector3 Vector3::operator*(float s) const
    {
        return Vector3(x * s, y * s, z * s);
    }

    Vector3& Vector3::operator+=(const Vector3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }

    Vector3 Vector3::Cross(const Vector3& rhs) const
    {
        return Vector3(
                y * rhs.z - z * rhs.y,
                z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x
                );
    }

    float Vector3::Dot(const Vector3& rhs) const
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    void Vector3::Normalize(void)
    {
        float length = sqrt(x * x + y * y + z * z);

        // do nothing for a zero vector
        if (length > EPSILON)
        {
            length = 1.0f / length;
            x *= length;
            y *= length;
            z *= length;
        }
    }

    Vector3 Vector3::Normalization(void) const
    {
        float length = sqrt(x * x + y * y + z * z);

        // do nothing for a zero vector
        if (length > EPSILON)
        {
            length = 1.0f / length;

            return Vector3(x * length, y * length, z * length);
        }
        else
        {
            return *this;
        }
    }

    const Matrix4 Matrix4::Zero(
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    );

    const Matrix4 Matrix4::Identity(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );

    Matrix4::Matrix4(void)
    {
        _11 = 1.0f;
        _12 = 0.0f;
        _13 = 0.0f;
        _14 = 0.0f;

        _21 = 0.0f;
        _22 = 1.0f;
        _23 = 0.0f;
        _24 = 0.0f;

        _31 = 0.0f;
        _32 = 0.0f;
        _33 = 1.0f;
        _34 = 0.0f;

        _41 = 0.0f;
        _42 = 0.0f;
        _43 = 0.0f;
        _44 = 1.0f;
    }

    Matrix4::Matrix4(
        float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44
        )
    {
        _11 = m11;
        _12 = m12;
        _13 = m13;
        _14 = m14;

        _21 = m21;
        _22 = m22;
        _23 = m23;
        _24 = m24;

        _31 = m31;
        _32 = m32;
        _33 = m33;
        _34 = m34;

        _41 = m41;
        _42 = m42;
        _43 = m43;
        _44 = m44;
    }

    Matrix4::Matrix4(const Matrix4& rhs)
    {
        memcpy(m, rhs.m, sizeof(rhs.m));
    }

    // operators
    Matrix4& Matrix4::operator=(const Matrix4& rhs)
    {
        if (&rhs != this)
        {
            memcpy(m, rhs.m, sizeof(rhs.m));
        }

        return *this;
    }

    Matrix4& Matrix4::operator*=(const Matrix4& rhs)
    {
        *this = *this * rhs;

        return *this;
    }

    Matrix4 Matrix4::operator*(const Matrix4& rhs) const
    {
        Matrix4 mat;
        mat.m[0][0] = m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0] + m[0][2] * rhs.m[2][0] + m[0][3] * rhs.m[3][0];
        mat.m[0][1] = m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1] + m[0][2] * rhs.m[2][1] + m[0][3] * rhs.m[3][1];
        mat.m[0][2] = m[0][0] * rhs.m[0][2] + m[0][1] * rhs.m[1][2] + m[0][2] * rhs.m[2][2] + m[0][3] * rhs.m[3][2];
        mat.m[0][3] = m[0][0] * rhs.m[0][3] + m[0][1] * rhs.m[1][3] + m[0][2] * rhs.m[2][3] + m[0][3] * rhs.m[3][3];

        mat.m[1][0] = m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0] + m[1][2] * rhs.m[2][0] + m[1][3] * rhs.m[3][0];
        mat.m[1][1] = m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1] + m[1][2] * rhs.m[2][1] + m[1][3] * rhs.m[3][1];
        mat.m[1][2] = m[1][0] * rhs.m[0][2] + m[1][1] * rhs.m[1][2] + m[1][2] * rhs.m[2][2] + m[1][3] * rhs.m[3][2];
        mat.m[1][3] = m[1][0] * rhs.m[0][3] + m[1][1] * rhs.m[1][3] + m[1][2] * rhs.m[2][3] + m[1][3] * rhs.m[3][3];

        mat.m[2][0] = m[2][0] * rhs.m[0][0] + m[2][1] * rhs.m[1][0] + m[2][2] * rhs.m[2][0] + m[2][3] * rhs.m[3][0];
        mat.m[2][1] = m[2][0] * rhs.m[0][1] + m[2][1] * rhs.m[1][1] + m[2][2] * rhs.m[2][1] + m[2][3] * rhs.m[3][1];
        mat.m[2][2] = m[2][0] * rhs.m[0][2] + m[2][1] * rhs.m[1][2] + m[2][2] * rhs.m[2][2] + m[2][3] * rhs.m[3][2];
        mat.m[2][3] = m[2][0] * rhs.m[0][3] + m[2][1] * rhs.m[1][3] + m[2][2] * rhs.m[2][3] + m[2][3] * rhs.m[3][3];

        mat.m[3][0] = m[3][0] * rhs.m[0][0] + m[3][1] * rhs.m[1][0] + m[3][2] * rhs.m[2][0] + m[3][3] * rhs.m[3][0];
        mat.m[3][1] = m[3][0] * rhs.m[0][1] + m[3][1] * rhs.m[1][1] + m[3][2] * rhs.m[2][1] + m[3][3] * rhs.m[3][1];
        mat.m[3][2] = m[3][0] * rhs.m[0][2] + m[3][1] * rhs.m[1][2] + m[3][2] * rhs.m[2][2] + m[3][3] * rhs.m[3][2];
        mat.m[3][3] = m[3][0] * rhs.m[0][3] + m[3][1] * rhs.m[1][3] + m[3][2] * rhs.m[2][3] + m[3][3] * rhs.m[3][3];

        return mat;
    }

    Vector3 Matrix4::operator*(const Vector3& v) const
    {
         float w = v.x * _41 + v.y * _42 + v.z * _43 + _44;
         if (0 == w)
         {
             return v;
         }
         else
         {
             w = 1.0f / w;

             return Vector3(
                     (v.x * _11 + v.y * _12 + v.z * _13 + _14) * w,
                     (v.x * _21 + v.y * _22 + v.z * _23 + _24) * w,
                     (v.x * _31 + v.y * _32 + v.z * _33 + _34) * w
                     );
         }
    }

    Vector4 Matrix4::operator*(const Vector4& v) const
    {
        return Vector4(
            v.x * _11 + v.y * _12 + v.z * _13 + v.w * _14,
            v.x * _21 + v.y * _22 + v.z * _23 + v.w * _24,
            v.x * _31 + v.y * _32 + v.z * _33 + v.w * _34,
            v.x * _41 + v.y * _42 + v.z * _43 + v.w * _44
            );
    }

    // gets
    Vector3 Matrix4::GetTranslation(void) const
    {
        return Vector3(_14, _24, _34);
    }

    Vector3 Matrix4::GetScaling(void) const
    {
        return Vector3(_11, _22, _33);
    }

    Matrix4 Matrix4::GetTranspose(void) const
    {
        return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
                       m[0][1], m[1][1], m[2][1], m[3][1],
                       m[0][2], m[1][2], m[2][2], m[3][2],
                       m[0][3], m[1][3], m[2][3], m[3][3]);
    }

    Matrix4 Matrix4::GetInverse(void) const
    {
        float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
        float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
        float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
        float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

        float v0 = m20 * m31 - m21 * m30;
        float v1 = m20 * m32 - m22 * m30;
        float v2 = m20 * m33 - m23 * m30;
        float v3 = m21 * m32 - m22 * m31;
        float v4 = m21 * m33 - m23 * m31;
        float v5 = m22 * m33 - m23 * m32;

        float t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
        float t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
        float t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
        float t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

        float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

        float d00 = t00 * invDet;
        float d10 = t10 * invDet;
        float d20 = t20 * invDet;
        float d30 = t30 * invDet;

        float d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        float d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        float d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        float d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m10 * m31 - m11 * m30;
        v1 = m10 * m32 - m12 * m30;
        v2 = m10 * m33 - m13 * m30;
        v3 = m11 * m32 - m12 * m31;
        v4 = m11 * m33 - m13 * m31;
        v5 = m12 * m33 - m13 * m32;

        float d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        float d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        float d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        float d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m21 * m10 - m20 * m11;
        v1 = m22 * m10 - m20 * m12;
        v2 = m23 * m10 - m20 * m13;
        v3 = m22 * m11 - m21 * m12;
        v4 = m23 * m11 - m21 * m13;
        v5 = m23 * m12 - m22 * m13;

        float d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        float d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        float d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        float d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        return Matrix4(
            d00, d01, d02, d03,
            d10, d11, d12, d13,
            d20, d21, d22, d23,
            d30, d31, d32, d33);
    }

    // operations
    void Matrix4::Transpose(void)
    {
        swap(_12, _21);
        swap(_13, _31);
        swap(_14, _41);

        swap(_23, _32);
        swap(_24, _42);

        swap(_34, _43);
    }
    void Matrix4::Inverse(void)
    {
        *this = GetInverse();
    }

    // static matrix makers
    Matrix4 Matrix4::Translation(const Vector3& t)
    {
        return Matrix4(1, 0, 0, t.x,
                        0, 1, 0, t.y,
                        0, 0, 1, t.z,
                        0, 0, 0, 1);
    }
    Matrix4 Matrix4::Translation(float x, float y, float z)
    {
        return Matrix4(1, 0, 0, x,
                        0, 1, 0, y,
                        0, 0, 1, z,
                        0, 0, 0, 1);
    }
    Matrix4 Matrix4::Scaling(const Vector3& s)
    {
        return Matrix4(s.x, 0, 0, 0,
                        0, s.y, 0, 0,
                        0, 0, s.z, 0,
                        0, 0, 0, 1);
    }
    Matrix4 Matrix4::Scaling(float x, float y, float z)
    {
        return Matrix4(x, 0, 0, 0,
                        0, y, 0, 0,
                        0, 0, z, 0,
                        0, 0, 0, 1);
    }

    Matrix4 Matrix4::RotationX(float radian)
    {
        return Matrix4(1, 0, 0, 0,
                        0, cos(radian), -sin(radian), 0,
                        0, sin(radian), cos(radian), 0,
                        0, 0, 0, 1);
    }

    Matrix4 Matrix4::RotationY(float radian)
    {
        return Matrix4(cos(radian), 0, sin(radian), 0,
                        0, 1, 0, 0,
                        -sin(radian), 0, cos(radian), 0,
                        0, 0, 0, 1);
    }


    Matrix4 Matrix4::RotationZ(float radian)
    {
        return Matrix4(cos(radian), -sin(radian), 0, 0,
                        sin(radian), cos(radian), 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
    }

     Matrix4 Matrix4::Rotation(const Vector3& axis, float radian)
     {
         return Rotation(axis.x, axis.y, axis.z, radian);
     }
     Matrix4 Matrix4::Rotation(float x, float y, float z, float radian)
     {
         Vector3 v(x, y, z);
         v.Normalize();

         float sine = sin(radian);
         float cosine = cos(radian);

         float one_minus_cosine = 1 - cosine;

         return Matrix4(
             cosine + one_minus_cosine * v.x * v.x,
             one_minus_cosine * v.x * v.y - v.z * sine,
             one_minus_cosine * v.x * v.z + v.y * sine,
             0,

             one_minus_cosine * v.x * v.y + v.z * sine,
             cosine + one_minus_cosine * v.y * v.y,
             one_minus_cosine * v.y * v.z - v.x * sine,
             0,

             one_minus_cosine * v.x * v.z - v.y * sine,
             one_minus_cosine * v.y * v.z + v.x * sine,
             cosine + one_minus_cosine * v.z * v.z,
             0,

             0, 0, 0, 1);
     }

    Matrix4 Matrix4::PerspectiveRH(float fovy, float aspect, float near, float far)
    {
#if 1
        // Chris, temp
        float xmin, xmax, ymin, ymax;

        ymax = near * tan(fovy * 0.5f);
        ymin = -ymax;
        xmin = ymin * aspect;
        xmax = -xmin;

        return FrustumRH(xmin, xmax, ymin, ymax, near, far);
#else
        float sinHalfFovy = sin(fovy * 0.5f);
        if (sinHalfFovy == 0.0f)
        {
            sinHalfFovy = EPSILON;
        }
        float rat = cos(fovy * 0.5f) / sinHalfFovy;

        float h =  1.0f  * rat;
        if (0.0f == aspect)
        {
            aspect = 1.0f;
        }
        float w = h / aspect;
        if(far == near)
        {
            far = near + EPSILON;
        }
        float Q = far / (far - near);

        Matrix4 mat = Zero;

        mat._11 = w;
        mat._22 = h;
        mat._33 = -Q;
        mat._34 = -1.0f;
        mat._43 = -Q * near;
        mat._44 = 0;

        return mat;
#endif
    }

    Matrix4 Matrix4::FrustumRH(float left, float right, float bottom, float top, float near, float far)
    {
        // Chris, temp
        float x, y, a, b, c, d;

        x = (2.0f * near) / (right - left);
        y = (2.0f * near) / (top - bottom);
        a = (right + left) / (right - left);
        b = (top + bottom) / (top - bottom);
        c = -(far + near) / ( far - near);
        d = -(2.0f * far * near) / (far - near);

        Matrix4 mat(
                    x, 0, a, 0,
                    0, y, b, 0,
                    0, 0, c, d,
                    0, 0, -1, 0
                    );
        return mat;
    }

    Matrix4 Matrix4::OrthoRH(float left, float right, float bottom, float top, float near, float far)
    {
        float x = 2.0f / (right - left);
        float y = 2.0f / (top - bottom);
        float a = - (right + left) / (right - left);
        float b = - (top + bottom) / (top - bottom);
        float c = - 2.0f / (far - near);
        float d = - (far + near) / (far - near);

        Matrix4 mat(
                    x, 0, 0, a,
                    0, y, 0, b,
                    0, 0, c, d,
                    0, 0, 0, 1
                    );
        return mat;
    }

    Matrix4 Matrix4::LookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up)
    {
        Vector3 xAxis;
        Vector3 yAxis;
        Vector3 zAxis(eye - at);

        zAxis.Normalize();

        xAxis = up.Cross(zAxis);

        xAxis.Normalize();
        yAxis = zAxis.Cross(xAxis);

        Matrix4 mat(
            xAxis.x, xAxis.y, xAxis.z, -eye.Dot(xAxis),
            yAxis.x, yAxis.y, yAxis.z, -eye.Dot(yAxis),
            zAxis.x, zAxis.y, zAxis.z, -eye.Dot(zAxis),
            0, 0, 0, 1);

        return mat;
    }

    float CalAngleVecToFloat(Vector3        vecDirVec)
    {
        float        fDirFloat = 0.5f * MATH_PI;
        if(vecDirVec.x != 0){
            float fTanDir = vecDirVec.z/vecDirVec.x;
            // -0.5 -> 0.5
            fDirFloat = atan(fTanDir);

            // 0.5 -> 1.5?
            if(vecDirVec.x < 0){
                fDirFloat = fDirFloat + MATH_PI;
            }

            // -0.5?
            if(fDirFloat<0){
                fDirFloat = fDirFloat + 2*MATH_PI;
            }
        }
        else{
            if(vecDirVec.z < 0){
                fDirFloat = 1.5f * MATH_PI;
            }
            else{
                fDirFloat = 0.5f * MATH_PI;
            }
        }
        return fDirFloat;
    }
}
