cmake_minimum_required(VERSION 2.6.2)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "${ENV{CXXFLAGS} -O3 -Wall")

add_subdirectory(OgreSimpleMain)
add_subdirectory(RenderSystems/GL)
add_subdirectory(Sample)