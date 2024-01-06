include_guard()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(MSVC)
	set(CXX_FLAGS "/EHsc /JMC /MP")

	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug>:EditAndContinue>$<$<CONFIG:Release>:ProgramDatabase>")

	#Release
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DNDEBUG ${CXX_FLAGS}") #Complier
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE  "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG") #Linker EXE
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG") #Linker DLL
	set(CMAKE_STATIC_LINKER_FLAGS_RELEASE  "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /DEBUG") #Linker LIB

	#Debug
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS}") #Complier
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}") #Linker EXE
	set(CMAKE_SHARED_LINKER_FLAGSDEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}") #Linker DLL
	set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG}") #Linker LIB
endif()

set(CONFIG_NAME "$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>")

function(LoadExternalFolder _LIST _FOLDER)
	file(GLOB_RECURSE LIST *.*)
	list(FILTER LIST INCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/${_FOLDER}/*" )
	foreach(ITEM ${LIST})
		set_property(SOURCE ${ITEM} PROPERTY VS_SETTINGS "ExcludedFromBuild=true")
	endforeach()
	set(${_LIST} ${LIST} PARENT_SCOPE)
endfunction()

function(CopyToBinaryDirPostBuild target file subPath)
	add_custom_command(TARGET ${target} POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${target}>/${subPath}")
	add_custom_command(TARGET ${target} POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy ${file} "$<TARGET_FILE_DIR:${target}>/${subPath}")
endfunction()

function(CopyToBuildDirPostBuild target file subPath)
	add_custom_command(TARGET ${target} POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/${subPath}")
	add_custom_command(TARGET ${target} POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy ${file} "${CMAKE_BINARY_DIR}/${subPath}")
endfunction()