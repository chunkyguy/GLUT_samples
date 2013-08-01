#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>

static float rotAngle = 0.0;

void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){
	
	//create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(200, 200);
	glutCreateWindow(argv[0]);
	
	//init
	init();
	
	//register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	//the loop
	glutMainLoop();
	return 0;
}

void init(){
	GLfloat values[2];
	glGetFloatv(GL_LINE_WIDTH_GRANULARITY, values);
	printf("GL_LINE_WIDTH_GRANUALARITY values: %3.1f %3.1f\n",values[0], values[1]);
	glGetFloatv(GL_LINE_WIDTH_RANGE, values);
	printf("GL_LINE_WIDTH_RANGE values: %3.1f %3.1f\n",values[0], values[1]);
	
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glLineWidth(3.0);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLint)w, (GLint)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
		gluOrtho2D(-1.0, 1.0, -1.0*(GLfloat)h/(GLfloat)w, 1.0*(GLfloat)h/(GLfloat)w);
	else
		gluOrtho2D(-1.0*(GLfloat)w/(GLfloat)h, 1.0*(GLfloat)w/(GLfloat)h, -1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor4f(0.0, 1.0, 0.0, 0.75);
	glPushMatrix();{
		glRotatef(-rotAngle, 0.0, 0.0, 0.1);
		glBegin(GL_LINES);{
			glVertex2f(-0.5, 0.5);
			glVertex2f(0.5, -0.5);
		}glEnd();
	}glPopMatrix();
	
	glColor4f(0.0, 0.0, 1.0, 0.5);
	glPushMatrix();{
		glRotatef(rotAngle, 0.0, 0.0, 0.1);
		glBegin(GL_LINES);{
			glVertex2f(0.5, 0.5);
			glVertex2f(-0.5, -0.5);
		}glEnd();
	}glPopMatrix();
	
	glFlush();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'r': case 'R':
			rotAngle += 5.0;
			if(rotAngle >= 360.0)
				rotAngle = 0.0;
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}
