from functools import reduce
import operator
def presek(lista1, lista2):
    return [a for a in lista1 if a in lista2]

print(presek([5, 4, "1", "8", 3, 7, 1], [1, 9, "1"]))

def izracunaj(lista):
    return [x**2 if isinstance(x, int) else reduce(operator.add, list(map(lambda y: y**2, x)), 0) for x in lista]

print(izracunaj([2, 4, [1, 2, 3], [4, 2], 2, [9, 5]]))