set(test_src
    gaussian
    gaussianfast
    bilateral
    guided_filter
    template)


foreach(test_code ${test_src})
    set(output_bin ${test_code}_test)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
    add_executable(${output_bin} ${test_code}/main.cpp)
    set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    target_link_libraries(${output_bin})
endforeach(test_code)

add_custom_target(copy_data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        ${CMAKE_BINARY_DIR}/bin/data
)