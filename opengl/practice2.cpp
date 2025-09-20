#include <iostream>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid MouseClick(int button, int state, int x, int y);

float bg_color[4][3];
float in_color[4][3];
int count[4] = { 0 };

float random_color() {
	return static_cast<float>(rand()) / RAND_MAX;
}

void de() {
	for (int i = 0; i < 4; ++i) {
		bg_color[i][0] = random_color();
		bg_color[i][1] = random_color();
		bg_color[i][2] = random_color();

		in_color[i][0] = random_color();
		in_color[i][1] = random_color();
		in_color[i][2] = random_color();
	}
}
void main(int argc, char** argv)
{
	srand(static_cast<unsigned int>(time(NULL)));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Practice2");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize glew" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "Glew initialized" << std::endl;

	de();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseClick);
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(bg_color[0][0], bg_color[0][1], bg_color[0][2]);
	glRectf(0.0f, 0.0f, 1.0f, 1.0f);

	glColor3f(bg_color[1][0], bg_color[1][1], bg_color[1][2]);
	glRectf(-1.0f, 0.0f, 0.0f, 1.0f);

	glColor3f(bg_color[2][0], bg_color[2][1], bg_color[2][2]);
	glRectf(-1.0f, -1.0f, 0.0f, 0.0f);

	glColor3f(bg_color[3][0], bg_color[3][1], bg_color[3][2]);
	glRectf(0.0f, -1.0f, 1.0f, 0.0f);
	//---------------------------------------
	glColor3f(in_color[0][0], in_color[0][1], in_color[0][2]);
	glRectf(0.0f + (count[0] * 0.1f), 0.0f + (count[0] * 0.1f), 1.0f - (count[0] * 0.1f), 1.0f - (count[0] * 0.1f));

	glColor3f(in_color[1][0], in_color[1][1], in_color[1][2]);
	glRectf(-1.0f + (count[1] * 0.1f), 0.0f + (count[1] * 0.1f), 0.0f - (count[1] * 0.1f), 1.0f - (count[1] * 0.1f));

	glColor3f(in_color[2][0], in_color[2][1], in_color[2][2]);
	glRectf(-1.0f + (count[2] * 0.1f), -1.0f + (count[2] * 0.1f), 0.0f - (count[2] * 0.1f), 0.0f - (count[2] * 0.1f));

	glColor3f(in_color[3][0], in_color[3][1], in_color[3][2]);
	glRectf(0.0f + (count[3] * 0.1f), -1.0f + (count[3] * 0.1f), 1.0f - (count[3] * 0.1f), 0.0f - (count[3] * 0.1f));

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid MouseClick(int button, int state, int x, int y)
{
	float glX = (static_cast<float>(x) / 800) * 2.0f - 1.0f;
	float glY = (static_cast<float>(600 - y) / 600) * 2.0f - 1.0f;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (glX >= 0.0f && glX <= 1.0f && glY >= 0.0f && glY <= 1.0f) {	//우상단
			if (glX >= 0.0f + (0.1f * count[0]) && glX <= 1.0f - (0.1f * count[0]) && glY >= 0.0f + (0.1f * count[0]) && glY <= 1.0f - (0.1f * count[0])) {	//내부
				if (count[0] <= 9)	count[0]++;

			}
			else {//외부
				if (count[0] >= 1)	count[0]--;
			}
		}
		else if (glX >= -1.0f && glX < 0.0f && glY >= 0.0f && glY <= 1.0f) {//좌상단
			if (glX >= -1.0f + (0.1f * count[1]) && glX <= 0.0f - (0.1f * count[1]) && glY >= 0.0f + (0.1f * count[1]) && glY <= 1.0f - (0.1f * count[1])) {//내부
				if (count[1] <= 9)	count[1]++;
			}
			else {//외부
				if (count[1] >= 1)	count[1]--;
			}
		}
		else if (glX >= -1.0f && glX < 0.0f && glY >= -1.0f && glY < 0.0f) {//좌하단
			if (glX >= -1.0f + (0.1f * count[2]) && glX <= 0.0f - (0.1f * count[2]) && glY >= -1.0f + (0.1f * count[2]) && glY <= 0.0f - (0.1f * count[2])) {	//내부
				if (count[2] <= 9)	count[2]++;
			}
			else {//외부
				if (count[2] >= 1)	count[2]--;
			}
		}
		else if (glX >= 0.0f && glX <= 1.0f && glY >= -1.0f && glY < 0.0f) {//우하단
			if (glX >= -0.0f + (0.1f * count[3]) && glX <= 1.0f - (0.1f * count[3]) && glY >= -1.0f + (0.1f * count[3]) && glY <= 0.0f - (0.1f * count[3])) {	//외부
				if (count[3] <= 9)	count[3]++;
			}
			else {//내부
				if (count[3] >= 1)	count[3]--;
			}
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (glX >= 0.0f && glX <= 1.0f && glY >= 0.0f && glY <= 1.0f) {	//우상단
			if (glX >= 0.0f + (0.1f * count[0]) && glX <= 1.0f - (0.1f * count[0]) && glY >= 0.0f + (0.1f * count[0]) && glY <= 1.0f - (0.1f * count[0])) {	//내부
				in_color[0][0] = random_color();
				in_color[0][1] = random_color();
				in_color[0][2] = random_color();
			}
			else {//외부
				bg_color[0][0] = random_color();
				bg_color[0][1] = random_color();
				bg_color[0][2] = random_color();
			}
		}
		else if (glX >= -1.0f && glX < 0.0f && glY >= 0.0f && glY <= 1.0f) {//좌상단
			if (glX >= -1.0f + (0.1f * count[1]) && glX <= 0.0f - (0.1f * count[1]) && glY >= 0.0f + (0.1f * count[1]) && glY <= 1.0f - (0.1f * count[1])) {//내부
				in_color[1][0] = random_color();
				in_color[1][1] = random_color();
				in_color[1][2] = random_color();
			}
			else {//외부
				bg_color[1][0] = random_color();
				bg_color[1][1] = random_color();
				bg_color[1][2] = random_color();
			}
		}
		else if (glX >= -1.0f && glX < 0.0f && glY >= -1.0f && glY < 0.0f) {//좌하단
			if (glX >= -1.0f + (0.1f * count[2]) && glX <= 0.0f - (0.1f * count[2]) && glY >= -1.0f + (0.1f * count[2]) && glY <= 0.0f - (0.1f * count[2])) {	//내부
				in_color[2][0] = random_color();
				in_color[2][1] = random_color();
				in_color[2][2] = random_color();
			}
			else {//외부
				bg_color[2][0] = random_color();
				bg_color[2][1] = random_color();
				bg_color[2][2] = random_color();
			}
		}
		else if (glX >= 0.0f && glX <= 1.0f && glY >= -1.0f && glY < 0.0f) {//우하단
			if (glX >= -0.0f + (0.1f * count[3]) && glX <= 1.0f - (0.1f * count[3]) && glY >= -1.0f + (0.1f * count[3]) && glY <= 0.0f - (0.1f * count[3])) {	//외부
				in_color[3][0] = random_color();
				in_color[3][1] = random_color();
				in_color[3][2] = random_color();
			}
			else {//내부
				bg_color[3][0] = random_color();
				bg_color[3][1] = random_color();
				bg_color[3][2] = random_color();
			}
		}
	}
	glutPostRedisplay();
}