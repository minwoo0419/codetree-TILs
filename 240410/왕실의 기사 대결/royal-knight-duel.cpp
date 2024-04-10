#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
int L, N, Q;
vector< vector<int> > map(41, vector<int>(41, 0));
vector< vector<int> > per(31, vector<int>(5, 0));
vector< vector<int> > new_per(31, vector<int>(5, 0));
vector<int> damage(31, 0);
vector<int> visit_knight(31, 0);
vector< pair<int, int> > command(0);
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int check_move(int idx, int d){
    new_per = per;
    fill(visit_knight.begin(), visit_knight.end(), 0);
    queue<int> q;
    q.push(idx);
    visit_knight[idx] = 1;
    while(!q.empty()){
        int nidx = q.front();
        q.pop();
        new_per[nidx][0] += dx[d];
        new_per[nidx][1] += dy[d];
        int nx = new_per[nidx][0];
        int ny = new_per[nidx][1];
        if (nx < 1 || nx  > L || ny < 1 || ny> L)
            return 0;
        for (int i = nx ; i < nx + per[nidx][2] ; i++){
            for (int j = ny ; j < ny + per[nidx][3] ; j++){
                if (i < 1 || i > L || j < 1 || j > L)
                    return 0;
                if (map[i][j] == 2)
                    return 0;
                if (map[i][j] == 1 && nidx != idx)
                    new_per[nidx][4] -= 1;
            }
        }
        for (int i = 1 ; i <= N ; i++){
            if (visit_knight[i] == 1 || per[i][4] <= 0)
                continue;
            if (per[i][0] >= nx + per[nidx][2] || nx >= per[i][0] + per[i][2])
                continue;
            if (per[i][1] >= ny + per[nidx][3] || ny >= per[i][1] + per[i][3])
                continue;
            q.push(i);
            visit_knight[i] = 1;
        }
    }
    return 1;
}
void move_per(int idx, int d){
    if (per[idx][4] <= 0)
        return ;
    if (check_move(idx, d)){
        per = new_per;
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
        cin >> per[i][0] >> per[i][1] >> per[i][2] >> per[i][3] >> per[i][4];
        damage[i] = per[i][4];
    }
    for (int i = 1 ; i <= Q ; i++){
        int a, b;
        cin >> a >> b;
        command.push_back(make_pair(a, b));
    }
    for (int i = 0 ; i < Q ; i++){
        move_per(command[i].first, command[i].second);
    }
    int sum = 0;
    for (int i = 1 ; i <= N ; i++){
        if (per[i][4] > 0)
            sum += (damage[i] - per[i][4]);
    }
    cout << sum;
    return 0;
}