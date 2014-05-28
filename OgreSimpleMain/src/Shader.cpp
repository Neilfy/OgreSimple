#include "Shader.h"

#include "RenderSystem.h"

using std::string;

namespace OgreSimple
{
	Shader::Shader(void)
        : mShaderHandle(0)
        , mType(ST_VERTEX)
        , mRenderer(0)
	{
	}

	Shader::~Shader(void)
	{
	    ReleaseHandle();
	}

	bool Shader::IsAttributeExist(VertexDataFormat vdf) const
	{
		return (mAttributes.find(vdf) != mAttributes.end());
	}

	bool Shader::GetSenmanticType(const string& s, VertexDataFormat& vertexDataType)
	{
		if (s == "POSITION")
		{
			vertexDataType = VDF_XYZ;
		}
		else if (s == "NORMAL")
		{
			vertexDataType = VDF_NORMAL;
		}
		else if (s == "DIFFUSE")
		{
			vertexDataType = VDF_DIFFUSE;
		}
		else if (s == "TEXCOORD0")
		{
			vertexDataType = VDF_UV;
		}
		else
		{
			return false;
		}

		return true;
	}

	bool Shader::GetShaderDataType(const string& s, DataType& dataType)
	{
		if (s == "float")
		{
			dataType = DT_FLOAT;
		}
		else if (s == "vec2")
		{
			dataType = DT_VEC2;
		}
		else if (s == "vec3")
		{
			dataType = DT_VEC3;
		}
		else if (s == "vec4")
		{
			dataType = DT_VEC4;
		}
		else if (s == "mat4")
		{
			dataType = DT_MAT4;
		}
		else if (s == "tex2D")
		{
			dataType = DT_TEX2D;
		}
		else
		{
			return false;
		}

		return true;
	}

	bool Shader::GetUniformType(const string& s, uint32& uniformType)
	{
		if (s == "WORLDVIEWPROJECTION")
		{
			uniformType = UT_MVPMatrix;
		}
		else if (s == "TEXTURE0")
		{
			uniformType = UT_TEXTURE0;
		}
		else
		{
			uniformType = UT_User;
		}

		return true;
	}

	void Shader::ReleaseHandle(void)
	{
	    if ((0 != mShaderHandle) && (0 != mRenderer))
	    {
	        mRenderer->DeleteShader(mShaderHandle);
	        mShaderHandle = 0;
	    }
	}
}
