cmake_minimum_required(VERSION 2.6.2)
PROJECT(HelloOgreSimple)

ADD_DEFINITIONS(-DGLUT_DISABLE_ATEXIT_HACK)
set(EXECUTABLE_OUTPUT_PATH ../../lib)
set (SOURCE_FILES
  HelloOgreSimple.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/OgreSimpleMain/include
  ${CMAKE_SOURCE_DIR}/RenderSystems/GL/include
)

link_directories( ${CMAKE_SOURCE_DIR}/lib )

add_executable( HelloOgreSimple ${SOURCE_FILES} )

TARGET_LINK_LIBRARIES(HelloOgreSimple "OgreMain")
TARGET_LINK_LIBRARIES(HelloOgreSimple "GLRenderSystem")

if(WIN32)
    TARGET_LINK_LIBRARIES(HelloOgreSimple "glut32")
    TARGET_LINK_LIBRARIES(HelloOgreSimple "opengl32")
elseif(UNIX)
    TARGET_LINK_LIBRARIES(HelloOgreSimple "GL")
    TARGET_LINK_LIBRARIES(HelloOgreSimple "glut")
endif()
