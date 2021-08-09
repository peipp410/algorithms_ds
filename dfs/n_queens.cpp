// https://leetcode-cn.com/problems/n-queens-ii/
class Solution {
private:
    int ans;
    vector<int> q;
public:
    bool check(int index, int j){
        for (int i = 1; i <= index-1; i++){
            if (q[i] == j || abs(i-index) == abs(j-q[i])) return false;
        }
        return true;
    }
    void dfs(int index, int n){
        if (index > n){
            ans++;
            return;
        }
        for (int j = 1; j <= n; j++){
            if (check(index, j)){
                q[index] = j;
                dfs(index+1, n);
                q[index] = 0;
            }
        }
    }
    int totalNQueens(int n) {
        ans = 0;
        q.resize(n+1);
        dfs(1, n);
        return ans;
    }
};