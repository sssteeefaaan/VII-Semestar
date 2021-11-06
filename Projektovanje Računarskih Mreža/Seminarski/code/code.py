import networkx as nx
import matplotlib.pyplot as plt
from networkx.algorithms.shortest_paths import weighted
from numpy.core.arrayprint import DatetimeFormat
import alert as al
import compareFuncs as cFunc
import xml_csv as util

url = 'https://archive.ll.mit.edu/ideval/data/2000/LLS_DDOS_1.0/data_and_labeling/tcpdump_dmz/mid-level-phase-3.xml'
fileName = util.downloadXML(url)
parsedData = util.parseXML(f'{fileName}.xml')

G = nx.Graph()
A = []
#c = [0] + [1/12] * 12
c = [0, 0.09, 0.09, 0.05, 0.05, 0.05, 0.15, 0.09, 0.05, 0.15, 0.09, 0.1, 0.04]
h = [cFunc.equals] + [cFunc.dateCmp] + [cFunc.timeCmp] + [cFunc.sessionCmp] + [cFunc.equals] + ([cFunc.equals] + [cFunc.addressCmp] + [cFunc.portCmp]) * 2 + [cFunc.equals] * 2
t = 0.75

for row in parsedData:
    a = al.Alert(row)
    
    G.add_nodes_from([
        (a.id, {
            # attributes
            #'key': 'value'
            })
        ])
    
    for node in A:
        weight = cFunc.F(a.getVector(), node.getVector(), c, h)
        if weight >= t:
            G.add_weighted_edges_from([(a.id, node.id, weight)])
                # attributes
                #'key': 'value'
                # weight = str(weight),
                # label = str(weight)
    
    nx.draw_networkx(G)
    plt.pause(0.05)
    plt.clf()
    
    A.append(a)

util.savetoCSV(list(map(lambda x: x.__dict__, A)), f'{fileName}.csv')
nx.draw_networkx(G)
plt.show()