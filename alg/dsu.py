rank, a = {}, {}


def make_set(x):
    a[x] = x
    rank[x] = 0


def find(x):
    if x != a[x]:
        a[x] = find(a[x])
    return a[x]


def union(x, y):
    px = find(x)
    py = find(y)
    a[px] = a[py]


def prepare_data():
    operations = []

    n, m = map(lambda x: int(x), input().split())
    for i in range(m):
        operations.append(input().split())

    return n, m, operations


def just_do_it():
    n, m, operations = prepare_data()
    for i in range(1, n+1):
        make_set(i)

    for operation in operations:
        if operation[0] == 'Check':
            print(find(int(operation[1])) == find(int(operation[2])))
        elif operation[0] == 'Union':
            union(int(operation[1]), int(operation[2]))


if __name__ == '__main__':
    just_do_it()