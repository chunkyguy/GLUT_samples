#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>

static int leftFirst = GL_TRUE;

void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void drawLeftTriangle();
void drawRightTriangle();

int main(int argc, char** argv){
	
	//create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(100, 100);
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void drawLeftTriangle(){
	glBegin(GL_TRIANGLES);{
		glColor4f(1.0, 1.0, 0.0, 0.75);
		glVertex3f(0.1, 0.9, 0.0);
		glVertex3f(0.1, 0.1, 0.0);
		glVertex3f(0.7, 0.5, 0.0);
	}glEnd();
}

void drawRightTriangle(){
	glBegin(GL_TRIANGLES);{
		glColor4f(0.0, 1.0, 1.0, 0.75);
		glVertex3f(0.9, 0.9, 0.0);
		glVertex3f(0.3, 0.5, 0.0);
		glVertex3f(0.9, 0.1, 0.0);
	}glEnd();
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
		gluOrtho2D(0.0, 1.0, 0.0, 1.0*(GLfloat)h/(GLfloat)w);
	else
		gluOrtho2D(0.0, 1.0*(GLfloat)w/(GLfloat)h, 0.0, 1.0);
}

//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	if(leftFirst){
		drawLeftTriangle();
		drawRightTriangle();
	}else{
		drawRightTriangle();
		drawLeftTriangle();
	}
	glFlush();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
			case 't': case 'T':
			leftFirst = !leftFirst;
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}
