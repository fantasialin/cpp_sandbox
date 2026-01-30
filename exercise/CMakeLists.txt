add_executable(0001_test 0001/main.cpp)
set_target_properties(0001_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(0001_test)

add_executable(0002_test 0002/main.cpp)
set_target_properties(0002_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(0002_test)

add_executable(0003_test 0003/main.cpp)
set_target_properties(0003_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(0003_test)