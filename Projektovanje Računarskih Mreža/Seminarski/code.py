import networkx as nx
import matplotlib.pyplot as plt


class Graph:
    
    def __init__(self):
        self.edges = []
    
    def addEdge(self, a, b):
        self.edges.append([a, b])
        
    def visualize(self):
        G = nx.Graph()
        G.add_edges_from(self.edges)
        nx.draw_networkx(G)
        plt.show()

G = Graph()
G.addEdge('a', 'b')
G.addEdge('a', 'c')
G.addEdge('b', 'd')
G.addEdge('c', 'd')
G.addEdge('b', 'e')
G.addEdge('e', 'f')
G.visualize()
