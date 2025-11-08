cmake_minimum_required(VERSION 3.16)
project(CoffeeQuality LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt meta-object compiler
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find Qt6 libraries
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt6_standard_project_setup()

qt6_add_executable(CoffeeQuality
    main.cpp
    functions.cpp
    functions.h
)

target_link_libraries(CoffeeQuality
    PRIVATE
    Qt6::Core
    Qt6::Widgets
)

set_target_properties(CoffeeQuality PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

if (APPLE)
    set_target_properties(CoffeeQuality PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "edu.ufl.CoffeeQuality"
        XCODE_ATTRIBUTE_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()
