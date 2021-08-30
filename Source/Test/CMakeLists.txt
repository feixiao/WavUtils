cmake_minimum_required(VERSION 3.2.0)

project(wav_test_library)

#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Release CACHE STRING "set build type to release")

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    message(FATAL_ERROR "Please into another dir to build!")
endif ()

#string(TOUPPER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME)
if (CMAKE_SYSTEM_NAME MATCHES "Android")
    # xxx: -flto can't be used on NDK with gnustl_shared
    if (ANDROID_STL MATCHES "gnustl_shared")
        add_definitions("-Oz -g -DHAVE_NO_ATEXIT")
    else ()
        add_definitions("-O3 -flto")
    endif ()

    add_definitions("-DANDROID")
    add_definitions("-Wno-unused-command-line-argument")
    #	add_definitions("-Wno-invalid-source-encoding")
    add_definitions("-fdata-sections -ffunction-sections")
    string(APPEND CMAKE_CXX_FLAGS "-Qunused-arguments")
    set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    #	add_definitions("-Wno-invalid-source-encoding")
    add_definitions("-O2")
    set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_definitions("-Wno-invalid-source-encoding")
    add_definitions("-fdata-sections -ffunction-sections")
    add_definitions("-flto")
    add_definitions("-Os")
    set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_SHARED_LINKER_FLAGS "/DYNAMICBASE ws2_32.lib")
    set(WIN_OS true)
else ()
    message(FATAL_ERROR "unknown CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
endif ()


##############################################################################


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/WavReaderTester
        ${CMAKE_CURRENT_SOURCE_DIR}/WavWriterTester
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../Classes
        ${CMAKE_CURRENT_SOURCE_DIR}/../Classes/WavWriter
        ${CMAKE_CURRENT_SOURCE_DIR}/../Classes/WavReader
)


set(src ${CMAKE_CURRENT_SOURCE_DIR})
set(sources
        ${src}
        ${src}/WavReaderTester
        ${src}/WavWriterTester
        )

foreach (iter ${sources})
    aux_source_directory(${iter} lib_src)
endforeach ()

##############################################################################

if (${UNIX_OS})
    add_definitions(
            "-W"
            "-fPIC"
            "-Wall"
            "-Werror"
            "-Wshadow"
            "-Wformat"
            "-Wpointer-arith"
            "-D_REENTRANT"
            "-D_USE_FAST_MACRO"
            "-Wno-long-long"
            "-Wuninitialized"
            "-D_POSIX_PTHREAD_SEMANTICS"
            "-Wno-unused-parameter"
            "-fexceptions"
    )


    if (!CMAKE_BUILD_TYPE STREQUAL "RELEASE")
        add_definitions("-g")
    endif ()

elseif (${WIN_OS})
    aux_source_directory(${src}/stdlib/internal lib_src)
endif ()

if (CMAKE_SYSTEM_NAME MATCHES "Android")
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../../out/android/lib/${ANDROID_ABI})
else ()
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../../out/lib)
endif ()

#set(LIBRARY_OUTPUT_PATH ${lib_output_path})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${lib_output_path})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${lib_output_path})

add_library(wav_tester STATIC ${lib_src})
