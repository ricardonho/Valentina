/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   array.h
 * Author: ricardonho
 *
 * Created on 24 de Março de 2018, 23:18
 */

#ifndef ARRAY_H
#define ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArrayType {
  void* buffer;
  unsigned int segmentSize;
  unsigned int chunkSize;
  unsigned int count;
} Array;

Array* array_init(const unsigned int chunkSize, const unsigned int initCount);

void* array_malloc(Array* array);

void array_free(Array* array);

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_H */

