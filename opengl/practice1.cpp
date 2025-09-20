#include <iostream>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Timer(int value);

bool timer = false;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Practice1");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize glew" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "Glew initialized" << std::endl;

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

float bgR = 1.0f;
float bgG = 1.0f;
float bgB = 1.0f;


GLvoid drawScene(GLvoid)
{
	glClearColor(bgR, bgG, bgB, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		bgR = 0.0f;
		bgG = 1.0f;
		bgB = 1.0f;
		break;
	case 'm':
		bgR = 1.0f;
		bgG = 0.0f;
		bgB = 1.0f;
		break;
	case 'y':
		bgR = 1.0f;
		bgG = 1.0f;
		bgB = 0.0f;
		break;
	case 'a':
		bgR = static_cast<float>(rand()) / RAND_MAX;
		bgG = static_cast<float>(rand()) / RAND_MAX;
		bgB = static_cast<float>(rand()) / RAND_MAX;
		break;
	case 'w':
		bgR = 1.0f; bgG = 1.0f; bgB = 1.0f;
		break;
	case 'k':
		bgR = 0.0f; bgG = 0.0f; bgB = 0.0f;
		break;
	case 't':
		if (!timer) {
			timer = true;
			glutTimerFunc(200, Timer, 0);
		}
		break;
	case 's':
		timer = false;
		break;
	case 'q':
		glutLeaveMainLoop();
	}
	glutPostRedisplay();
}

GLvoid Timer(int value) {
	if (timer) {
		bgR = static_cast<float>(rand()) / RAND_MAX;
		bgG = static_cast<float>(rand()) / RAND_MAX;
		bgB = static_cast<float>(rand()) / RAND_MAX;
		glutPostRedisplay();
		glutTimerFunc(200, Timer, 0);
	}

}