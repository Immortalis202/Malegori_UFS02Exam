/* 
*al client che invii i seguenti possibile comandi TESTUALI:
*Un server TCP ha una lista di pizze che puo' inviare
*- "with_tomato"
*- "with_cheese"
*- "sorted_by_price"
*risposta puo' essere testuale, JSON
*Si scrivano le opportune struct C a supporto (classe Pizza) La
*Via "nc" / telnet
*(Ogni pizza avrà una lista ingredienti) 

*/
#include "utils.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>


typedef float Price;


lookupTablePrice tab[20];

Price prices[20];

void swap(Price* a, Price* b) { 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

// Partition function 
int partition(Price arr[], int low, int high) { 

    // initialize pivot to be the first element 
    int pivot = arr[low]; 
    int i = low; 
    int j = high; 

    while (i < j) { 

        // condition 1: find the first element greater than 
        // the pivot (from starting) 
        while (arr[i] <= pivot && i <= high - 1) { 
            i++; 
        } 

        // condition 2: find the first element smaller than 
        // the pivot (from last) 
        while (arr[j] > pivot && j >= low + 1) { 
            j--; 
        } 
        if (i < j) { 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[low], &arr[j]); 
    return j; 
} 

// QuickSort function 
void quickSort(Price arr[], int low, int high) { 
    if (low < high) { 

        // call Partition function to find Partition Index 
        int partitionIndex = partition(arr, low, high); 

        // Recursively call quickSort() for left and right 
        // half based on partition Index 
        quickSort(arr, low, partitionIndex - 1); 
        quickSort(arr, partitionIndex + 1, high); 
    } 
} 


typedef char Label[32];
typedef char Recipe[5][32];

typedef char Ingredients[10][32];

Ingredients ing = {"tomato", "cheese", "pepperoni", "tuna", "mushrooms", "onion", "olive", "sausage", "pineapple", "vegetables" };

int seed;

Pizza listino[20];
int latestID = 0;


void initRecipe(){
    for(int j = 0; j<20;j++)
    {
        for(int i = 0; i < 5; i++){
            strcpy(listino[j].rec[i],ing[rand()%10]);
        }
    }
}

void initName(char name[], int id){
    strcpy(listino[id].name,name);
}

void printIngredients(int id, int connfd){
    char toSend[256];
    sprintf(toSend,"Ingredients: \n");
    write(connfd, toSend,15);
    for(int i = 0; i < 5; i++){
        bzero(toSend,256);
        sprintf(toSend,"\t%s\n\n\n",listino[id].rec[i]);
        write(connfd, toSend, sizeof(toSend));
    }
}

bool containCheese(int id){
    for(int i = 0; i < 10; i++){
        if(strcasecmp(listino[id].rec[i],"cheese") == 0){
            return true;
        }
    }
    return false;
}

bool containTomato(int id){
    for(int i = 0; i < 10; i++){
        if(strcasecmp(listino[id].rec[i],"tomato") == 0){
            return true;
        }
    }
    return false;
}

void setPrice(Price price, int id){
    listino[id].price = price;
    tab[latestID].price = price;
    strcpy(tab[latestID].label,listino[id].name);
    tab[latestID].id = id;
    prices[latestID] = id;

    latestID++;
}


void allTomato(int connfd){
    char print[256];
    sprintf(print,"The following Pizzas contain tomato: \n");
    write(connfd, print, 39);
    for(int i = 0; i < 20; i++){
        if(containTomato(i) == true){
            // printf("true");
            bzero(print, 256);
            sprintf(print,"Name:\t%s \nPrice:\t%lf\n\n",listino[i].name,listino[i].price);

            // printf("Name:\t%s \nPrice:\t%lf\n",listino[i].name,listino[i].price);

            write(connfd, print,256);
            printIngredients(i,connfd);
        }
    }
}



void allCheese(int connfd){
    char print[256];
    sprintf(print,"The following Pizzas contain tomato: \n");
    write(connfd, print, 39);
    for(int i = 0; i < 20; i++){
        if(containCheese(i) == true){
            // printf("true");
            bzero(print, 256);
            sprintf(print,"Name:\t%s \nPrice:\t%lf\n\n",listino[i].name,listino[i].price);

            // printf("Name:\t%s \nPrice:\t%lf\n",listino[i].name,listino[i].price);

            write(connfd, print,256);
            printIngredients(i,connfd);
        }
    }
}

void order(int connfd){
    char toSend[256];
    quickSort(prices, 0, 20);
    for(int i = 0; i < 20; i++){
        bzero(toSend,256);
        for(int j = 0; j < 20; j++){
            if (prices[i] == listino[j].price){
                bzero(toSend,256);
                sprintf(toSend, "%s:  %lf\n\n",listino[j].name,listino[j].price);
                write(connfd, toSend, 256);
            }
        }
    }
}


void su(){
    initRecipe();
    initName("Margherita", 0);
    initName("Capricciosa", 1);
    initName("Napoli", 2);
    initName("Hawaii", 3);
    initName("Bismark", 4);
    initName("Verdure", 5);
    initName("Quattro stagioni", 6);
    initName("Quattro formaggi", 7);
    initName("Peperoni", 8);
    initName("Piccante", 9);
    initName("Romana", 10);
    initName("Siciliana", 11);
    initName("Monzese", 12);
    initName("Campagnola", 13);
    initName("Agricola", 14);
    initName("Milanese", 15);
    initName("Esagerata", 16);
    initName("Qualcosa", 17);
    initName("Blash", 18);
    initName("Nonsense", 19);
    for(int i = 0; i < 20; i++){
        setPrice((float)(rand()%17), i);
    }
    


    // containCheese(0);
    // listino[0].tomato = containTomato(0);
    // printf("Cheese: %s\n", listino[0].cheese ? "true" : "false");
    // printf("Tomato: %s\n", listino[0].tomato ? "true" : "false");





}