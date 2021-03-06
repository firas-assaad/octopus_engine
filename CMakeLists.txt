cmake_minimum_required(VERSION 3.10)
project(octopus_engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

file(GLOB SOURCES LIST_DIRECTORIES false src/*.cpp)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/test_main.cpp)

file(GLOB EXTRA_SOURCES LIST_DIRECTORIES false src/commands/*.cpp src/utility/*.cpp src/vendor/*.cpp)

file(GLOB XD_SOURCES LIST_DIRECTORIES false src/xd/audio/*.cpp src/xd/graphics/*.cpp src/xd/lua/*.cpp src/xd/system/*.cpp)

set(OpenGL_GL_PREFERENCE "GLVND")

if (APPLE)
    find_package(Boost REQUIRED COMPONENTS filesystem)
else()
    find_package(Boost REQUIRED)
endif()
find_package(Freetype REQUIRED)
find_package(HarfBuzz REQUIRED)
find_package(Lua 5.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(ZLIB REQUIRED)
find_package(FMOD REQUIRED)

set(DEPENDENCIES ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${FREETYPE_LIBRARIES}
${HARFBUZZ_LIBRARIES} ${LUA_LIBRARIES} ${ZLIB_LIBRARIES} ${FMOD_LIBRARIES}
${HarfBuzz_LIBRARIES} GLEW::GLEW glfw)

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    LIST(APPEND DEPENDENCIES ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${Boost_LIBRARIES})

    add_compile_definitions(OCB_USE_BOOST_FILESYSTEM OCB_USE_C_LUA)
    string(APPEND CMAKE_EXE_LINKER_FLAGS "-headerpad_max_install_names")
endif()

include_directories(${LUA_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIR_ft2build})

add_executable(octopus_engine ${SOURCES} ${EXTRA_SOURCES} ${XD_SOURCES})

target_compile_features(octopus_engine PRIVATE cxx_std_17)

target_link_libraries(octopus_engine ${DEPENDENCIES})