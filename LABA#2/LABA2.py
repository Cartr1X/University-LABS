x = int(input("Start: "))
y = int(input("End: "))
def sum_range(start, end):
    if start == end:
        return start
    elif start < end:
        return start + sum_range(start + 1, end) # если начально число меньше конечного
    else:
        return start + sum_range(start - 1, end) # в обратную сторону
    
print(sum_range(x, y))