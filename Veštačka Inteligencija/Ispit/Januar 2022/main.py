from zad_1_transform import transform
from zad_2_pronadji_put import pronadji_put

def main():
    matrix =    [   3 * [False] + [True] + 6 * [False],
                    [False] + 8 * [True] + [False],
                    5 * [False] + [True, True, False, True],
                    2 * [False] + 3 * [True] + 2 * [False] + [True, True, False],
                    2 * [False] + [True, False] + 4 * [True] + 2 * [False],
                    [False, True, True] + 5 * [False] + [True, False],
                    [False, True, False] + 6 * [True] + [False],
                    [False] + 3 * [True] + 3 * [False] + [True, False, False],
                    [False] + 4 * [True] + [False] + 2 * [True] + 2 * [False],
                    6 * [False] + [True] + 3 * [False]
                ]
    result = transform(matrix)
    put = pronadji_put(result, (0, 3), (9, 6))
    print(put)
        
main()