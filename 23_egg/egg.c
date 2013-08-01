//make an egg!!

#include <stdio.h>
#include <math.h>

#define SQR(x) (x * x)

int rad_x = 10;
int rad_y = 9;

int main(){
	float x_min = -rad_x;
	float x_max = rad_x;
	float dx = 1.0f;
	float x;
	float y;
	int count = 0;
	printf("GLfloat eggVert[] = {\n");
	for(x = x_min; x < x_max; x += dx){
		y = sqrt( (SQR(rad_y)* (SQR(rad_x) - SQR(x) ) ) / SQR(rad_x) * (2 + 0.1f * x));
		printf("%.5f, %.5f,\n",x,y*-1);
		count++;
	}
	for(x = x_max; x > x_min; x -= dx){
		y = sqrt( (SQR(rad_y)* (SQR(rad_x) - SQR(x) ) ) / SQR(rad_x) * (2 + 0.1f * x));
		printf("%.5f, %.5f,\n",x,y);
		count++;
	}
	printf("};\n");
	printf("GLint eggVertLen = %d;\n",count);
	return 0;
}