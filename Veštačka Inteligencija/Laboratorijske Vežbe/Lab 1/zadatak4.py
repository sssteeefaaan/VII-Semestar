from itertools import tee
from functools import reduce

def pairwise(iter):
    a,b = tee(iter)
    next(b, None)
    return zip(a,b)

def zbir(lista)->list[int]:
    return [reduce(lambda x ,y: x + y, z, 0) for z in list(pairwise(lista))]

print(zbir([1, 2, 3, 4, 5]))

def suma(lista):
    return reduce(lambda x, y: x + y, [z for z in [reduce(lambda p, q: p + q, r, 0) for r in lista]], 0)

print(suma([[1, 2, 3],[4, 5, 6],[7, 8, 9]]))
