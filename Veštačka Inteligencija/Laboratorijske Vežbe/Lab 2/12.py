# Napisati funkciju koja pronalazi puteve zadate dužine u neorijentisanom grafu između dva zadata čvora.

def findPaths(graph, startNode, endNode, lenght):
    paths = []
    queue = [[startNode]]

    while queue:
        curr, *queue = queue
        for n in graph[curr[-1]]:
            if n not in curr and len(curr) <= lenght:
                queue += [curr + [n]]
                if n == endNode and lenght == len(curr):
                    paths += [curr + [n]]
    return paths


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
rez = findPaths(zadati_graf, 'A', 'C', 5)
for p in rez:
    print(p)
