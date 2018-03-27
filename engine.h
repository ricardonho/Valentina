#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

#ifdef __cplusplus
   extern “C” {
#endif

typedef void(*DISPLAY_FUNCTION)();

enum RenderEngineEnum {
  OPENGL = 0,
  OPENGL_GLUT,
  DIRECTX,
  RENDER_ENGINE_COUNT
};

typedef struct EngineType {

  unsigned int renderEngine;
  unsigned int width;
  unsigned int height;
  DISPLAY_FUNCTION display;

} Engine;

unsigned int engine_run(Engine* engine, int argc, char* argv[]);

#ifdef __cplusplus
   }
#endif

#endif //__ENGINE_H__
