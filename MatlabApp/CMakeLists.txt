# Minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Project name
project(MatlabApp)

# Find MATLAB
find_package(Matlab REQUIRED)

set(BUILD_MATLAB true)

if (BUILD_MATLAB)
    matlab_add_mex(
                NAME ${PROJECT_NAME}
                SRC
                main_matlab.cpp
                MatlabApp.cpp
                R2018a
            )
else() 
    add_executable(${PROJECT_NAME} main_exe.cpp MatlabApp.cpp)
endif()
target_link_libraries(${PROJECT_NAME} ImGuiApp)

        


# add symbolic link to resource folder to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_CURRENT_SOURCE_DIR}/resource $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource
    COMMENT "symbolic link resource folder from ${CMAKE_CURRENT_SOURCE_DIR}/resource to $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource"
)


# copy the resource folder to the build directory
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_CURRENT_SOURCE_DIR}/resource $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource
#     COMMENT "copy resource folder from ${CMAKE_CURRENT_SOURCE_DIR}/resource to $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource"
# )

