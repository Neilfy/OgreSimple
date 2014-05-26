#include "glew.h"
#include "OgreSimpleTypes.h"
#include "GLRenderSystem.h"
#include "Viewport.h"
#include "RenderOperation.h"
#include "GLHardwareManager.h"
#include "GLTextureManager.h"
#include "Material.h"
#include "GLTexture.h"
namespace OgreSimple
{
    GLRenderSystem::GLRenderSystem(void)
    {
        mGLInitialized = false;
        mViewport = NULL;
        mHardwareManager = NULL;
        mTextureManager = NULL;
    }

    GLRenderSystem::~GLRenderSystem(void)
    {
        if(mHardwareManager)
        {
            delete mHardwareManager;
        }
    }

    void GLRenderSystem::initialise()
    {
        if(GLEW_OK != glewInit())
            return;

        mHardwareManager = new GLHardwareManager();
        mTextureManager = new GLTextureManager();
    }

    void GLRenderSystem::setViewport(const Viewport& vp)
    {
        glViewport(vp.GetLeft(), vp.GetTop(), vp.GetWidth(), vp.GetHeight());

    }

    void GLRenderSystem::setWorldMatrix(const Matrix4& mat)
    {
		mWorldMatrix = mat;

        glMatrixMode(GL_MODELVIEW);
		Matrix4 world_view = (mViewMatrix * mat).GetTranspose();
        glLoadMatrixf(world_view.GetRawPointer());
    }

    void GLRenderSystem::setViewMatrix(const Matrix4& mat)
    {
		mViewMatrix = mat;

        glMatrixMode(GL_MODELVIEW);
        Matrix4 viewmat = mat.GetTranspose();
        glLoadMatrixf(viewmat.GetRawPointer());
    }

    void GLRenderSystem::setProjectionMatrix(const Matrix4& mat)
    {
        glMatrixMode(GL_PROJECTION);
        Matrix4 promat = mat.GetTranspose();
        glLoadMatrixf(promat.GetRawPointer());
    }

	void GLRenderSystem::clearFrameBuffer()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glDisable(GL_CULL_FACE);
		//glCullFace(GL_FRONT_AND_BACK);
	}
    void GLRenderSystem::render(RenderOperation* ro)
    {
        RenderSystem::render(ro);

        const VertexData *vertexData = ro->mVertexData;
        void* pBuffer = NULL;
        bool isUseVBO = vertexData->isUseVBO();
        if(isUseVBO)
        {
            vertexData->BindVBO();
            pBuffer = (char*)NULL;
        }else
        {
            pBuffer = vertexData->getBuffer();
        }
        //uint8 *buffer = vertexData->getBuffer();
        int vertexType = vertexData->getVertexType();
        int stride = vertexData->calVertexTypeSize(vertexType);
        int offset = 0;
        if (FVF_POSITION & vertexType)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, stride, pBuffer + offset);
			offset += 12;
		}
		if (FVF_NORMAL & vertexType)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, stride, pBuffer + offset);
			offset += 12;
		}
		if (FVF_DIFFUSE & vertexType)
		{
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_UNSIGNED_BYTE, stride, pBuffer + offset);
			offset += 4;
		}
		if (FVF_UV & vertexType)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, stride, pBuffer + offset);
			offset += 8;
		}

		GLint primType;

		switch (ro->mOperationType)
		{
		case RenderOperation::OT_POINT_LIST:
			primType = GL_POINTS;
			break;
		case RenderOperation::OT_LINE_LIST:
			primType =  GL_LINES;
			break;
		case RenderOperation::OT_LINE_STRIP:
			primType =  GL_LINE_STRIP;
			break;
		default:
		case RenderOperation::OT_TRIANGLE_LIST:
			primType =  GL_TRIANGLES;
			break;
		case RenderOperation::OT_TRIANGLE_STRIP:
			primType =  GL_TRIANGLE_STRIP;
			break;
		case RenderOperation::OT_TRIANGLE_FAN:
			primType = GL_TRIANGLE_FAN;
			break;
		}

		const IndexData *indexData = ro->mIndexData;
		if (indexData)
		{
		    bool isUseIndexVBO = indexData->isUseVBO();
			if(isUseIndexVBO)//vbo
			{
                indexData->BindVBO();
				pBuffer = (char*)NULL;
			}
			else
			{
				pBuffer = indexData->getBuffer();
			}

			GLenum indexType = (indexData->getIndexType() == IT_16BIT) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;

			glDrawElements(primType, indexData->getIndexesCount(), indexType, pBuffer);

			if(isUseIndexVBO)//vbo
			{
                indexData->UnbindVBO();
			}

		}
		else
		{
			glDrawArrays(primType, 0, vertexData->getVerticesCount());
		}

		if(isUseVBO)
        {
            vertexData->UnbindVBO();
        }

		if (FVF_POSITION & vertexType)
		{
			glDisableClientState(GL_VERTEX_ARRAY);
		}
		if (FVF_NORMAL & vertexType)
		{
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		if (FVF_DIFFUSE & vertexType)
		{
			glDisableClientState(GL_COLOR_ARRAY);
		}
		if (FVF_UV & vertexType)
		{
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
//glFlush();
    }

    void GLRenderSystem::setTextureUnit(TextureUnit* texUnit)
    {
		GLTexture* tex = (GLTexture*)texUnit->GetTexture();
		if (tex)
		{
			glBindTexture(GL_TEXTURE_2D, tex->getGLID());
		}

    }

    void GLRenderSystem::setMaterial(Material* mat)
    {
        Technique* tech = mat->getBestTechnique();
        // set lighting material
		if (tech->IsLightingEnabled())
		{
			// enable light
			enableLighting(true);

			// set Material
			Vector4 vec = tech->GetAmbient().ToVector4();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &vec.x);
			vec = tech->GetDiffuse().ToVector4();
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &vec.x);
			vec = tech->GetSpecular().ToVector4();
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &vec.x);
			vec = tech->GetEmission().ToVector4();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &vec.x);

			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, tech->GetShinness());
		}
		else
		{
			// disable light
			enableLighting(false);

			if (tech->IsColorEnabled())
			{
			    const Color& color = tech->GetObjectColor();
			    glColor4f(color.GetRf(), color.GetGf(), color.GetBf(), color.GetAf());
			}
		}

		// set texture
		TextureUnit* texUint = tech->GetTextureUnit();
		if (texUint)
		{
		    setTextureUnit(texUint);
			enableTexture(true);
		}
		else
		{
			enableTexture(false);
		}
    }

    void GLRenderSystem::enableLighting(bool enable)
	{
		if (enable)
		{
			glEnable(GL_LIGHTING);
		}
		else
		{
			glDisable(GL_LIGHTING);
		}
	}

	void GLRenderSystem::enableTexture(bool enable)
	{
		if (enable)
		{
			glEnable(GL_TEXTURE_2D);
		}
		else
		{
			glDisable(GL_TEXTURE_2D);
		}
	}
}

