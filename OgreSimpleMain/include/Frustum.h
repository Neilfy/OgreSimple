#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "NMath.h"

namespace OgreSimple
{
    //class AABB;
    class Camera;

    class Frustum
    {
        friend class Camera;

    public:
        Frustum(void);
        ~Frustum(void);

    public:
        void Set(float n, float f, float w, float h)
        {
             mNear = n;
             mFar = f;
             mWidth = w;
             mHeight = h;

            float widthFar = mFar * mWidth / mNear;
            float heightFar = mFar * mHeight / mNear;

            // near
            mVertices[0] = Vector3(-mWidth * 0.5f, -mHeight * 0.5f, -mNear);    // left bottom
            mVertices[1] = Vector3(mWidth * 0.5f, -mHeight * 0.5f, -mNear);        // right bottom
            mVertices[2] = Vector3(mWidth * 0.5f, mHeight * 0.5f, -mNear);        // right top
            mVertices[3] = Vector3(-mWidth * 0.5f, mHeight * 0.5f, -mNear);        // left top

            // far
            mVertices[4] = Vector3(-widthFar * 0.5f, -heightFar * 0.5f, -mFar);    // left bottom
            mVertices[5] = Vector3(widthFar * 0.5f, -heightFar * 0.5f, -mFar);        // right bottom
            mVertices[6] = Vector3(widthFar * 0.5f, heightFar * 0.5f, -mFar);        // right top
            mVertices[7] = Vector3(-widthFar * 0.5f, heightFar * 0.5f, -mFar);        // left top
        }

        void Update(const Matrix4& cMat);
        //ContainmentRelationshipType Contains(const AABB& aabb) const;

    protected:
        static const int VERTICES_COUNT = 8;
        static const int PLANES_COUNT = 6;

    protected:
        float    mNear;
        float    mFar;
        float    mWidth;
        float    mHeight;

        Vector3    mVertices[VERTICES_COUNT];
        //Plane    mPlanes[PLANES_COUNT];    // near, far, top, bottom, left, right

        //AABB    mAABB;
    };
}

#endif 
