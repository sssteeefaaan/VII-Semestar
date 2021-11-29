# Napisati funkciju koja određuje da li je orijentisani graf snažno povezani graf (da li postoji put između bilo koja dva čvora u grafu).

def isStronlgyConnected(graph):
    path1 = set()
    path2 = set()
    queue = [[list(graph.keys())[0]]]
    while queue:
        curr, *queue = queue
        for n in graph[curr[-1]]:
            path1 |= set(n)
            path2 |= set([x for x in graph.keys() if n in graph[x]])
            if n not in curr:
                queue += [curr + [n]]

    if path1 == path2 and path2 == set(graph.keys()):
        return True
    return False


zadati_graf = {
    'A': ['B', 'C', 'D'],
    'B': ['E', 'F', 'G'],
    'C': ['H', 'A', 'B'],
    'D': ['C', 'E', 'F'],
    'E': ['G', 'H', 'A'],
    'F': ['B', 'C', 'D'],
    'G': ['E', 'F', 'H'],
    'H': ['J'],
    'J': []
}
print(isStronlgyConnected(zadati_graf))

print(isStronlgyConnected({
    'A': ['B', 'C', 'D', 'E', 'F', 'G', 'H'],
    'B': ['A'],
    'C': ['A'],
    'D': ['A'],
    'E': ['A'],
    'F': ['A'],
    'G': ['A'],
    'H': ['J'],
    'J': ['A']
}))
