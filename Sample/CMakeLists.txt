cmake_minimum_required(VERSION 2.6.2)
PROJECT(HelloOgreSimple)
set(EXECUTABLE_OUTPUT_PATH ../../lib)
set (SOURCE_FILES
  HelloOgreSimple.cpp
)

include_directories(
  ../OgreSimpleMain/include/
  ../RenderSystems/GL/include/
)

link_directories( E:/WorkSpace/OgreSimple/lib )

add_executable( HelloOgreSimple ${SOURCE_FILES} )

TARGET_LINK_LIBRARIES(HelloOgreSimple "libOgreMain.dll")
TARGET_LINK_LIBRARIES(HelloOgreSimple "libGLRenderSystem.dll")

TARGET_LINK_LIBRARIES(HelloOgreSimple "libopengl32.dll")
