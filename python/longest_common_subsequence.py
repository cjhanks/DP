import sys

def print_matrix(m):
    for i in range(len(m)):
        for j in range(len(m[0])):
            sys.stderr.write('%2d ' % m[i][j])

        sys.stderr.write('\n')

def lcs(pattern_1, pattern_2):
    m = len(pattern_1)
    n = len(pattern_2)

    # dp will store solutions as the iteration goes on
    dp = [
        [None] * (n + 1) for item in range(m + 1)
    ]

    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0 or j == 0:
                dp[i][j] = 0
            elif pattern_1[i - 1] == pattern_2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else :
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    print_matrix(dp)
    return dp[m][n]

pattern_1 = "RGBGAARGA"
pattern_2 = "RGBRGBQ"
print("Length of LCS: ", lcs(pattern_1, pattern_2))
