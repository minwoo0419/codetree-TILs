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
vector< vector<int> > team_num(20, vector<int>(20, -1));
vector< vector< pair<int, int> > > teams(5, vector< pair<int, int> >(0));
vector<int> tails(5, 0);
int score = 0; 
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};
int indexx = 0;
void init_team(int x, int y, vector< vector<int> > &visit, int idx){
    visit[x][y] = 1;
    team_num[x][y] = idx;
    teams[idx].push_back(make_pair(x, y));
    for (int i = 0 ; i < 4 ; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n)
            continue;
        if (map[x][y] == 1 && map[nx][ny] != 2)
            continue;
        if (visit[nx][ny] || map[nx][ny] == 0)
            continue;
        if (map[nx][ny] == 3)
            tails[idx] = teams[idx].size();
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
void reverse_team(vector< pair<int, int> > &team, int idx){
    vector< pair<int, int> > temp_team;
    for(int i = tails[idx] ; i >= 0 ; i--){
        temp_team.push_back(team[i]);
    }
    for (int i = team.size() - 1 ; i > tails[idx] ; i--){
        temp_team.push_back(team[i]);
    }
    team = temp_team;
}
void move_team(vector< pair<int, int> > &team, int idx){
    int x = 0, y = 0;
    pair<int, int> last = team[team.size() - 1];
    for (int i = team.size() - 1 ; i >= 0 ; i--){
        team[i] = team[i - 1];
    }
    team[0] = last;
    for (int i = 0 ; i < team.size() ; i++){
        if (i == 0)
            map[team[i].first][team[i].second] = 1;
        else if (i < tails[idx])
            map[team[i].first][team[i].second] = 2;
        else if (i == tails[idx])
            map[team[i].first][team[i].second] = 3;
        else
            map[team[i].first][team[i].second] = 4;
    }
}
void move_teams(){
    for (int i = 0 ; i < indexx ; i++){
        move_team(teams[i], i);
    }
}
int throw_ball(int rounds){
    int way = rounds / n;
    int idx = rounds % n;
    int x = 0, y = 0;
    if (way % 4 == 0){
        x = idx;
        y = 0;
        for (; y < n ; y++){
            if (map[x][y] >= 1 && map [x][y] <= 3){
                for(int j = 0 ; j < teams[team_num[x][y]].size() ; j++){
                    if(teams[team_num[x][y]][j].first == x && teams[team_num[x][y]][j].second == y){
                        score += pow(j+1, 2);
                        break;
                    }
                }
                return team_num[x][y];
            }
        }
    } else if(way % 4 == 1){
        x = n - 1;
        y = idx;
        for (; x >= 0 ; x--){
            if (map[x][y] >= 1 && map [x][y] <= 3){
                for(int j = 0 ; j < teams[team_num[x][y]].size() ; j++){
                    if(teams[team_num[x][y]][j].first == x && teams[team_num[x][y]][j].second == y){
                        score += pow(j+1, 2);
                        break;
                    }
                }
                return team_num[x][y];
            }
        }
    } else if (way % 4 == 2){
        x = n - 1 - idx;
        y = n - 1;
        for (;y >= 0 ; y--){
            if (map[x][y] >= 1 && map [x][y] <= 3){
                for(int j = 0 ; j < teams[team_num[x][y]].size() ; j++){
                    if(teams[team_num[x][y]][j].first == x && teams[team_num[x][y]][j].second == y){
                        score += pow(j+1, 2);
                        break;
                    }
                }
                return team_num[x][y];
            }
        }
    } else if (way % 4 == 3){
        x = 0;
        y = n - 1 - idx;
        for (;x < n ; x++){
            if (map[x][y] >= 1 && map [x][y] <= 3){
                for(int j = 0 ; j < teams[team_num[x][y]].size() ; j++){
                    if(teams[team_num[x][y]][j].first == x && teams[team_num[x][y]][j].second == y){
                        score += pow(j+1, 2);
                        break;
                    }
                }
                return team_num[x][y];
            }
        }
    }
    return -1;
}
// void print_teams(){
//     cout << "==============print teams=============\n";
//     for (int i = 0 ; i < indexx ; i++){
//         for (int j = 0 ; j < teams[i].size() ; j++){
//             cout << teams[i][j].first << " " << teams[i][j].second << ", ";
//         }
//         cout << "\n";
//     }
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
        // cout << "\n=============실행==============\n";
        // print_teams();
        // print_map();
        move_teams();
        // print_map();
        int idx = throw_ball(i);
        if (idx >= 0){
            reverse_team(teams[idx], idx);
        }
        // print_map();
    }
    cout << score;
    return 0;
}