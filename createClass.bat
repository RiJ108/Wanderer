@echo off
set /p id="Enter class name : "
mkdir %id%
cd %id%
mkdir include
mkdir src

echo set(LIB_NAME  %id%) >> CMakeLists.txt
echo add_library("${LIB_NAME}" "") >> CMakeLists.txt
echo target_include_directories("${LIB_NAME}" PUBLIC >> CMakeLists.txt
echo     "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" >> CMakeLists.txt
echo     "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>" >> CMakeLists.txt
echo     "$<INSTALL_INTERFACE:include>" #${CMAKE_INSTALL_PREFIX}/include >> CMakeLists.txt
echo ) >> CMakeLists.txt
echo if(NOT BUILD_SHARED_LIBS) >> CMakeLists.txt
echo     set(STATIC_POSTFIX "-s") >> CMakeLists.txt
echo endif() >> CMakeLists.txt
echo set_target_properties("${LIB_NAME}" PROPERTIES >> CMakeLists.txt
echo     DEBUG_POSTFIX "-d" >> CMakeLists.txt
echo     RELEASE_POSTFIX "" >> CMakeLists.txt
echo     MINSIZEREL_POSTFIX "-mr" >> CMakeLists.txt
echo     RELWITHDEBUGINFO_POSTFIX "-rd" >> CMakeLists.txt
echo ) >> CMakeLists.txt
echo include("GenerateExportHeader") >> CMakeLists.txt
echo generate_export_header("${LIB_NAME}") >> CMakeLists.txt
echo install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}_export.h" DESTINATION "include") >> CMakeLists.txt
echo add_subdirectory("include") >> CMakeLists.txt
echo add_subdirectory("src") >> CMakeLists.txt
echo target_link_libraries( >> CMakeLists.txt
echo    "${LIB_NAME}" >> CMakeLists.txt
echo ) >> CMakeLists.txt

cd include
mkdir %id%

echo set(FILES "") >> CMakeLists.txt
echo set(SUBDIRECTORIES "${LIB_NAME}") >> CMakeLists.txt
echo set(RELATIVE_PATH "include") >> CMakeLists.txt

echo #Add all subdirectories >> CMakeLists.txt
echo foreach(VAR ${SUBDIRECTORIES}) >> CMakeLists.txt
echo     add_subdirectory(${VAR}) >> CMakeLists.txt
echo endforeach() >> CMakeLists.txt

echo if(FILES) >> CMakeLists.txt
echo     #Add source files to target >> CMakeLists.txt
echo     target_sources("${LIB_NAME}" PRIVATE ${FILES}) >> CMakeLists.txt

echo     #Install our source files >> CMakeLists.txt
echo     install(FILES ${FILES} DESTINATION ${RELATIVE_PATH}) >> CMakeLists.txt
echo endif() >> CMakeLists.txt

cd %id%
echo #ifndef >> %id%.hpp
echo #define >> %id%.hpp
echo #endif >> %id%.hpp

echo set(FILES "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}.hpp") >> CMakeLists.txt
echo set(SUBDIRECTORIES "") >> CMakeLists.txt
echo set(RELATIVE_PATH "include/${LIB_NAME}") >> CMakeLists.txt

echo #Add all subdirectories >> CMakeLists.txt
echo foreach(VAR ${SUBDIRECTORIES}) >> CMakeLists.txt
echo     add_subdirectory(${VAR}) >> CMakeLists.txt
echo endforeach() >> CMakeLists.txt

echo if(FILES) >> CMakeLists.txt
echo     #Add source files to target >> CMakeLists.txt
echo     target_sources("${LIB_NAME}" PRIVATE ${FILES}) >> CMakeLists.txt

echo     #Install our source files >> CMakeLists.txt
echo     install(FILES ${FILES} DESTINATION ${RELATIVE_PATH}) >> CMakeLists.txt
echo endif() >> CMakeLists.txt

cd ..
cd ..

cd src
mkdir %id%

echo set(FILES "") >> CMakeLists.txt
echo set(SUBDIRECTORIES "${LIB_NAME}") >> CMakeLists.txt
echo set(RELATIVE_PATH "src") >> CMakeLists.txt

echo #Add all subdirectories >> CMakeLists.txt
echo foreach(VAR ${SUBDIRECTORIES}) >> CMakeLists.txt
echo     add_subdirectory(${VAR}) >> CMakeLists.txt
echo endforeach() >> CMakeLists.txt

echo if(FILES) >> CMakeLists.txt
echo     #Add source files to target >> CMakeLists.txt
echo     target_sources("${LIB_NAME}" PRIVATE ${FILES}) >> CMakeLists.txt

echo     #Install our source files >> CMakeLists.txt
echo     install(FILES ${FILES} DESTINATION ${RELATIVE_PATH}) >> CMakeLists.txt
echo endif() >> CMakeLists.txt

cd %id%

echo #include "%id%/%id%.hpp">> %id%.cpp

echo set(FILES "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}.cpp") >> CMakeLists.txt
echo set(SUBDIRECTORIES "") >> CMakeLists.txt
echo set(RELATIVE_PATH "src/${LIB_NAME}") >> CMakeLists.txt

echo #Add all subdirectories >> CMakeLists.txt
echo foreach(VAR ${SUBDIRECTORIES}) >> CMakeLists.txt
echo     add_subdirectory(${VAR}) >> CMakeLists.txt
echo endforeach() >> CMakeLists.txt

echo if(FILES) >> CMakeLists.txt
echo     #Add source files to target >> CMakeLists.txt
echo     target_sources("${LIB_NAME}" PRIVATE ${FILES}) >> CMakeLists.txt

echo     #Install our source files >> CMakeLists.txt
echo     install(FILES ${FILES} DESTINATION ${RELATIVE_PATH}) >> CMakeLists.txt
echo endif() >> CMakeLists.txt

cd ..
cd ..
cd ..