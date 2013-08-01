
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
	float v[4];
}Rect;
Rect make_rect(float x0, float y0, float x1, float y1) {
	Rect r = {x0, y0, x1, y1};
	return r;
}
Rect make_point(float x0, float y0) {
	Rect r = {x0, y0, x0+10, y0+10};
	return r;
}

typedef struct Data_{
	Rect rect;
	Rect point;
	struct Data_ *next;
}Data;
Data *make_data(Rect r, Rect p) {
	Data *d = (Data *)malloc(sizeof(Data));
	d->rect = r;
	d->point = p;
	d->next = 0;
	return d;
}

Data *g_data_head = 0;
Data *g_data_tail = 0;

int g_time;

void read_data(char *file) {
	FILE *fp = fopen(file, "r");
	int ch;
	char line[1024];
	char *lp = &line[0];
	int l_no = -1;
	char data[5][1024];
	
	while ((ch = fgetc(fp)) != EOF) {
		switch (ch) {
			case '\n':{
				*lp = '\0';
				lp = &line[0];
				if (strcmp(line, "FishHit:") == 0){
					l_no = 0;
				} else if (l_no >= 0) {
					strcpy(data[l_no++], line);

					if (l_no == 5) {
						l_no = -1;
						float val[7];
						sscanf(data[0], "A: { %f, %f }",&val[0], &val[1]);
						sscanf(data[3], "D: { %f, %f }",&val[2], &val[3]);
						sscanf(data[4], "{ %f, %f, %f }",&val[4], &val[5], &val[6]);
						printf("%s %s %s = %.2f %.2f %.2f %.2f %.2f %.2f %.2f \n",data[0],data[3],data[4],val[0],val[1],val[2],val[3],val[4],val[5],val[6]);
						Data *d = make_data(make_rect(val[0],val[1],val[2],val[3]), make_point(val[4],val[5]));
						if (g_data_head) {
							g_data_tail->next = d;
							g_data_tail = d;
						} else {
							g_data_head = g_data_tail = d;
						}
					}
				}
								
			}break;

			default: *lp++ = ch;
				break;
		}
	}

	fclose(fp);
	g_data_tail = g_data_head;
}
void print_data() {
	printf("{%.2f,%.2f,%.2f,%.2f}\n",g_data_tail->rect.v[0],g_data_tail->rect.v[1],g_data_tail->rect.v[2],g_data_tail->rect.v[3]);
	printf("{%.2f,%.2f}\n",g_data_tail->point.v[0],g_data_tail->point.v[1]);
}

void next(){
	int t = glutGet(GLUT_ELAPSED_TIME);
	printf("%d\n",t);
	if(t - g_time > 100) {
		g_data_tail = (g_data_tail->next) ? g_data_tail->next : g_data_head;
		print_data();
		glutPostRedisplay();
		g_time = t;
	}
}

/*callback for mouse events*/
void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) {
				glutIdleFunc(next);
			} else {
				glutIdleFunc(NULL);				
			}
			break;
			
		case GLUT_MIDDLE_BUTTON:
			if(state == GLUT_DOWN)
				glutIdleFunc(NULL);
			
		default:
			break;
	}
}

/*callback for window resize*/
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-240, 240, -160, 160, -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//refresh screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
	glColor3f(0, 1, 0);
	
	//A: { 66.75058746, -27.50196838 }
	//B: { 146.7505798, -27.50196838 }
	//C: { 66.75058746, 25.49803162 }
	//D: { 146.7505798, 25.49803162 }
	
	Data *d = g_data_tail;
	Rect r = d->rect;
	Rect p = d->point;
	
	glRectf(r.v[0],r.v[1],r.v[2],r.v[3]);
	glColor3f(1,0,0);
	glRectf(p.v[0],p.v[1],p.v[2],p.v[3]);
	glPopMatrix();
	
	glutSwapBuffers();
}

void init(){
	glClearColor(0, 0 , 0, 0);
	glShadeModel(GL_FLAT);
}

int main(int argc, char** argv){
	
	if (argc != 2) {
		printf("Usage: %s <filename>\n",argv[0]);
		return 0;
	}


	//create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(480, 320);
	glutInitWindowPosition(100, 500);
	glutCreateWindow(argv[0]);
	
	//init
	read_data(argv[1]);
	print_data();
	g_time = glutGet(GLUT_ELAPSED_TIME);
	init();
	
	//register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	
	//the loop
	glutMainLoop();
	
	return 0;
}
