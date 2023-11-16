#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void ordSeleccion(Actividad actividades[], int n) {
    int indiceMayor, i, j;
    for (i = 0; i < n - 1; i++) {
        indiceMayor = i;
        for (j = i + 1; j < n; j++) {
            if (actividades[j].valor > actividades[indiceMayor].valor) {
                indiceMayor = j;
            }
        }
        if (i != indiceMayor) {
            Actividad aux = actividades[i];
            actividades[i] = actividades[indiceMayor];
            actividades[indiceMayor] = aux;
        }
    }
}

int main() {
    char actividadNombre[50];
    Actividad nuevaActividad;
    int decision;
    int n;

    // Crear una cola
    Cola* cola = crearCola();

    // Crear una pila
    Pila* pila = crearPila();

    printf("Bienvenido. Ingrese cualquier número para continuar.\nIngrese '0' o cualquier otro caracter para finalizar el programa:\n");
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
                scanf("%d", &n);

                nuevaActividad.valor = n;
                strcpy(nuevaActividad.nombre, actividadNombre);

                agregarActividad(nuevoDia, nuevaActividad);
                actividadActual++;
                }


            // Operaciones con la cola
            encolar(cola, nuevoDia);

            // Operaciones con la pila
            apilar(pila, nuevoDia);

        // Calcular y mostrar el orden recomendado
        double valores[5];
        Dia* diaActual = cola->frente;
        for (int i = 0; i < 5 && diaActual != NULL; i++) {
            valores[i] = diaActual->actividades[0].valor;
            diaActual = diaActual->siguiente;
        }
        ordSeleccion(nuevoDia->actividades, nuevoDia->cantidadActividades);

        printf("Actividades en orden recomendado:\n");
        for (int i = 0; i < 5; i++) {
            diaActual = cola->frente;
            while (diaActual != NULL) {
                if (diaActual->actividades[0].valor == valores[i]) {
                    imprimirActividadesDia(diaActual);
                    break;
                }
                diaActual = diaActual->siguiente;
            }
        }
    } 
    
        
  } else {
        printf("Hasta luego :)\n");
        
  }
       return 0; 
 
    
}
  
  




////// Utilizar el algoritmo de dijkstra para calcular el día más desocupado implementando el uso de grafos
////// Implementar árboles para búsqueda binaria de actividades que se repitan en varios días

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

void ordSeleccion(double a[], int n) {
    int indiceMenor, i, j;
    for (i = 0; i < n - 1; i++) {
        indiceMenor = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[indiceMenor]) {
                indiceMenor = j;
            }
        }
        if (i != indiceMenor) {
            double aux = a[i];
            a[i] = a[indiceMenor];
            a[indiceMenor] = aux;
        }
    }
}

int main() {
    char actividadNombre[50];
    Actividad nuevaActividad;
    int decision;
    int n;

    // Crear una cola
    Cola* cola = crearCola();

    // Crear una pila
    Pila* pila = crearPila();

    // Crear un grafo
    Grafo* grafo = crearGrafo();

    // Crear un árbol
    Arbol* arbol = crearArbol();

    printf("Bienvenido. Ingrese cualquier número para continuar.\nIngrese '0' o cualquier otro caracter para finalizar el programa:\n");
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
                scanf("%d", &n);

                nuevaActividad.valor = n;
                strcpy(nuevaActividad.nombre, actividadNombre);

                agregarActividad(nuevoDia, nuevaActividad);
                actividadActual++;
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

        // Calcular y mostrar el orden recomendado
        double valores[5];
        Dia* diaActual = cola->frente;
        for (int i = 0; i < 5 && diaActual != NULL; i++) {
            valores[i] = diaActual->actividades[0].valor;
            diaActual = diaActual->siguiente;
        }
        ordSeleccion(valores, 5);

        printf("Actividades en orden recomendado:\n");
        for (int i = 0; i < 5; i++) {
            diaActual = cola->frente;
            while (diaActual != NULL) {
                if (diaActual->actividades[0].valor == valores[i]) {
                    imprimirActividadesDia(diaActual);
                    break;
                }
                diaActual = diaActual->siguiente;
            }
        }
    } else {
        printf("Hasta luego :)\n");
    }

    return 0;
}




////// Utilizar el algoritmo de dijkstra para calcular el día más desocupado
//// Utilizar el arbol binario para búsqueda de actividades específicas que ingresó el usuario
