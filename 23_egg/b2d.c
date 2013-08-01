#include<stdio.h>

int main(){
 char b[] = "Box2D";
 int i;
 int sum = 0; 
 for(i = 0; i < strlen(b); i++){
  printf("%c: %d\n",b[i],b[i]);
  sum += b[i];
 }
 printf("%d\n",sum);
 return 0;
}
