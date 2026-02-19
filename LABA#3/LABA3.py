import inspect

def my_function(a: int, b: str) -> bool:
    return True

def inspect_function(func):
    """
    Возвращает тип функции и типы её переменных (аннотации).
    """
    signature = inspect.signature(func)
    types = {
        'function_name': func.__name__,
        'function_type': type(func).__name__,
        'parameters': {
            name: param.annotation 
            for name, param in signature.parameters.items()
        },
        'return_type': signature.return_annotation
    }
    return types

# Использование
info = inspect_function(my_function)
print(info)
# Вывод: {'function_name': 'my_function', 'function_type': 'function', 
#         'parameters': {'a': <class 'int'>, 'b': <class 'str'>}, 
#         'return_type': <class 'bool'>}
# Сделать ввод и вывод фукнции тип ее и тп