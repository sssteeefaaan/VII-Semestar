from itertools import tee, starmap
from functools import reduce
import operator

def izbroj(lista: list[object])->int:
    return reduce(lambda acc, x: acc + (1 if isinstance(x, int) else izbroj(x)), lista, 0)

print(izbroj([1, 2, [3, 4, [50, 6, [7, 8, 9, [10, 11], 12, 13], 14], 15, 16], 17]))

# nece da mi importuje pairwise iz itertools
def pairwise(iterable):
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)

def stepen(lista:list[int])->list[int]:
    return list(starmap(pow, pairwise(lista)))

print(stepen([1, 5, 2, 6, 1, 6, 3, 2, 9]))