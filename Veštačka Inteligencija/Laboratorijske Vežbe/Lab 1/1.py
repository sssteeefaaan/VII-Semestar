from itertools import zip_longest

# a)

def parni(lista:list[int]) -> int:
    return len(list(filter(lambda broj: not broj % 2, lista)))

# b)

def poredak(a:list[int], b:list[int]) -> list[tuple[int, int, str]]:
    return list(map(lambda x: (x[0], x[1], ('Jeste') if x[0] << 1 == x[1] else ('Nije')), list(zip_longest(a, b, fillvalue=0))))

print(parni(list(range(1,10))))
print(poredak([1, 2, 3, 4, 5], [2, 4, 7, 9, 10, 11, 8]))