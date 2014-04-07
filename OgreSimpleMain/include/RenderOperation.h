#ifndef RENDEROPERATION_H
#define RENDEROPERATION_H

#include "VertexIndexData.h"
namespace OgreSimple
{
    class RenderOperation
    {
    public:
        RenderOperation():
            mVertexData(NULL),
            mOperationType(OT_TRIANGLE_LIST),
            mUseIndexes(false),
            mIndexData(NULL)
        {

        };
        ~RenderOperation(){};

        enum OperationType {
            OT_POINT_LIST = 1,
            OT_LINE_LIST = 2,
            OT_LINE_STRIP = 3,
            OT_TRIANGLE_LIST = 4,
            OT_TRIANGLE_STRIP = 5,
            OT_TRIANGLE_FAN = 6
        };

        const VertexData *mVertexData;
        OperationType mOperationType;
        bool mUseIndexes;
        const IndexData *mIndexData;

    };
}
#endif // RENDEROPERATION_H
