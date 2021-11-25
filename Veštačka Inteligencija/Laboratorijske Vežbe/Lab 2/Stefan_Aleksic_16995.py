# Napisati funkciju koja određuje visinu stabla traženja (broj nivoa u stablu traženja), a za algoritam obilaska grafa po širini, koje se formira za zadati polazni čvor i zadati graf.

def countDepth(graph, startNode):
    paths = []

    queue = []
    queue.append([startNode])
    while queue:
        curr, * queue = queue
        numb = len(curr)
        for node in graph[curr[numb - 1]]:
            if not graph[node]:
                paths += [curr[:numb] + [node]]
            elif node in curr[:numb]:
                paths += [curr[:numb]]
            else:
                queue += [curr[:numb] + [node]]
            curr += [node]

    return max(list(map(lambda x: len(x), paths)))

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
print(countDepth(zadati_graf, 'A'))
