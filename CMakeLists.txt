cmake_minimum_required(VERSION 3.0.0)
project(cpp-refactoring-1 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set (CMAKE_CXX_FLAGS "-fcoroutines")


include(CTest)
enable_testing()

include_directories(/usr/local/include)
link_directories(/usr/local/lib64)
include_directories(/usr/local/gcc/include)
link_directories(/usr/local/gcc/lib64)
find_package(Boost 1.62 REQUIRED COMPONENTS coroutine)


add_executable(cpp-refactoring-1 main.cpp agent_session_handler.cpp)
target_link_libraries(cpp-refactoring-1 stdc++fs)
target_link_libraries(cpp-refactoring-1 Boost::coroutine)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
