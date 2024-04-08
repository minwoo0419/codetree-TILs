#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
int m, t, r, c;
vector< vector< vector <int> > > monster(4, vector< vector <int> >(4, vector<int>(0)));
vector< vector< vector <int> > > egg(4, vector< vector <int> >(4, vector<int>(0)));
vector< vector< vector <int> > > dead(4, vector< vector <int> >(4, vector<int>(0)));
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
void copy_monster(){
    vector< vector< vector < int > > > temp(4, vector< vector < int > >(4, vector< int >(0)));
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            for (int k = 0 ; k < monster[i][j].size() ; k++){
                temp[i][j].push_back(monster[i][j][k]);
            }
        }
    }
    egg = temp;
}
void move_monster(){
    vector< vector< vector < int > > > temp(4, vector< vector < int > >(4, vector< int >(0)));
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            for (int k = 0 ; k < monster[i][j].size() ; k++){
                int idx = monster[i][j][k];
                int p = 0;
                for (; p < 8 ; p++){
                    int index = idx + p;
                    if (index >= 8)
                            index -= 8;
                    int nx = i + dx[index];
                    int ny = j + dy[index];
                    if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4)
                        continue;
                    if ((nx == r && ny == c) || (!dead[nx][ny].empty()))
                        continue;
                    temp[nx][ny].push_back(index);
                    break;
                }
                if (p == 8)
                    temp[i][j].push_back(monster[i][j][k]);
            }
        }
    }
    monster = temp;
}
void move_pacman(){
    int px[4] = {0, 1, 0, -1};
    int py[4] = {1, 0, -1, 0};
    int cnt = -1;
    vector< pair<int, int> > point;
    for (int i = 0 ; i < 4 ; i++){
        int ax = r + px[i];
        int ay = c + py[i];
        if (ax < 0 || ax >= 4 || ay < 0 || ay >= 4)
            continue;
        for (int j = 0 ; j < 4 ; j++){
            int bx = ax + px[j];
            int by = ay + py[j];
            if (bx < 0 || bx >= 4 || by < 0 || by >= 4)
                continue;
            for (int k = 0 ; k < 4 ; k++){
                int cx = bx + px[k];
                int cy = by + py[k];
                if (cx < 0 || cx >= 4 || cy < 0 || cy >= 4)
                    continue;
                vector< pair<int, int> > temp(0);
                vector< vector<int> > visit(4, vector<int>(4, 0));
                int temp_cnt = 0;
                temp.push_back(make_pair(ax, ay));
                temp.push_back(make_pair(bx, by));
                temp.push_back(make_pair(cx, cy));
                for (int q = 0 ; q < temp.size() ; q++){
                    int nx = temp[q].first;
                    int ny = temp[q].second;
                    if (visit[nx][ny])
                        continue;
                    temp_cnt += monster[nx][ny].size();
                    visit[nx][ny] = 1;
                }
                if (temp_cnt > cnt){
                    cnt = temp_cnt;
                    point = temp;
                }
            }
        }
    }
    int x = r, y = c;
    for (int i = 0 ; i < point.size() ; i++){
        int nx = point[i].first;
        int ny = point[i].second;
        while(!monster[nx][ny].empty()){
            monster[nx][ny].erase(monster[nx][ny].begin());
        }
        x = nx;
        y = ny;
    }
    r = x;
    c = y;
}
void checks_dead(){
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            for (int k = 0 ; k < dead[i][j].size() ; k++){
                if (dead[i][j][k] == 1){
                    dead[i][j].erase(dead[i][j].begin() + k);
                    k--;
                } else {
                    dead[i][j][k] += 1;
                }
            }
        }
    }
}
void birth_egg(){
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            for (int k = 0 ; k < egg[i][j].size() ; k++){
                monster[i][j].push_back(egg[i][j][k]);
                egg[i][j].erase(egg[i][j].begin() + k);
                k--;
            }
        }
    }
}
int main() {
    cin >> m >> t;
    cin >> r >> c;
    r -= 1;
    c -= 1;
    for (int i = 0 ; i < m ; i++){
        int a, b, c;
        cin >> a >> b >> c;
        monster[a-1][b-1].push_back(c-1);
    }
    for (int q = 0 ; q < t ; q++){
        copy_monster();
        move_monster();
        move_pacman();
        checks_dead();
        birth_egg();
    }
    int sum = 0;
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            sum += monster[i][j].size();
        }
    }
    cout << sum;
    return 0;
}