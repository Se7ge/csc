def prepare_data():
    n = int(input())
    values = list(map(lambda x: int(x), input().split()))
    return n, values

counter = 0


def _merge(a, b):
    global counter
    res = []
    ia = 0
    ib = 0
    for i in range(0, len(a) + len(b)):
        if ia == len(a) or ib == len(b):
            break
        if a[ia] <= b[ib]:
            res.append(a[ia])
            ia += 1
        else:
            res.append(b[ib])
            ib += 1
            counter += len(a) - ia
    if ia < len(a):
        res.extend(a[ia:len(a)])
        # counter += (len(a) - ia) * (len(a) + len(b) - ia)
    if ib < len(b):
        res.extend(b[ib:len(b)])
    return res


def merge_sort(a):
    q = list()
    for i in range(0, len(a)):
        q.append([a[i]])
    while len(q) > 1:
        q.append(_merge(q.pop(0), q.pop(0)))
    return q


def recursive_merge_sort(a):
    length = len(a)

    if length == 1:
        return a
    m = length // 2
    return _merge(recursive_merge_sort(a[0:m]), recursive_merge_sort(a[m:length]))


def naive_counter(a):
    cntr = 0
    for i in range(0, len(a)):
        for j in range(i + 1, len(a)):
            if a[i] > a[j]:
                cntr += 1
    return cntr


# n, values = prepare_data()
import random
values = [i for i in range(1, 100)]
random.shuffle(values)
# values = [2, 3, 9, 1, 7, 4]
# values = [2, 3, 9, 2, 9, 1]
res = recursive_merge_sort(values)
print(counter)
print(naive_counter(values))