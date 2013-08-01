
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

int screen_width, screen_height;
static GLfloat spin = 0.0;

int main(int argc, char** argv){
	
	//create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
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
	glClearColor(0, 0 , 0, 0);
	glShadeModel(GL_FLAT);	
}

//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	int i, j;
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			glViewport((GLsizei)screen_width/2*i, (GLsizei)screen_height/2*j, (GLsizei)screen_width/2, (GLsizei)screen_height/2);
			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//			if((i+j)%2)
			//							glOrtho(-10, 10, -10, 10, 1, 10);
			//else
				glFrustum(-10, 10, -10, 10, 1, 10);
			
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glColor3f(i, j, 1);
			glPushMatrix();{
				glTranslatef(0, 0, -5.0);
				glRotatef(30, 1, 0, 0);
				glRotatef(30, 0, 1, 0);
				glutSolidCube(4.5);
			}glPopMatrix();
		}
	}
	glutSwapBuffers();
}

/*callback for window resize*/
void reshape(int w, int h){
	screen_width = w;
	screen_height = h;
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
