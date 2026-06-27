cmake_minimum_required(VERSION 4.0)
project(lojo_utils VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "C:/ProgramData/mingw64/mingw64/bin/gcc.exe")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# option for building shared lib (defaults to ON, use -DBUILD_SHARED_LIBS=OFF to build a static library)
option(BUILD_SHARED_LIBS "Build using a shared library." ON)

# source code
set(LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/lojo_utils.c")

# building shared lib:
add_library(lojo_utils ${LIB_SRC})

# LOJO_UTILS_EXPORTS must be defined when building lojo_utils as a shared lib
target_compile_definitions(lojo_utils PRIVATE $<$<BOOL:${BUILD_SHARED_LIBS}>:LOJO_UTILS_EXPORTS>)

# include dirs
target_include_directories(lojo_utils PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# executable for testing!
add_executable(lojo_utils_test "${CMAKE_CURRENT_SOURCE_DIR}/example.c")
target_link_libraries(lojo_utils_test PRIVATE lojo_utils)

# installing LOJO_UTILS
install(TARGETS lojo_utils 
	EXPORT lojo_utils_targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT lojo_utils_targets
	FILE lojo_utils_targets.cmake
	NAMESPACE LOJO_UTILS::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lojo_utils)

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/lojo_utils_config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/lojo_utils_config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lojo_utils)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/lojo_utils_config_version.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/lojo_utils_config.cmake
	${CMAKE_CURRENT_BINARY_DIR}/lojo_utils_config_version.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lojo_utils)
