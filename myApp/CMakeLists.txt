project(myApp VERSION 1.0.0 LANGUAGES CXX)

# find_package(OpenMP 2.0 REQUIRED)
set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/resource")

# define sources for myApp
set(SRCS_TO_BUILD
    ${PROJECT_SOURCE_DIR}/src/main.cpp

    # ${PROJECT_SOURCE_DIR}/src/Application.cpp
    ${PROJECT_SOURCE_DIR}/src/Renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/VertexBuffer.cpp
    ${PROJECT_SOURCE_DIR}/src/IndexBuffer.cpp
    ${PROJECT_SOURCE_DIR}/src/VertexArray.cpp
    ${PROJECT_SOURCE_DIR}/src/Shader.cpp
    ${PROJECT_SOURCE_DIR}/src/image_helper.cpp

    # ${PROJECT_SOURCE_DIR}/src/Demo.cpp
    ${VENDOR_PATH}/imgui/backends/imgui_impl_glfw.cpp # imgui backend
    ${VENDOR_PATH}/imgui/backends/imgui_impl_opengl3.cpp # imgui backend

    # ${PROJECT_SOURCE_DIR}/src/FrameBuffer.cpp
)

# Create the executable
add_executable(${PROJECT_NAME}
    ${SRCS_TO_BUILD}
)
target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_USER_CONFIG="${VENDOR_PATH}/my_imgui_config.h")

# include dirs
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${VENDOR_PATH}/imgui
    PUBLIC ${VENDOR_PATH}/imgui/backends
    PUBLIC ${VENDOR_PATH}/glew/include
    PUBLIC ${VENDOR_PATH}/stb
    PUBLIC ${GLFW_INCLUDE_DIR}
)

# target_link_directories(${PROJECT_NAME}
# PRIVATE ${CMAKE_SOURCE_DIR}/lib/glfw/src
# )
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    glfw libglew_static
    imgui # IMPLOT
)

# COPY RES
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_PATH} $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource/
)

# FILE(COPY ${CMAKE_SOURCE_DIR}/resources/Roboto-Medium.ttf DESTINATION "${CMAKE_BINARY_DIR}")

# we don't want to copy if we're building in the source dir
# list of files for which we add a copy rule
# set(data_SHADOW Roboto-Medium.ttf)

# foreach(item IN LISTS data_SHADOW)
# message(STATUS ${item})
# message(STATUS ${CMAKE_SOURCE_DIR}/resources/${item})
# message(STATUS ${CMAKE_CURRENT_BINARY_DIR}/${item})
# add_custom_command(

# OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
# COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/resources/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
# DEPENDS "${CMAKE_SOURCE_DIR}/resources/${item}"
# )
# endforeach()

# # files are only copied if a target depends on them
# add_custom_target(data-target ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Roboto-Medium.ttf")

# https://www.reddit.com/r/cmake/comments/gmewhu/copy_one_file_in_src_directory_to_build_directory/
# # Copy <filename> to build directory
# set(copy_source_dir "${CMAKE_SOURCE_DIR}/src/<path>")
# set(copy_dest_dir "${CMAKE_BINARY_DIR}/Build/<path>/$<CONFIG>")
# set(copy_file_name "<filename>")
# add_custom_command(
# TARGET ${PROJECT_NAME} POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E make_directory ${copy_dest_dir}
# )
# add_custom_command(
# TARGET ${PROJECT_NAME} POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E copy "${copy_source_dir}/${copy_file_name}" "${copy_dest_dir}/${copy_file_name}"
# COMMENT "Copying ${copy_file_name} to build directory"
# )