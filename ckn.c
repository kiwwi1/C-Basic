#include <stdio.h>
#include <stdint.h>

#define max 1000
#define MOD 1000000007

int64_t m[max][max];

int64_t C(int k_val, int n) {
    if (k_val == 0 || k_val == n)
        m[k_val][n] = 1;
    else {
        if (m[k_val][n] < 0) {
            m[k_val][n] = (C(k_val - 1, n - 1) + C(k_val, n - 1)) % MOD;
        }
    }
    return m[k_val][n];
}

int main() {
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            m[i][j] = -1;
        }
    }
    int k, n;
    scanf("%d%d", &k, &n);
    int64_t result = C(k, n);
    printf("%lld\n", result);
    return 0;
}
