cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(GameKeeb CXX C)

pico_sdk_init()

# Adapted from https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
else()
    message("Git not found or not a git repo")
endif()

add_compile_definitions(
    GC_DATA_PIN=${GC_DATA_PIN}
    GC_3V3_PIN=${GC_3V3_PIN}
)

include_directories(
    include
    lib/joybus-pio/include
)

add_executable(GameKeeb
    src/main.cpp
    src/hid.c
    src/logic.cpp
    src/inputs.cpp
    src/keymap.cpp
    src/runtime_remapping.cpp
    lib/joybus-pio/src/GamecubeConsole.cpp
    lib/joybus-pio/src/joybus.c
)

target_link_libraries(GameKeeb
    pico_stdlib
    pico_multicore
    hardware_resets
    hardware_irq
    hardware_flash
    hardware_pio
    tinyusb_host
    tinyusb_board
)

pico_add_extra_outputs(GameKeeb)
