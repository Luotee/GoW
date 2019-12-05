#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
double knn(uint_fast8_t g, uint_fast8_t b, uint_fast8_t r) 
{
    int min_distance = 1000;
    double distance;
    double x=1/3.0;
    distance = pow( (g*g+b*b+r*r) ,x);
    return distance;
}
int main()
{
    printf("%g\n",knn(3,4,5));
}