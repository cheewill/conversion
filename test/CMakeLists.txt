add_executable(ConversionTests
  test_runner.cpp
  strtoint_tests.cpp
  strtofloat_tests.cpp
  recognizer_tests.cpp
  recognizer_int_tests.cpp
  recognizer_float_tests.cpp
  recognizer_error_tests.cpp
  recognizer_empty_tests.cpp
  recognizer_zero_int_tests.cpp
  recognizer_zero_float_tests.cpp
  recognizer_zero_exp_tests.cpp
  converter_tests.cpp
  converter_base_tests.cpp
  converter_int_tests.cpp
  converter_float_tests.cpp
)
add_dependencies(ConversionTests Conversion)
set_target_properties(ConversionTests PROPERTIES FOLDER "${Conversion_test_folder}")

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries (ConversionTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
# Turn on exceptions for unit tests.
if(WIN32)
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /EHsc" )
else()
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fexceptions" )
endif()

set(Conversion_test_location $<TARGET_FILE:ConversionToolsTests>)
add_custom_target(check-conversion
  COMMAND ${conversion_test_location}
  DEPENDS ConversionTests
)
set_target_properties(check-conversion PROPERTIES FOLDER "${Conversion_test_folder}")
