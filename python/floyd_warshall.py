import sys

def print_matrix(m):
    for i in range(len(m)):
        for j in range(len(m[0])):
            sys.stderr.write('%3.f ' % m[i][j])

        sys.stderr.write('\n')

def create_matrix(rows, cols):
    matrix = []
    for _ in range(rows):
        matrix.append([0.0] * cols)

    return matrix

def floyd_warshall(adj):
    vertices = len(adj)

    for k in range(vertices):
        for i in range(vertices):
            for j in range(vertices):
                # Current viewed index.
                a = adj[i][j]

                #
                b = adj[i][k]
                c = adj[k][j]

                if c == float('inf'):
                    continue

                if b == float('inf'):
                    continue

                q = b + c
                if a > q:
                    adj[i][j] = q


matrix = create_matrix(4, 4)
# -
matrix[0][0] = 0
matrix[0][1] = 5
matrix[0][2] = float('inf')
matrix[0][3] = 10

matrix[1][0] = float('inf')
matrix[1][1] = 0
matrix[1][2] = 3
matrix[1][3] = float('inf')

matrix[2][0] = float('inf')
matrix[2][1] = float('inf')
matrix[2][2] = 0
matrix[2][3] = 1

matrix[3][0] = float('inf')
matrix[3][1] = float('inf')
matrix[3][2] = float('inf')
matrix[3][3] = 0

print('-' * 70)
print_matrix(matrix)
floyd_warshall(matrix)
print('-' * 70)
print_matrix(matrix)
