
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>

void update();
void mouse(int button, int state, int x, int y);
void reshape(int w, int h);
void display();
void init();

static GLfloat spin = 0.0;
static int spin_flag = 0;

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
	GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
	GLdouble eqn2[4] = {1.0, 0.0, 0.0, 0.0};
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glPushMatrix();
	
	glTranslatef(0.0, 0.0, -5.0);
	
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	
	glClipPlane(GL_CLIP_PLANE1, eqn2);
	glEnable(GL_CLIP_PLANE1);
	
	glRotatef(spin, 1.0, 0.0, 0.0);
	glutWireSphere(1.0, 20, 16);
	
	glPopMatrix();
	glFlush();
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
	
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		spin_flag = (spin_flag)?0:1;

		if(spin_flag)
			glutIdleFunc(update);
		else
			glutIdleFunc(NULL);		
	}
}
void update(){
	spin += 1.0;
	if(spin > 360.0)
		spin = spin - 360.0;
	
	glutPostRedisplay();
}
