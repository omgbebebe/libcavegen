cmake_minimum_required(VERSION 3.9)
project(cavegen VERSION 0.1.0 DESCRIPTION "generate caves from simplex noise")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_library(simplexnoise SHARED
    thirdparty/SimplexNoise/src/SimplexNoise.cpp
)

add_library(cavegen SHARED
    cavegen.cpp
	#    thirdparty/SimplexNoise/src/SimplexNoise.cpp
)

target_link_libraries(cavegen simplexnoise)

set_target_properties(cavegen PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER cavegen.hpp
)

target_include_directories(cavegen PRIVATE . thirdparty/SimplexNoise/src )

include(GNUInstallDirs)

install(TARGETS cavegen simplexnoise
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
target_link_libraries(test_floodfill cavegen)
add_test(NAME test_floodfill COMMAND test_floodfill)

add_executable(example1 examples/example1.cpp)
target_include_directories(example1 PRIVATE .)
target_link_libraries(example1 cavegen)
