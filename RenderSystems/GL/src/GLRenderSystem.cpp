#include "glew.h"
#include "OgreSimpleTypes.h"
#include "GLRenderSystem.h"
#include "Viewport.h"
#include "RenderOperation.h"
#include "GLHardwareManager.h"
#include "GLTextureManager.h"
#include "Material.h"
#include "GLTexture.h"
#include <stdio.h>
#include <map>
using std::map;
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
		if(tech->IsProgrammable())
		{
			mGpuProgram = tech->GetGpuProgram();

			if (!ActiveProgram(mGpuProgram))
			{
			}
		}
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

	void GLRenderSystem::DeleteShader(uint32 shader)
	{
		if (glIsShader(shader))
		{
			glDeleteShader(shader);
		}
	}

	void GLRenderSystem::DeleteProgram(uint32 program)
	{
		if (glIsProgram(program))
		{
			glDeleteProgram(program);
		}
	}

	bool GLRenderSystem::ActiveProgram(GpuProgram* program)
	{
		if (0 == program)
		{
			return false;
		}

		if (0 == program->GetProgramObjectHandle())
		{
			if (!CompileGpuProgram(program))
			{
				return false;
			}
		}

		glUseProgram(program->GetProgramObjectHandle());
		
		const map<uint32, Shader::Uniform>& userUniforms = program->GetUserUniforms();
		for (map<uint32, Shader::Uniform>::const_iterator it = userUniforms.begin();
			it != userUniforms.end(); ++it)
		{
			switch (it->second.type)
			{
			case Shader::DT_FLOAT:
				{
					float v;
					if (program->GetUserUniform(it->second.name, v))
					{
						glUniform1f(it->second.location, v);
					}
				}
				break;

			case Shader::DT_VEC2:
				{
					Vector2 v;
					if (program->GetUserUniform(it->second.name, v))
					{
						glUniform2fv(it->second.location, 1, &(v.x));
					}
				}
				break;

			case Shader::DT_VEC3:
				{
					Vector3 v;
					if (program->GetUserUniform(it->second.name, v))
					{
						 glUniform3fv(it->second.location, 1, &(v.x));
					}
				}
				break;

			case Shader::DT_VEC4:
				{
					Vector4 v;
					if (program->GetUserUniform(it->second.name, v))
					{
						glUniform4fv(it->second.location, 1, &(v.x));
					}
				}
				break;

			case Shader::DT_MAT4:
				{
					Matrix4 v;
					if (program->GetUserUniform(it->second.name, v))
					{
						glUniformMatrix4fv(it->second.location, 1, GL_FALSE, v.GetTranspose().GetRawPointer());
					}
				}
				break;

			default:
				break;
			}
		}

		return true;
	}

	bool GLRenderSystem::CompileGpuProgram(GpuProgram* program)
    {
        if (0 == program)
        {
            return false;
        }

        Shader* vs = program->GetVertexShader();
        Shader* fs = program->GetFragmentShader();

		if (0 == vs || 0 == fs)
		{
			return false;
		}

        // get vertex shader handle
        uint32 vsHandle = vs->GetShaderObjectHandle();
//        OutputDebugLog("K: RendererGLES2::CompileGpuProgram, 0x%X, handle %d", vs.get(), vsHandle);
        if (0 == vsHandle)
        {
            if (0 == (vsHandle = CompileShader(vs)))
            {
                return false;
            }
        }

        // get fragment shader handle
        uint32 fsHandle = fs->GetShaderObjectHandle();
        if (0 == fsHandle)
        {
            if (0 == (fsHandle = CompileShader(fs)))
            {
                return false;
            }
        }

		// create program
		uint32 programHandle = glCreateProgram();
		if (0 == programHandle)
		{
			return false;
		}

		// attach
		glAttachShader(programHandle, vsHandle);
		glAttachShader(programHandle, fsHandle);

		// bind attributes
		uint32 attr_index = 0;
		const Shader::AttributeList& attributes = vs->GetAttributes();
		for (Shader::AttributeList::const_iterator it = attributes.begin();
			it != attributes.end();
			++it)
		{
			if (program->GetAttributeIndex(it->first, attr_index))
			{
				glBindAttribLocation(programHandle, attr_index, it->second.name.c_str());
			}
		}

		// link
		glLinkProgram(programHandle);

		GLint linked = 0;
		glGetProgramiv(programHandle, GL_LINK_STATUS, &linked);
		if (0 == linked)
		{
			glDeleteProgram(programHandle);

			return false;
		}

		// get uniforms
		int uniform_location = -1;
		// uniforms of vertex shader
		const Shader::UniformList& vs_uniforms = vs->GetUniforms();
		for (Shader::UniformList::const_iterator it = vs_uniforms.begin();
			it != vs_uniforms.end();
			++it)
		{
			uniform_location = glGetUniformLocation(programHandle, it->second.name.c_str());
			program->AddUniform(it->first, Shader::Uniform(it->second.type, it->second.name, uniform_location));
		}
		// uniforms of fragment shader
		const Shader::UniformList& fs_uniforms = fs->GetUniforms();
		for (Shader::UniformList::const_iterator it = fs_uniforms.begin();
			it != fs_uniforms.end();
			++it)
		{
			uniform_location = glGetUniformLocation(programHandle, it->second.name.c_str());
			program->AddUniform(it->first, Shader::Uniform(it->second.type, it->second.name, uniform_location));
		}

		// user uniforms
		// uniforms of vertex shader
		const Shader::UniformList& vs_u_uniforms = vs->GetUserUniforms();
		uint32 user_unforms_index = 0;
		for (Shader::UniformList::const_iterator it = vs_u_uniforms.begin();
			it != vs_u_uniforms.end();
			++it)
		{
			uniform_location = glGetUniformLocation(programHandle, it->second.name.c_str());
			program->AddUserUniform(user_unforms_index++, Shader::Uniform(it->second.type, it->second.name, uniform_location));
		}
		// uniforms of fragment shader
		const Shader::UniformList& fs_u_uniforms = fs->GetUserUniforms();
		for (Shader::UniformList::const_iterator it = fs_u_uniforms.begin();
			it != fs_u_uniforms.end();
			++it)
		{
			uniform_location = glGetUniformLocation(programHandle, it->second.name.c_str());
			program->AddUserUniform(user_unforms_index++, Shader::Uniform(it->second.type, it->second.name, uniform_location));
		}

        program->SetProgramObjectHandle(programHandle);
        program->SetRenderer(this);

		return true;
    }

	uint32 GLRenderSystem::CompileShader(Shader* shader)
    {
        if (0 == shader)
        {
            return false;
        }

        GLenum shaderType = GL_VERTEX_SHADER;
        switch (shader->GetShaderType())
        {
        case Shader::ST_VERTEX:
            shaderType = GL_VERTEX_SHADER;
            break;

        case Shader::ST_FRAGMENT:
            shaderType = GL_FRAGMENT_SHADER;
            break;

        default:
            return 0;
        }

        // create shader object
		GLuint shaderHandle = glCreateShader(shaderType);
		if (0 == shaderHandle)
		{
			return 0;
		}

		const char* shader_src = shader->GetSource().c_str();
		glShaderSource(shaderHandle, 1, &shader_src, NULL);
		glCompileShader(shaderHandle);

		GLint compiled = 0;
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
		if (0 == compiled)
		{
				char info_log[5000];
				glGetShaderInfoLog(shaderHandle, 5000, NULL, info_log);
				printf("Error in vertex shader compilation!\n");
				printf("Info Log: %s\n", info_log);
			glDeleteShader(shaderHandle);
			return 0;
		}

        shader->SetShaderObjectHandle(shaderHandle);
        shader->SetRenderer(this);

        return shaderHandle;
    }
}

