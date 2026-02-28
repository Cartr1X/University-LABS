def evaluate(coef, x):
    if not coef:
        return 0
    if len(coef) == 1:
        return coef[0]
    else:
         return coef[0] * (x ** (len(coef) - 1)) + evaluate(coef[1:], x)
# Пример
print(evaluate([2, 4, 3], 10))
print(evaluate([1, 2, 3], 10))