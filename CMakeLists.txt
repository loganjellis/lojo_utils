cmake_minimum_required(VERSION 4.0)
project(lojo_utils VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "C:/ProgramData/mingw64/mingw64/bin/gcc.exe")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(BUILD_SHARED_LIBS "Build using a shared library." ON)

function(add_c_library name)
	set(options)
	set(oneValueArgs INCLUDE_DIR TEST)
	set(multiValueArgs SOURCES)

	cmake_parse_arguments(CLIB "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	if(NOT CLIB_SOURCES)
		message(FATAL_ERROR "add_c_library(${name}) requires SOURCES")
	endif()

	add_library(${name} ${CLIB_SOURCES})

	target_compile_definitions(${name} PRIVATE $<$<BOOL:${BUILD_SHARED_LIBS}>:LOJO_CORE_UTILS_EXPORTS LOJO_STR_UTILS_EXPORTS>)

	target_include_directories(${name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${CLIB_INCLUDE_DIR}>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

	if(CLIB_TEST)
		add_executable(${name}_test ${CLIB_TEST})
		target_link_libraries(${name}_test PRIVATE ${name})
	endif()

	install(TARGETS ${name}
		EXPORT ${name}_targets
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

	install(DIRECTORY ${CLIB_INCLUDE_DIR}/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

	install(EXPORT ${name}_targets
		FILE ${name}_targets.cmake
		NAMESPACE ${name}::
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${name})
endfunction()

add_c_library(lojo_core_utils SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/lojo_core_utils.c" INCLUDE_DIR include)
add_c_library(lojo_str_utils SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/lojo_str_utils.c" INCLUDE_DIR include)

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

# executable for testing!
add_executable(lojo_utils_test "${CMAKE_CURRENT_SOURCE_DIR}/example.c")
target_link_libraries(lojo_utils_test PRIVATE lojo_core_utils lojo_str_utils)
