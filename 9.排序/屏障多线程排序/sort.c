#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMS 15
#define TURN 3
#define N (NUMS/TURN)

pthread_barrier_t the_barrier;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int nums[NUMS];

void adjust(int i, int n, int turn)
{
    int parent = i;
    int child;
    int temp = nums[i+turn*N];

    while(parent*2+1 <= n-1){
        child = parent*2+1;
        if(child != n-1 && nums[child+turn*N] < nums[child+turn*N+1])
            child++;
        if(temp >= nums[child+turn*N])
            break;
        nums[parent+turn*N] = nums[child+turn*N];
        parent = child;
    }
    nums[parent+turn*N] = temp;
}

void *heap_sort(void *args)
{
    int turn = (int)args;

    for(int i = (N-2)/2; i >= 0; i--)
        adjust(i, N, turn);

    pthread_mutex_lock(&lock);
    printf("in thread%d before sort : ", turn);
    for(int i = 0; i < N; i++)
        printf("%d ", nums[i+turn*N]);
    printf("\n");
    pthread_mutex_unlock(&lock);

    for(int j = N-1; j > 0; j--){
        int t = nums[0+turn*N];
        nums[0+turn*N] = nums[j+turn*N];
        nums[j+turn*N] = t;
        adjust(0, j, turn);
    }

    pthread_mutex_lock(&lock);
    printf("in thread%d after  sort : ", turn);
    for(int i = 0; i < N; i++)
        printf("%d ", nums[i+turn*N]);
    printf("\n");
    pthread_mutex_unlock(&lock);

    pthread_barrier_wait(&the_barrier);

}

void merge(int start1, int start2, int end)
{
    int *a = malloc((end-start1+1)*sizeof(int));
    int k = 0;
    int i = start1;
    int j = start2;

    while(i <= start2-1 && j <= end){
        if(nums[i] <= nums[j]){
            a[k] = nums[i];
            k++;
            i++;
        }else{
            a[k] = nums[j];
            k++;
            j++;
        }
    }

    while(i <= start2-1){
        a[k] = nums[i];
        k++;
        i++;
    }
    while(j <= end){
        a[k] = nums[j];
        k++;
        j++;
    }

    for(i = start1, k = 0; i <= end; i++, k++)
        nums[i] = a[k];

}

int main()
{
    pthread_barrier_init(&the_barrier, NULL, TURN+1);

    srand(getpid());
    printf("before sort : ");
    for(int i = 0; i < NUMS; i++){
        nums[i] = rand()%100 +1; //生成1到100之间的随机数
        printf("%d ", nums[i]);
    }
    printf("\n");

    pthread_t tid[TURN];
    for(int i = 0; i < TURN; i++)
        pthread_create(&tid[i], NULL, heap_sort, (void*)i);

    pthread_barrier_wait(&the_barrier);

    int gap = NUMS/TURN;
    for( ; gap < NUMS; gap *= 2){
        int i;
        for(i = 0; i + gap*2 - 1 < NUMS; i += gap*2)
            merge(i, i + gap, i+ gap*2 -1);
        if(i + gap < NUMS)
            merge(i, i + gap, NUMS-1);
    }

    printf("after sort : ");
    for(int i = 0; i < NUMS; i++)
        printf("%d ", nums[i]);
    printf("\n");

    pthread_mutex_destroy(&lock);
    pthread_barrier_destroy(&the_barrier);
}