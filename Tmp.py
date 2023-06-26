import os


def remove_empty_directories(directory):
    for dir_name in os.listdir(directory):
        dir_path = os.path.join(directory, dir_name)
        try:
            if os.path.isdir(dir_path) and not os.listdir(dir_path):  # 检查目录是否为空
                os.rmdir(dir_path)  # 删除空目录
        except (PermissionError, OSError) as e:
            print("Failed to remove: " + dir_path)
            continue


# 使用示例
directory_path = r"C:\Users\FrozeWorld"
remove_empty_directories(directory_path)
