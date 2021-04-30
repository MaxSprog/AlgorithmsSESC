#include <iostream>
#include <fstream>

using namespace std;

bool dfs(int n, int** adj, bool* seen, int v, int f){
    if(adj[v][f]) return true;
    for(int i = 0; i < n; i++){
        if(adj[v][i] && !seen[i]){
            seen[i] = true;
            if(dfs(n, adj, seen, i, f)) return true;
        }
    }
    return false;
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

    int N, M, Type, s, f;
    fin >> s >> f;
    s--; f--;
    fin >> N >> M >> Type;
    bool* seen = new bool[N];
    int** adj = new int*[N];
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
    seen[s] = true;
    fout << dfs(N, adj, seen, s, f);
}