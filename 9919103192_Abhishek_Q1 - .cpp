#include <bits/stdc++.h>

using namespace std;

int evaluate(char x) {
    if (x == '^')
        return 3;
    if (x == '/' || x == '*')
        return 2;
    if (x == '+' || x == '-')
        return 1;
    return -1;
}

void convert(const string &str) {
    int size = str.size();
    stack<char> q;

    for (int i = 0; i < size; ++i) {
        char word = str[i];

        if (isalnum(word)) {
            cout << word;
        } else if (word == '(')
            q.push(word);
        else if (word == ')') {
            while (!q.empty() and q.top() != '(') {
                cout << q.top();
                q.pop();
            }
            q.pop();
        } else {
            while (!q.empty() and evaluate(q.top()) >= evaluate(word)) {
                cout << q.top();
                q.pop();
            }
            q.push(word);
        }
    }

    while (!q.empty()) {
        cout << q.top();
        q.pop();
    }
}

int main() {
    string v = "w1*f1*1/2+w2*f2*1/2+w3*f3";
    convert(v);
}
