# Задача на программирование.
# Дан неориентированный граф на n вершинах и m рёбрах (1≤n,m≤100000), а также номера вершин u и v.
# Выведите количество рёбер на кратчайшем пути между вершинами u и v или -1,
# если пути между ними в графе нет.

from collections import defaultdict, deque


def prepare_data():
    n, m = (int(x) for x in input().split())
    _vertices = defaultdict(list)
    _dist = defaultdict(int)

    for i in range(1, n+1):
        _vertices[i] = list()
        _dist[i] = float('inf')

    for i in range(0, m):
        source, dest = (int(x) for x in input().split())
        _vertices[source].append(dest)
        _vertices[dest].append(source)

    _u, _v = [int(x) for x in input().split()]
    return _vertices, _u, _v, _dist


graph, u, v, dist = prepare_data()


def bfs(_graph, _dist, _u):
    queue = deque([])
    _dist[_u] = 0
    queue.append(_u)
    while len(queue):
        vertex = queue.popleft()
        for child in _graph[vertex]:
            if _dist[child] == float('inf'):
                queue.append(child)
                _dist[child] = _dist[vertex] + 1
    return _dist


distance = bfs(graph, dist, u)
print(distance[v] if distance[v] != float('inf') else -1)