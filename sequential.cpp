/*
 * heat dissipation in a square grid with hot centeral part
 * propagation is by average of cell's neighborhood
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <omp.h>
using namespace std;

#define SIZE 1000 // size x size
#define MAX_ITER 500
#define HOT 10
#define NORM 3

float *board, *tmp;

void init()
{
    srand(time(0)); 
    board = (float*)calloc(SIZE * SIZE, sizeof(float));
    tmp = (float*)calloc(SIZE * SIZE, sizeof(float));
    for(int i = 0; i<SIZE; i++) 
        for(int j = 0; j<SIZE; j++) 
        {
            tmp[i*SIZE + j] = 0;
            board[i*SIZE + j] = (float)(rand()% (NORM*10)) / 10.0;
            if ( (i < 6*SIZE/10 and i > 4*SIZE/10) and (j < 6*SIZE/10 and j > 4*SIZE/10) ) ///center 20%x20%
                board[i*SIZE + j] = HOT;
        }
}

void update()
{
    for(int i = 1; i<SIZE-1; i++) 
        for(int j = 1; j<SIZE-1; j++) 
        {
            int here=i*SIZE+j;
            tmp[here] = (board[here-1]+board[here]+board[here+1] + board[here-1-SIZE]+board[here-SIZE]+board[here+1-SIZE] + board[here-1+SIZE]+board[here+SIZE]+board[here+1+SIZE] ) / 9.0;
        }

    int h=0;
    tmp[h] = (board[h] + board[h+SIZE] + board[h+1] + board[h+1+SIZE])/4.0;
    h=SIZE-1;
    tmp[h] = (board[h] + board[h+SIZE] + board[h-1] + board[h-1+SIZE])/4.0;
    h=SIZE*SIZE-SIZE;
    tmp[h] = (board[h] + board[h-SIZE] + board[h+1] + board[h+1-SIZE])/4.0;
    h=SIZE*SIZE-1;
    tmp[h] = (board[h] + board[h-SIZE] + board[h-1] + board[h-1+SIZE])/4.0;

    for(int i=1; i<SIZE-1; i++)
    {
        tmp[i]= ( board[i-1]+board[i]+board[i+1] + board[i-1+SIZE]+board[i+SIZE]+board[i+1+SIZE] ) /6.0;
        int here=i+SIZE*SIZE-SIZE;
        tmp[here]= ( board[here-1]+board[here]+board[here+1] + board[here-1-SIZE]+board[here-SIZE]+board[here+1-SIZE] ) /6.0;
    }

    for(int i=1; i<SIZE-1; i++)
    {
        int here=i*SIZE;
        tmp[here] = ( board[here-SIZE]+board[here]+board[here+SIZE] + board[1+here-SIZE]+board[1+here]+board[1+here+SIZE] ) /6.0;
        here = i*SIZE - 1;
        tmp[here] = ( board[here-SIZE]+board[here]+board[here+SIZE] + board[here-SIZE-1]+board[here-1]+board[here+SIZE-1] ) /6.0;
    }
}

void print_matrix(string name, int M, int N, float* A)
{
    cout << name << ": \n";
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
            //cout << A[i*N + j] << " " ;
            printf("% .4f ", A[i*N + j]);
        cout << endl;
    }
    cout << endl;
}

int main()
{
    init();
    for (int i=0; i<MAX_ITER; i++)
        update();
    return 0;
}

