#include <stdio.h>
#include <stdbool.h>

int n;
int x[1000];
bool m[1000];

void solution() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}

void try(int i) {
    for (int v = 1; v <= n; v++) {
        if (!m[v]) {
            x[i] = v;
            m[v] = true;
            if (i == n) {
                solution();
            } else {
                try(i + 1);
            }
            m[v] = false;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int v = 1; v <= n; v++) {
        m[v] = false;
    }
    try(1);
    return 0;
}
