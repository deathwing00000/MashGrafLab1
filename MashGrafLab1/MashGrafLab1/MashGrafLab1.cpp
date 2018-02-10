// MashGrafLab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>

/* подключаем библиотеку GLUT */
#include <gl/glut.h>

/* начальная ширина и высота окна */
GLint Width = 512, Height = 512;
GLfloat angle = 1.0f;
int refreshmill = 1;

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refreshmill, timer, 0);
}

/* размер куба */
const int CubeSize = 200, HandSize = 5;;

/* эта функция управляет всем выводом на экран */
void Display(void)
{
	int left, right, top, bottom, OTR[14];
	left = (Width - HandSize) / 2;
	right = left + HandSize;
	bottom = (Height - HandSize) / 2;
	top = bottom + 30 * HandSize;
	OTR[0] = left;
	OTR[1] = bottom;
	OTR[2] = left;
	OTR[3] = top;
	OTR[4] = left - 3;
	OTR[5] = top - 2;
	OTR[6] = left + (HandSize / 2);
	OTR[7] = top + 20;
	OTR[8] = right + 3;
	OTR[9] = top - 2;
	OTR[10] = right;
	OTR[11] = top;
	OTR[12] = right;
	OTR[13] = bottom; 
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, 0, OTR);
/*	left = (Width - CubeSize) / 2;
	right = left + CubeSize;
	bottom = (Height - CubeSize) / 2;
	top = bottom + CubeSize;*/
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(255, 255, 255);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslated(-OTR[6], -bottom, 0);
	glDrawArrays(GL_LINE_LOOP, 0, 7);
//	glTranslated(OTR[6], bottom, 0);
	glPopMatrix();
	glutSwapBuffers();
	angle += 0.2f;
//	glBegin(GL_QUADS);
/*	left = (Width - HandSize) / 2;
	right = left + HandSize;
	bottom = (Height - HandSize) / 2;
	top = bottom + 30*HandSize;*/
/*	glVertex2f(OTR[0], OTR[1]);
	glVertex2f(OTR[2], OTR[3]);
	glVertex2f(OTR[4], OTR[5]);
	glVertex2f(OTR[6], OTR[7]);
	glVertex2f(OTR[8], OTR[9]);
	glVertex2f(OTR[10], OTR[11]);*/
//	glEnd();

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

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
}