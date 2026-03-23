cmake_minimum_required(VERSION 4.1.0)
project(modelgen VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_executable(${PROJECT_NAME}
	src/main.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
	FILE_SET cxx_modules TYPE CXX_MODULES FILES
		src/vendor/werelib/weretype.cppm
		src/vendor/werelib/werevec.cppm
		src/core/modelgen.cppm
		src/core/doorgen.cppm
		src/core/hinge.cppm
		src/core/direction.cppm
		src/core/vrtx/vrtx.cppm
)

target_include_directories(${PROJECT_NAME} PRIVATE src/include)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	EMBED_ROOT=${CMAKE_CURRENT_SOURCE_DIR}/src/embed
)

target_compile_options(${PROJECT_NAME} PRIVATE
	-fno-exceptions
	-Wno-c23-extensions
)