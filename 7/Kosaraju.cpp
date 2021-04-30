#include <iostream>
#include <fstream>

#include "StackClass.cpp"

using namespace std;

void dfs(int n, int** adj, bool* seen, Stack<int>& S, int v){
    for(int i = 0; i < n; i++){
        if(adj[v][i] && !seen[i]){
            seen[i] = true;
            dfs(n, adj, seen, S, i);
        }
    }
    S.push(v);
}

void dfsinv(int n, int** adj, bool* seen, int v){
    for(int i = 0; i < n; i++){
        if(adj[v][i] && !seen[i]){
            seen[i] = true;
            dfsinv(n, adj, seen, i);
        }
    }
}

int main(int argc, char** argv){
    ifstream fin;
    ofstream fout;
    switch(argc){
        case 1:
            fin.open("input.txt");
            fout.open("output.txt");
            break;
        case 2:
            fin.open(argv[1]);
            fout.open("output.txt");
            break;
        default:
            fin.open(argv[1]);
            fout.open(argv[2]);
            break;
    }

    int N, M, Type;
    fin >> N >> M >> Type;
    int** adj = new int*[N];
    bool* seen = new bool[N];
    Stack<int> V;
    for(int i = 0; i < N; i++){
        adj[i] = new int[N];
        seen[i] = false;
        for(int j = 0; j < N; j++){
            adj[i][j] = 0;
        }
    }
    for(int i = 0; i < M; i++){
        int x, y, k;
        switch(Type){
            case 1:
                fin >> x >> y;
                adj[--x][--y] = 1;
                break;
            case 2:
                fin >> x >> y >> k;
                adj[--x][--y] = k;
                break;
            case 3:
                fin >> x >> y;
                adj[--x][--y] = 1;
                adj[y][x] = 1;
                break;
            default:
                fin >> x >> y >> k;
                adj[--x][--y] = k;
                adj[y][x] = k;
                break;
        }
    }
    fin.close();
    for(int i = 0; i < N; i++){
        if(!seen[i]){
            seen[i] = true;
            dfs(N, adj, seen, V, i);
        }
    }
    if(Type < 3){
        for(int i = 0; i < N; i++){
            for(int j = i; j < N; j++){
                swap(adj[j][i], adj[i][j]);
            }
        }
    }
    for(int i = 0; i < N; i++){
        seen[i] = false;
    }
    int x = 0;
    while(!V.empty()){
        int buf = V.pop();
        if(!seen[buf]){
            seen[buf] = true;
            dfsinv(N, adj, seen, buf);
            x++;
        }
    }
    fout << x;
}