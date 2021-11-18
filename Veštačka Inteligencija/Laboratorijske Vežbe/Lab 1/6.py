from itertools import takewhile, zip_longest

def razlika(A: list[object], B:list[object]) -> list[object]:
    return list(filter(lambda x: not list(filter(lambda y: y == x, B)), A))

print(razlika([1, 4, 6, "2", "6"], [4, 5, "2"]))

def objedini(A: list[int], B:list[int]) -> list[tuple[int, int]]:
    return list(map(lambda x: (x[0], x[1]) if x[0] < x[1] else (x[1],x[0]), zip_longest(A,B, fillvalue=0)))