cmake_minimum_required(VERSION 3.16)
project(tpk4128_tcpip_sockets)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(A A.c)
add_executable(B B.c)
add_executable(C C.c)
add_executable(D D.c)
target_link_libraries(B PRIVATE Threads::Threads)
target_link_libraries(C PRIVATE Threads::Threads)
target_link_libraries(D PRIVATE Threads::Threads)