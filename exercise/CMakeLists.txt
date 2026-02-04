set(test_src
    0001 
    0002
    0003)


foreach(test_code ${test_src})
    set(output_bin ${test_code}_test)
    add_executable(${output_bin} ${test_code}/main.cpp)
    set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    target_link_libraries(${output_bin})
endforeach(test_code)