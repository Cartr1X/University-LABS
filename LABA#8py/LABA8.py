import os
import pickle

bin_file_1 = "binary_numbers.bin"
bin_file_2 = "words_list.bin"

def load_list(filepath):
    if os.path.exists(filepath):
        with open(filepath, "rb") as f:
            return pickle.load(f)
    return []

def save_list(filepath, data):
    with open(filepath, "wb") as f:
        pickle.dump(data, f)

def edit_list(data, name):
    while True:
        print(f"\n{name} (сейчас {len(data)} шт.):")
        for i, val in enumerate(data):
            print(f" {i+1}.{val}")

        print("\nКоманды: + значение, - индекс, 0 - назад")
        cmd = input("> ").strip

        if cmd == '0':
            break
        elif cmd.startswith('+'):
            val =cmd[1:].strip()
            if val:
                data.append(val)
                print(f"Добавлено: {val}")
        elif cmd.startswith('-'):
            try:
                idx = int(cmd[1:].strip()) - 1
                if 0 <= idx < len(data):
                    removed =  data.pop(idx)
                    print(f"Удалено: {removed}")
            except:
                print("Неверный индекс")

def main():
    binary_list = load_list(bin_file_1)
    words_list = load_list(bin_file_2)

# МЕНЮ ГОВНА ПЕРЕДЕЛАТЬ ПОД ВВОД И ВЫВОД СОХРАНЕНИЕ И ЖОПА
# ДОБАВИТЬ 4 ВОССТАНОВЛЕНИЕ
# ЛАБА БЕЗ ПРОВЕРОК
# помогите
# ПОЛНОСТЬЮ ПЕРЕДЕЛАТЬ CHOISE
# ШАЙТАН
# СОЕДЕНИТЬ CHOISE с первым траем



    while True:
        print("\n" + "=" * 30)
        print()

        choice = input("Выберите пункт (1-4): ")

        if choice == '1':
            print("Запуск...")
        elif choice == '2':
            print("Настройки открыты")
        elif choice == '3':
            print("Выход из программы.")
            break
        else:
            print("Неверный ввод, попробуйте снова.")

if __name__ == "__main__":
    main()
