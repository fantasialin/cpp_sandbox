set(test_src 
    bind_test
    callback_test
    cpu_test
    function_test
    move_test
    placeholder_test)


foreach(test_code ${test_src})
    add_executable(${test_code} ${test_code}.cpp)
    set_target_properties(${test_code} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    target_link_libraries(${test_code})
endforeach(test_code)
