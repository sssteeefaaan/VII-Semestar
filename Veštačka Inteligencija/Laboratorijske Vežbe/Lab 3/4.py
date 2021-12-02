def findPath(player, end):
    queue = [[player]]
    while queue:
        curr, *queue = queue
        for nextPos in findNext(curr[-1]):
            if nextPos == end:
                return curr + [end]
            if nextPos not in curr:
                queue += [curr + [nextPos]]
    return []


def findPathAStar(player, end):
    open_set = set()
    closed_set = set()
    prev_state = {}
    g = {}
    h = {}
    path = []

    found_end = False
    open_set.add(player)
    g[player] = 0
    h[player] = heuritics(player, end)
    prev_state[player] = None

    while open_set and not found_end:
        state = None
        for next_state in open_set:
            h[next_state] = heuritics(next_state, end)
            if state is None or g[next_state] + h[next_state] < g[state] + h[state]:
                state = next_state

        if state == end:
            found_end = True
            break

        for ns in findNext(state):
            if ns not in open_set and ns not in closed_set:
                open_set.add(ns)
                prev_state[ns] = state
                h[ns] = heuritics(ns, end)
                g[ns] = g[state] + h[ns]
            elif g[ns] > g[state] + h[ns]:
                g[ns] = g[state] + h[ns]
                prev_state[ns] = state
                if ns in closed_set:
                    closed_set.remove(ns)
                    open_set.add(ns)

        open_set.remove(state)
        closed_set.add(state)

    if found_end:
        prev = end
        while prev_state[prev] is not None:
            path = [prev] + path
            prev = prev_state[prev]
        path = [player] + path

    return path


def heuritics(s, e):
    return abs(s[0] - e[0]) + abs(s[1] - e[1])


def findNext(state):
    newStates = []
    for vrsta in range(0, 6):
        newStates += [(vrsta, (state[0] + state[1] + vrsta + 1) % 6)]
    return newStates


def printBoard(s, c):
    for i in range(0, 6):
        for j in range(0, 6):
            temp = " |  "
            if (i, j) == c:
                temp = " | c"
            if (i, j) == s:
                temp = " | s"
            print(temp, end="")
        print(" |")


def main():
    start = (0, 4)
    end = (3, 4)

    print('\n***** Branch *****')
    for step in findPath(start, end):
        print("\nStep", end="\n\n")
        printBoard(step, end)

    print('\n\n***** A* *****')
    for step in findPathAStar(start, end):
        print("\nStep", end="\n\n")
        printBoard(step, end)


main()
