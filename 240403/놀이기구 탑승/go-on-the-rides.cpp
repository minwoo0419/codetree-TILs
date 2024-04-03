#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;
int n;
vector< vector<int> > map(20, vector<int>(20, 0));
vector< vector<int> > likes(400, vector<int>(5, 0));
int dx[4] = {-1, 0, 0 ,1};
int dy[4] = {0, -1, 1, 0};
pair<int, int> check_sit(vector<int> likes, int x, int y){
    int empty = 0, have = 0;
    for (int i = 0 ; i < 4 ; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < n && ny < n){
            if (map[nx][ny] == 0)
                empty++;
            else{
                for (int j = 1 ; j < likes.size() ; j++){
                    if (map[nx][ny] == likes[j]){
                        have += 1;
                    }
                }
            }
        }
    }
    return make_pair(have, empty);
}
void sit(){
    for (int k = 0 ; k < pow(n, 2) ; k++){
        int student = likes[k][0];
        int empty = -1, have = -1, x = 0, y = 0;
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                if (map[i][j] == 0){
                    pair<int, int> temp = check_sit(likes[k], i, j);
                    if (temp.first > have){
                        have = temp.first;
                        empty = temp.second;
                        x = i;
                        y = j;
                    } else if (temp.first == have){
                        if (temp.second > empty){
                            empty = temp.second;
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        map[x][y] = student;
    }
}
int check_point(int stu){
    int sum = 0;
    for (int i = 0 ; i < pow(n, 2) ; i++){
        if (likes[i][0] == stu){
            return i;
        }
    }
    return -1;
}
int sum_point(){
    int sum = 0;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            int idx = check_point(map[i][j]);
            int temp = check_sit(likes[idx], i, j).first;
            sum += pow(10, temp - 1);
        }
    }
    return sum;
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n;
    for (int i = 0 ; i < pow(n, 2) ; i++){
        for (int j = 0 ; j < 5 ; j++){
            int a;
            cin >> a;
            likes[i][j] = a;
        }
    }
    sit();
    cout << sum_point();
    return 0;
}