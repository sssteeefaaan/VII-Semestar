def branch_and_bound(G, start, end):
    processing = [[start]]
    path = []
    while processing and not path:
        head, *processing = processing
        for (g, n) in G[head[-1]][1]:
            if n == end:
                path = head + [n]
            elif n not in head:
                processing += [head + [n]]
        processing = sorted(processing, key=lambda x: G[x[-1]][0])
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
    print(branch_and_bound(graph, 'A', 'H'))
    
if __name__ == '__main__':
    main()