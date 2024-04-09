#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
int n, m, k;
vector< vector<int> > map(20, vector<int>(20, 0));
vector< vector< pair<int, int> > > teams(5, vector< pair<int, int> >(0));
vector< int> score(5, 0);
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};
int indexx = 0;
void init_team(int x, int y, vector< vector<int> > &visit, int idx){
    visit[x][y] = 1;
    teams[idx].push_back(make_pair(x, y));
    if (map[x][y] == 3)
        return;
    for (int i = 0 ; i < 4 ; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n)
            continue;
        if (visit[nx][ny] || (map[nx][ny] == 0 || map[nx][ny] == 4))
            continue;
        init_team(nx, ny, visit, idx);
    }
}
void init_teams(){
    vector< vector<int> > visit(n, vector<int>(n, 0));
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            if (visit[i][j])
                continue;
            if (map[i][j] == 1){
                init_team(i, j, visit, indexx);
                indexx++;
            }
        }
    }
}
void reverse_team(vector< pair<int, int> > &team){
    map[team[0].first][team[0].second] = 3;
    map[team[team.size()-1].first][team[team.size()-1].second] = 1;
    reverse(team.begin(), team.end());
}
void move_team(vector< pair<int, int> > &team){
    int x = 0, y = 0;
    vector< pair<int, int> > temp_team;
    map[team[team.size()-1].first][team[team.size()-1].second] = 4;
    x = team[0].first;
    y = team[0].second;
    for (int i = 0 ; i < 4 ; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n)
            continue;
        if (map[nx][ny] == 4){
            temp_team.push_back(make_pair(nx, ny));
            break;
        }
    }
    for (int i = 0 ; i < team.size() - 1 ; i++){
        temp_team.push_back(team[i]);
    }
    team = temp_team;
    for (int i = 0 ; i < team.size() ; i++){
        if (i == 0)
            map[team[i].first][team[i].second] = 1;
        else if (i == team.size()-1)
            map[team[i].first][team[i].second] = 3;
        else
            map[team[i].first][team[i].second] = 2;
    }
}
void move_teams(){
    for (int i = 0 ; i < indexx ; i++){
        move_team(teams[i]);
    }
}
int throw_ball(int rounds){
    int way = rounds / n;
    int idx = rounds % n;
    int x = 0, y = 0;
    int find = -1;
    if (way % 4 == 0){
        x = idx;
        y = 0;
    } else if(way % 4 == 1){
        x = n - 1;
        y = idx;
    } else if (way % 4 == 2){
        x = n - 1 - idx;
        y = n - 1;
    } else if (way % 4 == 3){
        x = 0;
        y = n - 1 - idx;
    }
    while(x >= 0 && x < n && y >= 0 && y < n){
        if (map[x][y] >= 1 && map [x][y] <= 3){
            break;
        }
        x += dx[way];
        y += dy[way];
    }
    for (int i = 0 ; i < indexx ; i++){
        for (int j = 0 ; j < teams[i].size() ; j++){
            if (teams[i][j].first == x && teams[i][j].second == y){
                find = i;
                score[i] += pow(j+1, 2);
                return find;
            }
        }
    }
    return find;
}
// void print_score(){
//     cout << "score : ";
//     for (int i = 0 ; i < score.size() ; i++){
//         cout << score[i] << " ";
//     }
//     cout << "\n";
// }
// void print_map(){
//     cout << "======map========\n";
//     for (int i = 0 ; i < n ; i++){
//         for (int j = 0 ; j < n ; j++){
//             cout << map[i][j] << " ";
//         }
//         cout << "\n";
//     }
//     cout << "=================\n";
// }
int main() {
    cin >> n >> m >> k;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            cin >> map[i][j];
        }
    }
    init_teams();
    for (int i = 0 ; i < k ; i++){
        move_teams();
        int idx = throw_ball(i);
        if (idx >= 0){
            reverse_team(teams[idx]);
        }
    }
    cout << accumulate(score.begin(), score.end(), 0);
    return 0;
}