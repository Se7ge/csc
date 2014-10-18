import random
import bisect
import math


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
    base_key = random.randint(l, r-1)
    a[l], a[base_key] = a[base_key], a[l]
    x = a[l]
    j = l
    eq = 0
    for i in range(l+1, r):
        if a[i] <= x:
            j += 1
            if i != j:
                a[i], a[j] = a[j], a[i]
                if a[i] == x and i <= base_key:
                    eq += 1
    a[l], a[j] = a[j], a[l]
    return j, eq


def qsort(a, l, r, max_depth, depth=0):
    if depth >= max_depth:
        a = sorted(a)
        return False

    if r - l < 40:
        a[l:r] = sorted(a[l:r])
        return True
    depth += 1
    while l < r - 1:
        m, eq = partition(a, l, r)
        ret = qsort(a, l, m, max_depth, depth)
        if ret == False:
            return False
        depth -= 1
        l = m + 1 + (eq - 1 if eq > 1 else 0)
    return True


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
    len_x = len(x)
    result = [0] * len_x
    checked = {}
    len_a = len(a)
    len_b = len(b)
    if not len_a:
        return result
    qsort(a, 0, len_a, math.floor(math.log2(len_a)))
    qsort(b, 0, len_b, math.floor(math.log2(len_b)))
    print(a)
    print(b)
    # a = sorted(a)
    # b = sorted(b)
    for i in range(0, len(x)):
        if x[i] < a[0]:
            continue
        if x[i] in checked:
            result[i] = result[checked[x[i]]]
        else:
            a_idx = bisect.bisect_right(a, x[i])
            b_idx = bisect.bisect_left(b, x[i])
            result[i] = a_idx - b_idx
        checked[x[i]] = i
    return result


points = [random.randint(1, 100) for i in range(1, 100)]
# random.shuffle(points)
num_segments = random.randint(1, 10000)
start = [random.randint(1, num_segments) for i in range(1, num_segments)]
# random.shuffle(start)
end = [random.randint(1, num_segments) for i in range(1, num_segments)]
# random.shuffle(end)
for i in range(0, len(start)):
    if start[i] > end[i]:
        start[i], end[i] = end[i], start[i]

# start = [11, 58, 12, 27, 5, 16, 16, 22, 4, 12, 21, 45, 67, 18, 12, 63, 27, 20, 4, 4, 23, 74, 3, 50, 25, 17, 61, 7, 7, 2, 5, 16, 20, 63, 4, 55, 53, 18, 22, 1, 1, 27, 12, 54, 37, 25, 30, 11, 7, 36, 18, 33, 44, 40, 13, 26, 24, 36, 55, 35, 1, 18, 58, 37, 33, 6, 10, 39, 3, 41, 40, 17, 43, 55, 39, 26, 12, 41, 1, 10, 7, 8, 19]
# end = [16, 73, 56, 58, 41, 57, 39, 49, 76, 59, 43, 81, 71, 48, 35, 81, 65, 69, 40, 52, 40, 83, 4, 83, 84, 26, 80, 50, 82, 62, 18, 76, 60, 74, 49, 65, 57, 49, 70, 38, 34, 69, 15, 64, 84, 78, 54, 58, 76, 58, 74, 74, 44, 43, 41, 84, 51, 71, 71, 46, 19, 36, 73, 56, 36, 66, 78, 51, 61, 82, 57, 74, 56, 63, 68, 30, 16, 71, 44, 33, 27, 39, 21]

# start = [83, 42, 7, 55, 22, 61, 36, 25, 59, 12, 4, 27, 91, 26, 17, 35, 18, 52, 29, 45, 14, 39, 17, 18, 47, 46, 66, 54, 40, 4, 37, 44, 42, 3, 54, 21, 58, 44, 24, 12, 57, 31, 60, 6, 57, 21, 33, 11, 83, 62, 33, 4, 19, 25, 19, 52, 11, 19, 38, 34, 6, 45, 31, 33, 4, 16, 5, 5, 22, 38, 10, 49]
# end = [86, 55, 49, 94, 29, 71, 69, 62, 85, 75, 76, 43, 96, 88, 42, 64, 35, 99, 59, 77, 32, 100, 37, 100, 87, 83, 86, 87, 93, 18, 87, 63, 52, 58, 75, 74, 89, 47, 75, 13, 86, 53, 65, 83, 60, 50, 48, 81, 96, 99, 41, 32, 49, 96, 98, 69, 82, 69, 59, 58, 33, 80, 66, 94, 64, 45, 46, 67, 54, 40, 24, 58]
# points = [54, 32, 40, 63, 43, 47, 24, 97, 35, 80, 76, 49, 70, 34, 56, 37, 25, 97, 94, 79, 95, 63, 7, 74, 2, 20, 56, 16, 20, 27, 91, 7, 97, 10, 3, 56, 36, 85, 78, 10, 76, 47, 95, 70, 8, 24, 91, 100, 97, 47, 44, 65, 27, 52, 97, 51, 4, 65, 94, 47, 23, 32, 98, 26, 24, 26, 82, 84, 23, 96, 17, 63, 1, 93, 24, 69, 23, 40, 92, 27, 47, 83, 65, 33, 62, 63, 88, 67, 14, 72, 9, 58, 17, 13, 67, 96, 49, 77, 16, 24, 23, 71, 95, 16, 65, 71, 31, 35, 13, 44, 85, 57, 61, 24, 61, 82, 52, 12, 63, 65, 17, 89, 31, 93, 29, 76, 8, 89, 12, 45, 40, 2, 77, 31, 74, 51, 96, 1, 43, 88, 56, 79, 76, 99, 9, 30, 93, 17, 75, 43, 34, 26, 79, 6, 82, 23, 82, 67, 96, 56, 87, 59, 5, 21, 85, 47, 18, 50, 93, 59, 35, 74, 79, 77, 86, 13, 88, 32, 9, 1, 93, 43, 22, 26, 10, 11, 5, 3, 53, 77, 53, 54, 12, 14, 53, 71, 65, 79, 59, 12, 59, 50, 100]
# print(segments)
print(start)
# qsort(points, 0, len(points))
print(end)


# segments, points = prepare_data()
# print(segments)
sorted_a = sorted(start)
sorted_b = sorted(end)
# start, end, points = prepare_data()
naive = naive_counter(start, end, points)
q_sorted = qsort_based_counter(start, end, points)
print(' '.join([str(x) for x in naive]))
print(' '.join([str(x) for x in q_sorted]))
print(sorted_a == start)
print(sorted_b == end)
print(naive == q_sorted)

#import random
#values = [i for i in range(1, 100)]
#random.shuffle(values)
# values = [2, 3, 9, 1, 7, 4]
# values = [2, 3, 9, 2, 9, 1]
#res = recursive_merge_sort(values)
#print(counter)
#print(naive_counter(values))

#@Evgeny_Kruten да для m вызовов partition получится O(m*n). А если сначала отсортировать отрезки за O(n*logn) и затем бинарным поиском найти
