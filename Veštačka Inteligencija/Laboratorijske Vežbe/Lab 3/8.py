def psudoku(table):
    taken = set([x for x in table if x])
    state = [[table, set([x for x in range(1, 10) if x not in taken]), 0]]

    while state:
        curr, *state = state
        for el in curr[0]:
            if el:
                for comb in findCombs(curr[1], row):
                    row[0] += comb[0]
                    row[1] += comb[1]
                    row[2] += comb[2]


Table = [1] + 7*[0] + [9]
