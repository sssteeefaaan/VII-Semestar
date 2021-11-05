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
        #nx.draw_networkx(G)
        nx.draw_networkx(G, pos=None, arrows=True)
        plt.pause(60)

G = Graph()
nodes = []
for s in "abcdefghijkl":
    nodes.append(s)
    
rand = random()

while True:
    G.addEdge(nodes[])
    G.visualize()
