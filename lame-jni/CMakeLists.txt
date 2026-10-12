cmake_minimum_required(VERSION 3.18)
project(mp3lame_jni C)

file(GLOB LAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/lame/libmp3lame/*.c)

add_library(mp3lame_jni SHARED mp3_jni.c ${LAME_SOURCES})
target_include_directories(mp3lame_jni PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lame
        ${CMAKE_CURRENT_SOURCE_DIR}/lame/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lame/libmp3lame)
target_compile_definitions(mp3lame_jni PRIVATE HAVE_CONFIG_H)
target_compile_options(mp3lame_jni PRIVATE -O2 -w -fno-strict-aliasing)
target_link_libraries(mp3lame_jni m)
# 16 KB page size support (required by Google Play for Android 15+ devices).
target_link_options(mp3lame_jni PRIVATE "-Wl,-z,max-page-size=16384")
