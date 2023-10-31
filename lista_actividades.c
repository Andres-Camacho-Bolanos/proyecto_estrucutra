(Node* head, Actividad actividad) {
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
