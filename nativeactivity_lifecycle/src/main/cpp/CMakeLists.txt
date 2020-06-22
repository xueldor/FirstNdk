# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)


#创建一个库，指定动态或静态，指定源文件
add_library(
        native-main
        SHARED
        NativeMain.cpp
        #file2.cpp
        #file3.cpp ...
        )

#将目标文件与依赖库文件进行链接
target_link_libraries( # Specifies the target library.
        native-main

        android
        log )
