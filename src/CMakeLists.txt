include_directories("${CMAKE_SOURCE_DIR}/include")
add_compile_options(-W -Wall -Wextra -pipe -O2)

set(mailbox_SOURCES fd.c wrap_kernel.c wrap_hello.c wrap_ours.c)
add_library(mailbox        SHARED ${mailbox_SOURCES})
add_library(mailbox-static STATIC ${mailbox_SOURCES})
set_target_properties(mailbox-static PROPERTIES OUTPUT_NAME mailbox)

install(TARGETS mailbox        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(TARGETS mailbox-static ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
