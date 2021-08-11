#include <bits/stdc++.h>
using namespace std;

vector<string> change(string s){
    vector<string> res;
    stack<char> st;
    int n = s.size();
    for (int i = 0; i < n; i++){
        if (s[i] == ' ') continue;
        if (isdigit(s[i])){
            int lab = i;
            while (isdigit(s[i+1])) i++;
            res.emplace_back(string(s.begin()+lab, s.begin()+i+1));
        }
        else if (s[i] == '+' || s[i] == '-'){
            while (!st.empty()){
                if (st.top() == '(') break;
                res.emplace_back(string(1, st.top()));
                st.pop();
            }
            st.push(s[i]);
        }
        else if (s[i] == '*' || s[i] == '/'){
            while (!st.empty()){
                if (st.top() == '(' || st.top() == '+' || st.top() == '-') break;
                res.emplace_back(string(1, st.top()));
                st.pop();
            }
            st.push(s[i]);
        }
        else if (s[i] == '(') st.push(s[i]);
        else if (s[i] == ')'){
            while (!st.empty()){
                if (st.top() == '('){
                    st.pop();
                    break;
                }
                res.emplace_back(string(1, st.top()));
                st.pop();
            }
        }
    }
    while (!st.empty()){
        res.emplace_back(string(1, st.top()));
        st.pop();
    }
    for (int i = 0; i < res.size(); i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
    return res;
}
int calculate(string s) {
    vector<string> rnp = change(s);
    int n = rnp.size();
    stack<int> st;
    for (int i = 0; i < n; i++){
        if (isdigit(rnp[i][0])){
            st.push(stoi(rnp[i]));
        }
        else{
            int num2 = st.top();
            st.pop();
            int num1 = 0;
            if (!st.empty()){
                num1 = st.top();
                st.pop();
            }
            switch (rnp[i][0]){
                case '+':
                    st.push(num1 + num2);
                    break;
                case '-':
                    st.push(num1 - num2);
                    break;
                case '*':
                    st.push(num1 * num2);
                    break;
                case '/':
                    st.push(num1 / num2);
                    break;
            }
        }
    }
    return st.top();
}

int main(){
    string s;
    getline(cin, s);
    printf("%d", calculate(s));
    return 0;
}