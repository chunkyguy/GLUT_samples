
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define ROTATION_FACTOR 5.0
#define EDGE 0.5f
#define VERTEX_COUNT 8
#define FACE_POINTS 4

typedef struct{
	GLfloat x, y, z;
}vec3;

vec3 vec3Make(GLfloat some_x, GLfloat some_y, GLfloat some_z){
	vec3 vec;
	vec.x = some_x; vec.y = some_y; vec.z = some_z;
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

typedef enum{ kFaceLeft = 0, kFaceRight, kFaceBottom, kFaceTop, kFaceFront, kFaceBack, kFaceTotal} kFace;

typedef struct{
	GLubyte facePoint[FACE_POINTS];
}FaceData;

FaceData FaceDataMake(GLubyte one, GLubyte two, GLubyte three, GLubyte four){
	FaceData aFace;
	int i = 0;
	aFace.facePoint[i++] = one;	aFace.facePoint[i++] = two;	aFace.facePoint[i++] = three;	aFace.facePoint[i++] = four;
	return aFace;
}

static GLuint vertexBuffer_;
static GLuint indexBuffer_;
static vec3 rotation_;

void init(){	
	int i = 0;
	VertexData vertex[VERTEX_COUNT];
	FaceData face[kFaceTotal];
	
	vertex[i++] = VertexDataMake(vec3Make(-EDGE, -EDGE, -EDGE),	vec3Make(0.0, 0.0, 0.0));
	vertex[i++] = VertexDataMake(vec3Make(EDGE, -EDGE, -EDGE),	vec3Make(1.0, 0.0, 0.0));
	vertex[i++] = VertexDataMake(vec3Make(	EDGE, EDGE, -EDGE),	vec3Make(1.0, 1.0, 0.0));
	vertex[i++] = VertexDataMake(vec3Make(	-EDGE, EDGE, -EDGE),vec3Make(0.0, 1.0, 0.0));
	vertex[i++] = VertexDataMake(vec3Make(	-EDGE, -EDGE, EDGE),vec3Make(0.0, 1.0, 1.0));
	vertex[i++] = VertexDataMake(vec3Make(	EDGE, -EDGE, EDGE),	vec3Make(0.0, 0.0, 1.0));
	vertex[i++] = VertexDataMake(vec3Make(	EDGE, EDGE, EDGE),	vec3Make(1.0, 0.0, 1.0));
	vertex[i++] = VertexDataMake(vec3Make(	-EDGE, EDGE, EDGE),	vec3Make(1.0, 1.0, 1.0));
	

	face[kFaceLeft] = FaceDataMake(0, 4, 7, 3);
	face[kFaceRight] = FaceDataMake(1, 2, 6, 5);
	face[kFaceBottom] = FaceDataMake(0, 1, 5, 4);
	face[kFaceTop] = FaceDataMake(3, 7, 6, 2);
	face[kFaceFront] = FaceDataMake(4, 5, 6, 7);
	face[kFaceBack] = FaceDataMake(0, 3, 2, 1);
	
	rotation_ = vec3Make(30.0, 30.0, 0.0);
	
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	
	glGenBuffers(1, &vertexBuffer_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_COUNT*sizeof(vertex[0]), vertex, GL_STATIC_DRAW);
	
	glGenBuffers(1, &indexBuffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, kFaceTotal*sizeof(face[0]), face, GL_STATIC_DRAW);
}

void drawFace(kFace face){
		
}

void drawCube(){
	kFace face = kFaceLeft;
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexData), 0);
	glColorPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid *)sizeof(vec3));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);

	for(face = kFaceLeft; face < kFaceTotal; face++){
		glDrawElements(GL_TRIANGLE_FAN, FACE_POINTS, GL_UNSIGNED_BYTE, (face == kFaceLeft)?0:(FaceData *)sizeof(FaceData)+(face-1));	
	}
}

//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();{
		glTranslatef(0.0, 0.0, -5.0);
		glRotatef(rotation_.x, 1, 0, 0);
		glRotatef(rotation_.y, 0, 1, 0);
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
			
		drawCube();
			
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
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
	
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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

