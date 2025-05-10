cmake_minimum_required(VERSION 3.16)
project(wifi_manager_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ESP-IDF/Arduino as component
set(EXTRA_COMPONENT_DIRS "${CMAKE_SOURCE_DIR}/../components")

# Find Boost (header-only for ESP32)
set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/../components/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
find_package(Boost 1.71.0 REQUIRED)

# Source files
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${BOOST_INCLUDEDIR}
)

target_link_libraries(${PROJECT_NAME}
    idf::wifi
    idf::freertos
    idf::nvs_flash
)

# Print Boost include dir for debug
message(STATUS "Boost include dir: ${BOOST_INCLUDEDIR}")
