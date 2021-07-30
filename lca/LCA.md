# LCA

lca也是一个经典的老问题了，这次首先来熟悉一下倍增算法。

在倍增算法中，由于不断需要计算$\log_2 n$​的值，所以我们在数组中先预处理给出这些值，到时候就可以以$O(1)$​的复杂度查询。一下计算了$\log_2 n+1$的值，在实际使用时可以视情况-1。

```c++
for (int i = 1; i <= n; i++){
    lg[i] = lg[i-1] + ((1 << lg[i-1]) == i);
}
```

然后我们用了fa数组记录了$i$号节点向上第$2^j$个祖先的值。更新fa数组时，我们首先从根节点出发，一路用图中的dfs解决。其中`fa[now][i] = fa[fa[now][i-1]][i-1];`的设计比较巧妙，这是因为$2^i=2^{i-1}\times 2^{i-1}$​。

```c++
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
```

我们选用前向星来存图。对于一个给定的节点now，我们从head[now]开始不断用next的值迭代，皆可以访问到从这个节点出发的所有终点。

```c++
void add(int x, int y){
    e[++tot].to = y;
    e[tot].next = head[x];
    head[x] = tot;
}
```

所有预处理查询完成以后，就可以查询两个节点的lca了。我们总是假设a节点的深度大于等于b节点，因此首先要使a节点向上跳，直到它位于和b节点统一深度。然后，我们让a和b一起向上跳，直到他们的父亲节点相同为止。那么最后返回的也就是他们的父亲节点。

```c++
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
```

最后感谢洛谷OIdalao的题解！