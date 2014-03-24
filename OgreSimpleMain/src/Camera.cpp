#include "Camera.h"

namespace OgreSimple
{
	Camera::Camera(void)
		: mPosition(0, 1, 0)
		, mDirection(0, -1, 0)
		, mUp(1, 0, 0)
		, mNear(0.1f)
		, mFar(100)
		, mFovy(ME_PI * 0.5f)
		, mFrustum()
		, mViewport(0, 0, 1, 1)
		, mViewportResized(false)
		, mMatProjDirty(true)
		, mMatViewDirty(true)
	{
		float h = mNear * tan(mFovy * 0.5f) * 2.0f;
		float w = h * mViewport.GetWidth() / mViewport.GetHeight();
		mFrustum.Set(mNear, mFar, w, h);
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
		mMatView = Matrix4::LookAtRH(mPosition, mPosition + mDirection, mUp);
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

    void Camera::SetDirection(const Vector3& dir)
    {
        if (mDirection != dir)
        {
            mDirection = dir;
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

	void Camera::SetViewportSize(uint32 left, uint32 top, uint32 width, uint32 height)
	{
	    if ((left == mViewport.GetLeft())
            && (top == mViewport.GetTop())
            && (width == mViewport.GetWidth())
            && (height == mViewport.GetHeight()))
        {
            return;
        }

		mViewport.SetSize(left, top, width, height);
		mViewportResized = true;

		float h = mNear * tan(mFovy * 0.5f);
		float w = h * width / height;
		mFrustum.Set(mNear, mFar, w, h);

		mMatProjDirty = true;
	}
}
