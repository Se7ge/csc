# Задача на программирование.
# Дан ациклический ориентированный граф на n вершинах и m рёбрах (1≤n≤100000, 0≤m≤100000).
# Необходимо вывести n чисел — номера вершин в порядке любой топологической сортировки.

from collections import defaultdict


def prepare_data():
    n, m = (int(x) for x in input().split())
    _graph = defaultdict(list)
    _visited = defaultdict(int)
    _times = defaultdict(list)

    for i in range(1, n+1):
        _graph[i] = list()
        _visited[i] = 0
        _times[i] = [0, 0]

    for i in range(0, m):
        source, dest = (int(x) for x in input().split())
        _graph[source].append(dest)

    return _graph, _visited, _times


graph, visited, times = prepare_data()
sorted_graph = list()


def explore(vertex):
    visited[vertex] = 1
    for _vertex in graph[vertex]:
        if not visited[_vertex]:
            explore(_vertex)
    sorted_graph.insert(0, str(vertex))


def dfs(_graph):
    for v in _graph.keys():
        if not visited[v]:
            explore(v)


dfs(graph)
print(' '.join(sorted_graph))