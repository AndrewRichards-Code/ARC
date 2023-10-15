cmake_minimum_required(VERSION 3.27)

include("src/CMakeFunctions.cmake")

file(DOWNLOAD 
	https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp
	EXPECTED_HASH SHA256=665fa14b8af3837966949e8eb0052d583e2ac105d3438baba9951785512cf921
	"${CMAKE_CURRENT_SOURCE_DIR}/External/json/json.hpp"
)
file(DOWNLOAD 
	https://github.com/Neargye/magic_enum/releases/download/v0.9.3/magic_enum.hpp
	"${CMAKE_CURRENT_SOURCE_DIR}/External/magic_enum/magic_enum.hpp"
)

#Files
set(HEADERS 
	"src/ConsoleOutputColours.h"
	"src/DateAndTime.h"
	"src/DebugMacros.h"
	"src/DynamicLibrary.h"
	"src/EnumClassBitwiseOperators.h"
	"src/ExportAttributes.h"
	"src/FileLoader.h"
	"src/FileSaver.h"
	"src/Helpers.h"
	"src/Log.h"
	"src/ScopeAndRef.h"
	"src/StringConversion.h"
	"src/VisualStudioDebugOutput.h"
	"src/WindowsErrorHandling.h"
	"src/WindowsVersionMacro.h"
)
set(CPP_FILES 
	"src/ConsoleOutputColours.cpp"
	"src/DateAndTime.cpp"
	"src/DynamicLibrary.cpp"
	"src/FileLoader.cpp"
	"src/FileSaver.cpp"
	"src/Log.cpp"
	"src/StringConversion.cpp"
	"src/VisualStudioDebugOutput.cpp"
	"src/WindowsErrorHandling.cpp"
)
set(CMAKE_FILES
	"src/CMakeFunctions.cmake"
)
set(JSON_HEADERS 
	"External/json/json.hpp"
)
set(MAGIC_ENUM_HEADERS 
	"External/magic_enum/magic_enum.hpp"
)

add_library(ARC STATIC)

target_sources(ARC PRIVATE ${CPP_FILES} ${HEADERS} ${CMAKE_FILES} ${MAGIC_ENUM_HEADERS} ${JSON_HEADERS})

source_group("src" FILES ${CPP_FILES} ${HEADERS} ${CMAKE_FILES})
source_group("External\\json" FILES ${JSON_HEADERS})
source_group("External\\magic_enum" FILES ${MAGIC_ENUM_HEADERS})