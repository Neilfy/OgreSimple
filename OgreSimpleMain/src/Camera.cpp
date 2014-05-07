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

    Vector3& Camera::_axisX()
	{
		return *(Vector3*)(&mMatrixBase._11);
	}

	Vector3& Camera::_axisY()
	{
		return *(Vector3*)(&mMatrixBase._21);
	}

	Vector3& Camera::_axisZ()
	{
		return *(Vector3*)(&mMatrixBase._31);
	}

	Vector3& Camera::_position()
	{
		return *(Vector3*)(&mMatrixBase._41);
	}


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
            float pr = - _position().Dot(_axisX());
            float pu = - _position().Dot(_axisY());
            float pd = - _position().Dot(- _axisZ());// opengl z·´Ïò
            mMatrixBase._14 = pr;
            mMatrixBase._24 = pu;
            mMatrixBase._34 = pd;
            mMatrixBase._44 = 1.0f;
            mMatView = mMatrixBase;
        }

        return mMatView;
    }

    void Camera::SetPosition(const Vector3& pos)
    {
		_position() = pos;
		mMatViewDirty = true;
    }

    void Camera::SetLookAt(const Vector3& atPos)
    {
		_axisZ() = atPos - _position();
		_axisZ().Normalize();

		_axisX() = _axisZ().Cross(Vector3(0, 1, 0));
		_axisX().Normalize();

		_axisY() = _axisX().Cross(_axisZ());
		mMatViewDirty = true;
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

    void Camera::Walk(int units)
    {
        _position() += _axisZ() * units;

		mMatViewDirty = true;
    }

    void Camera::Strafe(int units)
    {
	 _position() += _axisX() * units;
	 mMatViewDirty = true;
    }

    void Camera::Yaw(float angle)
    {
        Matrix4 rota = Matrix4::Rotation(Vector3(0, 1, 0), angle);
	mMatrixBase = mMatrixBase * rota;
	mMatViewDirty = true;
    }
    void Camera::Pitch( float angle )
    {
        Matrix4 rota = Matrix4::Rotation(_axisX(), angle);
        mMatrixBase = mMatrixBase * rota;
        mMatViewDirty = true;
    }
    void Camera::Fly( int units )
    {
	_position() += Vector3(0, 1, 0) * units;
        mMatViewDirty = true;
    }
}
