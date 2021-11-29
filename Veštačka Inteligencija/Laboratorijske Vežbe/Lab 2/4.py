# Napisati funkciju koja formira listu sastavljenu od elemenata (čvor, heuristika) za sve čvorove grafa do kojih se može stići od zadatog polaznog čvora. Heuristika za čvor se računa kao razlika broja čvorova u grafu i broja grana na putu od polaznog čvora do posmatranog čvora

def findRoutesWithHeuristics(graph, startNode):
    paths = {startNode: (startNode,)}
    queue = [[startNode]]

    while queue:
        curr, *queue = queue
        for n in graph[curr[-1]]:
            if not paths.get(n) or len(paths.get(n)) > len(curr):
                paths |= {n: (*curr, n)}
                queue += [curr + [n]]
            elif n not in curr:
                queue += [curr + [n]]
    return list(map(lambda x: (x[0], len(graph) - len(x[1][1:]), x[1]), paths.items()))


def main():
    zadati_graf = {
        'A': ['B', 'C', 'D'],
        'B': ['E', 'F', 'G'],
        'C': ['A', 'B'],
        'D': ['C', 'E', 'F'],
        'E': ['G', 'H', 'A'],
        'F': ['B', 'C', 'D'],
        'G': ['E', 'H'],
        'H': ['J'],
        'J': []
    }
    rez = findRoutesWithHeuristics(zadati_graf, 'A')
    for p in rez:
        print(p)


if __name__ == '__main__':
    main()
