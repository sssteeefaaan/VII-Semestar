# Nije dobro

N = 3
graph = { str(xKey): [str(xValue) for xValue in range(1, N + 1) if xValue is not xKey] for xKey in range(1, N + 1) }
domain = range(1, N + 1)

def backtracting_with_forward_checking_and_mvr(G, dom):
    stack = [{
        'unplaced' : list(G.keys()),
        'domain' : { x: list(dom) for x in G.keys() },
        'placed': {},
        'prev': None
    }]
    solution = None
    while stack and not solution:
        top, *stack = stack
        if not top['unplaced']:
            solution = top['placed']
        else:
            to_place = top['unplaced'][0]
            potential = list(top['domain'][to_place])
            for n in G[to_place]:
                if top['placed'].get(n, None):
                    spot = (int(n), int(top['placed'].get(n, None)))
                    if spot[1] in potential:
                        potential.remove(spot[1])
                    if spot[1] - spot[0] + int(to_place) in potential:
                        potential.remove(spot[1] - spot[0] + int(to_place))
            if potential:
                newDomain = dict(top['domain'])
                newDomain[to_place] = potential
                for n in G[to_place]:
                    if potential[0] in newDomain[n]:
                        newDomain[n] = list(filter(lambda x: x not in [potential[0], potential[0] + int(to_place) - int(n)], newDomain[n]))
                stack.append({
                    'unplaced': sorted([x for x in top['unplaced'] if x is not to_place], key=lambda x: len(newDomain[x])),
                    'domain': newDomain,
                    'placed': top['placed'] | { to_place: potential[0] },
                    'prev': top
                })
            elif top['prev']:
                stack.append(top['prev'])
    return solution

sol = backtracting_with_forward_checking_and_mvr(graph, domain)
for i in range(1, N + 1):
    print(str(i) + '\t|\t', end='')
    print(' \t' * (sol[str(i)] - 1), end='')
    print(str(sol[str(i)]) + '\t', end='')
    print((' \t' * (N - sol[str(i)])) + '|')