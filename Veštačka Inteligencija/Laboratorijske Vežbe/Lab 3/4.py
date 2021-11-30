def findPath(player, end):
    queue = [[player]]
    while queue:
        curr, *queue = queue
        pos = curr[-1]
        for vrsta in range(0, 6):
            nextPos = (vrsta, (pos[0] + pos[1] + vrsta + 1) % 6)
            if nextPos == end:
                return curr + [end]
            if nextPos not in curr:
                queue += [curr + [nextPos]]
    return []


print(findPath((1, 2), (3, 4)))
