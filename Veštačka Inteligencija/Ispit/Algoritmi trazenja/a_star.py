def a_star(G, start, end):
    processing = set(start)
    previous = {
        start: (0, None)
    }
    path = None
    while processing and not path:
        n = sorted(processing, key=lambda x: previous.get(x, (0, None))[0] + G[x][0])[0]
        if n == end:
            path = [n]
        else:
            for (g_n, n_n) in G[n][1]:
                if (n_n not in processing and not previous.get(n_n, None)) or previous[n_n][0] > g_n + previous[n][0]:
                    previous[n_n] = (g_n + previous[n][0], n)
                    processing.add(n_n)
        processing.remove(n)
    if path:
        while previous[path[0]][1]:
            path = [previous[path[0]][1]] + path
    return path

def main():
    graph = {
        'A': (4, [(1, 'B'), (2, 'C'), (3, 'D')]),
        'B': (3, [(2, 'E'), (3, 'F')]),
        'C': (5, [(3, 'D'), (1, 'E')]),
        'D': (4, [(1, 'A'), (2, 'B'), (3, 'C')]),
        'E': (4, [(1, 'A'), (2, 'B'), (3, 'C')]),
        'F': (2, [(3, 'G')]),
        'G': (1, [(3, 'H')]),
        'H': (0, [(3, 'E'), (3, 'F')])
    }
    print(a_star(graph, 'A', 'H'))
    
if __name__ == '__main__':
    main()