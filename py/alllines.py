import os

def count_lines_in_file(file_path):
    """
    统计单个文件的代码行数（排除空行和//单行注释）
    :param file_path: 文件路径
    :return: 有效代码行数
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            lines = file.readlines()
            # 过滤空行和以//开头的注释行
            return len([line for line in lines if line.strip() and not line.strip().startswith('//')])
    except Exception as e:
        print(f"读取文件 {file_path} 时出错: {e}")
        return 0

def count_lines_in_directory(directory):
    """
    递归统计目录下所有 .c 和 .h 文件的有效代码行数
    :param directory: 目录路径
    :return: .c 文件总行数, .h 文件总行数
    """
    c_total_lines = 0
    h_total_lines = 0
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.c'):
                file_path = os.path.join(root, file)
                lines = count_lines_in_file(file_path)
                c_total_lines += lines
            elif file.endswith('.h'):
                file_path = os.path.join(root, file)
                lines = count_lines_in_file(file_path)
                h_total_lines += lines
    return c_total_lines, h_total_lines

if __name__ == "__main__":
    # 核心修改：获取当前脚本文件的绝对路径，再取其上两级目录
    # 1. 获取当前脚本文件的完整路径
    current_script_path = os.path.abspath(__file__)
    # 2. 获取当前脚本所在的目录
    current_script_dir = os.path.dirname(current_script_path)
    # 3. 取当前脚本目录的上两级目录（前两层）
    target_directory = os.path.abspath(os.path.join(current_script_dir, "../"))
    
    # 打印目标目录路径，方便验证是否正确
    print(f"当前脚本路径: {current_script_path}")
    print(f"目标统计目录: {target_directory}")
    
    c_lines, h_lines = count_lines_in_directory(target_directory)
    print(f".c 文件: {c_lines} 行")
    print(f".h 文件: {h_lines} 行")
    print(f"总有效代码行数: {c_lines + h_lines} 行")