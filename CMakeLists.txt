cmake_minimum_required(VERSION 4.1.0)
project(modelgen VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

add_compile_options(-Wno-c23-extensions)

set(SOURCE_FILES 
	src/main.cpp
)
set_source_files_properties(${SOURCE_FILES} PROPERTIES
	COMPILE_OPTIONS "-fno-exceptions"
)

set(MODULE_FILES
	src/vendor/werelib/weretype.cppm
	src/core/modelgen.cppm
)
set_source_files_properties(${MODULE_FILES} PROPERTIES
	COMPILE_OPTIONS "-fno-exceptions"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE src/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE
	EMBED_ROOT=${CMAKE_CURRENT_SOURCE_DIR}/src/embed
)

target_sources(${PROJECT_NAME} PRIVATE
	FILE_SET cxx_modules TYPE CXX_MODULES FILES
		${MODULE_FILES}
)

target_link_libraries(
	${PROJECT_NAME} PRIVATE
)