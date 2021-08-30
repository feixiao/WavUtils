cmake_minimum_required(VERSION 3.2.0)
project(WAV_DEMO)


add_subdirectory(Classes)
add_subdirectory(Test)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Classes
        ${CMAKE_CURRENT_SOURCE_DIR}/Classes/WavReader
        ${CMAKE_CURRENT_SOURCE_DIR}/Classes/WavWriter
        ${CMAKE_CURRENT_SOURCE_DIR}/Test/WavReaderTester
        ${CMAKE_CURRENT_SOURCE_DIR}/Test/WavWriterTester
)

set(EXAMPLE_APP_NAME "wav-examples")

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "Android")
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../../../out/android/bin/${ANDROID_ABI})
else ()
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../../out/bin)
endif ()

set(EXECUTABLE_OUTPUT_PATH ${lib_output_path})

add_executable(${EXAMPLE_APP_NAME} ${SRC})

target_link_libraries(${EXAMPLE_APP_NAME} wav)
target_link_libraries(${EXAMPLE_APP_NAME} wav_tester)