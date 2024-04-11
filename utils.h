#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

typedef float Price;
typedef char Label[32];


typedef struct lookupTablePrice{
    Price price;
    int id;
    Label label;
}lookupTablePrice;

void swap(Price* a, Price* b);

int partition(Price arr[], int low, int high);

void quickSort(Price arr[], int low, int high);


typedef char Recipe[5][32];

typedef char Ingredients[10][32];

typedef struct Pizza{
    Label name;
    int id;
    Price price;
    Recipe rec;
}Pizza;

void initRecipe();

void initName(char name[], int id);

void printIngredients(int id, int connfd);

bool containCheese(int id);

bool containTomato(int id);

void setPrice(Price price, int id);

void allTomato(int connfd);

void allCheese(int connfd);

void order(int connfd);

void su();
