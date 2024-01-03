cmake_minimum_required(VERSION 3.5)

project(Sql LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 设置可执行文件输出路径为 build 目录下
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

if(ANDROID)
  add_library(Sql SHARED
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    usermain.cpp
    usermain.h
    usermain.ui
    meowuser.cpp
    meowuser.h
    meowmessage.hpp
    meowmessage.cpp
  )
else()
  add_executable(Sql
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    usermain.cpp
    usermain.h
    usermain.ui
    meowuser.cpp
    meowuser.h
    meowmessage.hpp
    meowmessage.cpp
    InitSocket.hpp
    UserTalk.h
    UserTalk.cpp
    UserTalk.ui
    AddNewTalk.h
    AddNewTalk.cpp
    AddNewTalk.ui
    meowregister.hpp
    meowregister.cpp
    meowregister.ui
    MeowBase.h
    res.qrc
  )
endif()


target_link_libraries(Sql PRIVATE Qt5::Widgets)

target_link_libraries(Sql PRIVATE odbc32 ws2_32)
