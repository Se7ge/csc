# Задача на программирование.
# Дан взвешенный ориентированный граф на n вершинах и m рёбрах (1≤n≤1000, 0≤m≤10000).
# Вес ребра — целое число, по модулю не превышающее 1000.
# Выведите 1, если в графе есть цикл отрицательного веса, и 0 в противном случае.

from collections import defaultdict


def prepare_data():
    n, m = (int(x) for x in input().split())
    _vertices = defaultdict(list)
    _dist = defaultdict(int)

    for i in range(1, n+1):
        _vertices[i] = list()
        _dist[i] = 1001

    for i in range(0, m):
        source, dest, weight = (int(x) for x in input().split())
        _vertices[source].append((dest, weight))
    return _vertices, _dist, n, m


graph, dist, num_vertex, num_edge = prepare_data()


def check_by_bellman_ford(_graph, _dist):

    relaxed = True
    for k in range(0, len(_graph)):
        if not relaxed:
            break
        relaxed = False
        for i in range(1, len(_graph) + 1):
            for edge in _graph[i]:
                if _dist[edge[0]] > _dist[i] + edge[1]:
                    _dist[edge[0]] = _dist[i] + edge[1]
                    relaxed = True

    return relaxed


if num_edge:
    result = check_by_bellman_ford(graph, dist)
    print(int(result))
else:
    print(0)