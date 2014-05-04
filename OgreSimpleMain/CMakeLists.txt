PROJECT(OgreMain)

set(LIBRARY_OUTPUT_PATH ../../lib)

set (SOURCE_FILES
  src/Camera.cpp
  src/Color.cpp
  src/NMath.cpp
  src/Frustum.cpp
  src/OgreSimpleRoot.cpp
  src/SceneManager.cpp
  src/Viewport.cpp
  src/RenderSystem.cpp
  src/MovableObject.cpp
  src/VertexIndexData.cpp
  src/HardwareManager.cpp
  src/Renderable.cpp
  src/MaterialManager.cpp
  src/Material.cpp
  src/Technique.cpp
  src/TextureUnit.cpp
  src/Texture.cpp
  src/TextureManager.cpp
  src/thread/ResourcesLoaderThread.cpp
  src/thread/ThreadBase.cpp
)
if(WIN32)
set (SOURCE_FILES_EX
  src/thread/platform_thread_win.cpp
)
elseif(UNIX)
set (SOURCE_FILES_EX
  src/thread/platform_thread_linux.cpp
)
endif()

include_directories(
  include
  include/thread/
)

add_library( OgreMain SHARED ${SOURCE_FILES} ${SOURCE_FILES_EX} )
#add_library( OgreMain_static STATIC ${SOURCE_FILES} )
#SET_TARGET_PROPERTIES(OgreMain_static PROPERTIES OUTPUT_NAME "OgreMain")

