
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>

void spinDisplay();
void mouse(int button, int state, int x, int y);
void reshape(int w, int h);
void display();
void init();

static GLfloat spin = 0.0;

int main(int argc, char** argv){
	
	//create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	
	//init
	init();
	
	//register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	
	//the loop
	glutMainLoop();
	
	return 0;
}

void init(){
	glClearColor(0, 0 , 0, 0);
	glShadeModel(GL_FLAT);	
}

//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
	glRotatef(spin, 0, 0, 1);
	glColor3f(1, 1, 1);
	glRectf(-25, -25, 25, 25);
	glPopMatrix();
	
	glutSwapBuffers();
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*callback for mouse events*/
void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN)
				glutIdleFunc(spinDisplay);
			break;
			
		case GLUT_MIDDLE_BUTTON:
			if(state == GLUT_DOWN)
				glutIdleFunc(NULL);
			
		default:
			break;
	}
}

void spinDisplay(){
	spin += 2.0;
	if(spin > 360.0){
		spin = spin - 360.0;
	}
	glutPostRedisplay();
}
