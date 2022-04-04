def bfs(G, start, end):
    queue = [start]
    path = []
    visited = set()
    prev = {
        start: None
    }
    while queue and not path:
        head, *queue = queue
        for n in G[head]:
            if n == end:
                path = [end]
                prev[end] = head
            elif n not in visited:
                prev[n] = head
                queue += [n]
        visited |= set(head)
    if path:
        while prev[path[0]]:
            path = [prev[path[0]]] + path
    return path

def main():
    graph = {
        'A': ['B', 'C', 'D'],
        'B': ['E', 'F'],
        'C': ['D', 'E'],
        'D': ['A', 'B', 'C'],
        'E': ['A', 'B', 'C'],
        'F': ['G'],
        'G': ['H'],
        'H': ['F', 'G']
    }
    
    print(bfs(graph, 'A', 'H'))
    
if __name__ == '__main__':
    main()