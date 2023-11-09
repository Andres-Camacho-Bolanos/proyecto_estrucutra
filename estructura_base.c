#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para representar una actividad
typedef struct Actividad {
    char nombre[50];
    int valor;
    // Puedes agregar más detalles según sea necesario
} Actividad;

// Estructura para representar un día
typedef struct Dia {
    int numero;
    Actividad actividades[5]; // Lista de hasta 5 actividades por día
    int cantidadActividades;  // Número actual de actividades en el día
    struct Dia* siguiente;
} Dia;

// Implementación de una cola (FIFO)
typedef struct Cola {
    Dia* frente;
    Dia* final;
} Cola;

// Implementación de una pila (LIFO)
typedef struct Pila {
    Dia* tope;
} Pila;

// Funciones para operar con colas
Cola* crearCola() {
    Cola* nuevaCola = (Cola*)malloc(sizeof(Cola));
    nuevaCola->frente = nuevaCola->final = NULL;
    return nuevaCola;
}

void encolar(Cola* cola, Dia* nuevoDia) {
    if (cola->final == NULL) {
        cola->frente = cola->final = nuevoDia;
        return;
    }

    cola->final->siguiente = nuevoDia;
    cola->final = nuevoDia;
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
    nuevoDia->numero = numero; // Corregir aquí
    nuevoDia->siguiente = NULL;
    nuevoDia->cantidadActividades = 0; // Inicializar la cantidad de actividades
    return nuevoDia;
}

void agregarActividad(Dia* dia, Actividad nuevaActividad) {
    if (dia->cantidadActividades < 5) { // Verificar antes de incrementar
        dia->actividades[dia->cantidadActividades] = nuevaActividad;
        dia->cantidadActividades++;
    } else {
        printf("¡Límite de actividades alcanzado para el día %d!\n", dia->numero);
    }
}
// Estructura para representar un nodo en el grafo
typedef struct NodoGrafo {
    Dia* dia;
    struct NodoGrafo* siguiente;
} NodoGrafo;

// Estructura para representar un grafo
typedef struct Grafo {
    NodoGrafo* inicio;
} Grafo;

// Funciones para operar con grafos
Grafo* crearGrafo() {
    Grafo* nuevoGrafo = (Grafo*)malloc(sizeof(Grafo));
    nuevoGrafo->inicio = NULL;
    return nuevoGrafo;
}

void agregarDiaGrafo(Grafo* grafo, Dia* nuevoDia) {
    NodoGrafo* nuevoNodo = (NodoGrafo*)malloc(sizeof(NodoGrafo));
    nuevoNodo->dia = nuevoDia;
    nuevoNodo->siguiente = NULL;

    if (grafo->inicio == NULL) {
        grafo->inicio = nuevoNodo;
    } else {
        NodoGrafo* nodoActual = grafo->inicio;
        while (nodoActual->siguiente != NULL) {
            nodoActual = nodoActual->siguiente;
        }
        nodoActual->siguiente = nuevoNodo;
    }
}

// Estructura para representar un nodo en el árbol
typedef struct NodoArbol {
    Actividad actividad;
    struct NodoArbol* izquierda;
    struct NodoArbol* derecha;
} NodoArbol;

// Estructura para representar un árbol
typedef struct Arbol {
    NodoArbol* raiz;
} Arbol;

// Funciones para operar con árboles
Arbol* crearArbol() {
    Arbol* nuevoArbol = (Arbol*)malloc(sizeof(Arbol));
    nuevoArbol->raiz = NULL;
    return nuevoArbol;
}

NodoArbol* insertarActividadArbol(NodoArbol* raiz, Actividad nuevaActividad) {
    if (raiz == NULL) {
        NodoArbol* nuevoNodo = (NodoArbol*)malloc(sizeof(NodoArbol));
        nuevoNodo->actividad = nuevaActividad;
        nuevoNodo->izquierda = nuevoNodo->derecha = NULL;
        return nuevoNodo;
    }

    if (strcmp(nuevaActividad.nombre, raiz->actividad.nombre) < 0) {
        raiz->izquierda = insertarActividadArbol(raiz->izquierda, nuevaActividad);
    } else {
        raiz->derecha = insertarActividadArbol(raiz->derecha, nuevaActividad);
    }

    return raiz;
}

void imprimirActividadesDia(Dia* dia) {
    printf("Actividades para el día %d:\n", dia->numero);
    for (int i = 0; i < dia->cantidadActividades; ++i) {
        printf("- %s\n", dia->actividades[i].nombre);
    }
}

void intercambiar(NodoGrafo* a, NodoGrafo* b) {
    Dia* temp = a->dia;
    a->dia = b->dia;
    b->dia = temp;
}

void calcularOrdenRecomendado(Grafo* grafo) {
    if (grafo == NULL || grafo->inicio == NULL) {
        return;
    }

    NodoGrafo* nodoActual = grafo->inicio;
    while (nodoActual != NULL) {
        NodoGrafo* siguienteNodo = nodoActual->siguiente;

        while (siguienteNodo != NULL) {
            // Comparar valores de las actividades
            if (nodoActual->dia->actividades[0].valor < siguienteNodo->dia->actividades[0].valor) {
                intercambiar(nodoActual, siguienteNodo);
            }

            siguienteNodo = siguienteNodo->siguiente;
        }

        nodoActual = nodoActual->siguiente;
    }
}

void imprimirArbolEnOrden(NodoArbol* raiz) {
    if (raiz != NULL) {
        imprimirArbolEnOrden(raiz->izquierda);
        printf("Día %d\n", raiz->actividad.valor);  // Imprimir el número del día
        printf("- %s\n", raiz->actividad.nombre);   // Imprimir el nombre de la actividad
        imprimirArbolEnOrden(raiz->derecha);
    }
}

int main() {
    
    char actividadNombre[50];
    Actividad nuevaActividad; 
    int decision;
    
    // Crear una cola
    Cola* cola = crearCola();

    // Crear una pila
    Pila* pila = crearPila();

    // Crear un grafo
    Grafo* grafo = crearGrafo();

    // Crear un árbol
    Arbol* arbol = crearArbol();

    printf("Bienvenido. Ingrese cualquier caracter para continuar. Ingrese '0' para finalizar el programa:\n");
    scanf("%d", &decision);

    if (decision != 0) {
        int actividadActual = 1;

        // Agregar días a la cola, pila, grafo y árbol

    for (int i = 1; i <= 5; ++i) {
    Dia* nuevoDia = crearDia(i);

    printf("Ingrese las actividades del día '%d'. Ingrese 'fin' para salir:\n", i);
    int actividadActual = 1;

    while (actividadActual <= 5) {
        printf("Actividad %d: ", actividadActual);
        scanf("%s", actividadNombre);

        if (strcmp(actividadNombre, "fin") == 0) {
            break;
        }

        printf("Valor de prioridad: ");
        scanf("%d", &nuevaActividad.valor);

        Actividad nuevaActividad;
        strcpy(nuevaActividad.nombre, actividadNombre);

        agregarActividad(nuevoDia, nuevaActividad);
        actividadActual++;
    }
    
    // Ejemplo de recorrer el grafo
NodoGrafo* nodoActual = grafo->inicio;
while (nodoActual != NULL) {
    printf("Día %d\n", nodoActual->dia->numero);

    // Ejemplo de recorrer las actividades del día
    for (int j = 0; j < nodoActual->dia->cantidadActividades; ++j) {
        printf("- %s\n", nodoActual->dia->actividades[j].nombre);
    }

    nodoActual = nodoActual->siguiente;
}

// Calcular y mostrar el orden recomendado
calcularOrdenRecomendado(grafo);
        printf("Actividades en orden recomendado:\n");

        // Ejemplo de recorrer la cola después de ordenar
        Dia* diaOrdenado = desencolar(cola);
        while (diaOrdenado != NULL) {
            printf("Día %d\n", diaOrdenado->numero);

            // Ejemplo de recorrer las actividades del día después de ordenar
            for (int j = 0; j < diaOrdenado->cantidadActividades; ++j) {
                printf("- %s\n", diaOrdenado->actividades[j].nombre);
            }

            diaOrdenado = desencolar(cola);
        }

    // Operaciones con la cola
    encolar(cola, nuevoDia);

    // Operaciones con la pila
    apilar(pila, nuevoDia);

    // Operaciones con el grafo
    agregarDiaGrafo(grafo, nuevoDia);

    // Operaciones con el árbol
    arbol->raiz = insertarActividadArbol(arbol->raiz, nuevoDia->actividades[0]);
    
    }

    } else {
        printf("Hasta luego :)\n");
        return 0;
    }
}
