#include "GpuProgram.h"

#include <utility>

#include "RenderSystem.h"

using std::string;
using std::map;
using std::make_pair;


namespace OgreSimple
{
	GpuProgram::GpuProgram(void)
		: mProgram(0)
		, mRenderer(0)
	{
	}

	GpuProgram::~GpuProgram(void)
	{
	    ReleaseHandle();
	}

	bool GpuProgram::GetUserUniform(const string& name, float& v) const
	{
		map<string, float>::const_iterator it = mFloatVars.find(name);
		if (it == mFloatVars.end())
		{
			return false;
		}

		v = it->second;
		return true;
	}

	bool GpuProgram::GetUserUniform(const string& name, Vector2& v) const
	{
		map<string, Vector2>::const_iterator it = mVec2Vars.find(name);
		if (it == mVec2Vars.end())
		{
			return false;
		}

		v = it->second;
		return true;
	}

	bool GpuProgram::GetUserUniform(const string& name, Vector3& v) const
	{
		map<string, Vector3>::const_iterator it = mVec3Vars.find(name);
		if (it == mVec3Vars.end())
		{
			return false;
		}

		v = it->second;
		return true;
	}

	bool GpuProgram::GetUserUniform(const string& name, Vector4& v) const
	{
		map<string, Vector4>::const_iterator it = mVec4Vars.find(name);
		if (it == mVec4Vars.end())
		{
			return false;
		}

		v = it->second;
		return true;
	}

	bool GpuProgram::GetUserUniform(const string& name, Matrix4& v) const
	{
		map<string, Matrix4>::const_iterator it = mMat4Vars.find(name);
		if (it == mMat4Vars.end())
		{
			return false;
		}

		v = it->second;
		return true;
	}

    bool GpuProgram::GetAttributeIndex(VertexDataFormat vdf, uint32& index) const
	{
	    if (0 == mVertexShader)
	    {
	        return false;
	    }

		switch (vdf)
		{
		case VDF_XYZ:
		case VDF_NORMAL:
		case VDF_DIFFUSE:
		case VDF_UV:
			if (mVertexShader->IsAttributeExist(vdf))
			{
				index = static_cast<uint32>(log(static_cast<float>(vdf)) / log(2.0));
			}
			else
			{
				return false;
			}

			break;

		default:
			return false;
		}

		return true;
	}

	void GpuProgram::SetUserUniform(const string& name, float v)
	{
		map<string, float>::iterator it = mFloatVars.find(name);
		if (it != mFloatVars.end())
		{
            it->second = v;
		}
	}

	void GpuProgram::SetUserUniform(const string& name, const Vector2& v)
	{
		map<string, Vector2>::iterator it = mVec2Vars.find(name);
		if (it != mVec2Vars.end())
		{
            it->second = v;
		}
	}

	void GpuProgram::SetUserUniform(const string& name, const Vector3& v)
	{
		map<string, Vector3>::iterator it = mVec3Vars.find(name);
		if (it != mVec3Vars.end())
		{
            it->second = v;
		}
	}

	void GpuProgram::SetUserUniform(const string& name, const Vector4& v)
	{
		map<string, Vector4>::iterator it = mVec4Vars.find(name);
		if (it != mVec4Vars.end())
		{
            it->second = v;
		}
	}

	void GpuProgram::SetUserUniform(const string& name, const Matrix4& v)
	{
		map<string, Matrix4>::iterator it = mMat4Vars.find(name);
		if (it != mMat4Vars.end())
		{
            it->second = v;
		}
	}

    void GpuProgram::AddUniform(uint32 uniformType, Shader::Uniform uniform)
    {
        mUniforms.insert(make_pair(uniformType, uniform));
    }

    void GpuProgram::AddUserUniform(uint32 uniformType, Shader::Uniform uniform)
    {
        mUserUniforms.insert(make_pair(uniformType, uniform));
    }

    void GpuProgram::ReleaseHandle(void)
    {
	    if ((0 != mProgram) && (0 != mRenderer))
	    {
	        mRenderer->DeleteProgram(mProgram);
	        mProgram = 0;
	    }

	    mUniforms.clear();
	    mUserUniforms.clear();
    }
}
