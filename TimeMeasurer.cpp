#include <iostream>
#include <limits>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;

typedef numeric_limits<double> dbl;

double getTime() {
  LARGE_INTEGER freq, val;
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&val);
  return (double)val.QuadPart / (double)freq.QuadPart;
}

int main(){
    cout.precision(dbl::max_digits10);
    double start = getTime();
    Sleep(1000);
    cout << 1000000000 * (getTime() - start);
}