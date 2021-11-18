from itertools import zip_longest
#a)

def numlista(lista: list[object])-> list[int]:
    return list(filter(lambda x: type(x)==int, lista))

#b)

def spojidict(a: list[object], b: list[object]) -> list[dict[str, object]]:
    return list(map(lambda x: dict({'prvi': x[0], 'drugi': x[1]}), list(zip_longest(a,b, fillvalue='-'))))