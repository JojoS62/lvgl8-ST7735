# Copyright (c) 2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.0)

# this would advise cmake to create larger object pathes, 
# but Ninja for Windows cannot handle path >260 chars
# set(CMAKE_OBJECT_PATH_MAX 512)

set(MBED_MEMAP_DEPTH 4)
set(MBED_MEMAP_CREATE_JSON false)

set(USE_SHARED_LIB_STRUCT true)
set(LVGL_STATIC true)

if (${USE_SHARED_LIB_STRUCT})
    set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../mbed-os CACHE INTERNAL "")
    set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
    set(LIB_PATH "../../libs/")
    set(CUSTOM_TARGETS_PATH "../../custom_targets/")

    include(${MBED_PATH}/tools/cmake/app.cmake)

    set(APP_TARGET lvgl8-ST7735)
    project(${APP_TARGET})

    add_executable(${APP_TARGET}
        main.cpp
    )

    target_include_directories(${APP_TARGET} 
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}
        )


    if (${LVGL_STATIC})
        add_subdirectory(${LIB_PATH}lvgl lvgl)
        target_compile_options(lvgl PRIVATE -O3)
        target_compile_definitions(lvgl PRIVATE LV_CONF_INCLUDE_SIMPLE )
        target_compile_definitions(lvgl_examples PRIVATE  LV_CONF_INCLUDE_SIMPLE LV_DEMO_CONF_INCLUDE_SIMPLE)
        target_include_directories(lvgl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    else()
        set(MICROPY_DIR true)           # force lvgl to create an interface lib
        add_subdirectory(${LIB_PATH}lvgl lvgl)
        add_library(lvgl ALIAS lvgl_interface)   # for compatibility with static/interface libs
    endif()
    list(APPEND EXTRA_LIBS lvgl)
    list(APPEND EXTRA_INCLUDES "${LIB_PATH}lvgl")

    add_subdirectory(${LIB_PATH}lvglDriver lvglDriver)
    target_compile_definitions(lvglDriver PRIVATE LV_CONF_INCLUDE_SIMPLE)
    list(APPEND EXTRA_LIBS lvglDriver)     # interface lib

    add_subdirectory(${CUSTOM_TARGETS_PATH} ./custom_targets)     # interface lib

    add_subdirectory(${MBED_PATH} ${CMAKE_CURRENT_BINARY_DIR}/mbed-os)

    target_link_libraries(${APP_TARGET}
        PRIVATE
            mbed-os
            ${EXTRA_LIBS}
        )

    target_include_directories(${APP_TARGET} 
        PRIVATE 
            ${EXTRA_INCLUDES}
        )

    mbed_set_post_build(${APP_TARGET})

    option(VERBOSE_BUILD "Have a verbose build process")
    if(VERBOSE_BUILD)
        set(CMAKE_VERBOSE_MAKEFILE ON)
    endif()
else()
    set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
    set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
    set(LIB_PATH "")
    set(CUSTOM_TARGETS_PATH "custom_targets")

    include(${MBED_PATH}/tools/cmake/app.cmake)

    set(APP_TARGET lvgl8-ST7735)
    project(${APP_TARGET})

    add_executable(${APP_TARGET}
        main.cpp
    )

    add_subdirectory(${MBED_PATH})

    if (${LVGL_STATIC})
        add_subdirectory(${LIB_PATH}lvgl)
        target_compile_options(lvgl PRIVATE -Os)
    else()
        set(MICROPY_DIR true)           # force lvgl to create an interface lib
        add_subdirectory(${LIB_PATH}lvgl)
        add_library(lvgl ALIAS lvgl_interface)   # for compatibility with static/interface libs
    endif()
    list(APPEND EXTRA_LIBS lvgl)
    list(APPEND EXTRA_INCLUDES "${LIB_PATH}lvgl")


    add_subdirectory(${LIB_PATH}lvglDriver)
    list(APPEND EXTRA_LIBS lvglDriver)     # interface lib
    list(APPEND EXTRA_INCLUDES "${LIB_PATH}lvglDriver")

    add_subdirectory(${CUSTOM_TARGETS_PATH})     # interface lib

    target_link_libraries(${APP_TARGET}
        PRIVATE
            mbed-os
            ${EXTRA_LIBS}
        )

    target_include_directories(${APP_TARGET} 
        PRIVATE 
            "."
            ${EXTRA_INCLUDES}
        )

    mbed_set_post_build(${APP_TARGET})

    option(VERBOSE_BUILD "Have a verbose build process")
    if(VERBOSE_BUILD)
        set(CMAKE_VERBOSE_MAKEFILE ON)
    endif()
endif()

