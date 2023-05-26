cmake_minimum_required(VERSION 3.10)
project(c-controller C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pthread")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -ggdb -fno-eliminate-unused-debug-symbols")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto -march=native")
#set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include_directories(c-controller/tofino_include)

set(c-controller_source_files
        c-controller/datastructures/flow_hashtable.c
        c-controller/datastructures/hashes/MurmurHash3.c
        c-controller/dataplane/dp_api.c
        c-controller/packet_handler/packet_handler.c
        c-controller/controller.c
    )

add_library(c-controller SHARED
        ${c-controller_source_files}
        )
target_link_libraries(c-controller pcap uuid)

add_executable(test_switch
        c-controller/mock.c
        ${c-controller_source_files}
        )
target_link_libraries(test_switch pcap uuid)
target_compile_definitions(test_switch PRIVATE MOCK_PACKETS VERBOSE)


message("CMAKE_C_FLAGS is ${CMAKE_C_FLAGS}")
message("CMAKE_C_FLAGS_DEBUG is ${CMAKE_C_FLAGS_DEBUG}")
message("CMAKE_C_FLAGS_RELEASE is ${CMAKE_C_FLAGS_RELEASE}")
