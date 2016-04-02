add_library(Conversion
  ${Conversion_include}/conversion/number_recognizer.h
  ${Conversion_include}/conversion/numbers.h
  ${Conversion_include}/conversion/number_convert.h
  ${Conversion_include}/conversion/number_properties.h
  ${Conversion_include}/conversion/strto.h
  number_converter.cpp
)
set_target_properties(Conversion PROPERTIES FOLDER "${Conversion_library_folder}")
