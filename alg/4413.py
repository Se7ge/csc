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


def partition(a, b, l, r):
    x = a[l]
    j = l
    for i in range(l+1, r):
        if a[i] < x:
            j += 1
            if i != j:
                a[i], a[j] = a[j], a[i]
                b[i], b[j] = b[j], b[i]
    a[l], a[j] = a[j], a[l]
    b[l], b[j] = b[j], b[l]
    return j


def qsort(a, b, l, r):
    while l < r - 1:
        m = partition(a, b, l, r)
        qsort(a, b, l, m)
        l = m + 1


def naive_counter(a, b, x):
    result = [0] * len(x)
    for i in range(0, len(x)):
        for j in range(0, len(a)):
            if a[j] <= x[i] <= b[j]:
                result[i] += 1
    return result


def find_idx(arr, x):
    j = l = 0
    r = len(arr)
    for i in range(l, r):
        if arr[i] <= x:
            j += 1
        else:
            break
    return j


def qsort_based_counter(a, b, x):
    result = [0] * len(x)
    checked = {}
    len_a = len(a)
    if not len_a:
        return result
    len_b = len(b)
    qsort(a, b, 0, len_a)
    print(a)
    for i in range(0, len(x)):
        if x[i] < a[0]:
            continue
        if x[i] in checked:
            result[i] = result[checked[x[i]]]
        else:
            for j in range(0, len_a):
                if x[i] < a[j]:
                    break
                if x[i] > b[j]:
                    continue
                if a[j] <= x[i] <= b[j]:
                    result[i] += 1
        checked[x[i]] = i
    return result




import random
points = [random.randint(1, 100) for i in range(1, random.randint(1, 500))]
# random.shuffle(points)
num_segments = random.randint(1, 100)
start = [random.randint(1, 100) for i in range(1, num_segments)]
# random.shuffle(start)
end = [random.randint(1, 100) for i in range(1, num_segments)]
# random.shuffle(end)
for i in range(0, len(start)):
    if start[i] > end[i]:
        start[i], end[i] = end[i], start[i]

# start = [83, 42, 7, 55, 22, 61, 36, 25, 59, 12, 4, 27, 91, 26, 17, 35, 18, 52, 29, 45, 14, 39, 17, 18, 47, 46, 66, 54, 40, 4, 37, 44, 42, 3, 54, 21, 58, 44, 24, 12, 57, 31, 60, 6, 57, 21, 33, 11, 83, 62, 33, 4, 19, 25, 19, 52, 11, 19, 38, 34, 6, 45, 31, 33, 4, 16, 5, 5, 22, 38, 10, 49]
# end = [86, 55, 49, 94, 29, 71, 69, 62, 85, 75, 76, 43, 96, 88, 42, 64, 35, 99, 59, 77, 32, 100, 37, 100, 87, 83, 86, 87, 93, 18, 87, 63, 52, 58, 75, 74, 89, 47, 75, 13, 86, 53, 65, 83, 60, 50, 48, 81, 96, 99, 41, 32, 49, 96, 98, 69, 82, 69, 59, 58, 33, 80, 66, 94, 64, 45, 46, 67, 54, 40, 24, 58]
# points = [54, 32, 40, 63, 43, 47, 24, 97, 35, 80, 76, 49, 70, 34, 56, 37, 25, 97, 94, 79, 95, 63, 7, 74, 2, 20, 56, 16, 20, 27, 91, 7, 97, 10, 3, 56, 36, 85, 78, 10, 76, 47, 95, 70, 8, 24, 91, 100, 97, 47, 44, 65, 27, 52, 97, 51, 4, 65, 94, 47, 23, 32, 98, 26, 24, 26, 82, 84, 23, 96, 17, 63, 1, 93, 24, 69, 23, 40, 92, 27, 47, 83, 65, 33, 62, 63, 88, 67, 14, 72, 9, 58, 17, 13, 67, 96, 49, 77, 16, 24, 23, 71, 95, 16, 65, 71, 31, 35, 13, 44, 85, 57, 61, 24, 61, 82, 52, 12, 63, 65, 17, 89, 31, 93, 29, 76, 8, 89, 12, 45, 40, 2, 77, 31, 74, 51, 96, 1, 43, 88, 56, 79, 76, 99, 9, 30, 93, 17, 75, 43, 34, 26, 79, 6, 82, 23, 82, 67, 96, 56, 87, 59, 5, 21, 85, 47, 18, 50, 93, 59, 35, 74, 79, 77, 86, 13, 88, 32, 9, 1, 93, 43, 22, 26, 10, 11, 5, 3, 53, 77, 53, 54, 12, 14, 53, 71, 65, 79, 59, 12, 59, 50, 100]
print(start)
print(points)
# qsort(points, 0, len(points))
print(end)


# start, end, points = prepare_data()

print(' '.join([str(x) for x in naive_counter(start, end, points)]))
print(' '.join([str(x) for x in qsort_based_counter(start, end, points)]))


#import random
#values = [i for i in range(1, 100)]
#random.shuffle(values)
# values = [2, 3, 9, 1, 7, 4]
# values = [2, 3, 9, 2, 9, 1]
#res = recursive_merge_sort(values)
#print(counter)
#print(naive_counter(values))