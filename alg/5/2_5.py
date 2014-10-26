#Задача на программирование.
# Дан неориентированный граф в следующем стандартном формате.
# Первая строка содержит два числа $n$ и $m$ ($1 \le n, m \le 1000$) — количества вершин и рёбер в графе.
# Следующие $m$ строк содержат описания ребер — номера вершин, соединенных ребром.
# Вершины нумеруются от 1 до $n$. Последняя строка содержит пару чисел $u$ и $v$ — номера вершин.
# Если из $u$ достижима $v$ (другими словами, $u$ и $v$ лежат в одной компоненте связности),
# необходимо вывести 1, иначе — 0.

from collections import defaultdict


def prepare_data():
    n, m = (int(x) for x in input().split())
    vertices = defaultdict(list)
    visited = defaultdict(int)

    for i in range(1, n+1):
        vertices[i] = list()
        visited[i] = 0

    for i in range(0, m):
        source, dest = (int(x) for x in input().split())
        vertices[source].append(dest)
        vertices[dest].append(source)

    u, v = [int(x) for x in input().split()]
    return vertices, u, v, visited


vertices, u, v, visited = prepare_data()


def explore(vertex):
    visited[vertex] = 1
    for _vertex in vertices[vertex]:
        if not visited[_vertex]:
            explore(_vertex)


explore(u)
print(visited[v])