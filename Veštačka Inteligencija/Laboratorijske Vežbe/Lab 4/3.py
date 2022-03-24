from display import display2

graph = {
    'A' : ['B', 'C'],
    'B' : ['A', 'D'],
    'C' : ['A', 'E', 'B'],
    'D' : ['B', 'E'],
    'E' : ['C', 'D']
}

colors = set({ 'R', 'G', 'B' })

def backtracting_with_forward_checking_and_degree(G, c):
    stack = [{
        'uncolored' : sorted(list(G.keys()), key=lambda x: len(G[x]), reverse=True),
        'domain' : { x: list(c) for x in G.keys() },
        'colored': {},
        'prev': None
    }]
    solution = None
    while stack and not solution:
        top, *stack = stack
        if not top['uncolored']:
            solution = top['colored']
        else:
            to_color = top['uncolored'][0]
            potential = list(top['domain'][to_color])
            for n in G[to_color]:
                if top['colored'].get(n, None) and top['colored'][n] in potential:
                    potential.remove(top['colored'][n])
            if potential:
                newDomain = dict(top['domain'])
                newDomain[to_color] = potential
                for n in G[to_color]:
                    if potential[0] in newDomain[n]:
                        newDomain[n].remove(potential[0])
                stack.append({
                    'uncolored': list(filter(lambda x: x is not to_color, top['uncolored'])),
                    'domain': newDomain,
                    'colored': top['colored'] | { to_color: potential[0] },
                    'prev': top
                })
            elif top['prev']:
                stack.append(top['prev'])
    return solution

sol = backtracting_with_forward_checking_and_degree(graph, colors)
print(sol)
if sol:
    display2(graph, sol)