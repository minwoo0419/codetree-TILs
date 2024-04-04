#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
int n, m;
vector<int> monster;
vector< vector<int> > map(25, vector<int>(25, 0));
vector< pair<int, int> > rounds;
void set_monster(){
    vector<int> temp;
    int x = n / 2;
    int y = n / 2;
    int cnt = 1;
    int flag = 0;
    while(x >= 0 && x < n && y >= 0 && y < n){
        for(int i = 0 ; i < cnt ; i++){
            int plus = (cnt % 2 == 1 ? -1 : 1);
            y += plus;
            if(x < 0 || x >= n || y < 0 || y >= n){
                flag = 1;
                break;
            }
            if (map[x][y] != 0){
                 temp.push_back(map[x][y]);
            }
        }
        if (flag)
            break;
        for(int i = 0 ; i < cnt ; i++){
            int plus = (cnt % 2 == 0 ? -1 : 1);
            x += plus;
            if(x < 0 || x >= n || y < 0 || y >= n){
                flag = 1;
                break;
            }
            if (map[x][y] != 0){
                temp.push_back(map[x][y]);
            }
        }
        if (flag)
            break;
        cnt++;
    }
    monster = temp;
}
void reset_monster(){
    vector<int> temp;
    int cnt = 1;
    for (int i = 0 ; i < monster.size() ; i++){
        if ( i < monster.size() - 1 && monster[i] == monster[i+1])
            cnt++;
        else{
            temp.push_back(cnt);
            temp.push_back(monster[i]);
            cnt = 1;
        }
    }
    monster = temp;
}
int attack(int d, int p){
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int x = n / 2;
    int y = n / 2;
    int sum = 0;
    for (int i = 0 ; i < p ; i++){
        x += dx[d];
        y += dy[d];
        sum += map[x][y];
        map[x][y] = 0;
    }
    return sum;
}
void move(){
    vector< vector<int> > temp(25, vector<int>(25, 0));
    int x = n / 2;
    int y = n / 2;
    int cnt = 1;
    int flag = 0;
    int idx = 0;
    while(1){
        for(int i = 0 ; i < cnt ; i++){
            int plus = (cnt % 2 == 1 ? -1 : 1);
            y += plus;
            if (idx == monster.size()){
                flag = 1;
                break;
            }
            temp[x][y] = monster[idx];
            idx++;
        }
        if (flag == 1)
            break;
        for(int i = 0 ; i < cnt ; i++){
            int plus = (cnt % 2 == 0 ? -1 : 1);
            x += plus;
            if (idx == monster.size()){
                flag = 1;
                break;
            }
            temp[x][y] = monster[idx];
            idx++;
        }
        if (flag == 1)
            break;
        cnt++;
    }
    map = temp;
}
int erase_same(){
    int cnt = 1;
    int sum = 0;
    for (int i = 0 ; i < monster.size() - 1 ; i++){
        if (monster[i] == monster[i+1]){
            cnt++;
        } else{
            if (cnt >= 4){
                sum += (monster[i] * cnt);
                for (int j = 0 ; j < cnt ; j++){
                    monster.erase(monster.begin() + (i - cnt + 1));
                }
            }
            cnt = 1;
        }
    }
    return sum;
}
int main() {
    cin >> n >> m;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            int a;
            cin >> a;
            map[i][j] = a;
        }
    }
    int sum = 0;
    set_monster();
    for (int i = 0 ; i < m ; i++){
        int a, b;
        cin >> a >> b;
        sum += attack(a, b);
        set_monster();
        move();
        while(1){
            int check = erase_same();
            if (check == 0)
                break;
            sum += check;
            move();
        }
        reset_monster();
        move();
    }
    cout << sum;
    return 0;
}