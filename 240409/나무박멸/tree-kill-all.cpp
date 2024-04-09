#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
using namespace std;
int n, m, k, c;
vector< vector<int> > tree(20, vector<int>(20, 0));
vector< vector<int> > dead(20, vector<int>(20, 0));
int check_near_tree(int x, int y){
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int count = 0;
    for (int i = 0 ; i < 4 ; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n)
            continue;
        if (tree[nx][ny] > 0){
            count++;
        }
    }
    return count;
}
void grow(){
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            if (tree[i][j] > 0)
                tree[i][j] += check_near_tree(i, j);
        }
    }
}
pair<int, vector< pair<int, int> > > check_near_blank(int x, int y){
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int count = 0;
    vector< pair<int, int> > point;
    for (int i = 0 ; i < 4 ; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n)
            continue;
        if (tree[nx][ny] == 0 && dead[nx][ny] == 0){
            count++;
            point.push_back(make_pair(nx, ny));
        }
    }
    return make_pair(count, point);

}
void reproduce(){
    vector< vector<int> > temp_tree(n, vector<int>(n, 0));
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            if (tree[i][j] <= 0)
                continue;
            pair<int, vector< pair<int, int> > > temp = check_near_blank(i, j);
            if (temp.first == 0)
                continue;
            int plus = tree[i][j] / temp.first;
            for (int w = 0 ; w < temp.second.size() ; w++){
                temp_tree[temp.second[w].first][temp.second[w].second] += plus;
            }
        }
    }
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            tree[i][j] += temp_tree[i][j];
        }
    }
}
void check_dead(){
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            if (dead[i][j] > 0)
                dead[i][j] -= 1;
        }
    }
}
pair<int, vector< pair<int, int> > > check_weed(int x, int y){
    int count = tree[x][y];
    vector< pair<int, int> > point;
    point.push_back(make_pair(x, y));
    int dx[4] = {1, 1, -1, -1};
    int dy[4] = {-1, 1, -1, 1};
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 1 ; j <= k ; j++){
            int nx = x + dx[i] * j;
            int ny = y + dy[i] * j;
            if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                continue;
            if (tree[nx][ny] != -1)
                count += tree[nx][ny];
            point.push_back(make_pair(nx, ny));
            if (tree[nx][ny] <= 0)
                break;

        }
    }
    return make_pair(count, point);
}
int weed(){
    int sum = 0;
    vector< pair<int, int> > point;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            if (tree[i][j] <= 0)
                continue;
            pair<int, vector< pair<int, int> > > temp = check_weed(i, j);
            if (sum < temp.first){
                sum = temp.first;
                point = temp.second;
            }
        }
    }
    for(int i = 0 ; i < point.size() ; i++){
        tree[point[i].first][point[i].second] = 0;
        dead[point[i].first][point[i].second] = c;
    }
    return sum;
}
// void print_tree(){
//     cout << "print Tree : \n";
//     for (int i = 0 ; i < n ; i++){
//         for (int j = 0 ; j < n ; j++){
//             cout << tree[i][j] << " ";
//         }
//         cout << "\n";
//     }
//     cout << "\n";
// }
int main() {
    int sum = 0;
    cin >> n >> m >> k >> c;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            cin >> tree[i][j];
        }
    }
    for (int i = 0 ; i < m ; i++){
        grow();
        reproduce();
        check_dead();
        sum += weed();
    }
    cout << sum;
    return 0;
}