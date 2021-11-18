from functools import reduce

def presek(A:list[object], B:list[object]) -> list[object]:
    return [a for a in A if a in B]

def izracunaj(A:list[int or list[int]]) -> list[int]:
    return list(map(lambda x: x**2 if isinstance(x, int) else reduce(lambda acc, y: acc + y**2, x, 0), A))

print(presek([5, 4, "1", "8", 3, 9, 7], [1, 9, "1"]))
print(izracunaj([2, 4, [1, 2, 3], [4, 2], 2, [9, 5]]))

