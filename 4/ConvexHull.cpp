#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// #include "getCPUTime.c"
#include "StackClass.cpp"

#define PI 3.14159265

using namespace std;

typedef numeric_limits<double> dbl;

struct point{
    double x=0, y=0;
    int n=0;
};

double getTime() {
  LARGE_INTEGER freq, val;
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&val);
  return (double)val.QuadPart / (double)freq.QuadPart;
}

int min(int n, point* arr){
    point m = arr[0];
    int ind = 0;
    for(int i = 1; i < n; i++){
        if((m.y > arr[i].y) || (m.y == arr[i].y && m.x > arr[i].x)){
            m = arr[i];
            ind = i;
        }
    }
    return ind;
}

double Abs(double x){
    return x < 0 ? -1 * x : x;
}

double angle(point x, point y){
    double a = Abs(x.x - y.x), b = Abs(x.y - y.y);
    if(a == 0){
        if(y.y < x.y)
            return 3 * PI / 2;
        return PI/2;
    }
    if(b == 0){
        if(y.x < x.x)
            return PI;
        return 0;
    }
    if(y.y > x.y){
        if(y.x > x.x)
            return atan(b/a);
        return PI - atan(b/a);
    }
    return y.x < x.x ? PI + atan(b/a) : 2 * PI - atan(b/a);
}

double dist(point x, point y){
    double a = x.x - y.x, b = x.y - y.y;
    return sqrt(a * a + b * b);
}

void sortpoints(int n, point* arr){
    for(int i = 1; i < n - 2; i++){
        for(int j = 2; j < n - i + 1; j++){
            if(angle(arr[0], arr[j - 1]) > angle(arr[0], arr[j]) || (angle(arr[0], arr[j - 1]) == angle(arr[0], arr[j]) && dist(arr[0], arr[j-1]) > dist(arr[0], arr[j]))){
                swap(arr[j-1], arr[j]);
            }
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

    int n;
    fin >> n;
    Stack<point> S;
    point* Q = new point[n];
    for(int i = 0; i < n; i++){
        fin >> Q[i].x >> Q[i].y;
        Q[i].n = i + 1;
    }
    fin.close();
    double startTime, endTime;
    startTime = getTime();
    int b = min(n, Q);
    swap(Q[0], Q[b]);
    sortpoints(n, Q);
    
    // for(int i = 0; i < n; i++){
    //     cout << Q[i].x << " " << Q[i].y << endl;
    // }

    S.push(Q[0]);
    S.push(Q[1]);
    for(int i = 2; i < n; i++){
        while((S.top().x - S.NextToTop().x)*(Q[i].y - S.top().y) - (S.top().y - S.NextToTop().y)*(Q[i].x - S.top().x) < 0){
            S.pop();
        }
        S.push(Q[i]);
    }
    endTime = getTime();
    fout.precision(dbl::max_digits10);
    fout << pow(10, 9) * (endTime - startTime) << endl;
    while(!S.empty()){
        fout << S.pop().n << " ";
    }
}