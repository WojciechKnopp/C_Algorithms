#include <iostream>
#include <cstdlib>
#include <fstream>
#define MLD 1000000000.0


using namespace std;


void przygotuj_tablice(int *C, string *A, int size, int litera){
    for (int i = 0; i<28; i++) //zeruje tablice
        C[i]=0;

    for(int i=1; i<size;i++){ //zlicza wystąpienia
        if(litera>=A[i].length())
            C[0]++;
        else
            C[A[i][litera]-96]++;        
    }

    for(int i=1; i<28;i++) //sumuje wystąpienia
        C[i]+=C[i-1];
}

int policz_dlugosc(string *A, int size){
    int max = 0;
    for(int i = 1; i<size;i++)
        if(A[i].length()>max)
            max=A[i].length();
    
    return max;
}

void countsort(string *A, int *numbers, int size, int max){
    
    string *B = new string[size];
    int *numbers2 = new int[size];

    int C[27]; //0 ,1a,2b,3c,4d,5e,6f,7g,8h,9i,10j,11k,12l,13m,14n,15o,16p,17q,18r,19w,20t,21u,22v,23w,24x,25y,26z
   
    for(int k=max-1;k>=0;k--){ //sortwanie wyrazów o różnej długości
        przygotuj_tablice(C,A,size,k);

        for(int j=size-1; j>0; j--){ //sortowanie po literze
            if(k>=A[j].length()){
                B[C[0]]=A[j];
                numbers2[C[0]]=numbers[j];
                C[0]--;
            }
            else{
                  //A[j][k]-96 - litera po której się sortuje zamieniona na odpowiadający jej indeks w tabeli C
                B[C[A[j][k]-96]]=A[j];
                numbers2[C[A[j][k]-96]]=numbers[j];
                C[A[j][k]-96]--;
            }
        }

        for(int j=1; j<size; j++){ //przepisanie z B do A
            A[j]=B[j];
            numbers[j]=numbers2[j];
        }
    }
}

void swapS(string* a, string* b){
    string temp = *a;
    *a = *b;
    *b = temp;
}

void swapI(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(string* A, int *numbers, int p, int r){
    string x = A[r];
    int i = p - 1;
    for(int j = p; j <= r; j++){
        if(A[j] <= x){
            i++;
            swapS(&A[i], &A[j]);
            swapI(&numbers[i], &numbers[j]);
        }
    }
    if(i < r)
        return i;
    else
        return i - 1;
}

void quicksort(string* A, int *numbers, int p, int r){
    if(p < r){
        int q = partition(A, numbers, p, r);
        quicksort(A, numbers, p, q);
        quicksort(A, numbers, q + 1, r);
    }
}

int main(){ 

    ifstream data;
    data.open("nazwiskaASCII.txt");
    
    if(!data.good()){
        cout << "błąd pliku\n";
        return 0;
    }

    int size=1;
    string *A;
    string napis;
    int *numbers;
    A = (string*) malloc(sizeof(string));
    numbers = (int*) malloc(sizeof(int));

    //Pobieranie danych z pliku do tablic
    for(; !data.eof(); size++){
        if(size%2){
            numbers = (int*)realloc(numbers,(size/2+2)*sizeof(int));
            data >> numbers[size/2+1];
        }
        else{
            A = (string*)realloc(A,(size/2+2)*sizeof(string));     
            data >> napis;
            A[size/2] = napis;
        }
    }
    size = size/2+1; //faktyczny rozmiar tablic
    
    for(int i=1;i<size;i++){ //zmienianie wielkiej litery na małą na początku nazwiska
        A[i][0]=A[i][0]+32;
    }

    int choice;
    cout << "Wybierz metodę sortowania:\n1. Pozycyjne\n2. Quicksort\n";    
    cin >> choice;
    switch(choice){
        case 1:{
            ofstream results_count("wynik_count.txt");
            struct timespec tp0,tp1;
            double czas;

            int max = policz_dlugosc(A, size); //znajduje długość najdłuższego napisu

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
            countsort(A, numbers, size, max);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
            czas = (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
            printf("COUNTSORT   \tCzas:%lf\n",czas);

            for(int i=1;i<size;i++){ //zmienianie małej litery na wielką na początku nazwiska
                A[i][0]=A[i][0]-32;
            }
    
            for(int i=1;i<size;i++){ //zapisanie do plików
                results_count << numbers[i] << " " << A[i] << endl;
            }
            results_count.close();
            break;
        }
        case 2:{
            ofstream results_quick("wynik_quick.txt");

            struct timespec tp0,tp1;
            double czas;

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
            quicksort(A, numbers, 1, size-1);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
            czas = (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
            printf("QUICKSORT   \tCzas:%lf\n",czas);

            for(int i=1;i<size;i++){ //zmienianie małej litery na wielką na początku nazwiska
                A[i][0]=A[i][0]-32;
            }
            for(int i=1;i<size;i++){ //zapisanie do plików
                results_quick << numbers[i] << " " << A[i] << endl;
            }
            results_quick.close();
            break;
        }
        default:
            cout<<"Nie ma takiego sortowania\n"; 
    }

    data.close();
    free(A);
    free(numbers);
    return 0;
}
