function(LoadExternalFolder _LIST _FOLDER)
    file(GLOB_RECURSE LIST *.*)
    list(FILTER LIST INCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/${_FOLDER}/*" )
    #message(STATUS ${LIST})
    foreach(ITEM ${LIST})
            set_property(SOURCE ${ITEM} PROPERTY VS_SETTINGS "ExcludedFromBuild=true")
    endforeach()
    set(${_LIST} ${LIST} PARENT_SCOPE)
endfunction()

function(CreateMSVCPrecompiledHeader precompiledHeader precompiledSourceDir)
    set_source_files_properties(${precompiledSourceDir} PROPERTIES COMPILE_FLAGS "/Yc${precompiledHeader}")
endfunction()

function(UseMSVCPrecompiledHeader target precompiledHeader)
    set_target_properties(${target} PROPERTIES COMPILE_FLAGS "/Yu${precompiledHeader}")  
endfunction()

function(SetMSVCPrecompiledHeader target precompiledHeader precompiledSourceDir)
    CreateMSVCPrecompiledHeader(${precompiledHeader} ${precompiledSourceDir})
    UseMSVCPrecompiledHeader(${target} ${precompiledHeader})
endfunction()