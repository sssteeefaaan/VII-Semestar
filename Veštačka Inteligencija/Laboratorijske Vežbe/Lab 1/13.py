from itertools import tee, zip_longest, starmap
from functools import reduce
import operator

def izmeni(lista:list[int])->list[int]:
    return [lista[i] + (1 if not i % 2 else -1) for i in range(0, len(lista))]

print(izmeni([8, 5, 3, 1, 1]))


# nece da mi importuje pairwise iz itertools
def pairwise(iterable):
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)

def skupi(lista:list[list[int]])->list[list[int]]:
    return list(starmap(lambda x, y: [x[i] + y[i] if i < len(x) and i < len(y) else x[i] if len(x)>len(y) else y[i] for i in range(0, max(len(x), len(y)))], pairwise(lista)))

print(skupi([[1, 3, 5],[2, 4, 6],[1, 2]]))