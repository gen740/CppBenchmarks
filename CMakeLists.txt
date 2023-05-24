cmake_minimum_required(VERSION 3.20)

project(CppBenchmarks CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

# Checking Build Type
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra")

find_package(benchmark)

file(GLOB BENCHMARK_SOURCES ${CMAKE_CURRENT_LIST_DIR}/benchmarks/*.cpp)

foreach(s ${BENCHMARK_SOURCES})
  get_filename_component(t ${s} NAME_WE)

  add_executable(${t} ${s})
  set_property(TARGET ${t} PROPERTY CXX_STANDARD 20)
  target_link_libraries(${t} PRIVATE benchmark::benchmark
                                     benchmark::benchmark_main)
  target_include_directories(${t} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
endforeach()
