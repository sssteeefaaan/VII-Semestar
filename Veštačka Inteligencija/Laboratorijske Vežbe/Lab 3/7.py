from functools import partial

def findShortestPath(player, end):
    path = []
    queue = [[player]]
    while queue:
        curr, *queue = queue
        for nextPos in findNext(curr[-1], end):
            print(nextPos)
            if nextPos == end and (not path or len(curr) + 1 < len(path)):
                path = curr + [end]
            elif nextPos not in curr:
                queue += [curr + [nextPos]]
    return path


def findNext(state, endPos):
    return list(filter(partial(isValid, state, endPos), [((state[0] + 1) % 6, state[1]), (state[0], (state[1] + 1) % 6),
                                 ((state[0] + 5) % 6, state[1]), (state[0], (state[1] + 5) % 6)]))
    
def isValid(currentPosition, endPosition, nextPosition):
    return currentPosition[0] < endPosition[0] and nextPosition[0] > currentPosition[0] or currentPosition[0] > endPosition[0] and nextPosition[0] < currentPosition[0] or currentPosition[1] < endPosition[1] and nextPosition[1] > currentPosition[1] or currentPosition[1] > endPosition[1] and nextPosition[1] < currentPosition[1]


print(findShortestPath((5, 5), (4, 3)))
