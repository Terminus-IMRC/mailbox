set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -pipe -O2 -g")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(info info.c)
target_link_libraries(info LINK_PUBLIC mailbox)
add_test(info info)
