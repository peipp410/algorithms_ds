//实现2000美赛B题requirementA的算法。但是发现递归层数太多了根本跑不出来，也不知道程序有没有问题（应该没有x
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int a[15][15], ans[15][15], min = 11; //论文里面提到之前手算的结果是11，尝试找到更小的解
int dx[6] = {-1, -1, 0, 1, 1, 0};  //判断2s条件
int dy[6] = {-1, 0, 1, 1, 0, -1};
int dx2[12] = {-2, -2, -1, 0, 1, 2, 2, 2, 1, 0, -1, -2}; //判断4s条件
int dy2[12] = {-1, 0, 1, 2, 2, 2, 1, 0, -1, -2, -2, -2};
int tot = 91; //正六边形总数

bool boundary(int x, int y){//判断这个点是不是图中那个大正六边形内
    bool pd = true;
    if (x <= 0 ||x >= 12) pd = false;
    else if (x <= 6){
        if (y <= 0 || y > x + 5) pd = false;
    }
    else if (x > 6){
        if (y < x - 5 || y > 11) pd = false;
    }
    return pd;
}

void print(){  //输出，可以不用管
    int max = 0;
    for (int i = 1; i <= 6; i++){
        for (int j = 1; j <= i+5; j++){
            if (a[i][j] > max) max = a[i][j];
        }
    }
    for (int i = 7; i <= 11; i++){
        for (int j = i-5; j <= 11; j++){
            if (a[i][j] > max) max = a[i][j];
        }
    }
    printf("Span = %d\n", max);
    printf("-------------------------------------------------\n");
    for (int i = 1; i <= 6; i++){
        for (int j = 1; j <= i+5; j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    for (int i = 7; i <= 11; i++){
        for (int j = i-5; j <= 11; j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool check(int x, int y, int val){
    for (int i = 0; i < 6; i++){  //判断是不是符合2s条件
        int x_ = x + dx[i], y_ = y + dy[i];
        if (boundary(x_, y_))  
            if (a[x_][y_] != 0 && abs(a[x_][y_]-val) <= 1) return false;
//        else{
//            if (a[x_][y_] && abs(a[x_][y_]-val) <= 1) return false;
//        }
    }
    for (int i = 0; i < 12; i++){ //判断是不是符合4s条件
        int x_ = x + dx2[i], y_ = y + dy2[i];
        if (boundary(x_, y_))
            if (a[x_][y_] != 0 && a[x_][y_] == val) return false;
//        else{
//            if (a[x_][y_] && a[x_][y_] == val) return false;
//        }
    }
    if (x == 11 && y == 11 && !(a[11][10] && a[10][11] && a[10][10])) return false;
    return true;
}

void dfs(int x, int y){
    if (tot == 1){
        print();
        return;
    }
    else{
        for (int i = 0; i < 6; i++){
            int x_ = x + dx[i], y_ = y + dy[i];
            if (boundary(x_, y_) && a[x_][y_] == 0) {
                for (int j = 1; j <= 11; j++)
                    if (check(x_, y_, j)) {
                        a[x_][y_] = j;
                        tot--;
                        dfs(x_, y_);
                        a[x_][y_] = 0;
                        tot++;
                    }
            }
        }
    }
}

int main(){
    a[1][1] = 1;
    dfs(1, 1);
    return 0;
}
