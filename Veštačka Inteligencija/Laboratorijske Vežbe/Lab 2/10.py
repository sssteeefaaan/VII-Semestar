# Napisati funkciju koja pronalazi put u neorijentisanom grafu između dva zadata čvora, pri čemu put prolaze kroz treći zadati čvor.

def findPath(graph, startNode, endNode, throughNode):
    path = []
    queue1 = [[startNode]]

    while queue1:
        curr1, *queue1 = queue1
        for n in graph[curr1[-1]]:
            if n == throughNode:
                path = curr1
                queue1.clear()
            if n not in curr1:
                queue1 += [curr1 + [n]]

    queue2 = [path]
    path2 = []
    while queue2:
        curr2, *queue2 = queue2
        for n in graph[curr2[-1]]:
            if n == endNode:
                path2 = curr2 + [n]
                queue2.clear()
            if n not in curr2:
                queue2 += [curr2 + [n]]

    return path2


zadati_graf = {
    'A': ['B', 'C', 'D'],
    'B': ['E', 'F', 'G'],
    'C': ['A', 'B'],
    'D': ['C', 'E', 'F'],
    'E': ['G', 'A'],
    'F': ['B', 'C', 'D'],
    'G': ['E', 'F', ],
    'H': ['J'],
    'J': []
}
print(findPath(zadati_graf, 'A', 'A', 'D'))
