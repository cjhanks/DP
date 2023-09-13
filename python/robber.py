

def maximum_path(path, distance):
    accum = [0] * distance
    accum[0] = path[0]
    accum[1] = max(path[0], path[1])

    for n in range(2, len(path)):
        maximum = max(accum[1], accum[0] + path[n])
        accum.pop(0)
        accum.append(maximum)

    return accum[-1]

path = [1, 3, 2, 4, 2, 5]
#path = [1,2,3,1]

print(maximum_path(path))
