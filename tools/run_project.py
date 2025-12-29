import os
import subprocess
import sys

# 如果是Windows，尝试将控制台代码页改为UTF-8
if sys.platform.startswith('win'):
    subprocess.run('chcp 65001', shell=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    # 设置标准输出的编码为UTF-8
    sys.stdout.reconfigure(encoding='utf-8')

def run_command(command, cwd=None):
    """运行命令并打印输出"""
    print(f"执行命令: {command}")
    result = subprocess.run(command, shell=True, cwd=cwd, capture_output=True, text=True)
    
    if result.stdout:
        print("输出:", result.stdout)
    if result.stderr:
        print("错误:", result.stderr)
    
    return result.returncode

def main():
    # 获取脚本所在目录
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # 项目根目录是脚本目录的父目录（因为脚本在tools文件夹中）
    project_root = os.path.dirname(script_dir)
    
    build_dir = os.path.join(project_root, "build")
    exe_path = os.path.join(build_dir, "bin", "CG_Final_Project.exe")
    
    print("=" * 50)
    print("开始构建和运行项目...")
    print(f"脚本位置: {script_dir}")
    print(f"项目根目录: {project_root}")
    print("=" * 50)
    
    # 1. 进入build目录（如果不存在则创建）
    if not os.path.exists(build_dir):
        print(f"创建构建目录: {build_dir}")
        os.makedirs(build_dir)
    
    # 2. 运行cmake配置
    print("\n[步骤1] 运行CMake配置...")
    ret_code = run_command("cmake ..", cwd=build_dir)
    if ret_code != 0:
        print("CMake配置失败!")
        sys.exit(1)
    
    # 3. 构建项目
    print("\n[步骤2] 构建项目...")
    ret_code = run_command("cmake --build .", cwd=build_dir)
    if ret_code != 0:
        print("构建失败!")
        sys.exit(1)
    
    # 5. 运行可执行文件
    print("\n[步骤3] 运行可执行文件...")
    if os.path.exists(exe_path):
        print(f"找到可执行文件: {exe_path}")
        print("=" * 50)
        print("程序输出:")
        print("=" * 50)
        
        # 运行程序
        subprocess.run([exe_path], cwd=os.path.dirname(exe_path))
    else:
        print(f"错误: 找不到可执行文件 CG_Final_Project.exe")
        print("在以下位置查找:")
        print(f"- {os.path.join(build_dir, 'bin', 'CG_Final_Project.exe')}")
        print(f"- {os.path.join(build_dir, 'CG_Final_Project.exe')}")
        print("\n尝试在build目录中查找.exe文件...")
        for root, dirs, files in os.walk(build_dir):
            for file in files:
                if file.endswith(".exe"):
                    print(f"找到: {os.path.join(root, file)}")

if __name__ == "__main__":
    main()