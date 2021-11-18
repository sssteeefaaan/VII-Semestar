from itertools import tee
from functools import reduce

def pairwise(iter):
    a,b = tee(iter)
    next(b, None)
    return zip(a,b)

def razlika(lista)->list[int]:
    return [reduce(lambda x ,y: x - y if x > y else y - x, z, 0) for z in list(pairwise(lista))]

print(razlika([8, 5, 3, 1, 1]))


def proizvod(lista):
    return reduce(lambda x, y: x * y, [z for z in [reduce(lambda p, q: p * q, r, 1) for r in lista]], 1)

print(proizvod([[1, 3, 5],[2, 4, 6],[1, 2, 3]]))
