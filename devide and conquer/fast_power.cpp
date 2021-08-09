#include <cstdio>
#include <cmath>

double pow(double x, int n){
    if (n == 0) return 1;
    if (n < 0) return 1/pow(x, -n);
    double tmp = pow(x, n >> 1);
    if (n % 2) return x*tmp*tmp;
    else return tmp*tmp;
}

int main(){
    double x;
    int n;
    scanf("%lf %d", &x, &n);
    printf("%.4f", pow(x, n));
    return 0;
}