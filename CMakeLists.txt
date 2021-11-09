# For CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required(VERSION 3.7.2)

project(libmailbox VERSION 3.1.1 LANGUAGES C
        DESCRIPTION "A wrapper library for Mailbox interface of Raspberry Pi")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "Yukimasa Sugizaki <ysugi@idein.jp>")
set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_DEPENDS libc6)

# CMAKE_INSTALL_PREFIX and CPACK_PACKAGING_INSTALL_PREFIX must be identical
# because the install prefix is used in the pkg-config file which will be
# auto-generated.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "Install prefix" FORCE)
endif()
set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
message(STATUS "Install prefix is set to ${CMAKE_INSTALL_PREFIX}")

include(CPack)

include(GNUInstallDirs)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)

configure_file(libmailbox.pc.in libmailbox.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libmailbox.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
