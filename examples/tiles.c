#include <engine.h>

int main(int argc, char* argv[]) {

  Engine* engine = malloc(sizeof(Engine));

  engine->renderEngine = OPENGL_GLUT;

  engine->display = engine_default_glut_display;

  engine_run(engine, argc, argv);

  free(engine);

  return 0;
}
