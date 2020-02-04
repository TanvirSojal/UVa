#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 9;

// checking conflict in N-Queen board in O(N) time and space
bool conflict(vector<int> &board){
    vector<int> row(N);
    vector<int> mdiag(2*N);
    vector<int> sdiag(2*N);
    for (int i = 1; i < N; i++){
        if (board[i] == 0) continue;
        row[ board[i] ]++;
        mdiag[ board[i] + i ]++;
        sdiag[ 9 - board[i] + i]++;
        if (row[ board[i] ] > 1) return true;
        if (mdiag[ board[i] + i ] > 1) return true;
        if (sdiag[ 9 - board[i] + i] > 1) return true;
    }
    return false;
}

vector<vector<int>> boards;

// generating solution using backtracking
void F(int pos, vector<int> board){
    if (pos > 8){
        if (conflict(board)) return ;
        boards.push_back(board);
        return;
    }
    for (int i = 1; i < N; i++){
        vector<int> tmp = board;
        tmp[pos] = i;
        // only proceed if next step
        // does not contain Queen conflict
        if (!conflict(tmp)){
            F(pos+1, tmp);
        }
    }
}

// generate all solution boards
void preprocess(){
    vector<int> newBoard(N);
    F(1, newBoard);
}

int main()
{
//    vector<int> v = {0, 7,1,3,8,6,4,2,5};
//    freopen("input.txt", "r", stdin);
    preprocess();

    vector<int> Board(N);
    int cs = 1;
    while(scanf("%d", &Board[1]) != EOF){
        int ans = INT_MAX;

        for (int i = 2; i < N; i++){
            scanf("%d", &Board[i]);
        }

        for (vector<int> board : boards){
            int cnt = 0;
            for (int i = 1; i < N; i++){
                if (board[i] != Board[i])
                    ++cnt;
            }
            ans = min(ans, cnt);
        }

        printf("Case %d: %d\n", cs++, ans);
    }
    return 0;
}



