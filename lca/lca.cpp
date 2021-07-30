#include <cstdio>
#include <algorithm>
using namespace std;

int head[500010], tot, depth[500001], fa[500001][22], lg[500001];

struct g{
    int to, next;
}e[500010 << 1];

void add(int x, int y){
    e[++tot].to = y;
    e[tot].next = head[x];
    head[x] = tot;
}

void dfs(int now, int father){
    fa[now][0] = father;
    depth[now] = depth[father] + 1;
    for (int i = 1; i <= lg[depth[now]]; i++){
        fa[now][i] = fa[fa[now][i-1]][i-1];
    }
    for (int i = head[now]; i; i = e[i].next){
        if (e[i].to != father) dfs(e[i].to, now);
    }
}

int lca(int a, int b){
    if (depth[a] < depth[b]) swap(a, b);
    while (depth[a] > depth[b]){
        a = fa[a][lg[depth[a]-depth[b]] - 1];
    }
    if (a == b) return a;
    for (int i = lg[depth[a]]-1; i >= 0; i--){  //i循环的边界条件是>=0
        if (fa[a][i] != fa[b][i]){
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    return fa[a][0];
}

int main(){
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; i++){
        lg[i] = lg[i-1] + ((1 << lg[i-1]) == i);
    }
    for (int i = 1; i <= n-1; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs(s, 0);
    for (int i = 1; i <=m; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", lca(a, b));
    }
    return 0;
}