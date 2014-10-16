def prepare_data():
    n, m = (int(x) for x in input().split())
    _start = []
    _end = []
    for i in range(0, n):
        a, b = (int(x) for x in input().split())
        _start.append(a)
        _end.append(b)
    _points = [int(x) for x in input().split()]
    return _start, _end, _points


def partition(a, l, r):
    x = a[l]
    j = l
    for i in range(l+1, r):
        if a[i] <= x:
            j += 1
            if i != j:
                a[i], a[j] = a[j], a[i]
    a[l], a[j] = a[j], a[l]
    return j


def qsort(a, l, r):
    while l < r - 1:
        m = partition(a, l, r)
        qsort(a, l, m)
        l = m + 1


def naive_counter(a, b, x):
    result = [0] * len(x)
    checked = []
    for i in range(0, len(x)):
        if x[i] in checked:
            result[i] = result[checked.index(x[i])]
        else:
            for j in range(0, len(a)):
                if a[j] <= x[i] <= b[j]:
                    result[i] += 1
        checked.append(x[i])
    return result


# start, end, points = prepare_data()
# print(' '.join([str(x) for x in naive_counter(start, end, points)]))


import random
points = [i for i in range(1, 100)]
random.shuffle(points)
print(points)
qsort(points, 0, len(points))
print(points)

#import random
#values = [i for i in range(1, 100)]
#random.shuffle(values)
# values = [2, 3, 9, 1, 7, 4]
# values = [2, 3, 9, 2, 9, 1]
#res = recursive_merge_sort(values)
#print(counter)
#print(naive_counter(values))