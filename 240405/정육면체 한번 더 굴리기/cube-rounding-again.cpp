#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
int n, m;
vector< vector<int> > map(20, vector<int>(20, 0));
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int sero[4] = {1, 3, 6, 4};
int garo[2] = {2, 5};
void turn_dice(int a){
    if (a == 0)
        return;
    int temp = 0;
    int first = (a == 1) ? 0 : 1;
    int second = (a == 1) ? 1 : 0;
    temp = sero[1];
    sero[1] = garo[first];
    garo[first] = temp;
    temp = sero[3];
    sero[3] = garo[second];
    garo[second] = temp;
}
void back_dice(){
    int temp = sero[1];
    sero[1] = sero[3];
    sero[3] = temp;
}
void run_dice(){
    int temp = sero[3];
    for (int i = 3 ; i > 0 ; i--){
        sero[i] = sero[i-1];
    }
    sero[0] = temp;
}
int bfs(int i, int j){
    queue< pair<int, int> > q;
    vector< vector<int> > visit(n, vector<int>(n, 0));
    q.push(make_pair(i, j));
    int sum = 0;
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        visit[x][y] = 1;
        int num = map[x][y];
        sum += num;
        q.pop();
        for (int k = 0 ; k < 4 ; k++){
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n){
                if (num == map[nx][ny] && visit[nx][ny] == 0){
                    q.push(make_pair(nx, ny));
                }
            }
        }
    }
    return sum;
}
void check_run(int &x, int &y, int &idx){
    if (x + dx[idx] < 0 || x + dx[idx] >= n || y + dy[idx] < 0 || y + dy[idx] >= n){
        idx += 2;
        back_dice();
    }
    if (idx < 0){
        idx += 4;
    } else if (idx >= 4){
        idx -= 4;
    }
    x += dx[idx];
    y += dy[idx];
}
int main() {
    cin >> n >> m;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            cin >> map[i][j];
        }
    }
    int sum = 0;
    int x = 0, y = 0, number = map[0][0], idx = 0;
    for (int i = 0 ; i < m ; i++){
        int temp = 0;
        if(number > map[x][y])
            temp = 1;
        else if (number < map[x][y])
            temp = -1;
        turn_dice(temp);
        idx += temp;
        if (idx < 0){
            idx += 4;
        } else if (idx >= 4){
            idx -= 4;
        }
        check_run(x, y, idx);
        run_dice();
        sum += bfs(x, y);
        number = sero[2];
    }
    cout << sum;
    return 0;
}