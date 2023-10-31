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
	// Inicialización de la lista circular de actividades
	Node* head = NULL;

	// Actividades predeterminadas
	Actividad actividades[] = {
    	{1, "Bañarse", 3},
    	{2, "Gimnasio", 2},
    	{3, "Comprar alimentos", 5},
    	{4, "Pasear a tu mascota", 1},
    	{5, "Trabajo", 8},
    	{6, "Proyectos personales", 6},
    	{7, "Tiempo con pareja", 7,
    	{8, "Tiempo recreativo", 4}
	};

	for (int i = 0; i < 8; i++) {
    	addActividad(&head, actividades[i]);
	}

	// Aquí puedes implementar las demás estructuras de datos y funcionalidades

	// Por ejemplo, podrías implementar la cola para las alarmas, grafos para la ruta ideal, árboles para actividades secundarias y pilas para el marcador de actividades personales.

	// Luego, puedes implementar la lógica para que el usuario interactúe con el sistema y obtenga recomendaciones de rutina.

	return 0;
}
