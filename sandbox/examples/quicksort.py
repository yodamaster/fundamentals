__author__ = 'GMatthews'


def partition(lst, pivot):
    left, right = [], []
    for item in lst:
        if item < pivot:
            left.append(item)
        else:
            right.append(item)
    return left, right


def quicksortr(lst):
    if not lst:
        return lst

    #select pivot - this implementation modifies the list
    pivot = lst.pop(len(lst) / 2)
    left, right = partition(lst, pivot)
    return quicksortr(left) + [pivot] + quicksortr(right)


def quicksorti(lst):
    lsts, sorted = [lst], []
    while lsts:
        tmp = lsts.pop()

        if len(tmp) == 1:
            sorted.extend(tmp)
            continue

        #select pivot
        pivot = tmp[0]
        left, right = partition(tmp[1:], pivot)

        if right:
            lsts.append(right)
        lsts.append([pivot])
        if left:
            lsts.append(left)
    return sorted


if __name__ == '__main__':
    print(quicksortr([23, 2, -4, 65, 103, 3, 4]))
    print(quicksorti([23, 2, -4, 65, 103, 3, 4]))
