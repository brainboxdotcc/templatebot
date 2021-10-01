cmake_minimum_required (VERSION 3.6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(BOT_NAME "templatebot")

project(${BOT_NAME})
aux_source_directory("src" coresrc)
add_executable(${BOT_NAME} ${coresrc})

string(ASCII 27 Esc)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set_target_properties(${BOT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(DPP)
if(APPLE)
	set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
	find_package(OpenSSL REQUIRED)
else()
	find_package(OpenSSL REQUIRED)
endif()

target_include_directories(${BOT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(${BOT_NAME}
    dl
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_CRYPTO_LIBRARY} 
    ${OPENSSL_SSL_LIBRARY}
)

if (DPP_FOUND)
    target_link_libraries(${BOT_NAME} ${DPP_LIBRARIES})
    target_include_directories(${BOT_NAME} PUBLIC ${DPP_INCLUDE_DIR})
else()
    message(WARNING "Could not find DPP install. Building from source instead.")
    option(DPP_BUILD_TEST "" OFF)
    include(FetchContent)

    FetchContent_Declare(
            libdpp
            GIT_REPOSITORY https://github.com/brainboxdotcc/DPP.git
            GIT_TAG v9.0.6)

    FetchContent_GetProperties(libdpp)
    if(NOT libdpp_POPULATED)
        FetchContent_Populate(libdpp)
        target_include_directories(${BOT_NAME} PUBLIC
            ${libdpp_SOURCE_DIR}/include
        )
        add_subdirectory(
            ${libdpp_SOURCE_DIR}
            ${libdpp_BINARY_DIR}
            EXCLUDE_FROM_ALL)
    endif()

    target_link_libraries(${BOT_NAME} dpp)
endif()
