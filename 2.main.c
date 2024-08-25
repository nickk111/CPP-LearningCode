#include <stdio.h>
#include<stdlib.h>

typedef int E;

struct  List {
    E * array;
    int capacity;
    int size;
};

typedef struct List * ArrayList;

int initList (ArrayList list){
    list->capacity = 10;
    list->array = malloc(sizeof(E)*list ->capacity);
    if(list->array == NULL) return 0;
    list->size = 0;
    return 1;
}
    
int main() {
    struct List list;
    if(initList( &list)){

    }else{
        printf("顺序表初始化失败，无法启动！");
    }
}