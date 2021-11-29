# Napisati funkciju koja formira listu sastavljenu od elemenata (čvor, nivo) za sve čvorove grafa do kojih se može stići iz zadatog polaznog čvora, gde nivo predstavlja nivo stabla traženja na kome se nalazi čvor.

def findAllShortestPaths(graph, startNode):
    paths = {startNode: (startNode,)}
    queue = [[startNode]]
    while queue:
        curr, *queue = queue
        for n in graph[curr[-1]]:
            if not paths.get(n) or len(paths[n]) > len(curr):
                paths |= {n: (*curr, n)}
                queue += [curr + [n]]
            elif n not in curr:
                queue += [curr + [n]]
    return list(map(lambda x: (x[0], len(x[1][1:]), x[1]), paths.items()))


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
    rez = findAllShortestPaths(zadati_graf, 'A')
    for p in rez:
        print(p)


if __name__ == '__main__':
    main()
