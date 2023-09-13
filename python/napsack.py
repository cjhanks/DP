#Example:
#
#def knapSack(W, wt, val, n):
# K = [[0 for x in range(W + 1)] for x in rаnge(n + 1)]
# # Build tаble K[][] in bоttоm uр mаnner
#     for i in range(n + 1):
#         for w in range(W + 1):
#             if i == 0  or  w == 0:
#                 K[i][w] = 0
#             elif wt[i-1] <= w:
#                 K[i][w] = max(val[i-1]
#                           + K[i-1][w-wt[i-1]],
#                               K[i-1][w])
#             else:
#                 K[i][w] = K[i-1][w]
#     return K[n][W]
# # Driver code
# val = [60, 100, 120]
# wt = [10, 20, 30]
# W = 50
# n = len(val)
# print(knapSack(W, wt, val, n))
#
import sys

def print_matrix(m):
    for i in range(len(m)):
        for j in range(len(m[0])):
            sys.stderr.write('%2d ' % m[i][j])

        sys.stderr.write('\n')

def create_matrix(col, row):
    matrix = []
    for _ in range(row):
        matrix.append([0] * col)
    return matrix

def knapSack(W, wt, val):
    n=len(val)
    table = [[0 for x in range(W + 1)] for x in range(n + 1)]

    for i in range(n + 1):
        for j in range(W + 1):
            if i == 0 or j == 0:
                table[i][j] = 0
            elif wt[i-1] <= j:
                table[i][j] = max(val[i-1]
+ table[i-1][j-wt[i-1]],  table[i-1][j])
            else:
                table[i][j] = table[i-1][j]

    return table[n][W]

def knapsack(capacity, weight, value, n):
    matrix = create_matrix(capacity + 1, n + 1)

    for i in range(1, n + 1):
        sys.stderr.write('\n')
        for j in range(1, capacity + 1):
            if weight[i - 1] <= j:
                #sys.stderr.write('A')
                #
                # If the previous weight is less than the current
                # target capacity...
                #
                # Solution:
                #   Value.
                # + Previous cached solution for remaining capacity.
                #
                a = value[i - 1] + matrix[i - 1][j - weight[i - 1]]

                assert  j - weight[i - 1] >= 0


                # Previous value for this.
                b = matrix[i - 1][j]

                matrix[i][j] = max(a, b)
            else:
                #sys.stderr.write('B')
                matrix[i][j] = matrix[i - 1][j]

        #print('-' * 20)
        ##print(i, j)
        #print_matrix(matrix)
    print_matrix(matrix)
    return matrix[n][capacity]

#value    = [60, 100, 120]
#weight   = [10,  20,  30]
#capacity = 50

import random

value  = []
weight = []

for _ in range(10):
    value .append(random.randint(1, 10))
    weight.append(random.randint(1, 10))

#value    = [10, 9, 4]
#weight   = [ 2, 3, 1]
val = [1, 2, 3, 4]
cst = [1, 2, 3, 4]
capacity = 5

print(knapsack(capacity, val, cst, len(val)))

import time
head = time.time()
print(knapsack(capacity, weight, value, len(value)))
print(time.time() - head)
