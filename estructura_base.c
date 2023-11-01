#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int tamaño;
} Pila;

// Definición de una estructura de cola
typedef struct Cola {
    Alarma* elementos;
    int frente, fin;
    int capacidad;
} Cola;

// Función para agregar una actividad a la lista circular
void Actividades(Node** head, Actividad) {
	// Implementa la lógica para agregar la actividad a la lista
}

// Función para mostrar las actividades en la lista
void mostrarActividades(Node* head) {
	// Implementa la lógica para recorrer y mostrar las actividades
}

// Función para añadir una alarma a las actividades por realizar
void sistemaAlarma(Node* head, Actividad) {
  // Implementar lógica para añadir un sistema recordatorio para las actividades seleccionadas
}

// Función para aladir un marcador a las actividades seleccionadas
void marcadorActividad(Node* head, Actividad) {
  // Impelementa la lógica para añadir un valor extra de prioridad a la actividad
}

int main() {
    Node* head = NULL;
    int numActividades = 8;

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

    Cola* colaAlarmas = inicializarCola(5);

    // Agregar alarmas de ejemplo
    Alarma alarma1 = {actividades[0]};
    Alarma alarma2 = {actividades[3]};

    agregarAlarma(colaAlarmas, alarma1);
    agregarAlarma(colaAlarmas, alarma2);

    // Mostrar las alarmas
    mostrarAlarmas(colaAlarmas);

    // Eliminar una alarma (cuando se dispara)
    eliminarAlarma(colaAlarmas);

    // Mostrar las alarmas actualizadas
    mostrarAlarmas(colaAlarmas);

    // Crear una pila de marcadores con una capacidad máxima de 5 marcadores
    Pila* pilaMarcadores = inicializarPila(5);

    // Agregar marcadores de ejemplo (puedes pedir al usuario que seleccione actividades)
    push(pilaMarcadores, actividades[0]); // Marcar "Bañarse"
    push(pilaMarcadores, actividades[5]); // Marcar "Proyectos personales"

    // Simulación: Incrementar la prioridad de las actividades marcadas
    while (!estaVacia(pilaMarcadores)) {
        Actividad actividadMarcada = pop(pilaMarcadores);
        actividadMarcada.prioridad *= 2;
        printf("Se ha marcado la actividad: %s\n", actividadMarcada.nombre);
    }

    // Imprimir las prioridades actualizadas
    for (int i = 0; i < numActividades; i++) {
        printf("Actividad: %s, Prioridad: %d\n", actividades[i].nombre, actividades[i].prioridad);
    }
	
    // Limpieza de memoria

    return 0;
}
