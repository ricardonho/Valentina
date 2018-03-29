#include "engine.h"

void engine_default_glut_display() {

}

unsigned int engine_run(Engine* engine, int argc, char* argv[]) {

  if(!engine) {
	return 0;
  }

  switch(engine->renderEngine) {
	
	case OPENGL: {
		  break;
	}

	case OPENGL_GLUT: {

	  glutInit(&argc, argv);
	  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	  glutCreateWindow(engine->windowTitle);
	  glutDisplayFunc(engine->display);

	  glutMainLoop();

	  break;
	}

	case DIRECTX: {
	  break;
	}

  }

  return 1;
}
