#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructura de datos para representar una actividad
typedef struct Actividad {
	int id;
	char nombre[100];
	int prioridad;
	// Aquí podrías agregar información adicional si es necesario
} Actividad;

// Lista circular doblemente enlazada para las actividades
typedef struct Node {
	Actividad dato;
	struct Node* next;
	struct Node* prev;
} Node;

// Definición de una estructura de grafo
typedef struct Grafo {
    int numNodos;
    int** matrizAdyacencia;
} Grafo;

// Definición de una estructura de alarma para las actividades
typedef struct Alarma {
    Actividad actividad;
    // Otros campos relacionados con la alarma
} Alarma;

// Definición de una estructura de pila
typedef struct Pila {
    Node* top;
    int capacidad;
    int tamano;
} Pila;

// Definición de una estructura de cola
typedef struct Cola {
    Alarma* elementos;
    int frente, fin;
    int capacidad;
} Cola;

// Definición de una estructura de un nodo de árbol para representar actividades programadas en una hora específica
typedef struct TreeNode {
    int hora;
    Node* actividades; // Lista de actividades programadas para esta hora
    struct TreeNode* izquierda;
    struct TreeNode* derecha;
} TreeNode;

// Función para agregar una actividad a la lista circular
void Actividades(Node** head, Actividad) {
	void Actividades(Node* head, Actividad actividad) {
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
}

// Función para añadir una alarma a las actividades por realizar
void sistemaAlarma(Node* head, Actividad) {
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
void marcadorActividad(Node* head, Actividad) {
// Inicializar una pila
Pila* inicializarPila(int capacidad) {
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    pila->top = NULL;
    pila->capacidad = capacidad;
    pila->tamaño = 0;
    return pila;
}

// Verificar si la pila está vacía
int estaVacia(Pila* pila) {
    return pila->top == NULL;
}

// Agregar un elemento (actividad marcada) a la pila
void push(Pila* pila, Actividad actividad) {
    if (pila->tamaño >= pila->capacidad) {
        printf("La pila de marcadores está llena. No se pueden agregar más marcadores.\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dato = actividad;
    newNode->next = pila->top;
    pila->top = newNode;
    pila->tamaño++;
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
    pila->tamaño--;

    return actividadMarcada;
}

void prioridadGrafos(Node* head, Actividad) {
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

    return ordenRecomendado;
}
}

void relojCuentafinal(Node* head, actividad) {
// Inicializar un nodo de árbol
TreeNode* inicializarNodo(int hora) {
    TreeNode* nodo = (TreeNode*)malloc(sizeof(TreeNode));
    nodo->hora = hora;
    nodo->actividades = NULL;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    return nodo;
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

int main() {
    Node* head = NULL;
    int numActividades = 8;
    int hora = 0; // Inicialmente, la hora es 0
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

    // Crear un árbol para almacenar actividades programadas en horas específicas
    TreeNode* arbolHoras = NULL;

    // Inicializar el generador de números aleatorios con la hora actual
    srand(time(NULL));

    Pila* pilaMarcadores = inicializarPila(5);
    Cola* colaAlarmas = inicializarCola(5);

    while (1) {
        // Simulación: Aumentar una hora cada 10 segundos
        segundosTranscurridos += 10;
        if (segundosTranscurridos >= 3600) {
            segundosTranscurridos = 0;
            aumentarHora(&hora);

            // Reiniciar las alarmas y los marcadores activos a la hora 0
            if (hora == 0) {
                // Limpia la cola de alarmas
                while (!estaVacia(colaAlarmas)) {
                    eliminarAlarma(colaAlarmas);
                }

                // Limpia la pila de marcadores
                while (!estaVacia(pilaMarcadores)) {
                    pop(pilaMarcadores);
                }
            }
        }

        // Agregar actividades a la lista circular (puedes omitir este bucle si las actividades ya están en la lista)
        for (int i = 0; i < numActividades; i++) {
            head = agregarActividad(head, actividades[i]);
        }

        // Crear el grafo
        Grafo* grafo = crearGrafo(actividades, numActividades);

        // Realizar una búsqueda topológica en el grafo
        Node** ordenRecomendado = topologicalSort(grafo, head, numActividades);

        printf("Orden recomendado de actividades (de mayor a menor prioridad):\n");
        for (int i = numActividades - 1; i >= 0; i--) {
            printf("%s\n", ordenRecomendado[i]->dato.nombre);
        }

        // Simulación: Programar una actividad aleatoria en una hora específica
        if (rand() % 10 == 0) { // 1 de cada 10 segundos
            Actividad actividad;
            actividad.id = rand() % 1000;
            sprintf(actividad.nombre, "Actividad %d", actividad.id);
            actividad.prioridad = rand() % 5 + 1; // Prioridad aleatoria del 1 al 5

            // Buscar la hora en el árbol y agregar la actividad
            TreeNode* nodoHora = arbolHoras;
            TreeNode* nodoPadre = NULL;

            while (nodoHora != NULL) {
                nodoPadre = nodoHora;

                if (hora < nodoHora->hora) {
                    nodoHora = nodoHora->izquierda;
                } else if (hora > nodoHora->hora) {
                    nodoHora = nodoHora->derecha;
                } else {
                    // Hora encontrada, agregar la actividad programada
                    agregarActividadProgramada(nodoHora, actividad);
                    break;
                }
            }

            // Si la hora no se encontró en el árbol, crear un nuevo nodo
            if (nodoHora == NULL) {
                nodoHora = inicializarNodo(hora);
                agregarActividadProgramada(nodoHora, actividad);

                if (nodoPadre == NULL) {
                    arbolHoras = nodoHora;
                } else if (hora < nodoPadre->hora) {
                    nodoPadre->izquierda = nodoHora;
                } else {
                    nodoPadre->derecha = nodoHora;
                }
            }
        }

        // Simulación de otras funciones y lógica de tu programa

        // Puedes agregar aquí la lógica para mostrar las actividades programadas en la hora actual
    }
    return 0;
}
