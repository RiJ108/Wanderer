set(FILES "") 
set(SUBDIRECTORIES "${LIB_NAME}") 
set(RELATIVE_PATH "include") 
#Add all subdirectories 
foreach(VAR ${SUBDIRECTORIES}) 
    add_subdirectory(${VAR}) 
endforeach() 
if(FILES) 
    #Add source files to target 
    target_sources("${LIB_NAME}" PRIVATE ${FILES}) 
    #Install our source files 
    install(FILES ${FILES} DESTINATION ${RELATIVE_PATH}) 
endif() 
