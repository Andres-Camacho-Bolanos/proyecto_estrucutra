#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Actividad {
    int id;
    char nombre[100];
    int prioridad;
} Actividad;

typedef struct Node {
    Actividad dato;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Grafo {
    int numNodos;
    int** matrizAdyacencia;
} Grafo;

typedef struct Alarma {
    Actividad actividad;
    // Add other fields related to the alarm if needed
} Alarma;

typedef struct Pila {
    Node* top;
    int capacidad;
    int tamano;
} Pila;

typedef struct Cola {
    Alarma* elementos;
    int frente, fin;
    int capacidad;
} Cola;

typedef struct TreeNode {
    int hora;
    Node* actividades;
    struct TreeNode* izquierda;
    struct TreeNode* derecha;
} TreeNode;

// Function declarations
Cola* inicializarCola(int capacidad);
int estaVacia(Cola* cola);
void eliminarAlarma(Cola* cola);
void pop(Pila* pila);
void aumentarHora(int* hora);
Node* agregarActividad(Node* head, Actividad actividad);
void sistemaAlarma(Cola* colaAlarmas, Actividad actividad);
Node* agregarActividad(Node* head, Actividad actividad);
Grafo* crearGrafo(Actividad actividades[], int numActividades);
void topologicalSortUtil(Grafo* grafo, int v, int visitado[], Node* actividades[], int* index);
Node** topologicalSort(Grafo* grafo, Node* actividades[], int numActividades);
TreeNode* relojCuentafinal(TreeNode* arbolHoras, Actividad actividad, int hora);
void agregarActividadProgramada(TreeNode* nodo, Actividad actividad);

int main() {
    Node* head = NULL;
    int numActividades = 8;
    int hora = 0;
    int segundosTranscurridos = 0;

    Actividad actividades[] = {
        {1, "Bañarse", 3},
        {2, "Gimnasio", 4},
        {3, "Comprar alimentos", 2},
        {4, "Pasear a tu mascota", 3},
        {5, "Trabajo", 5},
        {6, "Proyectos personales", 4},
        {7, "Tiempo con pareja", 5},
        {8, "Tiempo recreativo", 3}
    };

    Cola* colaAlarmas = inicializarCola(10);
    Pila* pilaMarcadores = inicializarPila(10);  // Fixed this line
    TreeNode* arbolHoras = NULL;

    srand(time(NULL));

    while (1) {
        segundosTranscurridos += 10;
        if (segundosTranscurridos >= 3600) {
            segundosTranscurridos = 0;
            aumentarHora(&hora);

            if (hora == 0) {
                while (!estaVacia(colaAlarmas)) {
                    eliminarAlarma(colaAlarmas);
                }

                while (!estaVacia(pilaMarcadores)) {
                    pop(pilaMarcadores);
                }
            }
        }

        if (rand() % 10 == 0) {
            Actividad actividad;
            actividad.id = rand() % 1000;
            sprintf(actividad.nombre, "Actividad %d", actividad.id);
            actividad.prioridad = rand() % 5 + 1;

            arbolHoras = relojCuentafinal(arbolHoras, actividad, hora);
        }
    }

    return 0;
}


Cola* inicializarCola(int capacidad) {
    Cola* cola = (Cola*)malloc(sizeof(Cola));
    cola->capacidad = capacidad;
    cola->elementos = (Alarma*)malloc(sizeof(Alarma) * capacidad);
    cola->frente = cola->fin = -1;
    return cola;
}

int estaVacia(Cola* cola) {
    return cola->frente == -1;
}

int estaLlena(Cola* cola) {
    return (cola->fin + 1) % cola->capacidad == cola->frente;
}

void agregarAlarma(Cola* cola, Alarma alarma) {
    if (estaLlena(cola)) {
        printf("La cola de alarmas está llena. No se puede agregar más alarmas.\n");
        return;
    }

    if (estaVacia(cola)) {
        cola->frente = 0;
    }

    cola->fin = (cola->fin + 1) % cola->capacidad;
    cola->elementos[cola->fin] = alarma;
}

void eliminarAlarma(Cola* cola) {
    if (estaVacia(cola)) {
        printf("No hay alarmas para eliminar.\n");
        return;
    }

    if (cola->frente == cola->fin) {
        cola->frente = cola->fin = -1;
    } else {
        cola->frente = (cola->frente + 1) % cola->capacidad;
    }
}

void pop(Pila* pila) {
    if (estaVacia(pila)) {
        printf("La pila de marcadores está vacía.\n");
        return;
    }

    Node* temp = pila->top;
    pila->top = pila->top->next;
    free(temp);
    pila->tamano--;
}

Node* agregarActividad(Node* head, Actividad actividad) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dato = actividad;

    if (head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }

    Node* last = head->prev;

    newNode->next = head;
    head->prev = newNode;

    newNode->prev = last;
    last->next = newNode;

    return head;
}

// Función para añadir una alarma a las actividades por realizar
void sistemaAlarma(Cola* colaAlarmas, Actividad actividad) {
// Inicializar una cola
Cola* inicializarCola(int capacidad) {
    Cola* cola = (Cola*)malloc(sizeof(Cola));
    cola->capacidad = capacidad;
    cola->elementos = (Alarma*)malloc(sizeof(Alarma) * capacidad);
    cola->frente = cola->fin = -1;
    return cola;
}

// Verificar si la cola está vacía
int estaVacia(Cola* cola) {
    return cola->frente == -1;
}

// Verificar si la cola está llena
int estaLlena(Cola* cola) {
    return (cola->fin + 1) % cola->capacidad == cola->frente;
}

// Agregar una alarma a la cola
void agregarAlarma(Cola* cola, Alarma alarma) {
    if (estaLlena(cola)) {
        printf("La cola de alarmas está llena. No se puede agregar más alarmas.\n");
        return;
    }

    if (estaVacia(cola)) {
        cola->frente = 0;
    }

    cola->fin = (cola->fin + 1) % cola->capacidad;
    cola->elementos[cola->fin] = alarma;
}

// Eliminar una alarma de la cola (cuando se dispara)
void eliminarAlarma(Cola* cola) {
    if (estaVacia(cola)) {
        printf("No hay alarmas para eliminar.\n");
        return;
    }

    if (cola->frente == cola->fin) {
        cola->frente = cola->fin = -1;
    } else {
        cola->frente = (cola->frente + 1) % cola->capacidad;
    }
}

// Mostrar las alarmas en la cola
void mostrarAlarmas(Cola* cola) {
    if (estaVacia(cola)) {
        printf("La cola de alarmas está vacía.\n");
        return;
    }

    int i = cola->frente;
    printf("Alarmas programadas:\n");
    while (i != cola->fin) {
        printf("Actividad: %s\n", cola->elementos[i].actividad.nombre);
        i = (i + 1) % cola->capacidad;
    }
    printf("Actividad: %s\n", cola->elementos[cola->fin].actividad.nombre);
}
}

// Función para aladir un marcador a las actividades seleccionadas
void marcadorActividad(Pila* pilaMarcadores, Actividad actividad) {
// Inicializar una pila
Pila* inicializarPila(int capacidad) {
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    pila->top = NULL;
    pila->capacidad = capacidad;
    pila->tamano = 0;
    return pila;
}

// Verificar si la pila está vacía
int estaVacia(Pila* pila) {
    return pila->top == NULL;
}

// Agregar un elemento (actividad marcada) a la pila
void push(Pila* pila, Actividad actividad) {
    if (pila->tamano >= pila->capacidad) {
        printf("La pila de marcadores está llena. No se pueden agregar más marcadores.\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dato = actividad;
    newNode->next = pila->top;
    pila->top = newNode;
    pila->tamano++;
}

// Obtener y eliminar el elemento superior de la pila
Actividad pop(Pila* pila) {
    if (estaVacia(pila)) {
        printf("La pila de marcadores está vacía.\n");
        Actividad actividadVacia;
        actividadVacia.id = -1;
        return actividadVacia;
    }

    Node* temp = pila->top;
    Actividad actividadMarcada = temp->dato;
    pila->top = pila->top->next;
    free(temp);
    pila->tamano--;

    return actividadMarcada;
}

Node** prioridadGrafos(Actividad actividades[], int numActividades) {
    Grafo* crearGrafo(Actividad actividades[], int numActividades) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numNodos = numActividades;
    grafo->matrizAdyacencia = (int**)malloc(numActividades * sizeof(int*));

    for (int i = 0; i < numActividades; i++) {
        grafo->matrizAdyacencia[i] = (int*)malloc(numActividades * sizeof(int));

        for (int j = 0; j < numActividades; j++) {
            if (i == j) {
                grafo->matrizAdyacencia[i][j] = 0;
            } else if (actividades[i].prioridad > actividades[j].prioridad) {
                grafo->matrizAdyacencia[i][j] = 1;
            } else {
                grafo->matrizAdyacencia[i][j] = 0;
            }
        }
    }

    return grafo;
}

// Función para realizar una búsqueda topológica en el grafo
void topologicalSortUtil(Grafo* grafo, int v, int visitado[], Node* actividades[], int* index) {
    visitado[v] = 1;
    for (int i = 0; i < grafo->numNodos; i++) {
        if (grafo->matrizAdyacencia[v][i] && !visitado[i]) {
            topologicalSortUtil(grafo, i, visitado, actividades, index);
        }
    }
    actividades[(*index)++] = agregarActividad(NULL, actividades[v]->dato);
}

// Función que llama a la búsqueda topológica
Node** topologicalSort(Grafo* grafo, Node* actividades[], int numActividades) {
    int* visitado = (int*)malloc(numActividades * sizeof(int));
    int index = 0;
    Node** ordenRecomendado = (Node**)malloc(numActividades * sizeof(Node*));

    for (int i = 0; i < numActividades; i++) {
        visitado[i] = 0;
    }

    for (int i = 0; i < numActividades; i++) {
        if (!visitado[i]) {
            topologicalSortUtil(grafo, i, visitado, actividades, &index);
        }
    }

    return NULL;
}
}

// Función para programar actividades en un árbol de horas
TreeNode* relojCuentafinal(TreeNode* arbolHoras, Actividad actividad, int hora)  {
    TreeNode* nodo = (TreeNode*)malloc(sizeof(TreeNode));
    nodo->hora = hora;
    nodo->actividades = NULL;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    
    return arbolHoras; 
}

// Agregar una actividad programada a un nodo de árbol
void agregarActividadProgramada(TreeNode* nodo, Actividad actividad) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dato = actividad;
    newNode->next = nodo->actividades;
    nodo->actividades = newNode;
}

// Función para aumentar una hora en el reloj
void aumentarHora(int* hora) {
    (*hora)++;
    if (*hora > 23) {
        *hora = 0;
    }
}
}
