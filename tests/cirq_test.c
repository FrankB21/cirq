#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cirq.h"

#define FAIL_IF_MSG(exp, msg)         \
    if (exp)                          \
    {                                 \
        fprintf(stderr, "%s\n", msg); \
        exit(EXIT_FAILURE);           \
    }

int main(void)
{
    cirq_queue_t *q = cirq_create(3);
    FAIL_IF_MSG(q == NULL, "cirq_create should return not null");

    int i = 0;
    int j = 1;
    int k = 2;
    int l = 3;

    FAIL_IF_MSG(cirq_count(q) != 0, "cirq_count() expected 0");
    FAIL_IF_MSG(cirq_isempty(q) == false, "cirq_isempty() expected true");

    FAIL_IF_MSG(cirq_enqueue(q, &i) == false, "cirq_enqueue expected true for i");
    FAIL_IF_MSG(cirq_enqueue(q, &j) == false, "cirq_enqueue expected true for j");
    FAIL_IF_MSG(cirq_count(q) != 2, "cirq_count() expected 2");
    FAIL_IF_MSG(cirq_isfull(q) == true, "cirq_isfull() expected false");
    FAIL_IF_MSG(cirq_isempty(q) == true, "cirq_isempty() expected false");
    FAIL_IF_MSG(cirq_enqueue(q, &k) == false, "cirq_enqueue expected true for k");
    FAIL_IF_MSG(cirq_isfull(q) == false, "cirq_isfull() expected true");
    FAIL_IF_MSG(cirq_count(q) != 3, "cirq_count() expected 3");
    FAIL_IF_MSG(cirq_enqueue(q, &l) == true, "cirq_enqueue expected false for l");

    FAIL_IF_MSG(*(int *)cirq_dequeue(q) != i, "cirq_dequeue expected i");
    FAIL_IF_MSG(*(int *)cirq_dequeue(q) != j, "cirq_dequeue expected j");
    FAIL_IF_MSG(*(int *)cirq_dequeue(q) != k, "cirq_dequeue expected k");
    FAIL_IF_MSG(cirq_isempty(q) == false, "cirq_isempty() expected true");
    FAIL_IF_MSG(cirq_dequeue(q) != NULL, "cirq_dequeue expected NULL");

    FAIL_IF_MSG(cirq_enqueue(q, &i) == false, "cirq_enqueue expected true for i");
    FAIL_IF_MSG(cirq_enqueue(q, &j) == false, "cirq_enqueue expected true for j");
    FAIL_IF_MSG(*(int *)cirq_dequeue(q) != i, "cirq_dequeue expected i");
    FAIL_IF_MSG(cirq_enqueue(q, &k) == false, "cirq_enqueue expected true for k");
    FAIL_IF_MSG(cirq_enqueue(q, &l) == false, "cirq_enqueue expected true for l");

    cirq_destroy(q);

    printf("All tests passed!");
    return 0;
}
