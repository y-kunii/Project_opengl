#include<stdio.h>
#include"glm\glm.hpp"
#include "glut.h"

#include "font.h"

using namespace glm;

ivec2 windowSize = {800,600};

bool keys[256];

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);//(GLenum mode);
	glLoadIdentity();
	gluOrtho2D(
		0,//GLdouble left,
		windowSize.x,//GLdouble right,
		windowSize.y,//GLdouble bottom,
		0//GLdouble top);
	);

	glMatrixMode(GL_MODELVIEW);//(GLenum mode);
	glLoadIdentity();

	glTranslatef(
		windowSize .x/2,//(GLfloat x,
		windowSize .y/2,//GLfloat y,
		0//GLfloat z);
	);

	static float angle;
	//angle += 1;
	if (keys['d'])
		angle += 1;
	if (keys['a'])
		angle -= 1;
	glRotatef(
		angle,
		0, 0, 1);//GLfloat angle, GLfloat x, GLfloat y, GLfloat z
	
	glScalef(
		256,//GLfloat x,
		256,//GLfloat y,
		1//GLfloat z);
	);
	glutWireTeapot(1);// GLdouble size

	fontBegin();
	fontSetColor(0,0xff,0x00);
	fontSetPosition(0,windowSize.y - fontgetSize()*1.5);
	fontSetSize(FONT_DEFAULT_SIZE/2);
	fontDraw("angle:%f", angle);
	fontEnd();

	glutSwapBuffers();
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(
		1000/60,//(unsigned int millis
		timer,//void (GLUTCALLBACK *func)(int value),
		0);//int value));
}

void reshape(int width, int height) {
	//printf("reshape: width:%d height:%d\n", width, height);
	glViewport(0,0,width,height);//(GLint x, GLint y, GLsizei width, GLsizei height);
	windowSize = ivec2(width, height);
};

void keyboard(unsigned char key, int x, int y) {
	if (key == 0x1b) {
		exit(0);
	}
	//printf("keyboard: :\'%c' (%#x)\n", key, key);
	keys[key] = true;
};

void keyboardUp(unsigned char key, int x, int y) {
	//printf("keyboardUp: :\'%c' (%#x)\n", key, key);
	keys[key] = false;
};


int main(int argc, char *argv[]) {
	glutInit(
		&argc,// int *argc
		argv);// char **argv
	glutInitDisplayMode(GL_DOUBLE);
	glutInitWindowPosition(640,0);//int x,y
	glutInitWindowSize(windowSize.x, windowSize.y);//int width,height
	glutCreateWindow("title"); //const char *title
	glutDisplayFunc(display); //void (GLUTCALLBACK *func)(void))
	//glutIdleFunc(idle);
	glutTimerFunc(
		0,//(unsigned int millis
		timer,//void (GLUTCALLBACK *func)(int value),
		0);//int value));
	glutReshapeFunc(reshape);//(void (GLUTCALLBACK *func)(int width, int height));
	glutKeyboardFunc(keyboard);//(void (GLUTCALLBACK *func)(unsigned char key, int x, int y));
	glutKeyboardUpFunc(keyboardUp);//(void (GLUTCALLBACK *func)(unsigned char key, int x, int y));
	glutIgnoreKeyRepeat(GL_TRUE);// int ignore
	glutMainLoop();
}