#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
// #include <bits/stdc++.h>
int L, N, Q;
vector< vector<int> > map(41, vector<int>(41, 0));
vector< vector<int> > knight(31, vector<int>(5, 0));
vector< vector<int> > knight_map(41, vector<int>(41, 0));
vector<int> damage(31, 0);
vector< pair<int, int> > command(0);
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
vector<int> check_move(int idx, int d){
    int tx = knight[idx][0];
    int ty = knight[idx][1];
    vector< vector<int> > visit(41, vector<int>(41, 0));
    vector<int> knight_visit(31, 0);
    queue< pair<int, int> > q;
    q.push(make_pair(knight[idx][0], knight[idx][1]));
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        visit[x][y] = 1;
        knight_visit[knight_map[x][y]] = 1;
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx < 1 || nx > L || ny < 1 || ny > L){
            knight_visit.clear();
            return knight_visit;
        }
        if (map[nx][ny] == 2){
            knight_visit.clear();
            return knight_visit;
        }
        for (int i = 0 ; i < 4 ; i++){
            int td = (d + 2 > 3) ? d - 2 : d + 2;
            if (i == td)
                continue;
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 1 || tx > L || ty < 1 || ty > L)
                continue;
            if (knight_map[tx][ty] == 0)
                continue;
            if (i != d){
                if (knight_map[x][y] != knight_map[tx][ty])
                    continue;
            }
            if (visit[tx][ty] == 0){
                q.push(make_pair(tx, ty));
            }
        }
    }
    return knight_visit;
}
void check_trap(int idx, vector<int> knight_visit){
    for (int i = 1 ; i <= L ; i++){
        for (int j = 1 ; j <= L ; j++){
            if (knight_map[i][j] == 0)
                continue;
            if (knight_map[i][j] != idx && map[i][j] == 1 && knight_visit[knight_map[i][j]] == 1){
                damage[knight_map[i][j]] += 1;
            }
        }
    }
}
void move_knight(int idx, int d){
    vector<int> can_move = check_move(idx, d);
    if (can_move.empty())
        return;
    if (d == 0){
        for (int i = 2 ; i <= L ; i++){
            for (int j = 1 ; j <= L ; j++){
                if (knight_map[i][j] == 0)
                    continue;
                int indexx = knight_map[i][j];
                if (can_move[indexx]){
                    if (knight[indexx][0] == i && knight[indexx][1] == j){
                        knight[indexx][0] = i + dx[d];
                        knight[indexx][1] = j + dy[d];
                    }
                    knight_map[i+dx[d]][j+dy[d]] = indexx;
                    knight_map[i][j] = 0;
                }
            }
        }
    } else if (d == 1){
        for (int j = L - 1 ; j >= 1 ; j--){
            for (int i = 1 ; i <= L ; i++){
                if (knight_map[i][j] == 0)
                    continue;
                int indexx = knight_map[i][j];
                if (can_move[indexx]){
                    if (knight[indexx][0] == i && knight[indexx][1] == j){
                        knight[indexx][0] = i + dx[d];
                        knight[indexx][1] = j + dy[d];
                    }
                    knight_map[i+dx[d]][j+dy[d]] = indexx;
                    knight_map[i][j] = 0;
                }
            }
        }
    } else if (d == 2){
        for (int i = L - 1 ; i >= 0 ; i--){
            for (int j = 1 ; j <= L ; j++){
                if (knight_map[i][j] == 0)
                    continue;
                int indexx = knight_map[i][j];
                if (can_move[indexx]){
                    if (knight[indexx][0] == i && knight[indexx][1] == j){
                        knight[indexx][0] = i + dx[d];
                        knight[indexx][1] = j + dy[d];
                    }
                    knight_map[i+dx[d]][j+dy[d]] = indexx;
                    knight_map[i][j] = 0;
                }
            }
        }
    } else if (d == 3){
        for (int j = 2 ; j <= L ; j++){
            for (int i = 1 ; i <= L ; i++){
                if (knight_map[i][j] == 0)
                    continue;
                int indexx = knight_map[i][j];
                if (can_move[indexx]){
                    if (knight[indexx][0] == i && knight[indexx][1] == j){
                        knight[indexx][0] = i + dx[d];
                        knight[indexx][1] = j + dy[d];
                    }
                    knight_map[i+dx[d]][j+dy[d]] = indexx;
                    knight_map[i][j] = 0;
                }
            }
        }
    }
    check_trap(idx, can_move);

}
void check_dead(){
    for (int i = 1 ; i <= N ; i++){
        if (knight[i][4] <= damage[i]){
            knight[i][0] = 0;
            knight[i][1] = 0;
            damage[i] = 0;
            for (int j = 1 ; j <= L ; j++){
                for (int k = 1 ; k <= L ; k++){
                    if (knight_map[j][k] == i)
                        knight_map[j][k] = 0;
                }
            }
        }
    }
}
void print_map(){
    cout << "\n============print_map=============\n";
    for(int i = 1 ; i <= L ; i++){
        for (int j =1 ; j <= L ; j++){
            cout << knight_map[i][j] << " ";
        }
        cout << "\n";
    }
}
int main() {
    cin >> L >> N >> Q;
    for (int i = 1 ; i <= L ; i++){
        for (int j = 1 ; j <= L ; j++){
            cin >> map[i][j];
        }
    }
    for (int i = 1 ; i <= N ; i++){
        int a, b, c, d, e;
        cin >> knight[i][0] >> knight[i][1] >> knight[i][2] >> knight[i][3] >> knight[i][4];
        for (int j = knight[i][0] ; j < knight[i][0] + knight[i][2] ; j++){
            for (int k = knight[i][1] ; k < knight[i][1] + knight[i][3] ; k++){
                knight_map[j][k] = i;
            }
        }
    }
    for (int i = 1 ; i <= Q ; i++){
        int a, b;
        cin >> a >> b;
        command.push_back(make_pair(a, b));
    }
    for (int i = 0 ; i < Q ; i++){
        // print_map();
        int idx = command[i].first;
        int d = command[i].second;
        if (knight[idx][0] == 0 && knight[idx][1] == 0)
            continue;
        move_knight(idx, d);
        check_dead();
    }
    // print_map();
    int sum = 0;
    for (int i = 1 ; i <= N ; i++){
        sum += damage[i];
    }
    cout << sum;
    return 0;
}