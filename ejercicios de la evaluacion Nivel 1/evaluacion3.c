#include <stdio.h>

int main()
{
    int valorMaximo=0, filas=0, i=0, j=0, espacio=0;
    
    printf("valor maximo:");
    fflush(stdout);
    scanf("%d", &valorMaximo);
    printf("filas:");
    fflush(stdout);
    scanf("%d", &filas);
    
    for(i=1; i<=filas; i++){
        if(i>1){
            for(espacio=1; espacio<i; espacio++){
                printf(" ");
            }
        }
        for(j=i; j<(valorMaximo+i); j++){
            printf("%d", j);
        }
        fflush(stdout);
        printf("\n");
        
    }
}
