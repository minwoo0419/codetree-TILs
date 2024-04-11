#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
int n, m, k;
int cx, cy;
vector< vector<int> > map(11, vector<int>(11, 0));
vector< vector<int> > nmap(11, vector<int>(11, 0));
vector<int> dis(11, 0);
vector<int> point(4, 0);
vector< pair<int, int> > per(0);
vector< pair<int, int> > nper(0);

void move_person(int idx){
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int x = per[idx].first;
    int y = per[idx].second;
    int d = pow(cx - x, 2) + pow(cy - y, 2);
    int temp = 0;
    int tidx = -1;
    for (int i = 0 ; i < 4 ; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 1 || nx > n || ny < 1 || ny > n)
            continue;
        if (map[nx][ny] != 0)
            continue;
        if (d > pow(cx - nx, 2) + pow(cy - ny, 2)){
            tidx = i;
            temp = pow(cx - nx, 2) + pow(cy - ny, 2);
            break;
        }
    }
    if (tidx == -1)
        return;
    dis[idx] += 1;
    if (temp == 0)
        per[idx] = make_pair(0, 0);
    else
        per[idx] = make_pair(x + dx[tidx], y + dy[tidx]);

}
void move_persons(){
    for (int i = 0 ; i < m ; i++){
        if (per[i].first == 0 && per[i].second == 0)
            continue;
        move_person(i);
    }
}
vector<int> check_square(){
    int min = n * n;
    vector<int> point(3, 0);
    for (int size = 0 ; size < n ; size++){
        for (int i = 1 ; i <= n - size ; i++){
            for (int j = 1 ; j <= n - size ; j++){
                int peo_cnt = 0;
                int check = 0;
                for (int x = i ; x <= i + size ; x++){
                    for (int y = j ; y <= j + size ; y++){
                        for (int p = 0 ; p < m ; p++){
                            if (per[p].first == x && per[p].second == y)
                                peo_cnt++;
                            if (cx == x && cy == y){
                                check = 1;
                            }
                        }
                    }
                }
                if (check && peo_cnt > 0){
                    point[0] = i;
                    point[1] = j;
                    point[2] = size;
                    return point;
                }
            }
        }
    }
    return point;
}
void turn_square(){
    point = check_square();
    if (point[0] == 0)
        return;
    nmap = map;
    nper = per;
    int x = point[0];
    int y = point[1];
    int num = point[2];
    int flag = 0;
    for (int i = 0 ; i <= num ; i++){
        for (int j = 0 ; j <= num ; j++){
            if (cx == x + i && cy == y + j && flag == 0){
                cx = x + j;
                cy = y + num - i;
                flag = 1;
            }
            nmap[x + j][y + num - i] = map[x + i][y + j];
            if (nmap[x+j][y+ num - i] > 0)
                nmap[x+j][y + num - i] -= 1;
            for (int k = 0 ; k < m ; k++){
                if (per[k].first == x + i && per[k].second == y + j){
                    nper[k] = make_pair(x+j, y+num-i);
                }
            }
        }
    }
    map = nmap;
    per = nper;
}
// void print_an(){
//     cout << "===map===\n";
//     for (int i = 1 ; i <= n ; i++){
//         for (int j = 1 ; j <= n ; j++){
//             cout << map[i][j] << " ";
//         }
//         cout << "\n";
//     }
//     cout << "\n===talchool===\n";
//     cout << cx << " " << cy << "\n";
//     cout << "\n===person===\n";
//     for (int i = 0 ; i < m ; i++){
//         cout << i << " " << per[i].first << " " << per[i].second << "\n";
//     }
//     cout << "\n===walk===\n";
//     for (int i = 0 ; i < m ; i++){
//         cout << dis[i] << "\n";
//     }
//     cout << "\n";
// }

int main() {
    cin >> n >> m >> k;
    for (int i = 1 ; i <= n ; i++){
        for (int j = 1 ; j <= n ; j++){
            cin >> map[i][j];
        }
    }
    for (int i = 1 ; i <= m ; i++){
        int x, y;
        cin >> x >> y;
        per.push_back(make_pair(x, y));
    }
    cin >> cx >> cy;
    for (int i = 1 ; i <= k ; i++){
        move_persons();
        turn_square();
    }
    int sum = 0;
    for (int i = 0 ; i < m ; i++){
        sum += dis[i];
    }
    cout << sum << "\n" << cx << " " << cy;
    return 0;
}