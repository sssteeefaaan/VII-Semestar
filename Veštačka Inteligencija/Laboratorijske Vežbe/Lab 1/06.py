from itertools import starmap, zip_longest

def razlika(A: list[object], B:list[object]) -> list[object]:
    return [x for x in A if x not in B]

print(razlika([1, 4, 6, "2", "6"], [4, 5, "2"]))

def objedini(A: list[int], B:list[int]) -> list[tuple[int, int]]:
    return list(map(lambda x: (x[0], x[1]) if x[0] < x[1] else (x[1],x[0]), zip_longest(A,B, fillvalue=0)))

def objedini2(A: list[int], B:list[int]) -> list[tuple[int, int]]:
    return list(starmap(lambda x, y: (x, y) if x < y else (y, x), zip_longest(A, B, fillvalue=0)))

print(objedini([1, 7, 2, 4, 5], [2, 5, 2]) )
print(objedini2([1, 7, 2, 4, 5], [2, 5, 2]) )