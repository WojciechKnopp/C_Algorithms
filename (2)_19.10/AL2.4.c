#include <stdio.h>
#include <stdbool.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void zapisz_tablice(int* A, int n, FILE* plik){
    for(int i = 1; i < n+1; i++)
        fprintf(plik, "%d\n", A[i]);
}
/*
REKURENCYJNIE
void heapify(int* A, int i, int heapsize){
    int l = 2*i;
    int r = 2*i+1;
    int largest;
    if(l <= heapsize && A[l] > A[i])
        largest = l;
    else
        largest = i;
    if( r <= heapsize && A[r] > A[largest])
        largest = r;
    if( largest != i ){
        swap(&A[i], &A[largest]);
        heapify(A, largest, heapsize);
    }
}
*/
//ITERACYJNIE
void heapify(int* A, int i, int heapsize){
    int r, l, largest;
    bool loop = true;
    while(loop){
        loop = false;
        l = 2*i;
        r = 2*i+1;
        if(l <= heapsize && A[l] > A[i])
            largest = l;
        else
            largest = i;
        if( r <= heapsize && A[r] > A[largest])
            largest = r;
        if( largest != i ){
            swap(&A[i], &A[largest]);
            loop = true;
            i = largest;
        }
    }
}
void buildHeap(int* A, int length, int* heapsize){
    *heapsize = length;
    for(int i = length/2; i >= 1; i--)
        heapify(A, i, *heapsize);
}

void heapSort(int* A, int length, int* heapsize){
    buildHeap(A, length, heapsize);
    *heapsize = length;
    for(int i = length; i >= 2; i--){
        swap(&A[1], &A[*heapsize]);
        (*heapsize)--;
        heapify(A, 1, *heapsize);
    }
}

int main(){
    int A[51];
    int heapsize=1;
    FILE * file;
    FILE * zapis;
    file = fopen("table.txt","r");
    zapis = fopen("wyjscie.txt", "w");
    
    while(fscanf(file, "%d" ,&A[heapsize]) != EOF)
        heapsize++;
    heapsize--;
    int length = heapsize;

    heapSort(A, length, &heapsize);
    zapisz_tablice(A,length, zapis);

    fclose(file);
    return 0;
}