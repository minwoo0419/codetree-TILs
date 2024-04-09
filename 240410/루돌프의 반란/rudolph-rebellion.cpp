#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int N, M, P, C, D;
int Rx, Ry;
int SUM = 0;
vector< vector< vector<int> > > santa_map(51, vector< vector<int> >(51, vector<int>(0)));
vector< pair<int, int> > santa(31);
vector<int> santa_point(31, 0);
vector<int> santa_dead(31, 0);
void crush_rudolf(int idx, int santa_idx){
    int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
    santa_point[santa_idx] += C;
    santa_dead[santa_idx] = 2;
    int nx = santa[santa_idx].first + C * dx[idx];
    int ny = santa[santa_idx].second + C * dy[idx];
    santa_map[santa[santa_idx].first][santa[santa_idx].second].erase(santa_map[santa[santa_idx].first][santa[santa_idx].second].begin());
    if (nx < 1 || nx > N || ny < 1 || ny > N){
        santa[santa_idx] = make_pair(0, 0);
    } else{
        santa[santa_idx] = make_pair(nx, ny);
        santa_map[nx][ny].push_back(santa_idx);
        if (santa_map[nx][ny].size() > 1){
            int tx = nx;
            int ty = ny;
            while(1){
                int temp_santa = santa_map[tx][ty][0];
                santa_map[tx][ty].erase(santa_map[tx][ty].begin());
                tx += dx[idx];
                ty += dy[idx];
                if (tx < 1 || tx > N || ty < 1 || ty > N){
                    santa[temp_santa] = make_pair(0, 0);
                    break;
                }
                santa_map[tx][ty].push_back(temp_santa);
                santa[temp_santa] = make_pair(tx, ty);
                if (santa_map[tx][ty].size() == 1)
                    break;
            }
        }
    }
}
void move_rudolf(){
    int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
    int min = 2 * pow(N, 2);
    int idx = 0;
    int santa_idx = 0;
    for (int i = 1 ; i <= P ; i++){
        if (santa[i].first == 0 && santa[i].second == 0)
            continue;
        int temp_min = pow(Rx- santa[i].first, 2) + pow(Ry - santa[i].second, 2);
        if (temp_min < min){
            santa_idx = i;
            min = temp_min;
        } else if (temp_min == min){
            if (santa[santa_idx].first < santa[i].first){
                santa_idx = i;
            } else if(santa[santa_idx].first == santa[i].first){
                if (santa[santa_idx].second < santa[i].second){
                    santa_idx = i;
                }
            }
        }
    }
    if (santa_idx == 0)
        return ;
    for (int i = 0 ; i < 8 ; i++){
        int nx = Rx + dx[i];
        int ny = Ry + dy[i];
        if (nx < 1 || nx > N || ny < 1 || ny > N)
            continue;
        int temp_min = pow(nx - santa[santa_idx].first, 2) + pow(ny - santa[santa_idx].second, 2);
        if (temp_min < min){
            idx = i;
            min = temp_min;
        }
    }
    Rx += dx[idx];
    Ry += dy[idx];
    if (min == 0){
        crush_rudolf(idx, santa_idx);
    }
}
void crush_santa(int idx, int santa_idx){
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    santa_point[santa_idx] += D;
    santa_dead[santa_idx] = 2;
    int nx = santa[santa_idx].first + D * dx[idx];
    int ny = santa[santa_idx].second + D * dy[idx];
    santa_map[santa[santa_idx].first][santa[santa_idx].second].erase(santa_map[santa[santa_idx].first][santa[santa_idx].second].begin());
    if (nx < 1 || nx > N || ny < 1 || ny > N){
        santa[santa_idx] = make_pair(0, 0);
    } else{
        santa[santa_idx] = make_pair(nx, ny);
        santa_map[nx][ny].push_back(santa_idx);
        if (santa_map[nx][ny].size() > 1){
            int tx = nx;
            int ty = ny;
            while(1){
                int temp_santa = santa_map[tx][ty][0];
                santa_map[tx][ty].erase(santa_map[tx][ty].begin());
                tx += dx[idx];
                ty += dy[idx];
                if (tx < 1 || tx > N || ty < 1 || ty > N){
                    santa[temp_santa] = make_pair(0, 0);
                    break;
                }
                santa_map[tx][ty].push_back(temp_santa);
                santa[temp_santa] = make_pair(tx, ty);
                if (santa_map[tx][ty].size() == 1)
                    break;
            }
        }
    }
}
void move_santa(int idx){
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    int min = pow(Rx - santa[idx].first, 2) + pow(Ry - santa[idx].second, 2);
    int indexx = -1;
    for (int i = 0 ; i < 4 ; i++){
        int nx = santa[idx].first + dx[i];
        int ny = santa[idx].second + dy[i];
        if (nx < 1 || nx > N || ny < 1 || ny > N)
            continue;
        if (!santa_map[nx][ny].empty())
            continue;
        int temp_min = pow(Rx - nx, 2) + pow(Ry - ny, 2);
        if (temp_min < min){
            min = temp_min;
            indexx = i;
        }
    }
    if (indexx != -1){
        int nx = santa[idx].first + dx[indexx];
        int ny = santa[idx].second + dy[indexx];
        santa_map[santa[idx].first][santa[idx].second].erase(santa_map[santa[idx].first][santa[idx].second].begin());
        santa[idx] = make_pair(nx, ny);
        santa_map[nx][ny].push_back(idx);
        if (nx == Rx && ny == Ry){
            crush_santa(indexx, idx);
        }
    }
}
void move_santas(){
    for (int i = 1 ; i <= P ; i++){
        if (santa[i].first == 0 && santa[i].second == 0)
            continue;
        if (santa_dead[i] > 0)
            continue;
        move_santa(i);
    }
}
void plus_one(){
    for (int i = 1 ; i <= P ; i++){
        if (santa[i].first == 0 && santa[i].second == 0)
            continue;
        santa_point[i] += 1;
    }
}
void check_dead(){
    for (int i = 1 ; i <= P ; i++){
        if (santa_dead[i] == 0)
            continue;
        santa_dead[i] -= 1;
    }
}
int main() {
    cin >> N >> M >> P >> C >> D;
    cin >> Rx >> Ry;
    for (int i = 0 ; i < P ; i++){
        int n, x, y;
        cin >> n >> x >> y;
        santa[n] = make_pair(x, y);
        santa_map[x][y].push_back(n);
    }
    for (int i = 0 ; i < M ; i++){
        move_rudolf();
        move_santas();
        plus_one();
        check_dead();
    }
    for (int i = 1 ; i <= P ; i++){
        cout << santa_point[i] << " ";
    }
    return 0;
}