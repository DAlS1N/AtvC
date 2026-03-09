#include <stdio.h>
#include <math.h> 

int main() {
    double x1, y1, x2, y2, distancia;

    if (scanf("%lf %lf", &x1, &y1) != 2) return 0;
    
    if (scanf("%lf %lf", &x2, &y2) != 2) return 0;

    distancia = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    printf("%.4f\n", distancia);

    return 0;
}