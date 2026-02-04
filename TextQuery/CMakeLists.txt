set(output_bin TextQuery)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${output_bin} main.cpp TextQuery.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

add_custom_command(TARGET TextQuery POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/test.txt"
        "$<TARGET_FILE_DIR:TextQuery>/test.txt"
    COMMENT "Copying test data file to output directory"
)