# Napisati funkciju koja određuje čvorove koje je moguće izbaciti iz neusmerenog grafa tako da graf i dalje ostane povezan.

def findRedundant(graph):
    path = []
    canRemove = []
    queue = [[list(graph.keys())[0]]]
    while queue:
        curr, *queue = queue
        temp = len(path)
        for n in graph[curr[-1]]:
            if n not in path:
                path += [n]
                if n not in curr:
                    queue += [curr + [n]]
        if temp == len(path):
            canRemove += curr[-1]
    return canRemove


zadati_graf = {
    'A': ['B', 'C', 'D'],
    'B': ['A', 'C', 'F', 'G'],
    'C': ['A', 'B'],
    'D': ['A', 'E', 'F'],
    'E': ['D', 'G'],
    'F': ['B', 'D'],
    'G': ['B', 'H'],
    'H': ['G', 'J'],
    'J': ['H']
}
print(findRedundant(zadati_graf))
