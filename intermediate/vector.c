// Simple vector implementation
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define ADEPT

#ifndef ADEPT
#include <stdio.h>
#endif

// Vector Struct
typedef struct Vector {
  uint16_t size;
  uint16_t count;
  uint8_t **data;
} Vector;

// Pointers to Vector and Data
#ifdef ADEPT
unsigned int *VECTOR_PTR = (unsigned int *)0xdeadbeef;
unsigned int N_VECTOR;
unsigned int *DATA_PTR = (unsigned int *)0xbabebabe;
unsigned int *VALUES_PTR = (unsigned int *)0xbabedead;
unsigned int N_VALUES;
#endif

// Create a new vector
//
// Exit:
// Will exit if either of the mallocs fail.
Vector *new_vector(void) {
#ifndef ADEPT
  Vector *vector = (Vector *)malloc(sizeof(Vector));

  if (vector == NULL) {
    exit(1);
  }

#else
  Vector *vector = (Vector *)VECTOR_PTR;
#endif

  // Set parameters
  vector->size = 32;
  vector->count = 0;

#ifndef ADEPT
  vector->data = (uint8_t **)malloc(sizeof(uint8_t *) * vector->size);

  if (vector->data == NULL) {
    exit(1);
  }
#else
  vector->data = (uint8_t **)DATA_PTR;
#endif

  for (size_t i = 0; i < vector->size; i++) {
#ifndef ADEPT
    vector->data[i] = (uint8_t *)malloc(sizeof(uint8_t));

    if (vector->data[i] == NULL) {
      exit(1);
    }
#else
    vector->data[i] = (uint8_t *)VALUES_PTR;
    N_VALUES++;
    VALUES_PTR += sizeof(uint8_t);
#endif
  }

  return vector;
}

// Add data to the vector.
//
// # Arguments
// * self -> the vector to store the coordinates on
// * x -> rows coordinates
//
// # Exit
// Will exit when expanding memory fails.
void vector_add(Vector *self, uint8_t x) {
  // If the size of the vector is equal to the current index count, then we need
  // to reallocate memory to make space for more data. Since reallocation is
  // expensive, we will always double the size of the vector.
  if (self->size == self->count) {
    self->size *= 2;
#ifndef ADEPT
    uint8_t **tmp_data = realloc(self->data, sizeof(uint8_t *) * self->size);

    if (tmp_data == NULL) {
      exit(1);
    }
#else
    uint8_t **tmp_data = self->data;
#endif

    for (size_t i = self->size / 2; i < self->size; i++) {
#ifndef ADEPT
      tmp_data[i] = (uint8_t *)malloc(sizeof(uint8_t));

      if (tmp_data[i] == NULL) {
        exit(1);
      }
#else
      tmp_data[i] = (uint8_t *)VALUES_PTR;
      N_VALUES++;
      VALUES_PTR += sizeof(uint8_t);
#endif
    }

    self->data = tmp_data;
  }

  // Store data
  self->data[self->count][0] = x;

  // Increment count
  self->count++;

  return;
}

// Get the values of vector at index. If the passed index is invalid a NULL
// pointer is returned.
//
// # Arguments
// * self -> the vector to get the index from
// * index -> index of the data
uint8_t *vector_get(Vector *self, uint8_t index) {
  if (index < self->count) {
    return self->data[index];
  }
  return NULL;
}

// Delete from the vector the coordinates at index.
//
// # Arguments
// * self -> the vector to delete the index from
// * index -> index to delete from
void vector_delete(Vector *self, uint16_t index) {
  if (index >= self->count) {
    return;
  }

  uint8_t *tmp = self->data[index];
  for (size_t i = index; i < (uint16_t)(self->count - 1); i++) {
    self->data[i] = self->data[i + 1];
  }
  self->data[self->count - 1] = tmp;

  self->count--;

  return;
}

// Check if a piece of data is in the vector
//
// # Arguments
// * self -> vector to search index
// * x -> x coordinate
//
// # Return Value
// True if in the vector, false otherwise
bool in_vector(Vector *self, uint8_t x) {
  for (size_t i = 0; i < self->count; i++) {
    if (self->data[i][0] == x) {
      return true;
    }
  }
  return false;
}

// Get the current size of the vector
//
// # Arguments
// * self -> the vector to check the size of
//
// # Return Value
// The size of the vector
uint16_t vector_len(Vector *self) { return self->count; }

// Get the average of all elements in the vector
int vector_avg(Vector *self) {
  int accumulation = 0;
  for (size_t i = 0; i < self->size; i++) {
    accumulation += self->data[i][0];
  }

  return accumulation / self->count;
}

// Calculate the average of all elements in the array
int avg(uint8_t *data, unsigned int size) {
  int accumulation = 0;
  for (size_t i = 0; i < size; i++) {
    accumulation += data[i];
  }

  return accumulation / size;
}

int main(void) {
  uint8_t garbage_data[10] = {
          [0] = 9,   [9] = 16, [7] = 15, [2] = 14,  [1] = 222,
          [5] = 124, [4] = 31, [6] = 0,  [8] = 128, [3] = 200,
  };

  Vector *my_vec = new_vector();

  // Copy data from garbage array to my_vec
  for (size_t i = 0; i < 10; i++) {
    vector_add(my_vec, (uint8_t)garbage_data[i]);
  }

  // Remove sixth element
  vector_delete(my_vec, 6);

  // Averages should be the same
  if (avg(garbage_data, 10) != vector_avg(my_vec)) {
    return -1;
  }

  return vector_avg(my_vec);
}
