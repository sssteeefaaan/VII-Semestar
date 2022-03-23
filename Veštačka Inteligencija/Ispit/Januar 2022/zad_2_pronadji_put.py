def pronadji_put(G, S, E):
    put = []
    M = [[S]]
    while M and not put:
        vrh, *M = M
        for sused in G[vrh[-1]]:
            if sused == E:
                put = vrh + [sused]
            elif sused not in vrh:
                M = [vrh + [sused]] + M
    return put
                