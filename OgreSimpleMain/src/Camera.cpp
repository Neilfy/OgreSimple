#include "Camera.h"

namespace OgreSimple
{
    Camera::Camera(void)
        : mPosition(0, 1, 0)
        , mAt(0, -1, 0)
        , mUp(1, 0, 0)
        , mNear(0.1f)
        , mFar(100)
        , mFovy(ME_PI * 0.5f)
        , mViewport(0, 0, 1, 1)
        , mFrustum()
        , mViewportResized(false)
        , mMatProjDirty(true)
        , mMatViewDirty(true)
    {
        mFrustum.Set(mNear, mFar, 1.f, 1.f);
    };


    const Matrix4& Camera::GetProjectionMatrix(void)
    {
        if (mMatProjDirty)
        {
        float aspect = 1.0f;
        if (mViewport.GetHeight() != 0)
        {
            aspect = static_cast<float>(mViewport.GetWidth()) / mViewport.GetHeight();
        }
        mMatPrj = Matrix4::PerspectiveRH(mFovy, aspect, mNear, mFar);
        }

        return mMatPrj;
    }

    const Matrix4& Camera::GetViewMatrix(void)
    {
        if (mMatViewDirty)
        {
        mMatView = Matrix4::LookAtRH(mPosition, mAt, mUp);
        }

        return mMatView;
    }

    void Camera::SetPosition(const Vector3& pos)
    {
        if (mPosition != pos)
        {
            mPosition = pos;
            mMatrix = Matrix4::Translation(mPosition);

            // >>> to-do, aabb should moved to frustum
            //mWorldAabb.Translate(mPosition);
            mMatViewDirty = true;
        }
    }

    void Camera::SetLookAt(const Vector3& at)
    {
        if (mAt != at)
        {
            mAt = at;
            mMatViewDirty = true;
        }
    }

    void Camera::SetUp(const Vector3& up)
    {
        if (mUp != up)
        {
            mUp = up;
            mMatViewDirty = true;
        }
    }

    void Camera::SetFovy(float fovy)
    {
        if (mFovy != fovy)
        {
            mFovy = fovy;
            mMatProjDirty = true;
        }
    }
    void Camera::SetClips(float fNear, float fFar)
    {
        if ((mNear != fNear) || (mFar != fFar))
        {
            mNear = fNear;
            mFar = fFar;
            mMatProjDirty = true;
        }
    }

    void Camera::SetViewport(const Viewport& vp)
    {
        mViewport = vp;
        mViewportResized = true;

        float h = mNear * tan(mFovy * 0.5f);
        float w = h * vp.GetWidth() / vp.GetHeight();
        mFrustum.Set(mNear, mFar, w, h);

        mMatProjDirty = true;
    }
}
