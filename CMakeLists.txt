cmake_minimum_required(VERSION 3.3)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
  # Standalone project
  message(STATUS "Library 'conversion' is built as a standalone project")
  project(Conversion)
  set(Conversion_library_folder "library")
  set(Conversion_test_folder "unit tests")
else()
  # Part of another project
  message(STATUS "Library 'conversion' is built as a part of another project")
  if (NOT DEFINED EXTERNAL_LIBRARY_FOLDER)
    set(Conversion_library_folder "external libraries")
  else()
    set(Conversion_library_folder "${EXTERNAL_LIBRARY_FOLDER}")
  endif()
  if (NOT DEFINED EXTERNAL_LIBRARY_TEST_FOLDER)
    set(Conversion_test_folder "external libraries tests")
  else()
    set(Conversion_test_folder "${EXTERNAL_LIBRARY_TEST_FOLDER}")
  endif()
endif()

set(BOOST_ROOT "" CACHE PATH "Path to boost includes")
set(BOOST_LIBRARYDIR "" CACHE PATH "Path to boost libraries")
if(WIN32)
  set(Boost_USE_STATIC_LIBS ON)
endif()

find_package(
  Boost
  REQUIRED
  COMPONENTS unit_test_framework
)

set(Conversion_include "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${Conversion_include})
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()

add_subdirectory(src)
add_subdirectory(test)
