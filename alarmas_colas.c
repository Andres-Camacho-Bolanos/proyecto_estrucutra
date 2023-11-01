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
