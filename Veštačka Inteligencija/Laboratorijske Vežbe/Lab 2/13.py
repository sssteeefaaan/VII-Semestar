# Napisati funkciju koja određuje listu grana u grafu koje je neophodno obrisati da bi se ciklični graf transformisao u aciklični (da bi se u njemu eliminisali ciklusi).
from display import display


def makeAcyclic(graph):
    canRemove = []
    queue = [[x] for x in graph.keys()]
    while queue:
        curr, *queue = queue
        for n in graph[curr[-1]]:
            if n not in curr:
                queue += [curr + [n]]
            elif (curr[-1], n) not in canRemove and (n, curr[-1]) not in canRemove:
                canRemove += [(curr[-1], n)]
    return canRemove


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

rez = makeAcyclic(zadati_graf)
for p in rez:
    print(p)

display(zadati_graf)
display({
    'A': ['C', 'D'],
    'B': ['E', 'F'],
    'C': ['H', 'B'],
    'D': ['F'],
    'E': ['G', 'H'],
    'F': [],
    'G': ['H'],
    'H': ['J'],
    'J': []
})
