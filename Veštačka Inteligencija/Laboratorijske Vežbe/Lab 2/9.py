# Napisati funkciju koja određuje broj čvorova do kojih može da se dođe od zadatog čvora, tako da je dužina puta do čvora jednaka nekoj vrednosti. Obići samo neophodne čvorove.

def countNodesOnDepth(graph, startNode, depth):
    paths = []
    queue = [[startNode]]

    while queue:
        curr, *queue = queue
        for n in graph[curr[-1]]:
            if n not in curr and len(curr) <= depth:
                queue += [curr + [n]]
                if len(curr) == depth and (not paths or n not in list(map(lambda x: x[-1], paths))):
                    paths += [(*curr, n)]

    return (paths, len(paths))


zadati_graf = {
    'A': ['D'],
    'B': ['E', 'F', 'G'],
    'C': ['H', 'A', 'B'],
    'D': ['C', 'F'],
    'E': ['G', 'H', 'A'],
    'F': ['B', 'C', 'D'],
    'G': ['E', 'H'],
    'H': ['J'],
    'J': []
}
rez = countNodesOnDepth(zadati_graf, 'A', 5)
for p in rez[0]:
    print(p)
print(
    f"Broj čvorova do kojih može da se dođe prolazeći kroz {5} čvora počevši od čvora '{'A'}': {rez[1]}")
