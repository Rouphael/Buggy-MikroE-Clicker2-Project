/* 
 * File:   CB.h
 * Author: Rafael
 */

#ifndef CB_H
#define	CB_H

#define CIRC_BBUF_DEF(x,y)                \
    uint8_t x##_data_space[y];            \
    circ_bbuf_t x = {                     \
        .buffer = x##_data_space,         \
        .readIndex = 0,                   \
        .writeIndex = 0,                  \
        .dataCounter = 0,                 \
        .buffersize = y                   \
    }
#define CIRC_BBUF_int_DEF(x,y)                \
    int x##_data_space[y];            \
    circ_bbuf_int_t x = {                     \
        .buffer = x##_data_space,         \
        .readIndex = 0,                   \
        .writeIndex = 0,                  \
        .dataCounter = 0,                 \
        .buffersize = y                   \
    }

typedef struct {
    uint8_t *buffer;
    int readIndex;
    int writeIndex;
    int dataCounter;
    int buffersize;
} circ_bbuf_t;
typedef struct {
    int *buffer;
    int readIndex;
    int writeIndex;
    int dataCounter;
    int buffersize;
} circ_bbuf_int_t;

void circ_bbuf_push(circ_bbuf_t *cb, uint8_t data);
void circ_bbuf_pop(circ_bbuf_t *cb, uint8_t *data);

void circ_bbuf_int_push(circ_bbuf_int_t *cb, int data);
void circ_bbuf_int_pop(circ_bbuf_int_t *cb, int *data);
#endif	/* CB_H */

//_int