#include <stdio.h>
#include <stdlib.h>
#include "logic.h"
#include "list.h"
#include "interface.h"
#include "signals.h"

struct list {
    int liczba[3];
    struct list *prev;
    struct list *next;
};

struct list *head, *tail;

void inicjuj_liste(){
    head = NULL;
    tail = NULL;
}

struct list *rezerwuj_pamiec(void){
    return (struct list *)malloc(sizeof(struct list));
}

void dodaj_na_koniec(int liczba, int x, int y){
    struct list *helper;

    if (tail == NULL){
        head = tail = rezerwuj_pamiec();
        head->prev = NULL;
        head->next = NULL;
    }
    else{
        helper = tail;
	tail = rezerwuj_pamiec();
	tail->next = NULL;
	tail->prev = helper;
	helper->next=tail;
    }
    tail->liczba[0] = liczba;
    tail->liczba[1] = x;
    tail->liczba[2] = y;
}

int usun_z_konca(){
    struct list *helper;
    if (tail == NULL){
    	return 0;
    }
    else if(tail->prev == NULL){
        free(tail);
        tail = NULL;
    }
    else{
        helper = tail;
        tail -> prev -> next = NULL;
        tail = tail -> prev;
        free(helper);
    }

    return 0;
}

void usun_liste(){
    struct list *helper;
    while(head != NULL){
        helper = head;
        head = head -> next;
        free(helper);
    }
}