
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>

#define RESOLUTION 60
#define VERTEX_COUNT 55
#define PROJECTION_ZOOM 5.0f
#define M_TAU 6.283185f

typedef struct {
	GLfloat x, y, z;
}Vertex;

Vertex Vertex2Make(GLfloat some_x, GLfloat some_y){
	Vertex v;
	v.x = some_x; v.y = some_y; v.z = 0.0f;
	return v;
}

Vertex Vertex3Make(GLfloat some_x, GLfloat some_y, GLfloat some_z){
	Vertex v;
	v.x = some_x; v.y = some_y; v.z = some_z;
	return v;
}

static GLfloat ROTATION_FACTOR = 5.0f;
static GLuint vertexBuffer_;
Vertex rotation_;

void init(){
	int i;
	float radius = 3.0;
	Vertex *vertex = (Vertex *)malloc(sizeof(Vertex)*VERTEX_COUNT);
	for(i = 0; i < VERTEX_COUNT; i++){
		float theta = ((float)i * M_TAU)/(float)RESOLUTION;
		vertex[i] = Vertex2Make(cos(theta)*radius, sin(theta)*radius);
	}
	

	rotation_ = Vertex3Make(30.0, 30.0, 0.0);
	
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	glGenBuffers(1, &vertexBuffer_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_COUNT*sizeof(vertex[0]), vertex, GL_STATIC_DRAW);
	
	free(vertex);
}

void renderCurve(){
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	
	glDrawArrays(GL_LINE_STRIP, 0, VERTEX_COUNT);
}

//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();{
		glTranslatef(0.0, 0.0, -PROJECTION_ZOOM/2);
		glRotatef(rotation_.x, 1, 0, 0);
		glRotatef(rotation_.y, 0, 1, 0);
	
		glEnableClientState(GL_VERTEX_ARRAY);
			
		renderCurve();
			
		glDisableClientState(GL_VERTEX_ARRAY);
		
	}glPopMatrix();
	
	glFlush();
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-PROJECTION_ZOOM, PROJECTION_ZOOM, -PROJECTION_ZOOM, PROJECTION_ZOOM, 0.1, PROJECTION_ZOOM);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){ 
		case 27:exit(0); break;
		case 'a':rotation_.y -= ROTATION_FACTOR; break;
		case 'd': rotation_.y += ROTATION_FACTOR; break;
		case 'w': rotation_.x += ROTATION_FACTOR; break;
		case 's': rotation_.x -= ROTATION_FACTOR; break;
		case 13: rotation_ = Vertex3Make(0.0, 0.0, 0.0); break;
	}
	glutPostRedisplay();
}

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
	glutKeyboardFunc(keyboard);
	
	//the loop
	glutMainLoop();	
	return 0;
}

