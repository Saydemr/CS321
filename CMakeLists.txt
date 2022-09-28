project(exams)

SET(CMAKE_CXX_STANDARD 20)
include_directories("range-v3/include")

add_executable(final final-main.cpp)
add_executable(first final-first.cpp)

add_executable(s1 mt2-snap1.cpp)
add_executable(s2 mt2-snap2.cpp)
add_executable(s3 mt2-snap3.cpp)
