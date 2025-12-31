cmake_minimum_required(VERSION 3.15)
project(CG_Final_Project)
# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置编译器模式为 Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# ===================== 编译器自动检测 =====================
# 区分 MSVC（VS）和 GNU（MinGW）
if (MSVC)
    set(IS_MSVC ON)
    set(IS_MINGW OFF)
    message(STATUS "Detected compiler: MSVC (Visual Studio)")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(IS_MSVC OFF)
    set(IS_MINGW ON)
    message(STATUS "Detected compiler: GNU (MinGW)")
else()
    message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}, fallback to MinGW config")
    set(IS_MSVC OFF)
    set(IS_MINGW ON)
endif()


# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 查找OpenGL
find_package(OpenGL REQUIRED)

# 下载GLFW和ImGui
include(FetchContent)
FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# 禁用GLFW的示例、测试、文档（减少编译时间）
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    imgui
    URL https://github.com/ocornut/imgui/archive/refs/tags/v1.90.4.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.0.zip 
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(glm)

# FetchContent_Declare(
#     glad
#     URL https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.6.zip
#     DOWNLOAD_EXTRACT_TIMESTAMP TRUE
# )
# FetchContent_MakeAvailable(glad)

# # 使用 Glad 官方的 CMake 接口
# add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
# glad_add_library(glad_gl_core_33 
#     REPRODUCIBLE 
#     API gl:core=3.3
# )

# ImGui源文件
set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# 递归查找 src 目录下的所有 C/C++ 源文件（.cpp/.cxx/.cc/.c）
file(GLOB_RECURSE PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.cxx
    ${CMAKE_SOURCE_DIR}/src/*.cc
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# 创建可执行文件
add_executable(${PROJECT_NAME} 
    test/enviroment.cpp
    # ${PROJECT_SOURCES} 
    ${IMGUI_SOURCES}
)

# 获取 src 下所有目录头文件
set(PROJECT_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/src/Common/
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_SOURCE_DIR}/src/House
    ${CMAKE_SOURCE_DIR}/src/Terrian
    ${CMAKE_SOURCE_DIR}/src/Skybox
    ${CMAKE_SOURCE_DIR}/src/Scene
)

# 包含目录：添加OpenGL自动识别的头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${glm_SOURCE_DIR}
    ${PROJECT_INCLUDE_DIRS}    
    # $<TARGET_PROPERTY:glad_gl_core_33,INTERFACE_INCLUDE_DIRECTORIES>
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL  # OpenGL核心库
    glfw        # GLFW库
    glu32.lib
    opengl32.lib
    glm::glm    # GLM 库
    # glad_gl_core_33
)

# 设置编译定义
target_compile_definitions(${PROJECT_NAME} PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLFW
    # IMGUI_IMPL_OPENGL_LOADER_GLAD
)

# 复制 DLL 文件
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:glfw>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
