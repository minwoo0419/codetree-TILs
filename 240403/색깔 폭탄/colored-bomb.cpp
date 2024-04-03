#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;
int n, m;
vector< vector<int> > map(20, vector<int>(20, 0));
int dx[4] = {-1, 0, 0 ,1};
int dy[4] = {0, -1, 1, 0};
pair<vector< pair<int, int> >, int> bfs(int x, int y, vector< vector<int> > &visit){
    vector< pair<int, int> > dot;
    visit[x][y] = 1;
    int color = map[x][y];
    dot.push_back(make_pair(x, y));
    int red = 0;
    queue< pair<int, int> > q;
    q.push(make_pair(x, y));
    while(!q.empty()){
        pair<int, int> temp = q.front();
        q.pop();
        for (int i = 0 ; i < 4 ; i++){
            int nx = temp.first + dx[i];
            int ny = temp.second + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n){
                if ((map[nx][ny] == color || map[nx][ny] == 0) && visit[nx][ny] == 0){
                    if (map[nx][ny] == 0)
                        red += 1;
                    else{
                        visit[nx][ny] = 1;
                        q.push(make_pair(nx, ny));
                    }
                    dot.push_back(make_pair(nx, ny));
                }
            }
        }
    }
    return make_pair(dot, red);
}
int remo_color(vector< pair<int, int> > dot){
    int cnt = 0;
    for(int i = 0 ; i < dot.size() ; i++){
        map[dot[i].first][dot[i].second] = -2;
    }
    return dot.size();
}
void gravity(){
    for(int i = 0 ; i < n ; i++){
        for(int j = n - 2 ; j >= 0 ; j--){
            int idx = j;
            if(map[idx][i] >= 0){
                while(idx < n - 1){
                    if (map[idx+1][i] == -2){
                        map[idx+1][i] = map[idx][i];
                        map[idx][i] = -2;
                    } else {
                        break;
                    }
                    idx++;
                }
            }
        }
    }
}
void turn(){
    vector< vector<int> > temp(n, vector<int>(n, 0));
    int idx = n - 1;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            temp[i][j] = map[j][idx];
        }
        idx--;
    }
    map = temp;
}
int simulation(){
    int sum = 0;
    while(1){
        int red = pow(n, 2);
        vector< pair<int, int> > dot;
        vector< vector<int> > visit(n, vector<int>(n, 0));
        for (int i = n - 1 ; i >= 0 ; i--){
            for (int j = 0 ; j < n ; j++){
                if (map[i][j] > 0 && visit[i][j] == 0){
                    pair< vector< pair<int, int> >, int> temp = bfs(i, j, visit);
                    if (temp.first.size() > 1){
                        if (temp.first.size() > dot.size()){
                            dot = temp.first;
                            red = temp.second;
                        } else if(temp.first.size() == dot.size()){
                            if (temp.second < red){
                                dot = temp.first;
                                red = temp.second;
                            }
                        }
                    }
                }
            }
        }
        if(dot.empty())
            break;
        sum += pow(remo_color(dot), 2);
        gravity();
        turn();
        gravity();
    }
    return sum;
}
int main() {
    cin >> n >> m;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            int num;
            cin >> num;
            map[i][j] = num;
        }
    }
    cout << simulation();
    return 0;
}