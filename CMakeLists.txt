cmake_minimum_required (VERSION 3.15)

project (Sonic_The_Hedgehog_project)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/permissive-)
endif ()

add_executable (Sonic_The_Hedgehog_project WIN32 "")

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources/images)
add_subdirectory (resources/sounds)
add_subdirectory (resources/texts)
add_subdirectory (resources/font)
add_subdirectory (external/box2d/src)

set (SFML_STATIC_LIBRARIES TRUE)
set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")

configure_file (C:/SFML/SFML-2.5.1/bin/openal32.dll ${CMAKE_BINARY_DIR} COPYONLY)

find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_link_libraries (Sonic_The_Hedgehog_project sfml-graphics  sfml-audio  sfml-main)
target_link_libraries (Sonic_The_Hedgehog_project box2d)
