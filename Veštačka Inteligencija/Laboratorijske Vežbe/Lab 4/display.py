from functools import reduce
from matplotlib.pyplot import show
from networkx import Graph, draw_kamada_kawai

colors = {
    'R': "#FF0000",
    'G': "#00FF00",
    'B': "#0000FF",
    'Y': "#FFFF00",
    'P': "#FF00FF",
    "C": "#00FFFF",
}


def display(graph, data):
    col = [0] * len(data)
    for n in data:
        col[int(n[0]) - 1] = colors[n[1]]
    G = Graph()
    G.add_nodes_from([str(x) for x in range(1, len(data) + 1)])
    G.add_edges_from(list(
        reduce(lambda acc, el: acc + [(el[0], x) for x in el[1]],
               [(key, val) for (key, val) in graph.items()],
               [])
    ))
    draw_kamada_kawai(G,
                      with_labels=True,
                      node_size=2000,
                      font_size=16,
                      node_color=col)
    show()
