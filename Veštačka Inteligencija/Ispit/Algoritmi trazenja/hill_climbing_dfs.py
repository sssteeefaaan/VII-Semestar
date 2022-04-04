def hill_climbing_dfs(G, start, end):
    stack = [start]
    path = []
    visited = set()
    prev = {
        start: None
    }
    while stack and not path:
        head, *stack = stack
        to_add = []
        for (g, n) in sorted(G[head][1], key=lambda x: G[x[1]]):
            if n == end:
                path = [end]
                prev[end] = head
            elif n not in visited:
                prev[n] = head
                to_add += [n]
        visited |= set({head})
        stack = to_add + stack
    if path:
        while prev[path[0]]:
            path = [prev[path[0]]] + path
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
    print(hill_climbing_dfs(graph, 'A', 'G'))
    
if __name__ == '__main__':
    main()