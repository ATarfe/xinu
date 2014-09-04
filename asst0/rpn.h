/*
 * Author: Peter Zhang (yz79), Eriya Terada (eterada)
 * CSCI P536 FA14 ASST0
 * Sept 2 2014
 * rpn.h file
 */

#ifndef __RPN_H__
#define __RPN_H__
#include "scanner.h"

#define SIZE 32

typedef struct{
    int type;
    void * value;
}Element;

Element new_element(int type, void * value);

/*
 //TODO: put implementation somewhere else
 Element new_element(int type, void * value){
 Element e;
 e.type=type;
 e.value=malloc(SIZE);
 memcpy(e.value,value,SIZE); //SIZE was size Sept 3 6:54pm - Eriya
 }
 
 void destroy_element(Element e){
 free(e.value);
 }
 */
#endif