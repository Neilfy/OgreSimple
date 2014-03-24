PROJECT(GLRenderSystem)
set(LIBRARY_OUTPUT_PATH ../../../lib)

set (SOURCE_FILES
  src/GLRenderSystem.cpp
)

include_directories(
  include
)
include_directories(../../OgreSimpleMain/include)
link_directories( E:/WorkSpace/OgreSimple/lib )


add_library( GLRenderSystem SHARED ${SOURCE_FILES} )
TARGET_LINK_LIBRARIES(GLRenderSystem "libOgreMain.dll")
TARGET_LINK_LIBRARIES(GLRenderSystem "libopengl32.dll")

#add_library( GLRenderSystem_static STATIC ${SOURCE_FILES} )
#SET_TARGET_PROPERTIES(GLRenderSystem_static PROPERTIES OUTPUT_NAME "GLRenderSystem")