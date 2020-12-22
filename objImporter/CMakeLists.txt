set(LIB_NAME  objImporter) 
add_library("${LIB_NAME}" "") 
target_include_directories("${LIB_NAME}" PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>" 
    "$<INSTALL_INTERFACE:include>" #${CMAKE_INSTALL_PREFIX}/include 
) 
if(NOT BUILD_SHARED_LIBS) 
    set(STATIC_POSTFIX "-s") 
endif() 
set_target_properties("${LIB_NAME}" PROPERTIES 
    DEBUG_POSTFIX "-d" 
    RELEASE_POSTFIX "" 
    MINSIZEREL_POSTFIX "-mr" 
    RELWITHDEBUGINFO_POSTFIX "-rd" 
) 
include("GenerateExportHeader") 
generate_export_header("${LIB_NAME}") 
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}_export.h" DESTINATION "include") 
add_subdirectory("include") 
add_subdirectory("src") 
target_link_libraries( 
   "${LIB_NAME}" 
) 
