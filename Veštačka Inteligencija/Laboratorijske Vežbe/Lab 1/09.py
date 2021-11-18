from functools import reduce
import operator

def prosek(lista:list[list[int]])->list[int]:
    return list(map(lambda x: (reduce(operator.add, x, 0) / len(x)) if len(x) > 0 else 0, lista))

print(prosek([[1, 4, 6, 2], [4, 6, 2, 7], [3, 5], [5, 6, 2, 7]]))

def zamena(lista:list[int], x:int) -> list[int]:
    return [(lista[i] if (lista[i] >= x) else (reduce(operator.add, lista[i+1:]))) for i in range(0, len(lista))]

print(zamena([1, 7, 5, 4, 9, 1, 2, 7], 5))