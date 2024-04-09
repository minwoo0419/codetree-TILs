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
int n, m, h, k;
int r, c;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int sum = 0;
int flag = 0;
int rounds = 0;
vector< vector<int> > tree(100, vector<int>(100, 0));
vector< vector< vector<int> > > people(100, vector< vector<int> >(100, vector<int>(4, 0)));
void move_people(){
    vector< vector< vector<int> > > temp_people(100, vector< vector<int> >(100, vector<int>(4, 0)));
    for (int i = 1 ; i <= n ; i++){
        for (int j = 1 ; j <= n ; j++){
            if (abs(i - r) + abs(j - c) > 3)
                continue;
            for (int t = 0 ; t < 4 ; t++){
                if (people[i][j][t] == 0)
                    continue;
                int idx = t;
                if (i + dx[idx] < 1 || i + dx[idx] > n || j + dy[idx] < 1 || j + dy[idx] > n){
                    idx += 2;
                    if (idx >= 4){
                        idx -= 4;
                    }
                }
                int nx = i + dx[idx];
                int ny = j + dy[idx];
                if (nx == r && ny == c)
                    temp_people[i][j][idx] += people[i][j][t];
                else
                    temp_people[nx][ny][idx] += people[i][j][t];
            }
        }
    }
    people = temp_people;
}
void move_soolae(){
    int sx[4] = {-1, 0, 1, 0};
    int sy[4] = {0, 1, 0, -1};
    int idx = rounds % 4;
    for (int i = 0 ; i <= rounds / 2 ; i++){
        if (i == n - 1){
            flag = 1;
            rounds += 1;
            break;
        }
        r += sx[idx];
        c += sy[idx];
    }
}
void move_soolae_re(){
    int sx[4] = {1, 0, -1, 0};
    int sy[4] = {0, -1, 0, 1};
    int idx = rounds % 4;
    for (int i = 0 ; i <= rounds / 2 ; i++){
        if (i == n - 1){
            break;
        }
        r += sx[idx];
        c += sy[idx];
    }
    if (r == (n+1) / 2 && c == (n+1) / 2){
        flag = 0;
        rounds -= 1;
    }
}
int catch_people(){
    int sx[4] = {-1, 0, 1, 0};
    int sy[4] = {0, 1, 0, -1};
    int idx = rounds % 4;
    int x = r, y = c;
    int temp = 0;
    for (int i = 0 ; i < 3 ; i++){
        if (x < 1 && x > n && y < 1 && y > n)
            continue;
        if (tree[x][y]){
            x += sx[idx];
            y += sy[idx];
            continue;
        }
        for (int j = 0 ; j < 4 ; j++){
            if(people[x][y][j] == 0)
                continue;
            temp += people[x][y][j];
            people[x][y][j] = 0;
        }
        x += sx[idx];
        y += sy[idx];
    }
    return temp;
}
int catch_people_re(){
    int sx[4] = {1, 0, -1, 0};
    int sy[4] = {0, -1, 0, 1};
    int idx = rounds % 4;
    int x = r, y = c;
    int temp = 0;
    for (int i = 0 ; i < 3 ; i++){
        if (x < 1 && x > n && y < 1 && y > n)
            continue;
        if (tree[x][y])
            continue;
        for (int j = 0 ; j < 4 ; j++){
            if(people[x][y][j] == 0)
                continue;
            temp += people[x][y][j];
            people[x][y][j] = 0;
        }
        x += sx[idx];
        y += sy[idx];
    }
    return temp;
}
// void print_people(){
//     cout << "print_people==========\n";
//     for (int i = 1 ; i <= n ; i++){
//         for (int j = 1 ; j <= n ; j++){
//             int sum = 0;
//             for (int t = 0 ; t < 4 ; t++){
//                 sum += people[i][j][t];
//             }
//             cout << sum << " ";
//         }
//         cout << "\n";
//     }
// }
// void print_rc(){
//     cout << "print_r_c===============\n" << r << " " << c << "\n";
// }
int main() {
    cin >> n >> m >> h >> k;
    for (int i = 0 ; i < m ; i++){
        int x, y, z;
        cin >> x >> y >> z;
        people[x][y][z-1] += 1;
    }
    for (int i = 0 ; i < h ; i++){
        int x, y;
        cin >> x >> y;
        tree[x][y] = 1;
    }
    r = (n+1) / 2;
    c = (n+1) / 2;
    for (int i = 1 ; i <= k ; i++){
        // print_people();
        move_people();
        // print_people();
        // print_rc();
        if (flag){
            move_soolae_re();
        } else{
            move_soolae();
        }
        // print_rc();
        if (flag){
            rounds--;
            sum += catch_people_re() * i;
        } else{
            rounds++;
            sum += catch_people() * i;
        }
        // print_people();
    }
    cout << sum;
    return 0;
}