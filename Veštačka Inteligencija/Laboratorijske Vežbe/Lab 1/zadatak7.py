from functools import reduce

# def operacija(lista, op, neutral):
#     return list(map(lambda x: reduce(op, x, neutral), lista))

# print(operacija([(1, 4, 6), (2, 4), (4, 1)], lambda x, y: x + y, 0))

def objedini(A:list):
   return dict(reduce(lambda acc,el: acc | {str(el[0]): el[1:] if el[1:] else None}, A, dict()))

print(objedini([(1,), (3, 4, 5), (7,), (1, 4, 5), (6, 2, 1, 3)]))