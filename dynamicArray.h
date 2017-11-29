//
// Created by diamondrubix on 11/17/17.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

template <class t> class dynamicArray{
private:
    int size;//size of the array
    int leng;//amount of elements in the array
    int end;//location of the last element in the array (prob replace with leng?)
    int growth;
    t* arr;

    void init(){
        size = 10;
        leng = -1; //needs to be 0 for the first add
        end = 0;
        growth = 2;
        //t* arr;
        arr = (t *) malloc ( size * sizeof(t) );
    }

public:
    dynamicArray(){
        init();
    }
    dynamicArray(int startSize){
        init();
        size = startSize;
    }

    t add(t a){
        if(leng==size){
            t *temp;
            size = size + growth;
            temp = (t *) malloc ( size * sizeof(t) );
            //temp[size];
            int i;
            for ( i = 0 ; i < leng ; i++)
                temp[i] = arr[i];
            leng = i++;
            free (arr);
            arr = temp;
        }
        leng++;
        arr[leng]=a;
    }

    void pop(){
        leng--;
    }

    void reset(){
        free(arr);
    }

    int isEmpty(){
        if(leng <0){
            return 1;
        }
        return 0;
    }

    t top(){
        return arr[leng];
    }

    //will return the amount of elements in the array
    int length(){
        return leng;
    }

    t get(int i){
        return arr[i];
    }


};