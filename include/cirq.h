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

#ifndef CIRQ_H
#define CIRQ_H 1

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Opaque data type for a CirQ FIFO queue
 * 
 */
typedef struct cirq_queue cirq_queue_t;

/**
 * @brief Create a new FIFO queue with at most max_size elements
 * 
 * @param max_size The maximum number of elements the queue can hold
 * @return cirq_queue_t* The queue handle
 */
cirq_queue_t *cirq_create(size_t max_size);

/**
 * @brief Add an element to the tail of the queue q
 * 
 * @param q The queue to act upon
 * @param element The element to enqueue
 * @return true if the element was enqueued
 * @return false if the queue was full
 */
bool cirq_enqueue(cirq_queue_t *q, void *element);

/**
 * @brief Remove and return the element at the front of the queue q
 * 
 * @param q The queue to act upon
 * @return void* The element removed or NULL if the queue is empty
 */
void *cirq_dequeue(cirq_queue_t *q);

/**
 * @brief Destroy the queue q
 * @note This does NOT free the element pointers
 * @param q The queue to act upon
 */
void cirq_destroy(cirq_queue_t *q);

#endif// CIRQ_H