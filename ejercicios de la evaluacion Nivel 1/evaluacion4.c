#include <stdio.h>

int factorial(int nro);

int main()
{
    int i=0, j=0, n=0, numero=0;
    
    printf("numero de filas\r\n");
    scanf("%d", &n);
    
    for(i=0; i<n; i++){
        for(j=0; j<=i; j++){
            numero = (factorial(i))/(factorial(j)*factorial(i-j));
            printf("%d", numero);
            printf(" ");
            fflush(stdout);
        }
        printf("\n");
    }
    
}

int factorial(int num){
    
    int i=num;
    int fact=1;
    for(i=num;i>0;i--)
    {
        fact*=i;
    }
    return fact;
}
