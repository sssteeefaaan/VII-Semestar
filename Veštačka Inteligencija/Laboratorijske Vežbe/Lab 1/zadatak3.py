def uredi(lista:list[int], n, value)->list[int]:
    return [lista[i] + (value if i < n else - value) for i in range(0, len(lista))]
print( uredi([1, 2, 3, 4, 5], 3, 1))
from itertools import starmap, zip_longest

def spoji(lista1, lista2):
    return list(starmap(lambda x, y: (x, y, x+y) if x<y else (y, x, x+y), zip_longest(lista1, lista2, fillvalue=0)))
print( spoji([1, 7, 2, 4], [2, 5, 2]))
