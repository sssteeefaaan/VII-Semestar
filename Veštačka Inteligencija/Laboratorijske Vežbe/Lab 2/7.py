# Napisati funkciju koja formira listu sastavljenu od elemenata (čvor, heuristika) za sve čvorove grafa do kojih se može stići od zadatog polaznog čvora. Heuristika za čvor se računa kao broj grana na putu od posmatranog do ciljnog čvora

def findPathsWithHeuristics(graph, startNode, endNode):
    shortestPath = [[]]
    queue = [[startNode]]

    while queue:
        curr, *queue = queue
        for n in graph[curr[-1]]:
            if n == endNode and (not shortestPath or len(shortestPath[0]) > len(curr)):
                shortestPath = [curr + [n]]

            if n not in curr:
                queue += [curr+[n]]

    return [(shortestPath[0][i], i) for i in range(0, len(shortestPath[0]))]

zadati_graf = {
    'A': ['B', 'C', 'D'],
    'B': ['E', 'F', 'G'],
    'C': ['H', 'A', 'B'],
    'D': ['C', 'E', 'F'],
    'E': ['G', 'H', 'A'],
    'F': ['B', 'C', 'D'],
    'G': ['E', 'F', 'H'],
    'H': ['J'],
    'J': [],
    'Q': []
}
rez = findPathsWithHeuristics(zadati_graf, 'A', 'Q')
for p in rez:
    print(p)
