#include <iostream>
using namespace std;

#include <pthread.h>
#include <cstdlib>
#include <ctime>

#define n 100   
#define K 100   
#define m 100   
long long A[n][K];
long long B[K][m];
long long C[n][m];

struct ThreadData {
    int row;
    int col;
};
void* multiplyOneElement(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int row = data->row;
    int col = data->col;

    long long sum = 0;
    for (int k = 0; k < K; k++) {
        sum = sum + A[row][k] * B[k][col];
    }
    C[row][col] = sum;
    delete data;
    return NULL;
}

int main() {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < K; j++) {
            A[i][j] = rand() % 10;
        }
    }
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < m; j++) {
            B[i][j] = rand() % 10;
        }
    }

    int totalThreads = n * m;
    pthread_t threads[n * m];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 256 * 1024);
    cout<<"Creating "<<totalThreads<<" threads,one for each element of C matrix "<<endl;

    int threadIndex = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ThreadData* data = new ThreadData;
            data->row = i;
            data->col = j;
            pthread_create(&threads[threadIndex], &attr, multiplyOneElement, data);
            threadIndex++;
        }
    }
    for (int t = 0; t < totalThreads; t++) {
        pthread_join(threads[t], NULL);
    }

    pthread_attr_destroy(&attr);
    cout<<"All threads finished."<<endl<<endl;
    int show = 5;
    cout<<"A (top-left "<<show<<"x"<<show<<" corner):"<<endl;
    for (int i = 0; i < show; i++) {
        for (int j = 0; j < show; j++) {
            cout << A[i][j] << "\t";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"B (top-left "<<show<<"x"<<show<<"corner):" << endl;
    for (int i = 0; i < show; i++) {
        for (int j = 0; j < show; j++) {
            cout<<B[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"C = A x B (top-left "<<show<<"x"<<show<<"corner):"<<endl;
    for (int i = 0; i < show; i++) {
        for (int j = 0; j < show; j++) {
            cout<<C[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;

    long long check = 0;
    for (int k = 0; k < K; k++) {
        check = check + A[0][k] * B[k][0];
    }
    cout<<"Check C[0][0]: thread result = "<<C[0][0]<<" normal calculation = "<<check;

    if (C[0][0] == check) {
        cout<<"-> MATCH"<<endl;
    } else {
        cout<<"-> MISMATCH"<<endl;
    }
    return 0;
}
