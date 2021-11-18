import operator
from functools import reduce

def unija(A:list[object], B:list[object])->list[object]:
    return reduce(lambda acc, y: (acc + [y] if y not in acc else acc), A + B, [])

print(unija([5, 4, "1", "1", "8", 3, 7], [1, 9, "1"]))

def suma(lista:list[object])->list[int]:
    return list(map(lambda x: reduce(operator.add, x), lista))

print(suma([[1, 2, 3],[4, 5, 6],[7, 8, 9]]))