import os
import json
import shutil

json_file_char = "char_list.json"
json_file_float = "float_list.json"
json_file_str = "words_list.json"

backup_char = "char_list.bak"
backup_float = "float_list.bak"
backup_str = "words_list.bak"

def load_list(filepath, backup_path, list_name, data_type = str):
    if os.path.exists(filepath):
        try:
            with open(filepath, "r", encoding="utf-8") as f:
                data = json.load(f)
                if not isinstance(data, list):
                    print(f"Ошибка: {list_name} не ялвяется списком")
                    return []
                if data_type != str and data:
                    try:
                        if data_type == int:
                            data = [int(x) for x in data]
                        elif data_type == float:
                            data = [float(x) for x in data]
                    except: print(f"Предупреждение: некоторые элементы {list_name} имеют неверный тип")
                    return data
        except: #дописать дома json файлы и менюшку, проверка на индентичность с LABA8
            return data