__author__ = 'GMatthews'


def merge(left, right):
    result = []
    while len(left) > 0 or len(right) > 0:
        if len(left) > 0 and len(right) > 0:
            if left[0] <= right[0]:
                result.append(left.pop(0))
            else:
                result.append(right.pop(0))
        elif len(left) > 0:
            result.append(left.pop(0))
        else:
            result.append(right.pop(0))
    return result


def mergesortr(lst):
    if len(lst) == 1:
        return lst

    middle = len(lst) / 2
    (left, right) = mergesortr(lst[:middle]), mergesortr(lst[middle:])
    return merge(left, right)


def mergesorti(lst):
    pass


if __name__ == '__main__':
    print(mergesortr([23, 2, -4, 65, 103, 3, 4]))
    print(mergesorti([23, 2, -4, 65, 103, 3, 4]))