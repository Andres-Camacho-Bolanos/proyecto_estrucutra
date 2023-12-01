#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graphs.h"
#include "tree.h"


// Estructura para representar una actividad
typedef struct Actividad {
    char nombre[50];
    int valor;
} Actividad;

// Estructura para representar un día
typedef struct Dia {
    int numero;
    Actividad actividades[5];
    int cantidadActividades;
    struct Dia* siguiente;
} Dia;

// Estructura para representar un grafo
typedef struct Grafo {
    Dia* nodos[5];
    int matrizAdyacencia[5][5];
} Grafo;

// Implementación de una cola (FIFO)
typedef struct Cola {
    Dia* frente;
    Dia* final;
} Cola;

// Implementación de una pila (LIFO)
typedef struct Pila {
    Dia* tope;
} Pila;

typedef struct Nodo {
    Actividad actividad;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

// Funciones para operar con colas
Cola* crearCola() {
    Cola* nuevaCola = (Cola*)malloc(sizeof(Cola));
    nuevaCola->frente = nuevaCola->final = NULL;
    return nuevaCola;
}

void encolar(Cola* cola, Dia* nuevoDia) {
    if (cola->final == NULL) {
        cola->frente = cola->final = nuevoDia;
    } else {
        cola->final->siguiente = nuevoDia;
        cola->final = nuevoDia;
    }
}

Dia* desencolar(Cola* cola) {
    if (cola->frente == NULL) {
        return NULL;
    }

    Dia* temp = cola->frente;
    cola->frente = cola->frente->siguiente;

    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    return temp;
}

// Funciones para operar con pilas
Pila* crearPila() {
    Pila* nuevaPila = (Pila*)malloc(sizeof(Pila));
    nuevaPila->tope = NULL;
    return nuevaPila;
}

void apilar(Pila* pila, Dia* nuevoDia) {
    nuevoDia->siguiente = pila->tope;
    pila->tope = nuevoDia;
}

Dia* desapilar(Pila* pila) {
    if (pila->tope == NULL) {
        return NULL;
    }

    Dia* temp = pila->tope;
    pila->tope = pila->tope->siguiente;

    return temp;
}

// Funciones para operar con listas enlazadas
Dia* crearDia(int numero) {
    Dia* nuevoDia = (Dia*)malloc(sizeof(Dia));
    nuevoDia->numero = numero;
    nuevoDia->siguiente = NULL;
    nuevoDia->cantidadActividades = 0;
    return nuevoDia;
}

void agregarActividad(Dia* dia, Actividad nuevaActividad) {
    if (dia->cantidadActividades < 5) {
        dia->actividades[dia->cantidadActividades] = nuevaActividad;
        dia->cantidadActividades++;
    } else {
        printf("¡Límite de actividades alcanzado para el día %d!\n", dia->numero);
    }
}

void imprimirActividadesDia(Dia* dia) {
    printf("Actividades para el día %d:\n", dia->numero);
    for (int i = 0; i < dia->cantidadActividades; ++i) {
        printf("- %s (Valor: %d)\n", dia->actividades[i].nombre, dia->actividades[i].valor);
    }
}

// Función de comparación para la ordenación por selección
int compararValores(const void* a, const void* b) {
    return (*(double*)b - *(double*)a);
}

// Función para ordenar días según sus valores
void ordenarDias(Cola* cola, int diasOrdenados[]) {
    double valores[5];
    Dia* diaActual = cola->frente;
    
    for (int i = 0; i < 5 && diaActual != NULL; i++) {
        valores[i] = diaActual->actividades[0].valor;
        diaActual = diaActual->siguiente;
    }

    qsort(valores, 5, sizeof(double), compararValores);

    for (int i = 0; i < 5; i++) {
        Dia* diaActual = cola->frente;
        while (diaActual != NULL) {
            if (diaActual->actividades[0].valor == valores[i]) {
                diasOrdenados[i] = diaActual->numero;
                break;
            }
            diaActual = diaActual->siguiente;
        }
    }
}

Grafo* crearGrafo() {
    Grafo* nuevoGrafo = (Grafo*)malloc(sizeof(Grafo));
    for (int i = 0; i < 5; i++) {
        nuevoGrafo->nodos[i] = NULL;
        for (int j = 0; j < 5; j++) {
            nuevoGrafo->matrizAdyacencia[i][j] = 0;
        }
    }
    return nuevoGrafo;
}

void agregarRelacion(Grafo* grafo, Dia* dia1, Dia* dia2) {
    // Agregar relación bidireccional entre los días
    int indiceDia1 = dia1->numero - 1;
    int indiceDia2 = dia2->numero - 1;
    grafo->matrizAdyacencia[indiceDia1][indiceDia2] = 1;
    grafo->matrizAdyacencia[indiceDia2][indiceDia1] = 1;
}

Nodo* insertar(Nodo* nodo, Actividad actividad) {
    // Si el árbol está vacío, asignar un nuevo nodo dirección
    if (nodo == NULL) {
        Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
        nuevoNodo->actividad = actividad;
        nuevoNodo->izquierdo = nuevoNodo->derecho = NULL;
        return nuevoNodo;
    }

    // Si el árbol no está vacío, descender por el árbol
    if (actividad.valor < nodo->actividad.valor)
        nodo->izquierdo  = insertar(nodo->izquierdo, actividad);
    else if (actividad.valor > nodo->actividad.valor)
        nodo->derecho = insertar(nodo->derecho, actividad);

    return nodo;
}

Nodo* buscar(Nodo* raiz, char* nombre) {
    // Base Cases: la raíz es nula o la clave está presente en la raíz
    if (raiz == NULL || strcmp(raiz->actividad.nombre, nombre) == 0)
        return raiz;

    // La clave es mayor que la raíz
    if (strcmp(raiz->actividad.nombre, nombre) < 0)
        return buscar(raiz->derecho, nombre);

    // La clave es menor que la raíz
    return buscar(raiz->izquierdo, nombre);
}

// Función para realizar búsqueda binaria en un arreglo de actividades
int busquedaBinaria(Actividad actividades[], int n, char* nombre) {
    int izquierda = 0, derecha = n - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        int comparacion = strcmp(actividades[medio].nombre, nombre);

        // Si se encuentra la actividad
        if (comparacion == 0) {
            return medio;
        }
        // Si la actividad está en la mitad derecha
        else if (comparacion < 0) {
            izquierda = medio + 1;
        }
        // Si la actividad está en la mitad izquierda
        else {
            derecha = medio - 1;
        }
    }
    // Si la actividad no se encuentra
    return -1;
}

// Algoritmo de Dijkstra para encontrar el día más desocupado
int dijkstra(Grafo* grafo, int inicio) {
    int distancia[5];
    int visitado[5] = {0};  // Inicializar todos los nodos como no visitados
    int minDistancia, siguienteNodo;

    // Inicializar distancias desde el nodo inicial
    for (int i = 0; i < 5; i++) {
        distancia[i] = grafo->matrizAdyacencia[inicio][i];
    }

    visitado[inicio] = 1;  // Marcar el nodo inicial como visitado

    for (int i = 1; i < 5; i++) {
        minDistancia = 9999;  // Un valor grande que represente infinito
        // Encontrar el nodo no visitado con la distancia mínima
        for (int j = 0; j < 5; j++) {
            if (!visitado[j] && distancia[j] < minDistancia) {
                minDistancia = distancia[j];
                siguienteNodo = j;
            }
        }

        visitado[siguienteNodo] = 1;  // Marcar el nodo como visitado

        // Actualizar las distancias a través del nodo recién visitado
        for (int j = 0; j < 5; j++) {
            if (!visitado[j] && (minDistancia + grafo->matrizAdyacencia[siguienteNodo][j]) < distancia[j]) {
                distancia[j] = minDistancia + grafo->matrizAdyacencia[siguienteNodo][j];
            }
        }
    }

    // Encontrar el nodo con la máxima distancia, que representará el día más desocupado
    int maxDistancia = 0;
    int diaMasDesocupado = 0;
    for (int i = 0; i < 5; i++) {
        if (distancia[i] > maxDistancia) {
            maxDistancia = distancia[i];
            diaMasDesocupado = i;
        }
    }

    return diaMasDesocupado + 1;  // Sumar 1 para obtener el número de día
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Enter() {
    printf("\nPresiona Enter para volver al menú...\n\n");
    limpiarBuffer();  // Limpia el búfer del teclado
    getchar();      // Espera a que se presione Enter
}

int main() {
    
    char actividadNombre[50];
    Actividad nuevaActividad;
    Cola* cola = crearCola();
    Grafo* grafo = crearGrafo();
    Dia* nuevoDia;
    int opcion=0;
    
     while (opcion != 7){ 
    
    printf("Bienvenido a nuestro humilde programa. Esperamos que les guste :D\n\n"); 
    printf("Menú principal:\n");
    printf("\nSeleccione la opción deseada, eligiendo el número correspondiente.\n");
    printf("\n1- Iniciar programa.\n");
    printf("\n2- Archivo de Pilas.\n");
    printf("\n3- Archivo de Colas.\n");
    printf("\n4- Archivo de Árboles.\n");
    printf("\n5- Archivo de Grafos.\n");
    printf("\n6- Archivo de Listas.\n");
    printf("\n7- Salir del programa.\n\n");
    
    printf("Opción: ");scanf("%i",&opcion);
    printf("\n");
     
    switch (opcion){
        
    case 1:

        for (int i = 1; i <= 5; ++i) {
            nuevoDia = crearDia(i);

            printf("Ingrese las actividades del día '%d'.\n", i);

            int actividadActual = 1;

            while (actividadActual <= 5) {
                printf("Actividad %d: ", actividadActual);
                scanf("%s", actividadNombre);

                if (strcmp(actividadNombre, "fin") == 0) {
                    break;
                }

                printf("Valor de prioridad: ");
                scanf("%d", &nuevaActividad.valor);

                strcpy(nuevaActividad.nombre, actividadNombre);

                agregarActividad(nuevoDia, nuevaActividad);
                actividadActual++;
            }

            // Operaciones con la cola
            encolar(cola, nuevoDia);

            // Agregar día al grafo
            grafo->nodos[i - 1] = nuevoDia;
        }

        // Calcular y mostrar el orden recomendado
        printf("Actividades en orden recomendado:\n");

        // Array para almacenar los días ordenados
        int diasOrdenados[5];

        // Ordenar los días según los valores
        ordenarDias(cola, diasOrdenados);

        // Imprimir las actividades según el orden recomendado
        for (int i = 0; i < 5; i++) {
            Dia* diaActual = cola->frente;
            while (diaActual != NULL) {
                if (diaActual->numero == diasOrdenados[i]) {
                    imprimirActividadesDia(diaActual);
                    break;
                }
                diaActual = diaActual->siguiente;
            }
        }

        // Búsqueda binaria
        char actividadBuscada[50];
        printf("\nIngrese el nombre de la actividad que desea buscar: ");
        scanf("%s", actividadBuscada);

        // Buscar la actividad en los días
        Dia* diaActual = cola->frente;
        int encontrado = 0;
        while (diaActual != NULL) {
            int indice = busquedaBinaria(diaActual->actividades, diaActual->cantidadActividades, actividadBuscada);
            if (indice != -1) {
                printf("La actividad '%s' fue encontrada en el día %d.\n", actividadBuscada, diaActual->numero);
                encontrado = 1;
            }

            diaActual = diaActual->siguiente;
        }

        if (!encontrado) {
            printf("La actividad '%s' no fue encontrada en ningún día.\n", actividadBuscada);
        }

        // Establecer relaciones entre días
        agregarRelacion(grafo, grafo->nodos[0], grafo->nodos[1]);
        agregarRelacion(grafo, grafo->nodos[0], grafo->nodos[3]);

        // Calcular el día más desocupado utilizando Dijkstra
        int diaMasDesocupado = dijkstra(grafo, 0);
        printf("\nEl día más desocupado es: %d\n", diaMasDesocupado);
        
        Enter();
        break;
    
    
    case 2:
        info_stack();
        Enter();
        break;
    
    case 3:
        info_queue();
        Enter();
        break;
    
    case 4:
        info_list();
        Enter();
        break;

    case 5:
        info_graphs();
        Enter();
        break;
    
    case 6:
        info_trees();
        Enter();
        break;
        
    case 7:
        printf("Hasta luego :)\n");
        break;
    
    default:
        printf("Opción no válida\n");
        Enter();
        break;
   }

    fflush(stdin);
 }
   
    return 0;
    
}
