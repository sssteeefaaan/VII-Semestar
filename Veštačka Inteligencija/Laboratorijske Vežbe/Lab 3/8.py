# from functools import reduce
# import operator


# def findComb(state, i, j):
#     table = state[0]
#     free = state[1]
#     r = [x[1] for x in table.items() if x[0][0] == i]
#     if len(r)==3:
#         combR
#     c = [x[1] for x in table.items() if x[0][1] == j]
#     sumC = reduce(operator.add, c, 0)
#     print('Table')
#     for indi in range(1, 4):
#         for indj in range(1, 4):
#             print(table.get(str(indi) + str(indj), "x"), end=" ")
#         print(end="\n")
#     print('Element indeks:', i, j)
#     print('Row sum:', sumR)
#     print('Column sum:', sumC)

#     ret = []
#     for el in free:
#         if (len(r) < 2 and sumR + el < 15 or len(r) == 2 and sumR + el == 15 or len(r)==3) and (len(c) < 2 and sumC + el <= 15 or len(c) == 2 and sumC + el == 15 or len(c)==3):
#             ret += [[table | {i + j: el}, set([x for x in free if x != el])]]
#     return ret


# def pseudoku(table):
#     solutions = []
#     taken = set(table.values())
#     state = [[dict(table), set([x for x in range(1, 10) if x not in taken])]]
#     while state:
#         curr, *state = state
#         if len(curr[0].keys()) == 9:
#             return curr[0]
#         for i in range(1, 4):
#             for j in range(1, 4):
#                 if not curr[0].get(str(i) + str(j), False):
#                     state += findComb(curr, str(i), str(j))
#     return solutions


from itertools import permutations


def allSums():

    r = range(1, 10)
    grids = permutations(r)

    solutions = [grid for grid in grids if allSumsAre15(grid)]
    return solutions


def allSumsAre15(grid):
    return (sumIs15(grid, 0, 1, 2) and
            sumIs15(grid, 3, 4, 5) and
            sumIs15(grid, 6, 7, 8) and
            sumIs15(grid, 0, 3, 6) and
            sumIs15(grid, 1, 4, 7) and
            sumIs15(grid, 2, 5, 8))


def sumIs15(grid, a, b, c):
    sum_ = grid[a] + grid[b] + grid[c]
    return sum_ == 15


def printAll():
    for array in allSums():
        printArray(array)


def printArray(array):
    print("-----")
    for i in range(0, 9, 3):
        print(array[i], array[i+1], array[i+2])


printAll()
# print(pseudoku({'11': 1, '33': 9}))
