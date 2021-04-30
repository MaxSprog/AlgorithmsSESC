#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

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
    int** adj = new int*[N];
    for(int i = 0; i < N; i++){
        adj[i] = new int[N];
        seen[i] = false;
        for(int j = 0; j < N; j++){
            adj[i][j] = INT_MAX;
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
    adj[s][s] = 0;
    for(int j = 1; j < N; j++){
        for(int l = 0; l < N; l++){
            for(int k = 0; k < N; k++){
                if(adj[l][k] != INT_MAX){
                    if(adj[s][k] > adj[s][l] + adj[l][k] && adj[s][l] != INT_MAX){
                        adj[s][k] = adj[s][l] + adj[l][k];
                    }
                }
            }
        }
    }
    int p = adj[s][f];
    for(int l = 0; l < N; l++){
        for(int k = 0; k < N; k++){
            if(adj[l][k] != INT_MAX){
                if(adj[s][k] > adj[s][l] + adj[l][k] && adj[s][l] != INT_MAX){
                    adj[s][k] = adj[s][l] + adj[l][k];
                }
            }
        }
    }
    if(p > adj[s][f]) fout << -1;
    else if(adj[s][f] == INT_MAX) fout << 0;
    else fout << adj[s][f];
}