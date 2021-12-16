# Implementirati Backtracking traženje u kombinaciji sa Forward checking tehnikom i LCV heuristikom za bojenje čvorova grafa sa tri boje (crvena, zelena i plava) tako da ni jedna dva susedna čvora nemaju istu boju.

def backtracking_with_LCV(graph, colors, maxChange=50):
    state = {
        'prev': None,
        'colored': set(),
        'plain': [(x, set(colors)) for x in graph.keys()]
    }
    changeNumb = 0
    while state:
        examine = state['plain'][-1]
        change = getChanges(state['plain'][:-1], examine, graph[examine[0]])
        if validState(change[1]):
            state = {
                'prev': state,
                'colored': state['colored'] | set([change[0]]),
                'plain': change[1]
            }
            changeNumb += 1
            if endState(state):
                break
        elif maxChange > changeNumb:
            state = state['prev']
        else:
            break
    return state


def validState(state):
    for plain in state:
        if not plain[1]:
            return False
    return True


def endState(state):
    return not state['plain']


def getChanges(plain, current, neighbours):
    uncoloredNeighbours = [x for x in plain if x[0] in neighbours]
    rest = [x for x in plain if x not in uncoloredNeighbours]
    countChoice = {x: 0 for x in current[1]}
    for uncoloredNeighbour in uncoloredNeighbours:
        for color in uncoloredNeighbour[1]:
            if color in countChoice.keys():
                countChoice[color] += 1
    col = sorted(countChoice.items(), key=lambda x: x[1])[0][0]
    return ((current[0], col), rest + list(map(lambda x: (x[0], set([y for y in x[1] if y != col])), uncoloredNeighbours)))


def main():
    graph = {
        '1': ['2', '3'],
        '2': ['1', '3', '5'],
        '3': ['1', '2', '4'],
        '4': ['3', '5'],
        '5': ['2', '4']
    }
    colors = ['R', 'G', 'B']

    result = backtracking_with_LCV(graph, colors)
    if result:
        print("Result: ", result['colored'])
    else:
        print("Max depth reached!")


if __name__ == "__main__":
    main()
