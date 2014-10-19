import sys
from math import log2

INFINITY = float('inf')


def _make_tree(data):
    size = origin_size = len(data)
    log2_size = log2(size)
    if log2(size) % 2 != 0:
        size = 2 ** int(log2_size + 1)

    tree = [0] * (2 * size - 1)

    for i in range(len(tree) - 1, -1, -1):
        if i > origin_size + size - 2:
            tree[i] = INFINITY
        elif i < size - 1:
            tree[i] = min(tree[2 * (i + 1) - 1], tree[2 * (i + 1)])
        else:
            tree[i] = data[i - size + 1]
    return tree


def tree_min(tree, l, r):
    res = INFINITY
    real_idx_start = int((len(tree) + 1) / 2)
    # идём снизу
    l = int(l) + real_idx_start - 2
    r = int(r) + real_idx_start - 2

    while l <= r:
        if l % 2 == 0:
            res = min(res, tree[l])
        if (r + 1) % 2 == 0:
            res = min(res, tree[r])
        l = int(l/2)
        r = int(r/2) - 1
    return res


def tree_set(tree, idx, value):
    index = (len(tree) + 1) / 2 + idx - 2  # у нас нумерация с 0
    tree[int(index)] = value
    while index:
        index = int((index - 1) / 2)
        tree[index] = min(tree[2 * (index + 1) - 1], tree[2 * (index + 1)])


def prepare_data():
    operations = []

    n, m = map(lambda x: int(x), input().split())
    values = list(map(lambda x: int(x), input().split()))
    for i in range(m):
        operations.append(input().split())

    return n, m, values, operations


def just_do_it():
    result = []
    n, m, values, operations = prepare_data()
    tree = _make_tree(values)

    for operation in operations:
        if operation[0] == 'Set':
            tree_set(tree, int(operation[1]), int(operation[2]))
        elif operation[0] == 'Min':
            result.append(tree_min(tree, int(operation[1]), operation[2]))
    print('\n'.join(map(lambda x: str(x), result)))


if __name__ == '__main__':
    a = [1, 2, 3, 4, 5]
    tree = _make_tree(a)
    print(tree)
    print(tree_min(tree, 1, 5))
    tree_set(tree, 1, 8)
    print(tree)
    print(tree_min(tree, 1, 5))
    print(tree_min(tree, 1, 1))
    print(tree_min(tree, 1, 3))
    tree_set(tree, 3, 1)
    print(tree)
    print(tree_min(tree, 2, 4))