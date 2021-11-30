def findShortestPath(player, end):
    path = []
    queue = [[player]]
    while queue:
        curr, *queue = queue
        pos = curr[-1]
        nextPos = (pos[0] + (1 if end[0] > pos[0] else -1 if end[0] < pos[0]
                             else 0), pos[1] + (1 if end[1] > pos[1] else -1 if end[1] < pos[1] else 0))
        if nextPos == end and (not path or len(curr) + 1 < len(path)):
            path = curr + [end]
        elif nextPos not in curr:
            queue += [curr + [nextPos]]
    return path


print(findShortestPath((5, 5), (5, 1)))
