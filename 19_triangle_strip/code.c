
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>

#define ROTATION_FACTOR 5.0f
#define VERTEX_COUNT 4
#define FACE_COUNT 9
#define PROJECTION_ZOOM 5.0f

typedef struct{
	GLfloat x, y, z;
}vec3;

vec3 vec3Make(GLfloat some_x, GLfloat some_y, GLfloat some_z){
	vec3 vec;
	vec.x = some_x; vec.y = some_y; vec.z = some_z;
	return vec;
}

vec3 vec2Make(GLfloat some_x, GLfloat some_y){
	vec3 vec;
	vec.x = some_x; vec.y = some_y; vec.z = 0.0f;
	return vec;
}

typedef struct{
	vec3 position;
	vec3 color;
}VertexData;

VertexData VertexDataMake(vec3 some_position, vec3 some_color){
	VertexData data;
	data.position = some_position; data.color = some_color;
	return data;
}

static GLuint vertexBuffer_;
static GLuint indexBuffer_;
static vec3 rotation_;



void init(){
	
	VertexData vertex[VERTEX_COUNT] = {
		VertexDataMake(vec2Make(-2, -2),	vec3Make(1.0, 0.0, 1.0)),
		VertexDataMake(vec2Make(2, -2),		vec3Make(1.0, 1.0, 0.0)),
		VertexDataMake(vec2Make(-1, 2),		vec3Make(0.0, 0.0, 0.0)),
		VertexDataMake(vec2Make(1, 2),		vec3Make(1.0, 0.0, 1.0)),		
	};
	GLubyte faceData[FACE_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

	rotation_ = vec3Make(30.0, 30.0, 0.0);
	
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	glGenBuffers(1, &vertexBuffer_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_COUNT*sizeof(vertex[0]), vertex, GL_STATIC_DRAW);
	
	glGenBuffers(1, &indexBuffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, FACE_COUNT*sizeof(faceData[0]), faceData, GL_STATIC_DRAW);
}

void testTriangleFan(){
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexData), 0);
	glColorPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid *)sizeof(vec3));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);
	glDrawElements(GL_LINE_STRIP, FACE_COUNT, GL_UNSIGNED_BYTE, 0);
	
}

void renderGrid(){
	GLfloat grid2x2[2][2][3] = {
		{{-2.0, -2.0, 0.0}, {4.0, -2.0, 0.0}},
		{{-2.0, 3.0, 0.0}, {3.0, 4.0, 0.0}}
	};
	
	glEnable(GL_MAP2_VERTEX_3);
	
	glMap2f(GL_MAP2_VERTEX_3,
			0.0, 1.0,  /* U ranges 0..1 */
			3,         /* U stride, 3 floats per coord */
			2,         /* U is 2nd order, ie. linear */
			0.0, 1.0,  /* V ranges 0..1 */
			2 * 3,     /* V stride, row is 2 coords, 3 floats per coord */
			2,         /* V is 2nd order, ie linear */
			grid2x2);  /* control points */
	
	glMapGrid2f(
				5, 0.0, 1.0,
				6, 0.0, 1.0);
	
	glEvalMesh2(GL_LINE,
				0, 5,   /* Starting at 0 mesh 5 steps (rows). */
				0, 6);  /* Starting at 0 mesh 6 steps (columns). */
	
	glDisable(GL_MAP2_VERTEX_3);
}
//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();{
		glTranslatef(0.0, 0.0, -PROJECTION_ZOOM/2);
		glRotatef(rotation_.x, 1, 0, 0);
		glRotatef(rotation_.y, 0, 1, 0);
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
			
		//testTriangleFan();
		renderGrid();
			
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		
	}glPopMatrix();
	
	glutSwapBuffers();
	//glFlush();
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
		case 13: rotation_ = vec3Make(0.0, 0.0, 0.0); break;
	}
	glutPostRedisplay();
}

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

