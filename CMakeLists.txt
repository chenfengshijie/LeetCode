cmake_minimum_required(VERSION 3.0.0)
project(template VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(template main2.cpp)

set(C_STANDARD C11)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
cmake_minimum_required(VERSION 3.10)
