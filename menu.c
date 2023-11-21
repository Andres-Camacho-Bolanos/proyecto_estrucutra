#include <stdio.h>

int opcion=0;

void seleccion(){

    printf("Menú\n\n");
    printf("Seleccionar la opción deseada, eligiendo el número correspondiente\n");
    printf("\n1-Iniciar programa\n");
    printf("\n2-Pilas\n");
    printf("\n3-Colas\n");
    printf("\n4-Arboles\n");
    printf("\n5-Grafos\n");
    printf("\n6-Listas\n");
    printf("\n");
    printf(":");scanf("%i",&opcion);
    
    
    switch (opcion)
    {
    case 1:
        printf("\n1");
        break;
    
    
    case 2:
        printf("2");
        break;
    
    case 3:
        printf("3");
        break;
    
    case 4:
        printf("4");
        break;

    case 5:
        printf("5");
        break;
    
    case 6:
        printf("6");
        break;
    
    default:
        printf("7");
        break;
    }
}




int main(){

    seleccion();
    return 0;
}