# Napisati funkciju koja ispituje koliko disjunktnih podgrafova postoji u zadatom neorijentisanom grafu. Dozvoljeno više puta pozvati algoritam obilaska grafa.

def findDisjunctive(graph):
    disj = {}
    queue = [[startNode] for startNode in graph.keys()]
    while queue:
        curr, *queue = queue
        for n in graph[curr[-1]]:
            if n not in curr:
                intersection = (
                    [x for x in curr if x in disj.keys()] or [curr[-1]])[0]
                disj |= {n: disj.pop(intersection, set()) | set(curr + [n])}
                queue += [curr + [n]]
    return (disj.values(), len(disj))


def main():
    graph = {
        'A': ['A', 'B', 'C', 'P'],
        'B': ['A', 'C'],
        'C': ['A', 'B'],
        'D': ['E', 'F'],
        'E': ['D', 'F'],
        'F': ['D', 'E', 'H', 'J'],
        'H': ['F', 'J'],
        'J': ['F', 'H'],
        'P': ['Q', 'P'],
        'Q': ['P'],
        'M': ['N', 'O'],
        'N': ['M'],
        'O': ['M']
    }
    rez = findDisjunctive(graph)
    for en in rez[0]:
        print(en)
    print(f"Broj disjunktnih podgrafova je: {rez[1]}")


if __name__ == '__main__':
    main()
