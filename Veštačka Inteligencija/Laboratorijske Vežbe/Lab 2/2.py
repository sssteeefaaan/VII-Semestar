# Napisati funkciju koja određuje broj disjunktnih puteva između dva zadata čvora u grafu. Rešenje ne mora biti optimalno prema broju puteva. Dozvoljeno više puta pozvati algoritam obilaska grafa.
from functools import reduce

def numbOfDisjunct(graph, startNode, endNode):
    paths = []
    taken = set()
    queue = [(startNode,)]

    while queue:
        current, *queue = queue
        for n in graph[current[-1]]:
            path = (*current, n)
            if n == endNode:
                partTaken = reduce(lambda acc, el: acc | (
                    {el} if el not in taken else set()), path[1:-1], set())

                if len(partTaken) == len(path[1:-1]):
                    paths += [path]
                    taken |= partTaken

            if n not in current:
                queue += [path]

    return (paths, len(paths))


zadati_graf = {
    'A': ['B', 'C', 'D'],
    'B': ['E', 'F', 'G'],
    'C': ['H', 'A', 'B'],
    'D': ['C', 'E', 'F'],
    'E': ['G', 'H', 'A'],
    'F': ['B', 'C', 'D', 'J'],
    'G': ['E', 'J', 'H'],
    'H': ['J'],
    'J': []
}
rez = numbOfDisjunct(zadati_graf, 'A', 'J')
for p in rez[0]:
    print(p)
print('Number of disjunt routes:', rez[1])
