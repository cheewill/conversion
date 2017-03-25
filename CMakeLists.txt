cmake_minimum_required(VERSION 3.3)

# --------------------------------------------
# Load CMake definitions for component support
#

# First try to load component support from sibling directory. If these sources
# are part of existing project, they must be placed in the project source tree
# that looks like:
#
# ...
# \- <directory-for-components>
#    \-component.cmake
#    \-<this-library-directory>
#      \-<this CMakeLists.txt>
#
# If sibling directory 'component.cmake' does not exist, use local copy.
#
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../component.cmake/main.cmake)
  include(${CMAKE_CURRENT_SOURCE_DIR}/../component.cmake/main.cmake)
else()
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/main.cmake)
endif()

#
# --------------------------------------------

# --------------------------------------------
# Tune component
#

set(COMPONENT_Conversion_NEEDS_UNITTESTS "ON")

#
# --------------------------------------------

# --------------------------------------------
# Set up boost component
#

if (COMPONENT_Conversion_NEEDS_UNITTESTS)
  set(BOOST_ROOT "" CACHE PATH "Path to boost includes")
  set(BOOST_LIBRARYDIR "" CACHE PATH "Path to boost libraries")
  if(WIN32)
    set(Boost_USE_STATIC_LIBS ON)
  endif()

  find_package(
    Boost 1.56
    COMPONENTS unit_test_framework
  )
  if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    get_filename_component(boost_library_path "${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}" DIRECTORY)
    link_directories(${boost_library_path})
  else()
    message(STATUS "No unit tests for component Conversion as Boost is not found")
    unset(COMPONENT_Conversion_NEEDS_UNITTESTS)
  endif()
endif()

#
# --------------------------------------------

# --------------------------------------------
# Set up component
#

make_component_project(conversion)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()

add_subdirectory(src)
if (COMPONENT_Conversion_NEEDS_UNITTESTS)
  add_subdirectory(test)
endif()
