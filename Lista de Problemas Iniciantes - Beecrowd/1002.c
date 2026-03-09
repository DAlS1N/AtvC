#include <stdio.h>
 
int main() {
double n = 3.14159;
double raio,area;

scanf("%lf",&raio);

area = n*raio*raio; 

printf("A=%.4lf\n",area);
return 0;
}