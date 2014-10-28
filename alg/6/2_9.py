# Задача на программирование.
# Дан ориентированный взвешенный граф на n вершинах и m рёбрах (1≤n≤1000, 0≤m≤100000).
# Вес ребра — натуральное число, не превышающее 1000.
# Последняя строка содержит номера двух вершин u и v.
# Выведите кратчайшее расстояние между вершинами u и v или -1, если в графе нет пути из u в v.

from collections import defaultdict, deque
import heapq


def prepare_data():
    n, m = (int(x) for x in input().split())
    _vertices = defaultdict(list)
    _dist = defaultdict(int)

    for i in range(1, n+1):
        _vertices[i] = list()
        _dist[i] = float('inf')

    for i in range(0, m):
        source, dest, weight = (int(x) for x in input().split())
        _vertices[source].append((dest, weight))

    _u, _v = [int(x) for x in input().split()]
    return _vertices, _u, _v, _dist


graph, u, v, dist = prepare_data()


def make_queue(_dist):
    source = [(value, key) for key, value in _dist.items()]
    heapq.heapify(source)
    return source


def Dijkstra(_graph, _dist, _u):
    # _prev = defaultdict(int)
    _dist[_u] = 0
    copy_dist = _dist.copy()

    queue = make_queue(copy_dist)
    while len(queue):
        vertex = heapq.heappop(queue)
        del copy_dist[vertex[1]]
        for edge in _graph[vertex[1]]:
            if _dist[edge[0]] > _dist[vertex[1]] + edge[1]:
                _dist[edge[0]] = _dist[vertex[1]] + edge[1]
                if edge[0] in copy_dist:
                    copy_dist[edge[0]] = _dist[edge[0]]
                    queue = make_queue(copy_dist)
                # _prev[edge[0]] = vertex[1]
    return _dist


distance = Dijkstra(graph, dist, u)
print(distance[v] if distance[v] != float('inf') else -1)