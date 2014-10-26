# Задача на программирование.
# Дан ориентированный граф на n вершинах и m рёбрах (1≤n≤100000, 0≤m≤100000).
# Выведите количество компонент сильной связности в данном графе.
import sys
from collections import defaultdict
sys.setrecursionlimit(20000)


def prepare_data():
    n, m = (int(x) for x in input().split())
    _graph = defaultdict(list)
    _transp_graph = defaultdict(list)
    _visited = defaultdict(int)
    _transp_visited = defaultdict(int)

    for i in range(1, n+1):
        _graph[i] = list()
        _transp_graph[i] = list()
        _visited[i] = 0
        _transp_visited[i] = 0

    for i in range(0, m):
        source, dest = (int(x) for x in input().split())
        _graph[source].append(dest)
        _transp_graph[dest].append(source)

    return _graph, _transp_graph, _visited, _transp_visited


graph, transp_graph, visited, transp_visited = prepare_data()

transp_verticies = list()


def explore_transp(_graph, vertex):
    transp_visited[vertex] = 1
    for _vertex in _graph[vertex]:
        if not transp_visited[_vertex]:
            explore_transp(_graph, _vertex)
    transp_verticies.insert(0, vertex)


def dfs_transp(_graph):
    for v in _graph.keys():
        if not transp_visited[v]:
            explore_transp(_graph, v)


def explore(_graph, vertex):
    visited[vertex] = 1
    for _vertex in _graph[vertex]:
        if not visited[_vertex]:
            explore(_graph, _vertex)


def dfs(_graph, _transp_verticies):
    ccnum = 0
    for v in _transp_verticies:
        if not visited[v]:
            ccnum += 1
            explore(_graph, v)
    return ccnum


def scc(_graph, _transp_graph):
    dfs_transp(_transp_graph)
    return dfs(_graph, transp_verticies)


print(scc(graph, transp_graph))