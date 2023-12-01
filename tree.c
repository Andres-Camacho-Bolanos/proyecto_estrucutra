#include <stdio.h>
#include "tree.h"

void info_trees(){
    printf("Los Árboles son las estructuras de datos más utilizadas, pero también una de las más complejas, Los Árboles se caracterizan por almacenar sus nodos en forma jerárquica y no en forma lineal como las listas ligadas, colas, pilas, etc., \n");
    printf("\nDatos importantes de los Árboles\n\nPara comprender mejor que es un árbol comenzaremos explicando cómo está estructurado.\n\n-Nodos: Se le llama Nodo a cada elemento que contiene un Árbol.\n\n-Nodo Raíz: Se refiere al primer nodo de un Árbol, Solo un nodo del Árbol puede ser la Raíz.\n\n-Nodo Padre: Se utiliza este término para llamar a todos aquellos nodos que tiene al menos un hijo.\n\n-Nodo Hijo: Los hijos son todos aquellos nodos que tiene un padre.\n\n-Nodo Hermano: Los nodos hermanos son aquellos nodos que comparte a un mismo padre en común dentro de la estructura.\n\n-Nodo Hoja: Son todos aquellos nodos que no tienen hijos, los cuales siempre se encuentran en los extremos de la estructura.\n\n-Nodo Rama: Estos son todos aquellos nodos que no son la raíz y que además tiene al menos un hijo.\n");
    printf("\nLos arboles a demás de los nodos tiene otras propiedades importantes que son utilizadas en diferentes ámbitos los cuales son:\n\nNivel: Nos referimos como nivel a cada generación dentro del árbol. Por ejemplo, cuando a un nodo hoja le agregamos un hijo, el nodo hoja pasa a ser un nodo rama, pero además el árbol crece una generación por lo que el Árbol tiene un nivel mas. Cada generación tiene un número de Nivel distinto que las demás generaciones.\n");
    printf("\nAltura: Le llamamos Altura al número máximo de niveles de un Árbol.\n");
    printf("\nPeso: Conocemos como peso a el número de nodos que tiene un Árbol. Este factor es importante porque nos da una idea del tamaño del árbol y el tamaño en memoria que nos puede ocupar en tiempo de ejecución (Complejidad Espacial en análisis de algoritmos.)\n");
    printf("\nOrden: El Orden de un árbol es el número máximo de hijos que puede tener un Nodo.\n");
    printf("\nGrado: El grado se refiere al número mayor de hijos que tiene alguno de los nodos del Árbol y está limitado por el Orden, ya que este indica el número máximo de hijos que puede tener un nodo.\n");

}
