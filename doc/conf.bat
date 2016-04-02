setlocal
PATH=G:\Program Files (x86)\CMake\bin;%PATH%

cmake -G "Visual Studio 14" ^
      -DBOOST_ROOT="G:/local/boost_1_60_0" ^
      -DBOOST_LIBRARYDIR="G:/local/boost_1_60_0/lib32-msvc-14.0" ^
      ..

