cmake_minimum_required(VERSION 3.9)

project(cavegen VERSION 0.1.0 DESCRIPTION "generate caves from simplex noise")
add_library(cavegen SHARED
    cavegen.cpp
	thirdparty/SimplexNoise/src/SimplexNoise.cpp
)
set_target_properties(cavegen PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER cavegen.hpp
)

target_include_directories(cavegen PRIVATE . thirdparty/SimplexNoise/src )

include(GNUInstallDirs)

install(TARGETS cavegen
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

configure_file(cavegen.pc.in cavegen.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/cavegen.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)

enable_testing()
add_library(test_main OBJECT tests/test_main.cpp)
add_executable(test_floodfill tests/test_floodfill.cpp $<TARGET_OBJECTS:test_main>)
target_include_directories(test_floodfill PRIVATE . thirdparty/SimplexNoise/src )
configure_file(tests/caves.txt test_data/caves.txt COPYONLY)
link_directories( src )
target_link_libraries(test_floodfill cavegen)
add_test(NAME test_floodfill COMMAND test_floodfill)
