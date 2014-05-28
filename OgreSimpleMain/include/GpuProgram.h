#ifndef CXX_GPUPROGRAM_H
#define CXX_GPUPROGRAM_H

#include <map>
#include <string>

#include "NMath.h"
#include "Shader.h"

namespace OgreSimple
{
	class RenderSystem;
	class GpuProgram
	{

	public:
		GpuProgram(void);
		~GpuProgram(void);

	public:
		bool GetUserUniform(const std::string& name, float& v) const;
		bool GetUserUniform(const std::string& name, Vector2& v) const;
		bool GetUserUniform(const std::string& name, Vector3& v) const;
		bool GetUserUniform(const std::string& name, Vector4& v) const;
		bool GetUserUniform(const std::string& name, Matrix4& v) const;

        Shader* GetVertexShader(void)
        {
            return mVertexShader;
        }

        Shader* GetFragmentShader(void)
        {
            return mFragmentShader;
        }

        uint32 GetProgramObjectHandle() const
        {
            return mProgram;
        }

		const std::map<uint32, Shader::Uniform>& GetUniforms(void) const
		{
			return mUniforms;
		}

		const std::map<uint32, Shader::Uniform>& GetUserUniforms(void) const
		{
			return mUserUniforms;
		}

		bool GetAttributeIndex(VertexDataFormat vdf, uint32& index) const;

		void SetUserUniform(const std::string& name, float v);
		void SetUserUniform(const std::string& name, const Vector2& v);
		void SetUserUniform(const std::string& name, const Vector3& v);
		void SetUserUniform(const std::string& name, const Vector4& v);
		void SetUserUniform(const std::string& name, const Matrix4& v);

		void SetProgramObjectHandle(uint32 handle)
		{
		    mProgram = handle;
		}

		void AddUniform(uint32 uniformType, Shader::Uniform uniform);

		void AddUserUniform(uint32 uniformType, Shader::Uniform uniform);

        void SetRenderer(RenderSystem* renderer)
        {
            mRenderer = renderer;
        }

        void ReleaseHandle(void);

	public:
		// user vars
		std::map<std::string, float>	mFloatVars;
		std::map<std::string, Vector2>	mVec2Vars;
		std::map<std::string, Vector3>	mVec3Vars;
		std::map<std::string, Vector4>	mVec4Vars;
		std::map<std::string, Matrix4>	mMat4Vars;

		// shaders
		Shader*	mVertexShader;
		Shader*	mFragmentShader;

		// program
		uint32	mProgram;

		// uniforms
		std::map<uint32, Shader::Uniform>	mUniforms;
		std::map<uint32, Shader::Uniform>	mUserUniforms;

		RenderSystem*   mRenderer;
	};

}


#endif // CXX_GPUPROGRAM_H
