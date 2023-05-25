cmake_minimum_required(VERSION 3.0.0)
project(nklang VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()
if(ENABLE_CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY clang-tidy -extra-arg=-std=gnu++${CMAKE_CXX_STANDARD} --config-file ${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy --header-filter=${CMAKE_CURRENT_SOURCE_DIR}/[src|test]*.*hpp)
  if(ENABLE_WERROR)
    set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} -warnings-as-errors=*)
  endif()
endif()
if(ENABLE_SANITIZE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,pointer-compare")
endif()

file(GLOB SOURCES
    src/*.hpp
    src/*.cpp
)

add_executable(nklang  ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
