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
