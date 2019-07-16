#include <stdio.h>

#define N 7
#define M 13

int main (void){
    int fil=0, col=0;
    
    for(fil=0; fil<N; fil++){
        if(fil%2==0){
            for(col=0; col<M; col++){
                    {
                    if(fil==0 || fil==(N-1)){
                        if(col>=(((N-1)-fil)/2) && col<=((M-1)-(((N-1)-fil)/2))){
                            printf("*");
                        }
                        else{
                            printf(" ");
                        }
                        fflush(stdout);
                    }
                    else{
                        if(col==(((N-1)-fil)/2) || col==((M-1)-(((N-1)-fil)/2))){
                            printf("*");
                        }
                        else{
                            printf(" ");
                        }
                        fflush(stdout);
                    }
                }
                
            }
        }
        else{
            printf("\r\n");
            fflush(stdout);
        }
    }
}
