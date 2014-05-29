PROJECT(OgreMain)

set(LIBRARY_OUTPUT_PATH ../../lib)

set (SOURCE_FILES
    src/ImageLoader/jpeg/jcapimin.c
	src/ImageLoader/jpeg/jcapistd.c
	src/ImageLoader/jpeg/jccoefct.c
	src/ImageLoader/jpeg/jccolor.c
	src/ImageLoader/jpeg/jcdctmgr.c
	src/ImageLoader/jpeg/jchuff.c
	src/ImageLoader/jpeg/jcinit.c
	src/ImageLoader/jpeg/jcmainct.c
	src/ImageLoader/jpeg/jcmarker.c
	src/ImageLoader/jpeg/jcmaster.c
	src/ImageLoader/jpeg/jcomapi.c
	src/ImageLoader/jpeg/jcparam.c
	src/ImageLoader/jpeg/jcphuff.c
	src/ImageLoader/jpeg/jcprepct.c
	src/ImageLoader/jpeg/jcsample.c
	src/ImageLoader/jpeg/jctrans.c
	src/ImageLoader/jpeg/jdapimin.c
	src/ImageLoader/jpeg/jdapistd.c
	src/ImageLoader/jpeg/jdatadst.c
	src/ImageLoader/jpeg/jdatasrc.c
	src/ImageLoader/jpeg/jdcoefct.c
	src/ImageLoader/jpeg/jdcolor.c
	src/ImageLoader/jpeg/jddctmgr.c
	src/ImageLoader/jpeg/jdhuff.c
	src/ImageLoader/jpeg/jdinput.c
	src/ImageLoader/jpeg/jdmainct.c
	src/ImageLoader/jpeg/jdmarker.c
	src/ImageLoader/jpeg/jdmaster.c
	src/ImageLoader/jpeg/jdmerge.c
	src/ImageLoader/jpeg/jdphuff.c
	src/ImageLoader/jpeg/jdpostct.c
	src/ImageLoader/jpeg/jdsample.c
	src/ImageLoader/jpeg/jdtrans.c
	src/ImageLoader/jpeg/jerror.c
	src/ImageLoader/jpeg/jfdctflt.c
	src/ImageLoader/jpeg/jfdctfst.c
	src/ImageLoader/jpeg/jfdctint.c
	src/ImageLoader/jpeg/jidctflt.c
	src/ImageLoader/jpeg/jidctfst.c
	src/ImageLoader/jpeg/jidctint.c
	src/ImageLoader/jpeg/jidctred.c
	src/ImageLoader/jpeg/jmemmgr.c
	src/ImageLoader/jpeg/jmemnobs.c
	src/ImageLoader/jpeg/jquant1.c
	src/ImageLoader/jpeg/jquant2.c
	src/ImageLoader/jpeg/jutils.c
	src/ImageLoader/CPictureLoader.cpp
	src/ImageLoader/CJPGLoader.cpp
	src/ImageLoader/CTGALoader.cpp
	src/tinyXML/tinystr.cpp
	src/tinyXML/tinyxml.cpp
	src/tinyXML/tinyxmlerror.cpp
	src/tinyXML/tinyxmlparser.cpp
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
  src/MaterialManager.cpp
  src/Material.cpp
  src/Technique.cpp
  src/TextureUnit.cpp
  src/Texture.cpp
  src/TextureManager.cpp
  src/thread/ResourcesLoaderThread.cpp
  src/thread/ThreadBase.cpp
  src/thread/MapSyncObj.cpp
  src/VirtualObject.cpp
  src/ModelLoader/OBJLoader.cpp
  src/Mesh.cpp
  src/MeshManager.cpp
  src/SubMesh.cpp
  src/SceneFileLoader.cpp
  src/Shader.cpp
  src/GpuProgram.cpp
  src/ShaderManager.cpp
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
  include/ModelLoader/
  include/ImageLoader/
  include/tinyXML/
)

add_library( OgreMain SHARED ${SOURCE_FILES} ${SOURCE_FILES_EX} )
#add_library( OgreMain_static STATIC ${SOURCE_FILES} )
#SET_TARGET_PROPERTIES(OgreMain_static PROPERTIES OUTPUT_NAME "OgreMain")

