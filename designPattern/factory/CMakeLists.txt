set(output_bin test_abstractFactory)
add_executable(${output_bin} main.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_af_shape)
add_executable(${output_bin} main_shape.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_af_hotdrink)
add_executable(${output_bin} main_hotdrink.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_innerAbstractFactory)
add_executable(${output_bin} main_inner.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})