def izmeni(lista:list[int])->list[int]:
    return [lista[i] + (1 if not i % 2 else -1) for i in range(0, len(lista))]

print(izmeni([8, 5, 3, 1, 1]))


# Nmg vise...
# def skupi(lista:list[list[int]])->list[list[int]]:
#     return [starmap(sum, )]