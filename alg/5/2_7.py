# Задача на программирование.
# Дан неориентированный граф, содержащий $n$ вершин и $m$ рёбер ($1 \le n \le 1000$, $0 \le m \le 1000$).
# Необходимо вывести количество компонент связности в заданном графе.

from collections import defaultdict


def prepare_data():
    n, m = (int(x) for x in input().split())
    _graph = defaultdict(list)
    _visited = defaultdict(int)

    for i in range(1, n+1):
        _graph[i] = list()
        _visited[i] = 0

    for i in range(0, m):
        source, dest = (int(x) for x in input().split())
        _graph[source].append(dest)
        _graph[dest].append(source)

    return _graph, _visited


graph, visited = prepare_data()


def explore(vertex):
    visited[vertex] = 1
    for _vertex in graph[vertex]:
        if not visited[_vertex]:
            explore(_vertex)


def dfs(_graph):
    ccnum = 0
    for v in _graph.keys():
        if not visited[v]:
            ccnum += 1
            explore(v)
    return ccnum

print(dfs(graph))