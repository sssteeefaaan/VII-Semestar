# Napisati funkciju koja formira stablo traženja za zadati graf, zadati polazni čvor i algoritam koji će se koristiti za obilazak stabla.

def formSearchTree(graph, startNode, breathSearch=True):
    paths = [(startNode,)]
    struct = [(startNode,)]
    while struct:
        if breathSearch:
            curr, *struct = struct
        else:
            *struct, curr = struct
        for n in graph[curr[-1]]:
            if n not in curr:
                paths += [(*curr, n)]
                struct += [(*curr, n)]
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
rez = formSearchTree(zadati_graf, 'A')
for p in rez:
    print(p)