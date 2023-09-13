
def printDistances(distances, token1Length, token2Length):
    for t1 in range(token1Length + 1):
        for t2 in range(token2Length + 1):
            print(int(distances[t1][t2]), end=" ")
        print()

def create_matrix(rows, cols):
    matrix = []
    for _ in range(rows):
        matrix.append([0.0] * cols)

    return matrix

def minpath(matrix, r, c, score, prefix):
    neighbors = [
        (r + 0, c + 1),
        (r + 1, c + 1),
        (r + 1, c + 0),
    ]

    min_value = float('inf')
    min_index = []

    for (i, j) in neighbors:
        if i >= len(matrix) or j >= len(matrix[0]):
            continue

        value = matrix[i][j]
        if value < min_value:
            min_value = value
            min_index = [(i, j)]

        if value == min_value:
            min_index.append((i, j))

    if len(min_index) == 0:
        return (score, prefix)

    min_score = float('inf')
    min_path  = None
    for (i, j) in min_index:
        (p_score, p_prefix) = \
                minpath(matrix, i, j, score, prefix + [(i, j)])

        if p_score < min_score:
            min_score = p_score
            min_path  = p_prefix;

    return min_score, min_path

def find_edits(token1, token2, matrix):
    i1 = 0
    i2 = 0


def levenshteinDistanceDP(token1, token2):
    distances = create_matrix(len(token1) + 1, len(token2) + 1)

    for t1 in range(len(token1) + 1):
        distances[t1][0] = t1

    for t2 in range(len(token2) + 1):
        distances[0][t2] = t2

    a = 0
    b = 0
    c = 0

    for t1 in range(1, len(token1) + 1):
        for t2 in range(1, len(token2) + 1):
            # If the previous token in 1 is equal to the previous token in 2.
            # The distance is identical to the cost of the previous comparison.
            if (token1[t1-1] == token2[t2-1]):
                distances[t1][t2] = distances[t1 - 1][t2 - 1]
            else:
                # +-+-+
                # |c|b|
                # +-+-+
                # |a|x|
                # +-+-+
                #
                a = distances[t1    ][t2 - 1]
                b = distances[t1 - 1][t2    ]
                c = distances[t1 - 1][t2 - 1]

                distances[t1][t2] = min([a, b, c]) + 1


    (_, full_minpath) = minpath(distances, 0, 1, 1, [(1, 1)])

    for (i, j) in full_minpath:
        i -= 1
        j -= 1
        print(i, j)
        if i < len(token1) and j < len(token2):
            print(token1[i], token2[j])

    return distances[len(token1)][len(token2)]

print(levenshteinDistanceDP('words', 'AwBoCrDdEs'))
