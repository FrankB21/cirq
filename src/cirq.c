// MIT License
// 
// Copyright (c) 2021 FrankB21
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdlib.h>

#include "cirq.h"

typedef struct cirq_queue
{
    size_t head;
    size_t tail;
    size_t max_size;
    void **data;
} cirq_queue_t;

cirq_queue_t *cirq_create(size_t max_size)
{
    cirq_queue_t *q = malloc(sizeof(cirq_queue_t));

    if (q == NULL) return NULL;

    q->head     = 0;
    q->tail     = 0;
    q->max_size = max_size;
    q->data     = calloc(max_size, sizeof(void *));

    if (q->data == NULL)
    {
        free(q);
        return NULL;
    }

    return q;
}

bool cirq_enqueue(cirq_queue_t *q, void *element)
{
    // Check if spot is occupied (queue full)
    if (q->data[q->tail] != NULL) return false;

    q->data[q->tail++] = element;
    if (q->tail >= q->max_size) q->tail = 0;
    return true;
}

void *cirq_dequeue(cirq_queue_t *q)
{
    // Check if queue is empty
    if (q->head == q->tail && q->data[q->head] == NULL) return NULL;

    void *tmp = q->data[q->head];

    q->data[q->head++] = NULL;
    if (q->head >= q->max_size) q->head = 0;
    return tmp;
}

void cirq_destroy(cirq_queue_t *q)
{
    free(q->data);
    free(q);
}