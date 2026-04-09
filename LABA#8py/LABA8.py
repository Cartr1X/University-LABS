import os
import pickle
import shutil

bin_file_1 = "binary_numbers.bin"
bin_file_2 = "words_list.bin"
backup_file_1 = "binary_numbers.bak"
backup_file_2 = "words_list.bak"

def load_list(filepath, backup_path, list_name):
    if os.path.exists(filepath):
        try:
            with open(filepath, "rb") as f:
                return pickle.load(f)
        except:
            print(f"\nФайл {list_name} повреждён!")
            if os.path.exists(backup_path):
                print(f"Доступна резервная копия для {list_name}")
                print(f"Используйте пункт 4 для восстановления")
            else:
                print(f"Нет резервной копии для {list_name}")
            return []
    return []

def save_list(filepath, data, backup_path=None):
    if backup_path and os.path.exists(filepath):
        try:
            shutil.copy2(filepath, backup_path)
        except:
            pass
    with open(filepath, "wb") as f:
        pickle.dump(data, f)

def edit_list(data, name):
    while True:
        print(f"\n{name} (сейчас {len(data)} шт.):")
        for i, val in enumerate(data):
            print(f" {i+1}.{val}")
        print("\nКоманды: + значение, - индекс, 0 - назад")
        cmd = input("> ").strip()
        if cmd == '0':
            break
        elif cmd.startswith('+'):
            val = cmd[1:].strip()
            if val:
                data.append(val)
                print(f"Добавлено: {val}")
        elif cmd.startswith('-'):
            try:
                idx = int(cmd[1:].strip()) - 1
                if 0 <= idx < len(data):
                    removed = data.pop(idx)
                    print(f"Удалено: {removed}")
            except:
                print("Неверный индекс")

def restore_from_backup(filepath, backup_path, list_name):
    if os.path.exists(backup_path):
        try:
            with open(backup_path, "rb") as f:
                data = pickle.load(f)
            save_list(filepath, data, None)
            print(f"Файл {list_name} восстановлен из резервной копии")
            return data
        except:
            print(f"Не удалось восстановить {list_name} из резервной копии")
            return []
    else:
        print(f"Резервная копия для {list_name} не найдена")
        return []

def check_file_integrity(filepath, backup_path, list_name):
    if os.path.exists(filepath):
        try:
            with open(filepath, "rb") as f:
                pickle.load(f)
            return True
        except:
            print(f"\nФайл {list_name} повреждён!")
            if os.path.exists(backup_path):
                print(f"Доступна резервная копия. Используйте пункт 4 для восстановления")
            else:
                print(f"Нет резервной копии для {list_name}")
            return False
    return True

def main():
    binary_list = load_list(bin_file_1, backup_file_1, "бинарных чисел")
    words_list = load_list(bin_file_2, backup_file_2, "слов")

    while True:
        print("\n" + "="*40)
        print("ГЛАВНОЕ МЕНЮ")
        print("1. Работа со списком бинарных чисел")
        print("2. Работа со списком слов")
        print("3. Сохранить и выйти")
        print("4. Восстановить файл из резервной копии")
        
        choice = input("Выберите: ")
        
        if choice == '1':
            if check_file_integrity(bin_file_1, backup_file_1, "бинарных чисел"):
                binary_list = load_list(bin_file_1, backup_file_1, "бинарных чисел")
                edit_list(binary_list, "Бинарные числа")
                save_list(bin_file_1, binary_list, backup_file_1)
            else:
                print("Невозможно работать с повреждённым файлом. Используйте пункт 4 для восстановления.")
        elif choice == '2':
            if check_file_integrity(bin_file_2, backup_file_2, "слов"):
                words_list = load_list(bin_file_2, backup_file_2, "слов")
                edit_list(words_list, "Слова")
                save_list(bin_file_2, words_list, backup_file_2)
            else:
                print("Невозможно работать с повреждённым файлом. Используйте пункт 4 для восстановления.")
        elif choice == '3':
            save_list(bin_file_1, binary_list, backup_file_1)
            save_list(bin_file_2, words_list, backup_file_2)
            print("Сохранено")
            break
        elif choice == '4':
            print("1. Восстановить бинарные числа из бэкапа")
            print("2. Восстановить слова из бэкапа")
            sub = input("Выберите: ")
            if sub == '1':
                binary_list = restore_from_backup(bin_file_1, backup_file_1, "бинарных чисел")
            elif sub == '2':
                words_list = restore_from_backup(bin_file_2, backup_file_2, "слов")
            else:
                print("Неверный выбор")

if __name__ == "__main__":
    main()
# СДЕЛАТЬ КОММЕНТАРИИ