
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>

#define ROTATION_FACTOR 5.0f
#define PROJECTION_ZOOM 5.0f

#define RESOLUTION 20

#define RADIUS 2.0

typedef struct{
	GLfloat position[3];
	GLfloat color[3];
}CircleVertex;

GLfloat rotation[3];
CircleVertex sphere[RESOLUTION][RESOLUTION];
GLsizei size;

void init(){
	int i, j, k;
	float thetha, phi;
	for(i = 0; i < RESOLUTION; i++){
		phi = i*3.14/RESOLUTION;
		for(j = 0; j < RESOLUTION; j++){
			thetha = j*2*3.14/RESOLUTION;
			CircleVertex vertex;
			vertex.position[0] = RADIUS*cos(thetha)*sin(phi);
			vertex.position[1] = RADIUS*sin(thetha)*sin(phi);
			vertex.position[2] = RADIUS*cos(phi);
			
			vertex.color[0] = j%2?1.0:0.0;
			vertex.color[1] = j%2?0.0:1.0;
			vertex.color[2] = 0.0;
			
			sphere[i][j] = vertex;
		}
	}
	
	rotation[0] = rotation[1] = rotation[2] = 0.0;
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	size = 0;
}

void renderSphere(){
	
	glVertexPointer(3, GL_FLOAT, sizeof(CircleVertex), &sphere[0][0].position);
	glColorPointer(3, GL_FLOAT, sizeof(CircleVertex), &sphere[0][0].color);
	glDrawArrays(GL_POINTS, 0, size);
}

//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glPushMatrix();{
		glTranslatef(0.0, 0.0, -PROJECTION_ZOOM/2);
		glRotatef(rotation[0], 1, 0, 0);
		glRotatef(rotation[1], 0, 1, 0);
		glRotatef(rotation[2], 0, 0, 1);
			
		renderSphere();
			
	}glPopMatrix();
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
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
		case 'n':
			if(size < RESOLUTION * RESOLUTION)
				size++;
			else
				printf("done\n");
			break;
		case 'q':	rotation[2] -= ROTATION_FACTOR; break;
		case 'e':	rotation[2] += ROTATION_FACTOR; break;
		case 'a':	rotation[1] -= ROTATION_FACTOR; break;
		case 'd':	rotation[1] += ROTATION_FACTOR; break;
		case 'w':	rotation[0] += ROTATION_FACTOR; break;
		case 's':	rotation[0] -= ROTATION_FACTOR; break;
		case 13:	rotation[0] = rotation[1] = rotation[2] = 0.0; break;
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

