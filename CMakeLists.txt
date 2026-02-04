cmake_minimum_required (VERSION 3.16)
project (cv_test_prj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(_USE_MATH_DEFINES)

set(THREADS_PREFER_PTHREAD_FLAG ON)
option(BUILD_GUI_TEST_PROGRAM "Build GUI test program" ON)
find_package(Threads REQUIRED)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  include_directories(
    /usr/local/include
    /opt/local/include
    /opt/homebrew/include
  )

  
  find_library(OPENGL_LIBRARY OpenGL REQUIRED)
  find_library(GLEW_LIBRARY GLEW REQUIRED)
  find_library(COCOA_LIBRARY Cocoa REQUIRED)
  find_library(IOKIT_LIBRARY IOKit REQUIRED)
  find_library(COREVID_LIBRARY CoreVideo REQUIRED)

  set(EXTRA_LIBRARIES
      ${OPENGL_LIBRARY}
      ${GLEW_LIBRARY}
      ${COCOA_LIBRARY}
      ${IOKIT_LIBRARY}
      ${COREVID_LIBRARY}
      glfw
      )
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(exercise)
add_subdirectory(tests)
add_subdirectory(polymorphism)
add_subdirectory(ref_count)
add_subdirectory(rvalue_ref)
add_subdirectory(test_rvo)
add_subdirectory(designPattern)
add_subdirectory(ctor_dtor)
add_subdirectory(complex)
add_subdirectory(allocator)
add_subdirectory(TextQuery)
add_subdirectory(thread)
add_subdirectory(unorderedMap)
add_subdirectory(variadic)

