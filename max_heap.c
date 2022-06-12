#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define HEAP_SIZE 100000000
#define MAX 100000

int heap[HEAP_SIZE];
int heapCount = 0;

void swap(int* a, int* b);
void insert_heap(int x);
int pop();

int main()
{
    int heap_num = 0;
    printf("정렬할 원소의 개수: ");
    scanf("%d", &heap_num);
    heap_num *= 4;
    char* item[MAX] = { 0, };
    char save_heap[MAX] = { 0, };
    int i = 0;

    FILE* fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("파일이 열리지 않음");
        return 0;
    }
    fread(save_heap, 1, heap_num, fp);

    char* ptr = strtok(save_heap, ",");
    while (ptr != NULL) {
        item[i] = ptr;
        i++;
        ptr = strtok(NULL, ",");

    }
    int k = 0;
    for (int j = 0; j < MAX; j++) {

        int item1 = 0;
        if (item[j] == 0)
        {
            break;
        }
        item1 = atoi(item[j]);
        insert_heap(item1);
        item1 = 0;
        k++;
    }

    printf("Heap : ");
    for (int i = 0; i < k; i++)
    {
        printf("%d ", pop());
    }
    return 0;
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insert_heap(int x)
{
    heap[++heapCount] = x;

    int child = heapCount;
    int parent = child / 2;

    while (child > 1 && heap[child] > heap[parent])
    {
        swap(&heap[child], &heap[parent]);
        child = parent;
        parent = child / 2;
    }

}

int pop()
{
    int ret = heap[1];
    swap(&heap[1], &heap[heapCount]);
    heapCount = heapCount - 1;

    int parent = 1;
    int child = parent * 2;

    if (child + 1 <= heapCount)
    {
        child = (heap[child] > heap[child + 1]) ? child : child + 1;
    }

    while (child <= heapCount && heap[child] > heap[parent])
    {
        swap(&heap[child], &heap[parent]);
        parent = child;
        child = parent * 2;

        if (child + 1 <= heapCount)
        {
            child = (heap[child] > heap[child + 1]) ? child : child + 1;
        }
    }

    return ret;
}
