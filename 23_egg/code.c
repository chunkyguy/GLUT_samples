
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#import "eggGL.h"

static GLuint vertexBuffer_;

void init(){	
	
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
	//glGenBuffers(1, &vertexBuffer_);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	//glBufferData(GL_ARRAY_BUFFER, eggVertLen*sizeof(eggVert[0]), eggVert, GL_STATIC_DRAW);
}


void drawCube(){
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glVertexPointer(2, GL_FLOAT, 0, eggVert);
	glDrawArrays(GL_LINE_LOOP, 0, eggVertLen);
}

//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();{
		glTranslatef(0.0, 0.0, -5.0);
	
		glEnableClientState(GL_VERTEX_ARRAY);
			
		drawCube();
			
		glDisableClientState(GL_VERTEX_ARRAY);
		
	}glPopMatrix();
	
	glutSwapBuffers();
	//glFlush();
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, 1.0, 10.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv){
	
	//create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	
	//init
	init();
	
	//register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	//the loop
	glutMainLoop();	
	return 0;
}

