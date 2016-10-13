def initialize(graph, source):
    d = {}
    for node in graph:
        d[node] = float('Inf')
    d[source] = 0
    return d

def relax(u, v, graph, d):
    if d[v] > d[u] + graph[u][v]:
        d[v]  = d[u] + graph[u][v]

def bellman_ford(graph, source):
    d = initialize(graph, source)
    for i in range(len(graph)-1):
        for u in graph:
            for v in graph[u]:
                relax(u, v, graph, d)
    for u in graph:
        for v in graph[u]:
            assert d[v] <= d[u] + graph[u][v]
    return d

def test():
    
    graph = {
        'a': {'b': 1, 'c':  4},
        'b': {'c':  3, 'd':  2, 'e':  2},
        'c': {},
        'd': {'b':  1, 'c':  5},
        'e': {'d': -2}
        }
    
    d= bellman_ford(graph, 'a')
    print("cost="+str(d['d']))

if __name__ == '__main__': test()