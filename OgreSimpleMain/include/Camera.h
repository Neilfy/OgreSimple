#ifndef CAMERA_H
#define CAMERA_H

#include "Viewport.h"
#include "Frustum.h"

namespace OgreSimple
{
    class Camera
    {
        public:
            Camera(void);
            virtual ~Camera(void){};

        public:
        //virtual void Update(const sTileCoord& mapCenter, int iMapHeight, unsigned int carDir, bool mapCenterChanged);
        //virtual void UpDateFrustum(const Matrix4& cMat);

    public:
        const Vector3& GetPosition(void) const
        {
            return mPosition;
        }

        const Matrix4& GetProjectionMatrix(void);
        const Matrix4& GetViewMatrix(void);

        const Vector3& GetDirection(void) const
        {
            return mAt;
        }
        const Vector3& GetUp(void) const
        {
            return mUp;
        }

        float GetFovy(void) const
        {
            return mFovy;
        }
        void GetClips(float& fNear, float& fFar) const
        {
            fNear = mNear;
            fFar = mFar;
        }

        const Frustum& GetFrustum(void) const
        {
            return mFrustum;
        }

        bool IsViewportResized(void) const
        {
            return mViewportResized;
        }

        void SetPosition(const Vector3& pos);
        void SetLookAt(const Vector3& at);
        void SetUp(const Vector3& up);

        void SetFovy(float fovy);
        void SetClips(float fNear, float fFar);

        void SetViewport(const Viewport& vp);

        void ClearViewportResizedFlag(void)
        {
            mViewportResized = false;
        }

    protected:
        Vector3        mPosition;
        Vector3        mAt;
        Vector3        mUp;

        float        mNear;
        float        mFar;
        float        mFovy;

        Frustum        mFrustum;

        Viewport    mViewport;
        bool        mViewportResized;

        bool        mMatProjDirty;
        Matrix4        mMatPrj;
        bool        mMatViewDirty;
        Matrix4        mMatView;
        Matrix4     mMatrix;
    };
}

#endif // CXX_MAP_CAMERA_H
