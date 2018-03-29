#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

#include "configuration.h"

#include "primitives.h"
#include "3ds.h"
#include "light.h"
#include "camera.h"
#include "entity.h"
#include "layer.h"
#include "scene.h"

#ifdef __USING_GLUT__

#include <GL/glut.h>

#endif //__USING_GLUT__

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

  char windowTitle[256];
  unsigned int renderEngine;
  unsigned int width;
  unsigned int height;
  DISPLAY_FUNCTION display;

} Engine;

void engine_default_glut_display();

unsigned int engine_run(Engine* engine, int argc, char* argv[]);

#ifdef __cplusplus
   }
#endif

#endif //__ENGINE_H__
