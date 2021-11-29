# Napisati funkciju koja određuje visinu stabla traženja (broj nivoa u stablu traženja), a za algoritam obilaska grafa po širini, koje se formira za zadati polazni čvor i zadati graf.

def countDepth(graph, startNode):
    paths = [(startNode,)]
    queue = [(startNode,)]
    while queue:
        curr, *queue = queue
        for node in graph[curr[-1]]:
            if node not in curr:
                paths += [(*curr, node)]
                queue += [(*curr, node)]
    return (paths, max(list(map(lambda x: len(x), paths))) - 1)

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
rez = countDepth(zadati_graf, 'A')
for p in rez[0]:
    print(p)
print('Depth is:', rez[1])
