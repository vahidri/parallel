#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#define epsilon 1e-15

using namespace std;

void f(int* inp)
{
    for(int i=0;i<5;i++)
        inp[i]=i;
}

int main()
{
    int sum=0,prod=1;
#pragma omp parallel for reduction(+:sum) reduction(*:prod)
    for(int it=1;it<=10;it++)
    {
        prod*=it;
        sum+=it;
    }
    cout<<sum<<endl<<prod<<endl;
    return 0;

    double area, pi, x;
    int i, n=1000;
    area = 0.0;
//#pragma omp parallel for private(x)
#pragma omp parallel for private(x) reduction(+:area)
    for (i = 0; i < n; i++) {
           x = (i+0.5)/n;
//#pragma omp critical
       area += 4.0/(1.0 + x*x);
    }
    pi = area / n;
    cout<<pi<<endl;
    return 0;
}

