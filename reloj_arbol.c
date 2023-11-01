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
