clang++ main.cpp -o main

clang++ main.cpp -fno-elide-constructors -o main_disable

clang++ throw_exception.cpp -o throw_exception

clang++ RVO.cpp -o RVO

clang++ RVO.cpp -fno-elide-constructors -o RVO_disable

clang++ with_rvalue_reference.cpp -o with_rvalue_reference

clang++ without_rvalue_reference.cpp -o without_rvalue_reference
