
def izdvoji(lista: list[list[int]])->list[int]:
    return [lista[i][i] if len(lista[i]) > i else 0 for i in range(0, len(lista))]

print(izdvoji([[5, 4, 4], [1, 9, 1], [5, 6], [4, 6, 10, 12]]))

def promeni(lista: list[int], x: int)->list[int]:
    return [y + (-x if y >= x else x) for y in lista]

print(promeni([7, 1, 3, 5, 6, 2], 3))