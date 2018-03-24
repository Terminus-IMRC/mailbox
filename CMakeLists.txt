cmake_minimum_required(VERSION 3.0)

project(mailbox)
include(CTest)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "libmailbox")
set(CPACK_PACKAGE_CONTACT "Sugizaki Yukimasa <ysugi@idein.jp>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
        "A wrapper library for Mailbox interface of Raspberry Pi")
set(CPACK_PACKAGE_VERSION_MAJOR 2)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
include(CPack)
