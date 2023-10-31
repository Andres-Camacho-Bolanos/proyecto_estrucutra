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
