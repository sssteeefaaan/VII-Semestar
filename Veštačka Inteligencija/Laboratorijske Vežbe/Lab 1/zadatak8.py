from functools import reduce
from itertools import accumulate
import operator
def izmeni(lista):
    return list(accumulate(lista,operator.add))

print(izmeni([1, 2, 4, 7, 9]))

def izracunaj(lista):
    return [x if isinstance(x, int) else reduce(operator.mul, x , 1) for x in lista]

print(izracunaj([1, 5, [1, 5, 3], [4, 2], 2, [6, 3]]))