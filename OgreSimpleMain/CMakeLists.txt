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
)

include_directories(
  include
)

add_library( OgreMain SHARED ${SOURCE_FILES} )
#add_library( OgreMain_static STATIC ${SOURCE_FILES} )
#SET_TARGET_PROPERTIES(OgreMain_static PROPERTIES OUTPUT_NAME "OgreMain")

