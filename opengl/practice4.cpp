#include <iostream>
#include <vector>
#include <cmath>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid MouseClick(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid update(int value);

struct Rectangle1 {

	// ���� ���°�
	float x, y;
	float width, height;
	float r, g, b;

};

std::vector<Rectangle1> rectangles;
const int MAX_RECTANGLES = 5;
//int width = 800, height = 800;

float randomFloat1(float min, float max) {
	if (min > max) std::swap(min, max);
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

float randomFloat() {
	return static_cast<float>(rand()) / RAND_MAX;
}

void main(int argc, char** argv)
{
	srand(static_cast<unsigned int>(time(NULL)));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("OpenGL Practice3");

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
	glutMouseFunc(MouseClick);
	glutKeyboardFunc(Keyboard);

	glutTimerFunc(16, update, 0);
	//glutMotionFunc(MouseDrag);
	glutMainLoop();
}

GLvoid update(int value) {
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (const auto& rect : rectangles) {
		// 1. ���� �簢���� ���� ����
		glColor3f(rect.r, rect.g, rect.b);

		// 2. �߽����� �ʺ�/���̷κ��� �����ϴ�, ������� ��ǥ ���
		float x1 = rect.x - rect.width / 2.0f;
		float y1 = rect.y - rect.height / 2.0f;
		float x2 = rect.x + rect.width / 2.0f;
		float y2 = rect.y + rect.height / 2.0f;

		// 3. ���� ��ǥ�� �簢�� �׸���
		glRectf(x1, y1, x2, y2);
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid MouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		// 1. �簢�� ������ �ִ�ġ(5��) �̸����� Ȯ��
		if (rectangles.size() < MAX_RECTANGLES) {
			float glX = (static_cast<float>(x) / 800) * 2.0f - 1.0f;
			float glY = (static_cast<float>(800 - y) / 800) * 2.0f - 1.0f;

			Rectangle1 newRect;
			newRect.x = glX; // �߽� X��ǥ�� ���콺 Ŭ�� ��ġ
			newRect.y = glY; // �߽� Y��ǥ�� ���콺 Ŭ�� ��ġ
			newRect.width = 0.4f;  // �ʺ�� 0.4�� ����
			newRect.height = 0.4f; // ���̴� 0.4�� ����
			newRect.r = randomFloat(); // ������ ����
			newRect.g = randomFloat();
			newRect.b = randomFloat();

			// 4. �ϼ��� �� �簢���� ���Ϳ� �߰�
			rectangles.push_back(newRect);

			// 5. ȭ���� ���� �׸����� ��û
			glutPostRedisplay();

		}
	}
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q': case 27:
		glutLeaveMainLoop();
		break;
	}
}