# Implementirati Backtracking traženje u kombinaciji sa Forward checking tehnikom i LCV heuristikom za bojenje čvorova grafa sa tri boje (crvena, zelena i plava) tako da ni jedna dva susedna čvora nemaju istu boju.

def backTrackingWithLCV(graph, colors):
    state = {
        'prev': None,
        'colored': set(),
        'plain': [(x, set(colors)) for x in graph.keys()]
    }
    while state:
        examine = state['plain'][-1]
        change = getChanges(state['plain'][:-1], examine, graph[examine[0]])
        if validState(change[1]):
            state = {
                'prev': state,
                'colored': state['colored'] | set(change[0]),
                'plain': change[1]
            }
            if endState(state):
                return state
        elif state['plain'][-1][1]:
            state['plain'][-1][1].remove(change[0][1])
        else:
            state = state['prev']
    return None

def validState(state):
    for plain in state:
        if not plain[1]:
            return False
    return True

def endState(state):
    return not state['plain']

def getChanges(plain, current, graph):
    col = min()