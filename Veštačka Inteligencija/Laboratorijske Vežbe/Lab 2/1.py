# Napisati funkciju koja određuje visinu stavlja traženja (broj nivoa u stablu traženja), a za algoritam obilaska grafa po širini, koje se formira za zadati polazni čvor i zadati graf
from functools import reduce
from display import display

def findPath(graph, startNode, endNode):
    path = list()

    if startNode is endNode:
        path.append(startNode)
        return path

    queue = list()
    visited = set()
    prev_nodes = dict()
    prev_nodes[startNode] = None
    visited.add(startNode)
    queue.append(startNode)
    found = False

    while not found and len(queue):
        curr, *queue = queue

        for dest in graph[curr]:
            if dest not in visited:
                prev_nodes[dest] = curr
                if dest is endNode:
                    found = True
                visited.add(dest)
                queue.append(dest)

    if found:
        path.append(endNode)
        prev = prev_nodes[endNode]
        
        while prev is not None:
            path.append(prev)
            prev = prev_nodes[prev]
            
        path.reverse()
    return path


def main():
    zadati_graf = {
        'A': ['B', 'C', 'D'],
        'B': ['E', 'F', 'G'],
        'C': ['H', 'A', 'B'],
        'D': ['C', 'E', 'F'],
        'E': ['G', 'H', 'A'],
        'F': ['B', 'C', 'D'],
        'G': ['E', 'F', 'H'],
        'H': []
    }
    print(findPath(zadati_graf, 'A', 'H'))
    display(zadati_graf)

if __name__ == '__main__':
    main()
