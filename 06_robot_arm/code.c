/*Robot Arm*/

#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>

void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void display();
void init();

static int shoulder = 0;
static int elbow = 0;

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
	
	glPushMatrix();
	{
		glTranslatef(-1.0, 0.0, 0.0);
		glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
		glTranslatef(1.0, 0.0, 0.0);
		glPushMatrix();
		{
			glScalef(2.0, 0.4, 1.0);
			glutWireCube(1.0);
		}
		glPopMatrix();
		
		glTranslatef(1.0, 0.0, 0.0);
		glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
		glTranslatef(1.0, 0.0, 0.0);
		glPushMatrix();
		{
			glScalef(2.0, 0.4, 1.0);
			glutWireCube(1.0);
		}
		glPopMatrix();
	}
	glPopMatrix();
	
	glutSwapBuffers();
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 's':
			shoulder = (shoulder + 5) % 360;
			glutPostRedisplay();
			break;
		case 'S':
			shoulder = (shoulder - 5) % 360;
			glutPostRedisplay();
			break;
		case 'e':
			elbow = (elbow + 5) % 360;
			glutPostRedisplay();
			break;
		case 'E':
			elbow = (elbow - 5) % 360;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}
