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
int is_rev = 0;
vector< vector<int> > tree(100, vector<int>(100, 0));
vector< vector< vector<int> > > people(100, vector< vector<int> >(100, vector<int>(4, 0)));
vector< vector< int > > turn(100, vector<int>(100, 0));
vector< vector< int > > rev_turn(100, vector<int>(100, 0));
void init_turn(){
    int tx[4] = {-1, 0, 1, 0};
    int ty[4] = {0, 1, 0, -1};
    int index = 0;
    int x = (n + 1) / 2;
    int y = (n + 1) / 2;
    int flag = 1;
    while(flag){
        int rounds = index % 4;
        for (int i = 0 ; i <= index / 2 ; i++){
            turn[x][y] = rounds;
            x += tx[rounds];
            y += ty[rounds];
            rev_turn[x][y] = (rounds + 2 >= 4) ? (rounds - 2) : (rounds + 2);
            if (x < 1 || x > n || x < 1 || y > n){
                flag = 0;
                break;
            }
        }
        index++;
    }
}
void move_people(){
    vector< vector< vector<int> > > temp_people(100, vector< vector<int> >(100, vector<int>(4, 0)));
    for (int i = 1 ; i <= n ; i++){
        for (int j = 1 ; j <= n ; j++){
            if (abs(i - r) + abs(j - c) > 3){
                for (int t = 0 ; t < 4 ; t++){
                    temp_people[i][j][t] += people[i][j][t];
                }
                continue;
            }
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

// void print_people(){
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
// void print_tree(){
//     for (int i = 1 ; i <= n ; i++){
//         for (int j = 1 ; j <= n ; j++){
//             cout << tree[i][j] << " ";
//         }
//         cout << "\n";
//     }
// }
// void print_rc(){
//     cout << "print_r_c=============== " << r << " " << c << "\n";
// }
void move_soolae(){
    int tx[4] = {-1, 0, 1, 0};
    int ty[4] = {0, 1, 0, -1};
    int x = r;
    int y = c;
    if (is_rev == 0){
        r += tx[turn[x][y]];
        c += ty[turn[x][y]];
    } else{
        r += tx[rev_turn[x][y]];
        c += ty[rev_turn[x][y]];
    }
    if(is_rev == 1 && r == (n+1) / 2 && c == (n+1) / 2){
        is_rev = 0;
    } else if (is_rev == 0 && r == 1 && c == 1){
        is_rev = 1;
    }
}
int catch_people(){
    int tx[4] = {-1, 0, 1, 0};
    int ty[4] = {0, 1, 0, -1};
    int idx = 0;
    if (is_rev == 0)
        idx = turn[r][c];
    else
        idx = rev_turn[r][c];
    int x = r, y = c;
    int temp = 0;
    for (int i = 0 ; i < 3 ; i++){
        if (x < 1 && x > n && y < 1 && y > n)
            continue;
        if (tree[x][y]){
            x += tx[idx];
            y += ty[idx];
            continue;
        }
        for (int j = 0 ; j < 4 ; j++){
            if(people[x][y][j] == 0)
                continue;
            temp += people[x][y][j];
            people[x][y][j] = 0;
        }
        x += tx[idx];
        y += ty[idx];
    }
    return temp;
}
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
    init_turn();
    for (int i = 1 ; i <= k ; i++){
        // print_people();
        // print_tree();
        // print_rc();
        move_people();
        move_soolae();
        sum += (catch_people() * i);
    }
    cout << sum;
    return 0;
}