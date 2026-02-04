set(output_bin test_ace_command)
add_executable(${output_bin} command.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_bank_command)
add_executable(${output_bin} command_bank.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_app_framework_command)
add_executable(${output_bin} command_app_framework.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_command_app_fw_factory)
add_executable(${output_bin} command_app_fw_factory.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_cmd_app_fw_factory_singleton)
add_executable(${output_bin} cmd_app_fw_factory_singleton.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})

set(output_bin test_cmd_app_fw_factory_singleton_MVC)
add_executable(${output_bin} cmd_app_fw_factory_singleton_MVC.cpp)
set_target_properties(${output_bin} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${output_bin})