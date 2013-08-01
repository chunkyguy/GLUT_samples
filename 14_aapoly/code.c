
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static GLfloat rotationSpeed = 5.0f;
GLboolean polySmooth = GL_FALSE;
GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;

void init(){
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawCube(float e){
	//printf("%f %f\n",e/2,-e/2);
	static GLfloat v[8][3];
	v[0][0] = -e/2; v[0][1] = -e/2;	v[0][2] = -e/2;
	v[1][0] = e/2;	v[1][1] = -e/2;	v[1][2] = -e/2;	
	v[2][0] = e/2;	v[2][1] = e/2;	v[2][2] = -e/2;	
	v[3][0] = -e/2; v[3][1] = e/2;	v[3][2] = -e/2;	
	v[4][0] = -e/2; v[4][1] = -e/2;	v[4][2] = e/2;	
	v[5][0] = e/2;	v[5][1] = -e/2;	v[5][2] = e/2;	
	v[6][0] = e/2;	v[6][1] = e/2;	v[6][2] = e/2;	
	v[7][0] = -e/2; v[7][1] = e/2;	v[7][2] = e/2;
	
	static GLfloat c[8][4] = {
		0,0,0,1,
		0,0,1,1,
		0,1,0,1,
		0,1,1,1,
		1,0,0,1,
		1,0,1,1,
		1,1,0,1,
		1,1,1,1
	};
	
	static GLubyte face[6][4] = {
		4,5,6,7,
		2,3,7,6,
		0,4,7,3,
		0,1,5,4,
		1,5,6,2,
		0,3,2,1,
	};
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v);
	glColorPointer(4, GL_FLOAT, 0, c);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, face);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void display(){
	
	if(polySmooth){
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glEnable(GL_POLYGON_SMOOTH);
		glDisable(GL_DEPTH_TEST);
		//glColor3f(1.0, 0.0, 0.0);
	}else{
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glDisable(GL_BLEND);
		glDisable(GL_POLYGON_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		//glColor3f(0.0, 1.0, 0.0);
	}
	
	glPushMatrix();{
		glTranslatef(0.0, 0.0, -10.0);
		glRotatef(rotX, 1.0, 0.0, 0.0);
		glRotatef(rotY, 0.0, 1.0, 0.0);
		drawCube(1.0f);
	}glPopMatrix();
	
	glFlush();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			rotX -= rotationSpeed;
			break;
		case 's':
			rotX += rotationSpeed;
			break;
		case 'a':
			rotY -= rotationSpeed;
			break;
		case 'd':
			rotY += rotationSpeed;
			break;
		case 27: exit(0); break;
		default:
			rotX = rotY = 0.0f;
			break;
	}
	if(rotX > 360.0f)
		rotX = 360.0f - rotX;
	if(rotY > 360.0f)
		rotY = 360.0f - rotY;
	glutPostRedisplay();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB| GLUT_ALPHA| GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	
	init();
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();
	
	return 0;
}