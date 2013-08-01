/*Planetery System*/

#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>

void keyboard(unsigned char key, int x, int y);
void update();
void reshape(int w, int h);
void display();
void init();

static int year = 0;
static int day = 0;

int main(int argc, char** argv){
	
	//create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	
	//init
	init();
	
	//register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(update);
	glutKeyboardFunc(keyboard);
	
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
	glColor3f(1.0, 1.0, 1.0);
	
	//sun
	glPushMatrix();
	{
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
		glutWireSphere(1.0, 20, 16);
	}
	glPopMatrix();
	
	//earth
	glPushMatrix();
	{
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
		glTranslatef(2.0, 0.0, 0.0);
		
		//moon
		glPushMatrix();
		{
			glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
			glTranslatef(0.15, 0.0, 0.0);
			glutWireSphere(0.01, 5, 4);
		}
		glPopMatrix();
		
		glRotatef((GLfloat)day, 1.0, 1.0, 0.0);
		glutWireSphere(0.1, 10, 8);
	}
	glPopMatrix();
	
	glutSwapBuffers();
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void update(){
	day = (day + 10) % 360;
	year = (year + 5) % 360;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'd':
			day = (day + 10) % 360;
			glutPostRedisplay();
			break;
		case 'D':
			day = (day - 10) % 360;
			glutPostRedisplay();
			break;
		case 'y':
			year = (year + 5) % 360;
			glutPostRedisplay();
			break;
		case 'Y':
			year = (year - 5) % 360;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}
