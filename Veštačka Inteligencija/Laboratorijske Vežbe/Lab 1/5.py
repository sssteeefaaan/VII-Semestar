from functools import reduce

#a)
def brojel(lista: list[object]) -> list[int]:
    return list(map(lambda x: (-1) if not type(x)==list else len(x), lista))

#b)
def proizvod(A:list[list[int]], B:list[int]) -> list[int]:
    return list(map(lambda x: reduce(lambda y, z: y + z, x[0]) * x[1], list(zip(A, B))))