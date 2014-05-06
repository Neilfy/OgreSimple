#ifndef NMATH_H
#define NMATH_H

#include <math.h>

namespace OgreSimple
{
    class Matrix4;

    static const float EPSILON = 0.0000001f;
    static const float HALF_PI = 1.5707963f;
    static const float MATH_PI = HALF_PI * 2;

    class Vector2
    {
    public:
        Vector2(void)
            : x(0.0f)
            , y(0.0f)
        {}

        Vector2(float fX, float fY)
            : x(fX)
            , y(fY)
        {}

        ~Vector2(void){};

    public:
        Vector2 operator+(const Vector2& rhs) const;
        Vector2 operator-(const Vector2& rhs) const;
        Vector2 operator*(float s) const;

        Vector2& operator+=(const Vector2& rhs);

        float Dot(const Vector2& rhs) const;

        void Normalize(void);
        Vector2 Normalization(void) const;

        float SquaredLength(void) const
        {
            return x * x + y * y;
        }

        float Length(void) const
        {
            return sqrt(x * x + y * y);
        }

        float SquaredDistance(const Vector2& rhs) const
        {
            return (x - rhs.x) * (x - rhs.x)
                + (y - rhs.y) * (y - rhs.y);
        }

    public:
        float x;
        float y;
    };

    class Vector3
    {
    public:
        Vector3(void)
            : x(0.0f)
            , y(0.0f)
            , z(1.0f)
        {}

        Vector3(float fX, float fY, float fZ)
            : x(fX)
            , y(fY)
            , z(fZ)
        {}

        ~Vector3(void){};

    public:
        bool operator==(const Vector3& rhs) const;
        bool operator!=(const Vector3& rhs) const;
        Vector3 operator+(const Vector3& rhs) const;
        Vector3 operator-(const Vector3& rhs) const;
        Vector3 operator*(float s) const;

        Vector3& operator+=(const Vector3& rhs);

        Vector3 Cross(const Vector3& rhs) const;
        float Dot(const Vector3& rhs) const;

        void Normalize(void);
        Vector3 Normalization(void) const;

        float SquaredLength(void) const
        {
            return x * x + y * y + z * z;
        }

        float Length(void) const
        {
            return sqrt(x * x + y * y + z * z);
        }

        float SquaredDistance(const Vector3& rhs) const
        {
            return (x - rhs.x) * (x - rhs.x)
                + (y - rhs.y) * (y - rhs.y)
                + (z - rhs.z) * (z - rhs.z);
        }
    friend Vector3 operator-(const Vector3& rhs)
    {
        return Vector3(- rhs.x,
                    - rhs.y,
                    - rhs.z
                    );
    }
    public:
        float x;
        float y;
        float z;
    };

    class Vector4
    {
    public:
        Vector4(void)
            : x(0.0f)
            , y(0.0f)
            , z(1.0f)
            , w(1.0f)
        {}

        Vector4(float fX, float fY, float fZ, float fW)
            : x(fX)
            , y(fY)
            , z(fZ)
            , w(fW)
        {}

        ~Vector4(void){};

    public:

    public:
        float x;
        float y;
        float z;
        float w;
    };


    class Matrix4
    {
    public:
        static const Matrix4 Zero;
        static const Matrix4 Identity;

    public:
        Matrix4(void);
        Matrix4(
            float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44
            );

        Matrix4(const Matrix4& rhs);

        ~Matrix4(void){};

    public:
        // operators
        Matrix4& operator=(const Matrix4& rhs);
        Matrix4& operator*=(const Matrix4& rhs);
        Matrix4 operator*(const Matrix4& rhs) const;
        Vector3 operator*(const Vector3& v) const;
        Vector4 operator*(const Vector4& v) const;

    public:
        // gets
        const float* GetRawPointer(void) const
        {
            return &(m[0][0]);
        }

        Vector3 GetTranslation(void) const;
        Vector3 GetScaling(void) const;
        Matrix4 GetTranspose(void) const;
        Matrix4 GetInverse(void) const;

        // operations
        void Transpose(void);
        void Inverse(void);

    public:
        // static matrix makers
        static Matrix4 Translation(const Vector3& t);
        static Matrix4 Translation(float x, float y, float z);
        static Matrix4 Scaling(const Vector3& s);
        static Matrix4 Scaling(float x, float y, float z);
        static Matrix4 RotationX(float radian);
        static Matrix4 RotationY(float radian);
        static Matrix4 RotationZ(float radian);
        static Matrix4 Rotation(const Vector3& axis, float radian);
        static Matrix4 Rotation(float x, float y, float z, float radian);
        static Matrix4 PerspectiveRH(float fovy, float aspect, float near, float far);
        static Matrix4 FrustumRH(float left, float right, float bottom, float top, float near, float far);
        static Matrix4 OrthoRH(float left, float right, float bottom, float top, float near, float far);
        static Matrix4 LookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up);

    public:
        union
        {
            struct {
                float        _11, _12, _13, _14;
                float        _21, _22, _23, _24;
                float        _31, _32, _33, _34;
                float        _41, _42, _43, _44;
            };
            float m[4][4];
        };
    };

    float CalAngleVecToFloat(Vector3        vecDirVec);
}

#endif // CXX_MAP_MATH_H
