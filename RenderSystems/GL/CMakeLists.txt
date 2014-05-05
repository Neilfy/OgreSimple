PROJECT(GLRenderSystem)
set(LIBRARY_OUTPUT_PATH ../../../lib)

set (SOURCE_FILES
  src/glew.cpp
  src/GLRenderSystem.cpp
  src/GLVertexIndexVBO.cpp
  src/GLHardwareManager.cpp
  src/GLTexture.cpp
  src/GLTextureManager.cpp
)

include_directories(
  include/
  include/GL
  ${CMAKE_SOURCE_DIR}/OgreSimpleMain/include
)

link_directories( ${CMAKE_SOURCE_DIR}/lib )

add_library( GLRenderSystem SHARED ${SOURCE_FILES} )

TARGET_LINK_LIBRARIES(GLRenderSystem "OgreMain")
if(WIN32)
    TARGET_LINK_LIBRARIES(GLRenderSystem "opengl32")
elseif(UNIX)
    TARGET_LINK_LIBRARIES(GLRenderSystem "GL")
endif()

#add_library( GLRenderSystem_static STATIC ${SOURCE_FILES} )
#SET_TARGET_PROPERTIES(GLRenderSystem_static PROPERTIES OUTPUT_NAME "GLRenderSystem")
