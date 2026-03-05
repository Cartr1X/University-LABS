def evaluate(coef, x):
    if not coef:
        return 0
    if len(coef) == 1:
        return coef[0]
    else:
         return coef[0] * (x ** (len(coef) - 1)) + evaluate(coef[1:], x)
# Пример
*coef, x = map(int, input("Введите коэффициенты и x: ").split())
print(evaluate(coef, x))