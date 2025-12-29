# cg-final
2025年中山大学计算机图形学作业

## 📚 Ready to Development
建议首先阅读并完善 [docs](/docs) 中的文档

关于使用 GitHub 合作的注意事项，请阅读 [Git_Guide.md](/docs/Git_Guide.md) 和 [PR_WorkFlow.md](/docs/PR_WorkFlow.md)

## ⚙️ Environment

- 本项目针对中山大学计算机图形学作业的开发需求，基于 CMake 实现了 OpenGL+ImGui+GLFW+GLM 的自动配置环境。
- 项目根目录已预设完成 CMakeLists.txt 配置，无需手动处理库的链接与路径配置，仅需在对应 IDE 中完成简单初始化即可开发。

已兼容的 IDE 确定有 vscode / visual studio，已兼容的 编译器 确定有 MinGW / MSVC


## 🛠️ Installation

Clone this repo:

```
git clone https://github.com/Super-Gluten/cg-final.git
```

- 关于环境配置的详细信息和配置步骤，请阅读 [Install.md](/docs/Install.md)

- 关于模型配置参数，请于都 [Model_Instruction.md](/docs/Model_Instruction.md)

- 关于运行项目，可以使用 `python tools/run_project.py` 命令运行

## 🔤 Encoding Specification
> 重要：为避免中文乱码、编译异常、协作冲突等问题，本项目**强制要求所有文件使用 UTF-8 编码格式**，禁止使用 GBK（包括 GB2312、GB18030 等衍生中文编码）。

关于解决文件编码的问题，请阅读 [Encoding_Problem_Solutions.md](/docs/Encoding_Problem_Solutions.md)


## 📂 概览

以下为项目结构示例：

```
.
├─docs/                        
│   ├── Git_Guide.md           # Github 命令行使用手册
│   ├── Install.md             # 安装环境文档
│   └── PR_WorkFlow.md         # PR和协作手册
|
├─src/                         
│   ├── Buildings/             # 建筑相关功能模块
|   |   ├── include/
|   |   └── src/  
|   |
│   ├── Light_System/          # 光照系统功能模块
|   |   ├── include/
|   |   └── src/  
|   |
│   ├── Scene_Component/       # 场景部件功能模块
|   |   ├── include/
|   |   └── src/  
|   |
│   └── main.cpp               
|
├─test/                        
│   └── environment.cpp        # 环境检测功能代码
├─tools/
|   ├── gbk_to_uft8.py         # 编码转换辅助代码
│   └── run_project.py         # 自动化运行项目代码
|
├── CMakeLists.txt             # CMake 项目构建配置文件
```