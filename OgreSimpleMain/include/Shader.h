#ifndef CXX_SHADER_H
#define CXX_SHADER_H

#include <string>
#include <map>
#include "OgreSimpleTypes.h"

namespace OgreSimple
{
    class RenderSystem;

	class Shader
	{

	public:
		enum ShaderType
		{
			ST_VERTEX,
			ST_FRAGMENT,
		};

		enum DataType
		{
			DT_FLOAT,
			DT_VEC2,
			DT_VEC3,
			DT_VEC4,
			DT_MAT4,
			DT_TEX2D,
		};

		struct VertexAttribute
		{
			DataType		type;
			std::string		name;
		};

		struct Uniform
		{
			Uniform(DataType dataType, const std::string& uniformName, int32 uniformLocation = -1)
				: type(dataType)
				, name(uniformName)
				, location(uniformLocation)
			{}

			DataType	type;
			std::string name;
			int32		location;
		};

		typedef std::map<VertexDataFormat, VertexAttribute>	AttributeList;
		typedef std::map<uint32, Uniform> UniformList;

	public:
		Shader(void);
		~Shader(void);

	public:
        uint32 GetShaderObjectHandle(void) const
        {
            return mShaderHandle;
        }

        ShaderType GetShaderType(void) const
        {
            return mType;
        }

		bool IsAttributeExist(VertexDataFormat vdf) const;

		const AttributeList& GetAttributes(void) const
		{
			return mAttributes;
		}

		const UniformList& GetUniforms(void) const
		{
			return mUniforms;
		}

		const UniformList& GetUserUniforms(void) const
		{
			return mUserUniforms;
		}

		const std::string& GetSource(void) const
		{
			return mSource;
		}

		void SetShaderObjectHandle(uint32 handle)
		{
		    mShaderHandle = handle;
		}

        void SetRenderer(RenderSystem* renderer)
        {
            mRenderer = renderer;
        }

        void SetShaderType(Shader::ShaderType shaderType)
        {
            mType = shaderType;
        }

        void SetShaderSource(const std::string& content)
        {
            mSource = content;
        }

        void ReleaseHandle(void);

	public:
		static bool GetSenmanticType(const std::string& s, VertexDataFormat& vertexDataType);
		static bool GetShaderDataType(const std::string& s, DataType& dataType);
		static bool GetUniformType(const std::string& s, uint32& uniformType);

	private:
        uint32      mShaderHandle;    // handle
		ShaderType	mType;

		AttributeList	mAttributes;
		UniformList		mUniforms;
		UniformList		mUserUniforms;

		std::string 	mSource;

		RenderSystem*       mRenderer;
	};

}

#endif // CXX_SHADER_H
