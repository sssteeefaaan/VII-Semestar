from functools import reduce
from matplotlib.pyplot import show
from networkx import DiGraph, draw


def display(grph):
    G = DiGraph()
    G.add_edges_from(list(
        reduce(lambda acc, el: acc + [(el[0], x) for x in el[1]],
               [(key, val) for (key, val) in grph.items()],
               [])
    ))
    draw(G,
         with_labels=True,
         node_size=2000,
         font_size=16,
         arrows=True,
         arrowsize=20)
    show()
