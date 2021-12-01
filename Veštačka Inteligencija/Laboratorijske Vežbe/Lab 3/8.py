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


# print(pseudoku({'11': 1, '33': 9}))
