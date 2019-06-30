#include <iostream>
#include <stack>
#include <vector>
#include <cassert>
using namespace std;

const int W = 9, H = 9;
const int FULL = 0b111111111;

int a[H][W];
int h_sum[H] = {};
int v_sum[W] = {};
int area_sum[H/3][W/3];
bool finish = false;

stack<pair<int, int>> s;

int depow(int p){
    int cnt = 0;
    while(p) {
        cnt++;
        if(p & 1) break;
        p >>= 1;
    }

    return cnt;
}

void dfs() {
    if(finish) return;
    if(s.empty()) {
        finish = true;
        return;
    }

    auto next = s.top();
    int x = next.second, y = next.first;
    s.pop();

    int possibility = FULL ^ (v_sum[x] | h_sum[y] | area_sum[y/3][x/3]);

    for(int i = 0; i < 9; ++i){
        if(possibility & (1 << i)) {
            h_sum[y] |= 1 << i;
            v_sum[x] |= 1 << i;
            area_sum[y/3][x/3] |= 1 << i;
            a[y][x] = 1 << i;

            dfs();
            if(finish) return;

            a[y][x] = 0;
            area_sum[y/3][x/3] &= ~(1 << i);
            v_sum[x] &= ~(1 << i);
            h_sum[y] &= ~(1 << i); 
        } 
    }

    s.push(next);
}

bool puzzle_assert(){
    for(int y = 0; y < H; y += 3){
        for(int x = 0; x < W; x += 3){
            int tmp = 0;
            for(int dy = 0; dy < 3; ++dy) {
                for(int dx = 0; dx < 3; ++dx){
                    tmp |= a[y+dy][x+dx];
                }
            }
            if(tmp != FULL) return false;
        }
    }

    for(int y = 0; y < H; y++) {
        int tmp = 0;
        for(int x = 0; x < W; x++) {
            tmp |= a[y][x];
        }
        if(tmp != FULL) return false;
    }

    for(int x = 0; x < W; x++) {
        int tmp = 0;
        for(int y = 0; y < H; y++) {
            tmp |= a[y][x];
        }
        if(tmp != FULL) return false;
    }

    return true;
}

int main(){
    for(int y = 0; y < H; y++) {
        string str;
        cin >> str;
        std::vector<char> d(str.begin(), str.end());
        for(int x = 0; x < W; x++) {
            int tmp = d[x] - '0';
            if(!tmp) s.push(pair<int, int>(y, x));
            a[y][x] = (1 << tmp) / 2;
            h_sum[y] |= a[y][x];
        }
    }

    cout << "-- input -------------------------\n";
    for(int y = 0; y < H; y++) {
        for(int x = 0; x < W; x++) {
            if(x) printf(" ");
            printf("%d", depow(a[y][x]));
        }
        printf("\n");
    }
    cout << "----------------------------------\n\n";

    for(int x = 0; x < W; x++) {
        for(int y = 0; y < H; y++) {
            v_sum[x] |= a[y][x];
        }
    }

    for(int y = 0; y < H; y += 3){
        for(int x = 0; x < W; x += 3){
            for(int dy = 0; dy < 3; ++dy) {
                for(int dx = 0; dx < 3; ++dx){
                    area_sum[y/3][x/3] |= a[y+dy][x+dx];
                }
            }
        }
    }

    dfs();

    if(!puzzle_assert()) {
        cerr << "The answer not found" << endl;
    }

    cout << "-- answer ------------------------\n";
    for(int y = 0; y < H; y++) {
        for(int x = 0; x < W; x++) {
            if(x) printf(" ");
            printf("%d", depow(a[y][x]));
        }
        printf("\n");
    }
    cout << "----------------------------------\n";
}
