#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int min(int n, int* dist, bool* tree){
    int min = INT_MAX, ind;
    for(int i = 0; i < n; i++){
        if(!tree[i] && dist[i] < min){
            min = dist[i];
            ind = i;
        }
    }
    return ind;
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
    bool* tree = new bool[N];
    int** adj = new int*[N];
    int* dist = new int[N];
    int* p = new int[N];
    for(int i = 0; i < N; i++){
        adj[i] = new int[N];
        tree[i] = false;
        dist[i] = INT_MAX;
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

    dist[0] = 0;
    p[0] = -1;
    for(int i = 0; i < N; i++){
        int u = min(N, dist, tree);
        tree[u] = true;
        for(int j = 0; j < N; j++){
            if (adj[u][j] && !tree[j] && adj[u][j] < dist[j]){
                p[j] = u;
                dist[j] = adj[u][j];
            }
        }
    }
    for(int i = 0; i < N; i++){
        if(!tree[i]){
            fout << -1;
            return 0;
        }
    }
    int S = 0;
    for(int i = 1; i < N; i++){
        S += adj[i][p[i]];
    }
    fout << S;
}