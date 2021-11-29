# Napisati funkciju koja proverava da li graf sadrži Ojlerov put (put kojim se obilazi celokupan graf, uz obilazak svake grane tačno jednom).

def findEulersPath(graph):
    queue = [[x] for x in graph.keys()]

    while queue:
        curr, *queue = queue
        for n in graph[curr[-1]]:
            if n not in curr:
                if set(curr + [n]) == set(graph.keys()):
                    return curr + [n]
                queue += [curr + [n]]
    return []


print(findEulersPath({
    'A': ['B', 'C', 'D'],
    'B': ['E', 'F', 'G'],
    'C': ['H', 'A', 'B'],
    'D': ['C', 'E', 'F'],
    'E': ['G', 'H', 'A'],
    'F': ['B', 'C', 'D'],
    'G': ['E', 'F', 'H', 'J'],
    'H': [],
    'J': ['G']
}))
