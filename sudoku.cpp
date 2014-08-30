#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

#define rep(i,n) for(int i=0;i<n;i++)
#define forup(i,a,b) for(int i=a;i<=b;i++)
#define fordn(i,a,b) for(int i=a;i>=b;i--)
#define pb push_back

int board[9][9];

bool issafe(int I,int J,int x){

    //check row
    rep(i,9)if(board[I][i]==x)return false;

    //check col
    rep(i,9)if(board[i][J]==x)return false;
    
    //check grid
    int sx = (I/3)*3,sy=(J/3)*3;

    rep(i,3)
        rep(j,3)
            if(board[sx+i][sy+j]==x)return false;

    return true;
}

bool backtrack(vector<pii> &v,int index){
    if(index == v.size())return true;
    int x = v[index].first,y=v[index].second;
    forup(i,1,9)
        if(issafe(x,y,i)){
            board[x][y]=i;
            if(backtrack(v,index+1))return true;
        }
    board[x][y]=0;
    return false;
}

bool solve(){
    vector<pii> v;
    rep(i,9)rep(j,9)if(board[i][j]==0)v.pb(pii(i,j));
    return backtrack(v,0);
}

int main(){
    puts("\n***************************************************************");
    puts("*");
    puts("*\t9*9 Sudoku Solver by JJ");
    puts("*");
    puts("* Instructions:");
    puts("* -- total 9 input lines");
    puts("* -- each input line should contain only 9 chars (no spaces)");
    puts("* -- char can be either 1-9 or a '.' (signifies unknown number)");
    puts("* -- ensure there are no trailing/leading whitespaces");
    puts("*");
    puts("***************************************************************\n");

    rep(i,9){
        rep(j,9){
            char ch; scanf("%c",&ch);
            board[i][j]= ch=='.' ? 0 : ch-'0';
        }
        getchar();
    }
    if(solve()){
        puts("");
        rep(i,9){
            rep(j,9)
                printf(" %d |",board[i][j]);
            puts("\n------------------------------------");
        }
    }
    else
        puts("\nNo solution");
}
