def masterMind(codeBreaker, codeMaker):
    open_set = set()
    closed_set = set()
    prev_state = {}
    g = {}
    h = {}
    path = []

    store = {}
    store[codeBreaker] = {
        'attempt': codeBreaker,
        'taken': codeBreaker,
        'free': str([i * (4 - codeBreaker.count(i)) for i in ['b', 'y', 'c', 'z', 'p']])
    }

    end = False
    open_set.add(codeBreaker)
    g[codeBreaker] = 0
    h[codeBreaker] = heuristics(store[codeBreaker], codeMaker)
    prev_state[codeBreaker] = None

    while open_set and not end:
        state = None
        for next_state in open_set:
            h[next_state] = heuristics(store[next_state], codeMaker)
            if state is None or g[next_state] + h[next_state] < g[state] + h[state]:
                state = next_state

        if state == codeMaker:
            end = True
            break

        for ns in findNext(store[state]):
            store[ns['attempt']] = ns
            if ns['attempt'] not in open_set and ns['attempt'] not in closed_set:
                open_set.add(ns['attempt'])
                prev_state[ns['attempt']] = state
                h[ns['attempt']] = heuristics(ns, codeMaker)
                g[ns['attempt']] = g[state] + h[ns['attempt']]
            elif g[ns['attempt']] > g[state] + h[ns['attempt']]:
                g[ns['attempt']] = g[state] + h[ns['attempt']]
                prev_state[ns['attempt']] = state
                if ns['attempt'] in closed_set:
                    closed_set.remove(ns['attempt'])
                    open_set.add(ns['attempt'])

        open_set.remove(state)
        closed_set.add(state)

    if end:
        prev = state
        while prev_state[prev] is not None:
            path = [prev] + path
            prev = prev_state[prev]
        path = [codeBreaker] + path

    return path


# To be implemented
def heuristics(state, codeMaker):
    ret = 0
    for i in range(0, 4):
        if codeMaker[i] == state['attempt'][i]:
            ret += 5
        elif codeMaker[i] in state['attempt']:
            ret += 1
    
    return len(state['taken'])*5 - ret


def findNext(state):
    newStates = []
    codeBreaker = state['attempt']
    free = state['free']
    taken = state['taken']

    for f in free:
        newStates += [
            {
                'attempt': f + codeBreaker[1:],
                'free': free.replace(f, "", 1),
                'taken': taken + f
            },
            {
                'attempt': codeBreaker[0] + f + codeBreaker[2:],
                'free': free.replace(f, "", 1),
                'taken': taken + f
            },
            {
                'attempt': codeBreaker[:2] + f + codeBreaker[3],
                'free': free.replace(f, "", 1),
                'taken': taken + f
            },
            {
                'attempt': codeBreaker[:3] + f,
                'free': free.replace(f, "", 1),
                'taken': taken + f
            }
        ]

    return list(filter(isValid, newStates))


def isValid(state):
    return len(state['taken']) <= 20


road2Success = masterMind("bcyp", "pzbc")
for step in road2Success:
    print(step)
