# Задача на программирование.
# Дан ориентированный граф на n вершинах и m рёбрах (1≤n,m≤1000).
# Необходимо вывести 1, если граф содержит цикл, и 0 в противном случае.

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
timer = 0


def explore(vertex):
    global timer
    result = False
    visited[vertex] = 1
    timer += 1
    times[vertex][0] = timer
    for _vertex in graph[vertex]:
        if times[_vertex][0] and times[vertex][0] > times[_vertex][0] and not times[_vertex][1]:
            return True
        if not visited[_vertex]:
            result = explore(_vertex)
    timer += 1
    times[vertex][1] = timer
    return result


def dfs(_graph):
    for v in _graph.keys():
        if not visited[v]:
            if explore(v):
                return 1
    return 0

print(dfs(graph))