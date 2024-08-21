/* 
 * File:   CB.c
 * Author: Rafael
 */

#include "xc.h"
#include "CB.h"
#include <stdio.h>
#include <string.h>

void circ_bbuf_push(circ_bbuf_t *cb, uint8_t data){
    if(cb->dataCounter <= cb->buffersize){
        cb->buffer[cb->writeIndex] = data;
        cb->writeIndex = (cb->writeIndex + 1) % cb->buffersize;
        cb->dataCounter++;
    }
    /*else{
        cb->buffer[cb->writeIndex] = data;
        cb->writeIndex = (cb->writeIndex + 1) % cb->buffersize;
        cb->readIndex = (cb->readIndex + 1) % cb->buffersize;
    }*/
}
void circ_bbuf_pop(circ_bbuf_t *cb, uint8_t *data){
    if(cb->dataCounter){
        *data = cb->buffer[cb->readIndex];
        cb->readIndex = (cb->readIndex + 1) % cb->buffersize;
        cb->dataCounter--;
    }
}

void circ_bbuf_int_push(circ_bbuf_int_t *cb, int data){
    if(cb->dataCounter <= cb->buffersize){
        cb->buffer[cb->writeIndex] = data;
        cb->writeIndex = (cb->writeIndex + 1) % cb->buffersize;
        cb->dataCounter++;
    }
    /*else{
        cb->buffer[cb->writeIndex] = data;
        cb->writeIndex = (cb->writeIndex + 1) % cb->buffersize;
        cb->readIndex = (cb->readIndex + 1) % cb->buffersize;
    }*/
}
void circ_bbuf_int_pop(circ_bbuf_int_t *cb, int *data){
    if(cb->dataCounter){
        *data = cb->buffer[cb->readIndex];
        cb->readIndex = (cb->readIndex + 1) % cb->buffersize;
        cb->dataCounter--;
    }
}