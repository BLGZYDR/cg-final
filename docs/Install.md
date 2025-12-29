# How to Configure the Environment correctly 

> 请保证严格按照文档步骤进行，部分因 **平台差异和编译器差异** 导致的命令不尽相同，可以询问大模型得到合适的意见

Use CMake to build enviroment

```bash
mkdir build
cd build
cmake ..
```
> 如果这里 cmake .. 出现问题，请检查一下编译器是否为 MinGW 或 MSVC，使用 vscode / visual studio 的编译器一般为上述两者之一
如果构建失败
1. 请检查一下编译器是否为 MinGW 或 MSVC（使用 vscode / visual studio 的编译器一般为上述两者之一）
2. 解决问题以后，使用如下指令重新进行

```bash
cd ..
rm -r build
mkdir build
cd build
cmake .. -G "$<你的编译器>"
```

Compile

```bash
cmake --build .
```

Check whether the environment is available

- 方法一：点击 test/enviroment.cpp，使用 `ctrl + shift + B` 运行代码
- 方法二：在系统文件管理器中，点击并运行 build/bin/CG_Final_Project.exe

正常运行结果的截图如下：
[](/docs/attachment/run_enviroment.png)


# How to Run and Dev this Project

## 在 CMakeLists 中更改注释

1. 注释掉 `test/enviroment.cpp`
2. 取消掉 `${PROJECT_SOURCES}` 的注释

```txt
# 原文件
# 创建可执行文件
add_executable(${PROJECT_NAME} 
    test/enviroment.cpp
    # ${PROJECT_SOURCES} 
    ${IMGUI_SOURCES}
)

# 新文件
add_executable(${PROJECT_NAME} 
    # test/enviroment.cpp
    ${PROJECT_SOURCES} 
    ${IMGUI_SOURCES}
)
```

## 方法一：在 build 文件夹下使用 CMake 自动执行
```bash
cd build
cmake .. build
cmake --build .
```

## 方法二：使用 tools/run_project.py 自动执行
```bash
cd tools
python run_project.py
```

