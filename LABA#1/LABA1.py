n = int(input())
x = n if n >= 0 else -n 
z = -1 if n < 0 else 1
reversed_n = 0
while x > 0:
    reversed_n = reversed_n * 10 + x % 10
    x //= 10
result = z * reversed_n
print(result)