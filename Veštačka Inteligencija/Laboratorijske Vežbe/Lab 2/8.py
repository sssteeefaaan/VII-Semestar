# Napisati funkciju koja određuje put između zadatog polaznog i ciljnog čvora neorijentisanog grafa tako što istovremeno pokrede traženje po širini od polaznog i od ciljnog čvora. Traženje se završava kada se nađe prvi zajednički čvor za oba traženja

def findPathDouble(graph, startNode, endNode):
    path = []
    queueStart = [[startNode]]
    queueEnd = [[endNode]]
    while queueStart and queueEnd:
        headStart, *queueStart = queueStart
        headEnd, *queueStart = queueEnd

        for n in graph[headStart[-1]]:
            if n == headEnd[0]:
                path = headStart + headEnd
                queueStart.clear()
            elif n not in headStart:
                queueStart += [headStart + [n]]
        
        for n in graph[headEnd[0]]:
            if n == headStart[-1]:
                path = headStart + headEnd
                queueEnd.clear()
            elif n not in headEnd:
                queueEnd = [[n] + headEnd]
                
    return path

zadati_graf = {
    'A': ['B', 'C', 'D'],
    'B': ['E', 'F', 'G'],
    'C': ['H', 'A', 'B'],
    'D': ['C', 'E', 'F'],
    'E': ['G', 'H', 'A'],
    'F': ['B', 'C', 'D'],
    'G': ['E', 'F', 'H'],
    'H': ['J'],
    'J': []
}
print(findPathDouble(zadati_graf, 'A', 'J'))
