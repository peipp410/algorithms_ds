#include <cstdio>

int a[10001];

int find(int x){
    if (a[x] == x) return x;
    else{
        a[x] = find(a[x]);
        return a[x];
    }
}

void merge(int x, int y){
    int f1 = find(x), f2 = find(y);
    if (f1 != f2) a[f2] = f1;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++){
        a[i] = i;
    }
    for (int i = 1; i <= m; i++){
        int z, x, y;
        scanf("%d %d %d", &z, &x, &y);
        if (z == 1) merge(x, y);
        else{
            if (find(x) == find(y)) printf("Y\n");
            else printf("N\n");
        }
    }
    return 0;
}