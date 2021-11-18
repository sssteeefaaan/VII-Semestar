from functools import reduce
from itertools import starmap
import operator

#a)
def brojel(*args) -> list[int]:
    return [len(x) if isinstance(x, list) else -1 for x in list(args)]

print(brojel([1, 2], [3, 4, 5], 'el', ['1', 1]))

#b)
def proizvod(A:list[list[int]], B:list[int]) -> list[int]:
    return list(starmap(lambda x, y: reduce(operator.add, x) * y, list(zip(A, B))))

print(proizvod([[1,2,3],[4,5,6],[7,8,9]], [1,2,3]))