#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>

static int spin = 0;

void init();
void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv){
	
	//create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
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
	glClearColor(0.0, 0.0, 0.2, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//refresh screen
void display(){
	GLfloat position[]	= {0.0, 0.0, 1.5, 0.0};
	GLfloat diffuse[]	= {0.0, 1.0, 0.0, 1.0};
	GLfloat ambience[]	= {1.0, 1.0, 1.0, 1.0};
	GLfloat specular[]	= {1.0, 1.0, 1.0, 1.0};
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	{
		glTranslatef(0.0, 0.0, -5.0);
		glPushMatrix();
		{
			glRotated((GLdouble)spin, 1.0, 0.0, 0.0);
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
			glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
			glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
			
			glTranslated(0.0, 0.0, 1.5);
			glDisable(GL_LIGHTING);
			glColor3f(0.0, 1.0, 1.0);
			glutWireCube(0.1);
			glEnable(GL_LIGHTING);
		}
		glPopMatrix();
		glutSolidTorus(0.275, 0.85, 8, 15);
	}
	glPopMatrix();
	
	glFlush();
}

void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){
				spin = spin + 10;
				if(spin >= 360)
					spin = 360 - spin;
				glutPostRedisplay();
			}
			break;
		default:
			break;
	}
}
