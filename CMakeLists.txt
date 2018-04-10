cmake_minimum_required(VERSION 3.0)

project(mailbox)
include(CTest)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "libmailbox")
set(CPACK_PACKAGE_CONTACT "Sugizaki Yukimasa <ysugi@idein.jp>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
        "A wrapper library for Mailbox interface of Raspberry Pi")
set(CPACK_PACKAGE_VERSION_MAJOR 2)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
if ("${CPACK_PACKAGING_INSTALL_PREFIX}" STREQUAL "")
    set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
endif()
include(CPack)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)

configure_file(libmailbox.pc.in libmailbox.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libmailbox.pc"
        DESTINATION lib/pkgconfig)
