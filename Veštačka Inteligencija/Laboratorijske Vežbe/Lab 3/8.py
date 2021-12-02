from functools import reduce
import operator
import copy

# To be implemented


def heuritics(s):
    return 0


def findNext(state):
    newStates = []
    table = state['table']
    taken = state['taken']
    free = state['free']

    for i in range(0, 3):
        for j in range(0, 3):
            if table[i][j] == 0:
                for el in free:
                    cp = copy.deepcopy(table)
                    cp[i][j] = el
                    newStates += [{
                        'table': cp,
                        'taken': taken | set([el]),
                        'free': set(filter(lambda a: a != el, free))
                    }]

    return list(filter(isValid, newStates))


def isValid(state):
    table = state['table']
    free = state['free']
    for r in [list(filter(lambda y: y != 0, x)) for x in table]:
        rSum = reduce(operator.add, r, 0)
        if len(r) == 3 and rSum != 15:
            return False
        elif len(r) == 2 and (15 - rSum) not in free:
            return False
    for c in [list(filter(lambda y: y != 0, x)) for x in list(zip(*table))]:
        cSum = reduce(operator.add, c, 0)
        if len(c) == 3 and cSum != 15:
            return False
        elif len(c) == 2 and (15 - cSum) not in free:
            return False
    return True


def isComplete(state):
    table = state['table']
    for r in table:
        if reduce(operator.add, r, 0) != 15:
            return False
    for c in list(zip(*table)):
        if reduce(operator.add, c, 0) != 15:
            return False
    return True


def pseudokuBranch(table):
    initialState = {
        'table': table,
        'taken': set([x for y in table for x in y if x != 0])
    }
    initialState['free'] = set([x for x in range(
        1, 10) if x not in initialState['taken']])

    examine = [[initialState]]
    solutions = []
    while examine:
        *examine, currentState = examine
        for nextState in findNext(currentState[-1]):
            if isComplete(nextState) and nextState['table'] not in list(map(lambda x: x[-1], solutions)):
                solutions += [list(map(lambda x: x['table'],
                                   currentState + [nextState]))]
                #return solutions[-1]
            elif len(nextState['free']):
                examine += [currentState + [nextState]]
    return solutions


def pseudokuAStar(table):
    open_set = set()
    closed_set = set()
    prev_state = {}
    g = {}
    h = {}
    path = []

    store = {'0': {}}
    store['0']['table'] = table
    store['0']['taken'] = set([x for y in table for x in y if x != 0])
    store['0']['free'] = set(
        [x for x in range(1, 10) if x not in store['0']['taken']])

    end = False
    open_set.add('0')
    g['0'] = 0
    h['0'] = heuritics(store['0'])
    prev_state['0'] = None

    while open_set and not end:
        state = None
        for next_state in open_set:
            h[next_state] = heuritics(store[next_state])
            if state is None or g[next_state] + h[next_state] < g[state] + h[state]:
                state = next_state

        if isComplete(store[state]):
            end = True
            break

        for ns in findNext(store[state]):
            k = str(len(store.keys()))
            store |= {
                k: ns
            }
            if k not in open_set and k not in closed_set:
                open_set.add(k)
                prev_state[k] = state
                h[k] = heuritics(ns)
                g[k] = g[state] + h[k]
            elif g[k] > g[state] + h[k]:
                g[k] = g[state] + h[k]
                prev_state[k] = state
                if k in closed_set:
                    closed_set.remove(k)
                    open_set.add(k)

        open_set.remove(state)
        closed_set.add(state)

    if end:
        prev = state
        while prev_state[prev] is not None:
            path = [store[prev]['table']] + path
            prev = prev_state[prev]
        path = [table] + path

    return path


def main():

    print("A*:", end="\n"*2)
    road2Success = pseudokuAStar([[1, 0, 0], [8, 0, 0], [0]*3])
    for step in road2Success:
        for row in step:
            for val in row:
                print("\t", val, end=" ")
            print()
        print("-" * 40)

    print("\nBranch, all solutions:", end="\n"*2)
    sols = pseudokuBranch([[1, 0, 0], [0]*3, [0, 0, 3]])
    for i in range(0, len(sols)):
        print("*"*50)
        print(f'\t\tSolution #{i + 1}')
        print("*"*50)
        for step in sols[i]:
            for row in step:
                for val in row:
                    print("\t", val, end=" ")
                print()
            print("-" * 40)


if __name__ == "__main__":
    main()
