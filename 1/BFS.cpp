#include <iostream>
#include <fstream>
#include <queue>
#include <climits>

using namespace std;

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
    int* dist = new int[N];
    int** adj = new int*[N];
    queue<int> Q;
    for(int i = 0; i < N; i++){
        adj[i] = new int[N];
        seen[i] = false;
        dist[i] = SHRT_MAX;
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
    dist[s] = 0;
    Q.push(s);
    int P;
    while(!Q.empty()){
        P = Q.front();
        Q.pop();
        if(P == f) break;
        if(!seen[P]){
            seen[P] = 1;
            for(int j = 0; j < N; j++){
                if(adj[P][j] == 1 && !seen[j]){
                    Q.push(j);
                    if(dist[j] > dist[P] + 1){
                        dist[j] = dist[P] + 1;
                    }
                }
            }
        }
    }
    if(dist[f] == SHRT_MAX){
        fout << -1 << endl;
    }
    else{
        fout << dist[f] << endl;
    }
}