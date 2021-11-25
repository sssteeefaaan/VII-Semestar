# Napisati funkciju koja određuje visinu stavlja traženja (broj nivoa u stablu traženja), a za algoritam obilaska grafa po širini, koje se formira za zadati polazni čvor i zadati graf
from functools import reduce
from matplotlib.pyplot import show
from networkx import Graph, drawing
from networkx import *

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
        
        print(curr)
        
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
    
print(findPath(zadati_graf, 'A', 'H'))

G = Graph()
G.add_edges_from(list(reduce(lambda acc, el: acc + [(el[0], x) for x in el[1]], [(key, val) for (key, val) in zadati_graf.items()], [])))
draw(G, with_labels=True, node_size=2000,font_size=16, arrows=True)
show()
