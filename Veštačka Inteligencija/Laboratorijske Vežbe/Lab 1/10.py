from itertools import tee
from functools import reduce
import operator

def izbroj(lista: list[object])->int:
    return reduce(operator.add, [1 if type(x) == int else izbroj(x) for x in lista])

# nece da mi importuje pairwise iz itertools
def pairwise(iterable):
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)

def stepen(lista:list[int])->list[int]:
    return [x[0]**x[1] for x in list(pairwise(lista))]

print(stepen([1, 5, 2, 6, 1, 6, 3, 2, 9]))