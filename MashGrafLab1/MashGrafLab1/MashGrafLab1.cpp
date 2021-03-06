// MashGrafLab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>

/* подключаем библиотеку GLUT */
#include <gl/glut.h>

/* начальная ширина и высота окна */
GLint Width = 512, Height = 512;
GLfloat angle = 0.0f, alarm_angle;
int refreshmill = 500;

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refreshmill, timer, 0);
}

/* размер куба */
const int CubeSize = 200, hand_size = 5;;

/* эта функция управляет всем выводом на экран */
void Display(void)
{
	int left, right, top, bottom, OTR[14];
	left = -hand_size / 2;
	right = hand_size / 2;
	bottom = 0;
	top = 30 * hand_size;
	//создаём массив координат четный индекс - x, нечётный - y
	OTR[0] = left;
	OTR[1] = bottom;
	OTR[2] = left;
	OTR[3] = top;
	OTR[4] = left - 3;
	OTR[5] = top - 2;
	OTR[6] = left + (hand_size / 2);
	OTR[7] = top + 20;
	OTR[8] = right + 3;
	OTR[9] = top - 2;
	OTR[10] = right;
	OTR[11] = top;
	OTR[12] = right;
	OTR[13] = bottom;
	//объявляем массив точек
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, 0, OTR);
	//чистим экран
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(255, 255, 255);
	//рисуем секундную стрелку
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslated((Width - hand_size) / 2, (Height / 2), 0);
	glRotatef(angle, 0.0f, 0.0f, -1.0f);
	glDrawArrays(GL_LINE_LOOP, 0, 7);
	glPopMatrix();
	glutSwapBuffers();
	//рисуем стрелку будильника
	glTranslated((Width - hand_size) / 2, (Height / 2), 0);
	glRotatef(alarm_angle, 0.0f, 0.0f, -1.0f);
	int alarm_clock[2];
	alarm_clock[0] = 0;
	alarm_clock[1] = hand_size * 30;
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(alarm_clock[0], alarm_clock[1]);
	glEnd();
	//рисуем круг
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 40; i++)
	{
		float angle_circle = 2.0 * 3.1415926 * float(i) / float(40);
		float dx = OTR[7] * cosf(angle_circle);
		float dy = OTR[7] * sinf(angle_circle);
		glVertex2f(dx, dy);
	}
	glEnd();
	if ((fmod(angle, 360) >= alarm_angle) && (fmod(angle - 6.0f, 360) < alarm_angle))
	{
		Beep(2000, 100);
	}
	angle += 6.0f;
	glFinish();
}

/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h)
{
	Width = w;
	Height = h;

	/* устанавливаем размеры области отображения */
	glViewport(0, 0, w, h);

	/* ортографическая проекция */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'

	if (key == ESCAPE)
		exit(0);
}

/* Главный цикл приложения */
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Red square example");
	std::cin >> alarm_angle;

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
}