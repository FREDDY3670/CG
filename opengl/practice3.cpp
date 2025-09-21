#include <iostream>
#include <vector>
#include <algorithm>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid MouseClick(int button, int state, int x, int y);
GLvoid MouseDrag(int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

int draggedRectIndex = -1;

struct Rectangle1 {
	float x, y;
	float width = 0.2, height = 0.2; 
	float r, g, b;
};

std::vector<Rectangle1> rectangles;
const int MAX_RECTANGLE = 10;

float randomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
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
	glutMotionFunc(MouseDrag);
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		if (rectangles.size() < MAX_RECTANGLE) {
			Rectangle1 newRect;
			float x_range = 1.0f - newRect.width / 2.0f;
			float y_range = 1.0f - newRect.height / 2.0f;
			newRect.x = randomFloat(-x_range, x_range);
			newRect.y = randomFloat(-y_range, y_range);
			newRect.r = randomFloat(0.0f, 1.0f);
			newRect.g = randomFloat(0.0f, 1.0f);
			newRect.b = randomFloat(0.0f, 1.0f);
			rectangles.push_back(newRect);
		}
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid MouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			float glx = (static_cast<float>(x) / 800) * 2.0f - 1.0f;
			float gly = (static_cast<float>(800 - y) / 800) * 2.0f - 1.0f;
			for (int i = rectangles.size() - 1; i >= 0; --i) {
				float x1 = rectangles[i].x - rectangles[i].width / 2.0f;
				float y1 = rectangles[i].y - rectangles[i].height / 2.0f;
				float x2 = rectangles[i].x + rectangles[i].width / 2.0f;
				float y2 = rectangles[i].y + rectangles[i].height / 2.0f;

				if (glx >= x1 && glx <= x2 && gly >= y1 && gly <= y2) {
					draggedRectIndex = i; 
					break;
				}
			}
		}
		else if (state == GLUT_UP) {
			if (draggedRectIndex != -1) {
				Rectangle1& moveRect = rectangles[draggedRectIndex];
				float moved_x1 = moveRect.x - moveRect.width / 2.0f;
				float moved_y1 = moveRect.y - moveRect.height / 2.0f;
				float moved_x2 = moveRect.x + moveRect.width / 2.0f;
				float moved_y2 = moveRect.y + moveRect.height / 2.0f;

				for (int i = 0; i < rectangles.size(); ++i) {
					if (i == draggedRectIndex)	continue;
					Rectangle1& otherRect = rectangles[i];
					float other_x1 = otherRect.x - otherRect.width / 2.0f;
					float other_y1 = otherRect.y - otherRect.height / 2.0f;
					float other_x2 = otherRect.x + otherRect.width / 2.0f;
					float other_y2 = otherRect.y + otherRect.height / 2.0f;

					if (moved_x1 < other_x2 && moved_x2 > other_x1 &&
						moved_y1 < other_y2 && moved_y2 > other_y1)
					{
						// 1. 겹쳤다면, 두 사각형을 포함하는 새 경계 상자 계산
						float new_x1 = std::min(moved_x1, other_x1);
						float new_y1 = std::min(moved_y1, other_y1);
						float new_x2 = std::max(moved_x2, other_x2);
						float new_y2 = std::max(moved_y2, other_y2);

						Rectangle1 mergedRect;
						mergedRect.width = new_x2 - new_x1;
						mergedRect.height = new_y2 - new_y1;
						mergedRect.x = new_x1 + mergedRect.width / 2.0f;
						mergedRect.y = new_y1 + mergedRect.height / 2.0f;
						mergedRect.r = randomFloat(0.0f, 1.0f);
						mergedRect.g = randomFloat(0.0f, 1.0f);
						mergedRect.b = randomFloat(0.0f, 1.0f);

						if (draggedRectIndex > i) {
							rectangles.erase(rectangles.begin() + draggedRectIndex);
							rectangles.erase(rectangles.begin() + i);
						}
						else {
							rectangles.erase(rectangles.begin() + i);
							rectangles.erase(rectangles.begin() + draggedRectIndex);
						}

						rectangles.push_back(mergedRect);

						break;
					}
				}
			}
			draggedRectIndex = -1; 
		}
	}
	else if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		int clickedRectIndex = -1;
		float glx = (static_cast<float>(x) / 800) * 2.0f - 1.0f;
		float gly = (static_cast<float>(800 - y) / 800) * 2.0f - 1.0f;

		for (int i = rectangles.size() - 1; i >= 0; --i) {
			float x1 = rectangles[i].x - rectangles[i].width / 2.0f;
			float y1 = rectangles[i].y - rectangles[i].height / 2.0f;
			float x2 = rectangles[i].x + rectangles[i].width / 2.0f;
			float y2 = rectangles[i].y + rectangles[i].height / 2.0f;
			if (glx >= x1 && glx <= x2 && gly >= y1 && gly <= y2) {
				clickedRectIndex = i;
				break;
			}
		}

		if (clickedRectIndex != -1) {
			if (rectangles.size() < 30) {
				Rectangle1 oldRect = rectangles[clickedRectIndex];
				rectangles.erase(rectangles.begin() + clickedRectIndex);

				for (int i = 0; i < 2; ++i) {
					Rectangle1 newRect;
					newRect.width = randomFloat(0.1f, oldRect.width * 0.7f);
					newRect.height = randomFloat(0.1f, oldRect.height * 0.7f);
					float offsetX = randomFloat(-oldRect.width / 4.0f, oldRect.width / 4.0f);
					float offsetY = randomFloat(-oldRect.height / 4.0f, oldRect.height / 4.0f);
					newRect.x = oldRect.x + offsetX;
					newRect.y = oldRect.y + offsetY;
					newRect.r = randomFloat(0.0f, 1.0f);
					newRect.g = randomFloat(0.0f, 1.0f);
					newRect.b = randomFloat(0.0f, 1.0f);
					rectangles.push_back(newRect);
				}
			}
		}
	}
	glutPostRedisplay();
}


GLvoid MouseDrag(int x, int y)
{
	if (draggedRectIndex != -1) {
		float glx = (static_cast<float>(x) / 800) * 2.0f - 1.0f;
		float gly = (static_cast<float>(800 - y) / 800) * 2.0f - 1.0f;

		rectangles[draggedRectIndex].x = glx;
		rectangles[draggedRectIndex].y = gly;

		glutPostRedisplay(); 
	}
}