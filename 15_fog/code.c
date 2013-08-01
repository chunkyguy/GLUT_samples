#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TOTAL_SPHERES 5

enum kMaterial{
	kMaterialAmbience = 0,
	kMaterialDiffuse = 1,
	kMaterialSpecular = 2
};

static GLint fogMode;

void init(){
	static GLfloat position[] = {0.5, 0.5, 3.0, 0.0};
	static GLfloat mat[3][3] = {
		{0.1745, 0.01175, 0.01175},
		{0.61424, 0.04136, 0.04136},
		{0.727811, 0.626959, 0.626959}
	};
	static GLfloat fogColor[] = {0.5, 0.5, 0.5, 1.0};
	
	glEnable(GL_DEPTH_TEST);
	
	//light
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat[kMaterialAmbience]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat[kMaterialDiffuse]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat[kMaterialSpecular]);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.6*128.0);
	
	//fog
	glEnable(GL_FOG);
	fogMode = GL_EXP;
	glFogi(GL_FOG_MODE, fogMode);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.35);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 1.0);
	glFogf(GL_FOG_END, 5.0);
	
	glClearColor(0.5, 0.5, 0.5, 1.0);
}

void reshape(int w, int h){
	GLfloat aspectRatio[2] = {1.0, 1.0};
	
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h){
		aspectRatio[0] = 1.0;
		aspectRatio[1] = (GLfloat)h/(GLfloat)w;
	}else{
		aspectRatio[0] = (GLfloat)w/(GLfloat)h;
		aspectRatio[1] = 1.0;
	}
	glOrtho(-2.5*aspectRatio[0], 2.5*aspectRatio[0], -2.5*aspectRatio[1], 2.5*aspectRatio[1], -10.0, 10.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawSphere(GLfloat x, GLfloat y, GLfloat z){
	glPushMatrix();{
		glTranslatef(x, y, z);
		glutSolidSphere(0.4, 16, 16);
	}glPopMatrix();
}

void display(){
	GLfloat coords[3] = {-2.0, -0.5, -1.0};
	int sphereNo;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for(sphereNo = 0; sphereNo < TOTAL_SPHERES; sphereNo++)
		drawSphere(coords[0]+(1.0 * sphereNo), coords[1], coords[2]-(1.0 * sphereNo));

	glFlush();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'f':
			if(fogMode == GL_EXP){
				fogMode = GL_EXP2;
			}else if(fogMode == GL_EXP2){
				fogMode = GL_LINEAR;
			}else if(fogMode == GL_LINEAR){
				fogMode = GL_EXP;
			}
			glFogi(GL_FOG_MODE, fogMode);
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
	}
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	
	init();
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();
	return 0;
}