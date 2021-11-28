include(CTest)

if (NOT BUILD_TESTING)
    return()
endif ()

include_directories("${CMAKE_SOURCE_DIR}/include")
add_compile_options(-W -Wall -Wextra -pipe -O2)

add_executable(info info.c)
target_link_libraries(info LINK_PUBLIC mailbox)
add_test(Info info)

add_executable(memflag memflag.c)
target_link_libraries(memflag LINK_PUBLIC mailbox)
add_test(MemFlag memflag)
