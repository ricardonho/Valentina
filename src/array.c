/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>

#include "array.h"

Array* array_init(const unsigned int chunkSize, const unsigned int initCount) {

  Array* array = malloc(sizeof(Array));

  array->buffer = malloc(chunkSize * initCount);
  array->segmentSize = initCount;
  array->chunkSize = chunkSize;
  array->count = 0;

  return array;

}

void* array_malloc(Array* array) {

  if(array->count + 1 > array->segmentSize) {
    array->segmentSize *= 2;
    array->buffer = realloc(array->buffer, array->chunkSize * array->segmentSize);
  }

  char* ret =  array->buffer + array->count * array->chunkSize;

  ++array->count;

  return ret;
}

void array_free(Array* array) {

  if(!array || !array->buffer) return;

  free(array->buffer);

  free(array);
}
