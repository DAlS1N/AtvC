#include <stdio.h>

double media(double a, double b, double c){
    return (a + b + c) / 3;
}

int main() {
    char nome[50];  
    int validacao;
    int numeros[5];
    int maior = 0;
    int soma = 0;
    double n1,n2,n3;

    printf("Digite seu nome: \n");
    fgets(nome, 50, stdin);

    printf("Digote sua idade: \n");
    scanf("%d", &validacao);

    if (validacao >= 0){
       
        printf("Digite as 3 notas: \n");
        scanf("%lf %lf %lf",&n1,&n2,&n3);
        double m = media(n1,n2,n3);


        printf("Sua media e: \n");
        if (m >= 7) printf("Aprovado\n");
        else if( m >= 5 ) printf("Recuperacao\n");
        else printf("Reprovado\n");


        printf("Qual e o maior numero ?: \n");
        for (int i = 0; i < 5; i++)
        {
        printf("Digite o %d Numero: ", i);
        scanf("%d", &numeros[i]);
        if (i == 0 || numeros[i] >= maior){
            maior = numeros[i];
        }
        soma = numeros[i] + soma;
        }
        
        printf("O maior numero: %d",maior);
        printf("\nA soma dos 5 numeros: %d",soma);
        printf("\nA media e: %.2lf",m);


        return 0;

    }else{
        
        printf("Idade Invalida\n");
        return 0;
    
    }

}

