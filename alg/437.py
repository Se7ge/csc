def prepare_data():
    n = int(input())
    values = list(map(lambda x: int(x), input().split()))

    return n, values


def just_do_it():
    n, values = prepare_data()
    for i in sorted(values):
        print('{0} '.format(i))

if __name__ == '__main__':
    just_do_it()