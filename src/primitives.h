/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   primitives.h
 * Author: ricardonho
 *
 * Created on 24 de Março de 2018, 13:01
 */

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#define TWOPI 3.1415*2
#define PID2 3.1415/2

//#define WIDTHBYTES(bits) ((bits + 31) / 32) * 4

#define MAX_VERTICES 8000 // Max number of vertices (for each object)
#define MAX_POLYGONS 8000 // Max number of polygons (for each object)

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct VertexType {
        float x, y, z;
    } Vertex;

    typedef struct PolygonType {
        unsigned int a, b, c;
    } Polygon;
    
    typedef struct MapcoordType {
        float u,v;
    } Mapcoord;
    
    typedef struct ObjectType {
        char name[256];
        struct VertexType   vertices[MAX_VERTICES];
        struct PolygonType  polygons[MAX_POLYGONS];
        struct MapcoordType mapcoords[MAX_VERTICES];
        struct VertexType   normals[MAX_VERTICES];
        unsigned int vCount;
        unsigned int pCount;
    } Object;
    
#ifdef __cplusplus
}
#endif

#endif /* PRIMITIVES_H */

