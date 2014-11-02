# Задача на программирование повышенной сложности.
# Дан ориентированный взвешенный граф и вершина s в нем.
# Требуется для каждой вершины u найти длину кратчайшего пути из s в u.

# Первая строка содержит три числа n, m и s (1≤s≤n≤1000,0≤m≤10000) — количество вершин,
# рёбер и стартовая вершина, соответственно.
# Следующие m строк содержат описание ребер графа (граф может содержать кратные рёбра).
# Вес ребра по модулю не превосходит 109 (веса — целые числа).
# Для каждой вершины u в отдельной строке выведите:

# *, если в графе нет пути из s в u;
# -, если путь из s в u есть, но кратчайшего пути из s в u нет;
# длину кратчайшего пути из s в u, если такой пусть есть.

from collections import defaultdict


def prepare_data():
    n, m, s = (int(x) for x in input().split())
    _vertices = defaultdict(list)
    _dist = defaultdict(int)

    for i in range(1, n + 1):
        _vertices[i] = list()
        _dist[i] = float('inf')

    for i in range(0, m):
        source, dest, weight = (int(x) for x in input().split())
        _vertices[source].append((dest, weight))
    return _vertices, _dist, s


graph, dist, start = prepare_data()


def explore(_graph, vertex, last_relaxed):
    last_relaxed[vertex] = True
    for edge in _graph[vertex]:
        if not last_relaxed[edge[0]]:
            explore(_graph, edge[0], last_relaxed)
    return last_relaxed


def bellman_ford(_graph, _dist, s):
    _dist[s] = 0

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

    last_relaxed = defaultdict(bool)
    result_dist = _dist.copy()
    for i in range(1, len(_graph) + 1):
        for edge in _graph[i]:
            if _dist[edge[0]] > _dist[i] + edge[1]:
                _dist[edge[0]] = _dist[i] + edge[1]
                last_relaxed[edge[0]] = True
                last_relaxed = explore(_graph, edge[0], last_relaxed)

    return result_dist, last_relaxed

result, flags = bellman_ford(graph, dist, start)
for idx in range(1, len(result) + 1):
    if result[idx] == float('inf'):
        print('*')
    elif flags[idx]:
        print('-')
    else:
        print(result[idx])