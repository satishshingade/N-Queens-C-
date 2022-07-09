
#include<bits/stdc++.h>
using namespace std;


int N;
bool found=false;
vector<vector<int>>ret;
bool is_valid(vector<string> &board, int row, int col){
    // check col
    for(int i=row;i>=0;--i)
        if(board[i][col] == 'Q') return false;
    // check left diagonal
    for(int i=row,j=col;i>=0&&j>=0;--i,--j)
        if(board[i][j] == 'Q') return false;
    //check right diagonal
    for(int i=row,j=col;i>=0&&j<board.size();--i,++j)
        if(board[i][j] == 'Q') return false;
    return true;
}
void dfs(vector<string> &board, int row){
    if(found)
        return;

    if(row == board.size()){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(board[i][j]=='Q')
                    ret[i][j]=1;
            }
        }
        found=true;
        return;
    }
    // iterate every possible position
    for(int i=0;i<board.size();++i){
        if(is_valid(board,row,i)){
            // make decision
            board[row][i] = 'Q';
            // next iteration
            dfs(board,row+1);
            // back-tracking
            board[row][i] = '.';
        }
    }
}
vector<vector<int>> solveNQueens(int n) {
    found=false;
    N=n;
    ret.clear();
    ret.resize(N,vector<int>(N));
    // return empty if n <= 0

    if(n <= 0) return ret;
    vector<string> board(n,string(n,'.'));
    dfs(board,0);

    return ret;
}

