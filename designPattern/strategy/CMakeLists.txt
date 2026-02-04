set(output_bin test_strategy_dynamic)
add_executable(${output_bin} dynamic.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_strategy_static)
add_executable(${output_bin} static.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_strategy_layout)
add_executable(${output_bin} layout.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

add_custom_command(TARGET test_strategy_layout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/quote.txt"
        "$<TARGET_FILE_DIR:test_strategy_layout>/quote.txt"
    COMMENT "Copying test data file to output directory"
)