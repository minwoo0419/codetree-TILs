#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
int n, m;
vector<int> d;
vector<int> p;
vector< vector<int> > tree(15, vector<int>(15, 0));
vector< vector<int> > special(15, vector<int>(15, 0));
int dx[4] = {-1, -1, 1 ,1};
int dy[4] = {-1, 1, -1, 1};
int go_x[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int go_y[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int change_cor(int a){
    if (a < 0){
        a += n;
    } else if (a >= n){
        a -= n;
    }
    return a;
}
void move_special(int a){
    vector< vector<int> > temp(n, vector<int>(n, 0));
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            if (special[i][j] == 1){
                int x = change_cor(i + go_x[d[a]-1] * p[a]);
                int y = change_cor(j + go_y[d[a]-1] * p[a]);
                temp[x][y] = 1;
                tree[x][y] += 1;
            }
        }
    }
    special = temp;
}
void grow(){
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            int cnt = 0;
            if (special[i][j] == 1){
                for (int k = 0 ; k < 4 ; k++){
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n){
                        if (tree[nx][ny] >= 1)
                            cnt++;
                    }
                }
                tree[i][j] += cnt;
            }
        }
    }
}
void cut(){
    vector< vector<int> > temp(n, vector<int>(n, 0));
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            if (tree[i][j] >= 2 && special[i][j] == 0){
                tree[i][j] -= 2;
                temp[i][j] = 1;
            }
        }
    }
    special = temp;
}
int main() {
    cin >> n >> m;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            int num;
            cin >> num;
            tree[i][j] = num;
        }
    }
    for (int i = n - 2 ; i < n ; i++){
        for (int j = 0 ; j < 2 ; j++){
            special[i][j] = 1;
        }
    }
    for (int i = 0 ; i < m ; i++){
        int a, b;
        cin >> a >> b;
        d.push_back(a);
        p.push_back(b);
    }
    for (int i = 0 ; i < m ; i++){
        move_special(i);
        grow();
        cut();
    }
    int sum = 0;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            sum += tree[i][j];
        }
    }
    cout << sum;
    return 0;
}