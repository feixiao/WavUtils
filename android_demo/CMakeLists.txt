cmake_minimum_required(VERSION 3.2.0)
project(WAV_READER_DEMO)


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../Source/Classes
        ${CMAKE_CURRENT_SOURCE_DIR}/../Source/Classes/WavReader
        ${CMAKE_CURRENT_SOURCE_DIR}/../Source/Classes/WavWriter
)

set(EXAMPLE_APP_NAME "wav-reader-examples")

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "Android")
    set(exe_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../out/android/bin/${ANDROID_ABI})
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../out/android/lib/${ANDROID_ABI})
else ()
    set(exe_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../out/bin)
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../out/lib)
endif ()

set(EXECUTABLE_OUTPUT_PATH ${exe_output_path})
link_libraries(${lib_output_path}/libwav.a)

add_executable(${EXAMPLE_APP_NAME} ${SRC})