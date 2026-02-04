set(output_bin variadic_test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${output_bin} variadic_test.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin tuple_test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${output_bin} tuple_test.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

