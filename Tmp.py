import re

if __name__ == "__main__":
    directory = "F:\Movies\BBC猎捕.The.Hunt.2015.1080P.国语双语.中文字幕"
    for file_path in os.listdir(directory):
        file = os.path.join(directory, file_path)

        if os.path.isfile(file):
            new_name = os.path.splitext(file)[0]
            if new_name.endswith("mp4"):
                os.rename(file, new_name)
