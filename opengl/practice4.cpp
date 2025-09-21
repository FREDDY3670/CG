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

	// 현재 상태값
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
		// 1. 현재 사각형의 색상 설정
		glColor3f(rect.r, rect.g, rect.b);

		// 2. 중심점과 너비/높이로부터 좌측하단, 우측상단 좌표 계산
		float x1 = rect.x - rect.width / 2.0f;
		float y1 = rect.y - rect.height / 2.0f;
		float x2 = rect.x + rect.width / 2.0f;
		float y2 = rect.y + rect.height / 2.0f;

		// 3. 계산된 좌표로 사각형 그리기
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

		// 1. 사각형 개수가 최대치(5개) 미만인지 확인
		if (rectangles.size() < MAX_RECTANGLES) {
			float glX = (static_cast<float>(x) / 800) * 2.0f - 1.0f;
			float glY = (static_cast<float>(800 - y) / 800) * 2.0f - 1.0f;

			Rectangle1 newRect;
			newRect.x = glX; // 중심 X좌표는 마우스 클릭 위치
			newRect.y = glY; // 중심 Y좌표는 마우스 클릭 위치
			newRect.width = 0.4f;  // 너비는 0.4로 고정
			newRect.height = 0.4f; // 높이는 0.4로 고정
			newRect.r = randomFloat(); // 색상은 랜덤
			newRect.g = randomFloat();
			newRect.b = randomFloat();

			// 4. 완성된 새 사각형을 벡터에 추가
			rectangles.push_back(newRect);

			// 5. 화면을 새로 그리도록 요청
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