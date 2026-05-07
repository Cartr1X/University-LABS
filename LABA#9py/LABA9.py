import os
import json
import shutil

json_file_char = "char_list.json"
json_file_float = "float_list.json"
json_file_str = "words_list.json"

backup_char = "char_list.bak"
backup_float = "float_list.bak"
backup_str = "words_list.bak"

def load_list(filepath, backup_path, list_name):
    """Загрузка списка из JSON файла"""
    if os.path.exists(filepath):
        try:
            with open(filepath, "r", encoding="utf-8") as f:
                data = json.load(f)
                if not isinstance(data, list):
                    print(f"Ошибка: {list_name} не является списком!")
                    return []
                return data
        except (json.JSONDecodeError, FileNotFoundError) as e:
            print(f"\nФайл {list_name} повреждён! Ошибка: {e}")
            if os.path.exists(backup_path):
                print(f"Доступна резервная копия для {list_name}")
                print(f"Используйте пункт 4 для восстановления")
            else:
                print(f"Нет резервной копии для {list_name}")
            return []
    return []

def save_list(filepath, data, backup_path=None):
    """Сохранение списка в JSON файл"""
    if backup_path and os.path.exists(filepath):
        try:
            shutil.copy2(filepath, backup_path)
        except:
            pass
    with open(filepath, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)

def edit_list(data, name, list_type="str"):
    """Редактирование списка с учётом типа данных"""
    while True:
        print(f"\n{name} (сейчас {len(data)} шт.):")
        for i, val in enumerate(data):
            print(f" {i+1}. {val}")
        print("\nКоманды: + значение, - индекс, 0 - назад")
        cmd = input("> ").strip()
        
        if cmd == '0':
            break
        elif cmd.startswith('+'):
            val = cmd[1:].strip()
            if val:
                # Проверка для char (один символ)
                if list_type == "char":
                    if len(val) == 1:
                        data.append(val)
                        print(f"Добавлен символ: {val}")
                    else:
                        print("Ошибка: для char нужно ввести ровно один символ!")
                # Проверка для float
                elif list_type == "float":
                    try:
                        float_val = float(val)
                        data.append(float_val)
                        print(f"Добавлено число: {float_val}")
                    except ValueError:
                        print("Ошибка: введите корректное число с плавающей точкой!")
                # Для str (слова)
                else:
                    data.append(val)
                    print(f"Добавлено слово: {val}")
        elif cmd.startswith('-'):
            try:
                idx = int(cmd[1:].strip()) - 1
                if 0 <= idx < len(data):
                    removed = data.pop(idx)
                    print(f"Удалено: {removed}")
                else:
                    print("Индекс вне диапазона")
            except ValueError:
                print("Неверный индекс")

def restore_from_backup(filepath, backup_path, list_name):
    """Восстановление из резервной копии"""
    if os.path.exists(backup_path):
        try:
            with open(backup_path, "r", encoding="utf-8") as f:
                data = json.load(f)
            save_list(filepath, data, None)
            print(f"Файл {list_name} восстановлен из резервной копии")
            return data
        except (json.JSONDecodeError, FileNotFoundError) as e:
            print(f"Не удалось восстановить {list_name} из резервной копии: {e}")
            return []
    else:
        print(f"Резервная копия для {list_name} не найдена")
        return []

def check_file_integrity(filepath, backup_path, list_name):
    """Проверка целостности JSON файла"""
    if os.path.exists(filepath):
        try:
            with open(filepath, "r", encoding="utf-8") as f:
                json.load(f)
            return True
        except json.JSONDecodeError:
            print(f"\nФайл {list_name} повреждён!")
            if os.path.exists(backup_path):
                print(f"Доступна резервная копия. Используйте пункт 4 для восстановления")
            else:
                print(f"Нет резервной копии для {list_name}")
            return False
    return True

def main():
    # Загрузка списков
    char_list = load_list(json_file_char, backup_char, "списка символов")
    float_list = load_list(json_file_float, backup_float, "списка чисел с плавающей точкой")
    words_list = load_list(json_file_str, backup_str, "списка слов")

    while True:
        print("\n" + "="*40)
        print("ГЛАВНОЕ МЕНЮ")
        print("1. Работа со списком символов (char)")
        print("2. Работа со списком чисел с плавающей точкой (float)")
        print("3. Работа со списком слов (str)")
        print("4. Сохранить и выйти")
        print("5. Восстановить файл из резервной копии")
        
        choice = input("Выберите: ")
        
        if choice == '1':
            if check_file_integrity(json_file_char, backup_char, "списка символов"):
                char_list = load_list(json_file_char, backup_char, "списка символов")
                edit_list(char_list, "Символы (char)", "char")
                save_list(json_file_char, char_list, backup_char)
            else:
                print("Невозможно работать с повреждённым файлом. Используйте пункт 5 для восстановления.")
                
        elif choice == '2':
            if check_file_integrity(json_file_float, backup_float, "списка чисел с плавающей точкой"):
                float_list = load_list(json_file_float, backup_float, "списка чисел с плавающей точкой")
                edit_list(float_list, "Числа с плавающей точкой (float)", "float")
                save_list(json_file_float, float_list, backup_float)
            else:
                print("Невозможно работать с повреждённым файлом. Используйте пункт 5 для восстановления.")
                
        elif choice == '3':
            if check_file_integrity(json_file_str, backup_str, "списка слов"):
                words_list = load_list(json_file_str, backup_str, "списка слов")
                edit_list(words_list, "Слова (str)", "str")
                save_list(json_file_str, words_list, backup_str)
            else:
                print("Невозможно работать с повреждённым файлом. Используйте пункт 5 для восстановления.")
                
        elif choice == '4':
            save_list(json_file_char, char_list, backup_char)
            save_list(json_file_float, float_list, backup_float)
            save_list(json_file_str, words_list, backup_str)
            print("Все данные сохранены. До свидания!")
            break
            
        elif choice == '5':
            print("\nВосстановление из резервной копии:")
            print("1. Восстановить список символов (char)")
            print("2. Восстановить список чисел с плавающей точкой (float)")
            print("3. Восстановить список слов (str)")
            sub = input("Выберите: ")
            
            if sub == '1':
                char_list = restore_from_backup(json_file_char, backup_char, "списка символов")
            elif sub == '2':
                float_list = restore_from_backup(json_file_float, backup_float, "списка чисел с плавающей точкой")
            elif sub == '3':
                words_list = restore_from_backup(json_file_str, backup_str, "списка слов")
            else:
                print("Неверный выбор")
        else:
            print("Неверный выбор. Пожалуйста, выберите 1-5.")

if __name__ == "__main__":
    main()