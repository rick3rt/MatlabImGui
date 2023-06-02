include(FetchContent)

# =============================================================================
# FETCHCONTENT
# =============================================================================
# Dear ImGui -- imgui
# GIT_TAG 9aae45eb4a05a5a1f96be1ef37eb503a12ceb889 # 1.88
# GIT_TAG d7aca168eee54e1423e362384a3cfeec92b22563 # docking
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG d7aca168eee54e1423e362384a3cfeec92b22563 # docking
    SOURCE_DIR ${VENDOR_PATH}/imgui # to download to local dir
)
FetchContent_MakeAvailable(imgui)

# =================== IMGUI ===================
set(IMGUI_PATH ${VENDOR_PATH}/imgui)
add_library(imgui STATIC)
set(MYIMGUI_CONFIG "${VENDOR_PATH}/my_imgui_config.h")
target_compile_definitions(imgui PUBLIC IMGUI_USER_CONFIG="${MYIMGUI_CONFIG}")
target_sources(imgui
    PRIVATE
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/imgui.cpp
)

target_include_directories(imgui
    PUBLIC ${IMGUI_PATH}

    # ${CMAKE_CURRENT_SOURCE_DIR}/config
)

# =============================================================================
# ImPlot -- implot/0.14
# FetchContent_Declare(
# implot
# GIT_REPOSITORY https://github.com/epezent/implot
# GIT_TAG 15e494b76a78b44ae2c1b76608ff9bc39a661409 # 0.14
# SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/implot # to download to local dir
# )
# FetchContent_MakeAvailable(implot)

# =================== IMPLOT ===================
# set(IMPLOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/implot)
# add_library(IMPLOT STATIC)
# target_sources(IMPLOT
# PRIVATE
# ${IMPLOT_DIR}/implot.cpp
# ${IMPLOT_DIR}/implot_demo.cpp
# ${IMPLOT_DIR}/implot_items.cpp
# )

# target_include_directories(IMPLOT
# PUBLIC ${IMPLOT_DIR}
# )
# target_link_libraries(IMPLOT PUBLIC IMGUI)

# =============================================================================
# GLFW -- glfw/3.3.7
# GIT_TAG 7d5a16ce714f0b5f4efa3262de22e4d948851525 # 3.3.6
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 45ce5ddd197d5c58f50fdd3296a5131c894e5527 # 3.3.7
    SOURCE_DIR ${VENDOR_PATH}/glfw # to download to local dir
)
FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    # add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR} EXCLUDE_FROM_ALL)
    add_subdirectory(glfw EXCLUDE_FROM_ALL)
endif()

# =============================================================================
# GLEW -- glew/2.2.0
FetchContent_Declare(
    glew
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
    GIT_TAG f456deace7b408655109aaeff71421ef2d3858c6 # 2.2.0
    SOURCE_DIR ${VENDOR_PATH}/glew # to download to local dir
)
FetchContent_MakeAvailable(glew)

# add_subdirectory(glew)

# default repo without cmake stuff:
# GIT_REPOSITORY https://github.com/nigels-com/glew
# GIT_TAG 9fb23c3e61cbd2d581e33ff7d8579b572b38ee26 # 2.2.0

# =============================================================================
# STB
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
    SOURCE_DIR ${VENDOR_PATH}/stb # to download to local dir
)
FetchContent_MakeAvailable(stb)

# =============================================================================

# EIGEN
# FetchContent_Declare(
# eigen
# GIT_REPOSITORY https://gitlab.com/libeigen/eigen
# GIT_TAG 3147391d946bb4b6c68edd901f2add6ac1f31f8c # 3.4.0
# SOURCE_DIR ${VENDOR_PATH}/eigen # to download to local dir
# )
# FetchContent_MakeAvailable(eigen)
# add_subdirectory(eigen)

# =============================================================================

# # ADD CONTENT
# add_subdirectory(glew)

# set options for glfw
# set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs" FORCE) # https://stackoverflow.com/questions/20239334/cmake-set-subdirectory-options
# set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs" FORCE)
# set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation" FORCE)
# add_subdirectory(glfw EXCLUDE_FROM_ALL)

# option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
# option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" ON)
# option(GLFW_INSTALL "Generate installation target" OFF)
# option(GLFW_VULKAN_STATIC "Assume the Vulkan loader is linked with the application" OFF)

# OPTION(WITH_FUNCTION_X "enable X functionality" ON)
# set(WITH_FUNCTION_X OFF CACHE BOOL "enable X functionality")
# set(WITH_FUNCTION_X OFF CACHE BOOL "enable X functionality" FORCE)
# set(WITH_FUNCTION_X OFF CACHE INTERNAL "" FORCE)