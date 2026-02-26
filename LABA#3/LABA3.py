from inspect import signature, Parameter

def inspect(func):
    name = func.__name__
    sig = signature(func)
    param_types = {}

    for param in sig.parameters.values():
        if param.kind.description != 'positional or keyword': #позиционные или ключевые аргументы
            param_types[param.name] = param.kind.description
        else:
            if param.default is Parameter.empty:
                param_types[param.name] = 'positional'
            else:
                param_types[param.name] = 'keyword'
    return name, param_types

def my_function(a, b: int, c = 10) -> bool:
    return True

print(inspect(my_function))