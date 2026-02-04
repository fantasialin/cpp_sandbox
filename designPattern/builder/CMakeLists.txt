set(output_bin test_simpleBuilder)
add_executable(${output_bin} simpleBuilder.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_innerBuilder)
add_executable(${output_bin} innerBuilder.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_fluentBuilder)
add_executable(${output_bin} fluentBuilder.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_personBuilder)
add_executable(${output_bin} person.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})