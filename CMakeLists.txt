# For CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required(VERSION 3.7.2)

project(mailbox)
include(CTest)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "libmailbox")
set(CPACK_PACKAGE_CONTACT "Sugizaki Yukimasa <ysugi@idein.jp>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
        "A wrapper library for Mailbox interface of Raspberry Pi")

# See https://semver.org/ and https://www.pakin.org/~scott/ltver.html .
set(CPACK_PACKAGE_VERSION_MAJOR 3)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 1)

# CMAKE_INSTALL_PREFIX and CPACK_PACKAGING_INSTALL_PREFIX must be identical
# because the install prefix is used in the pkg-config file which will be
# auto-generated.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "Install prefix" FORCE)
endif()
set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
message(STATUS "Install prefix is set to ${CMAKE_INSTALL_PREFIX}")
include(CPack)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)

configure_file(libmailbox.pc.in libmailbox.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libmailbox.pc"
        DESTINATION lib/pkgconfig)
