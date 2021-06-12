#include <stdio.h>
#include <stdlib.h>

//Estructura del nodo
typedef struct nodo
{
    int dato;
    struct nodo *next;
    struct nodo *before;
} NODO;



NODO *CrearNodo(int dato);
int EliminarNodo(NODO **head, int dato);
int InsertarFinal(NODO **head, int dato);
void ImprimirLista(NODO *cabeza);
void EliminarLista(NODO*head);
int InsertarInicio(NODO **head, int dato);
NODO *insertarDespues(NODO **head, int dato, int position);
NODO *insertarAntes(NODO **head, int dato, int position);


int main()
{
    NODO *head = NULL;
    InsertarInicio(&head, 1);
    InsertarInicio(&head, 2);
    InsertarFinal(&head, 3);
    InsertarInicio(&head, 0);
    InsertarFinal(&head, 4);
    insertarDespues(&head, 5, 1);
    insertarAntes(&head, 60, 4);
    EliminarNodo(&head, 4);
    ImprimirLista(head);
    EliminarLista(head);

    return 0;
}



//Función para eliminar lista completa

void EliminarLista(NODO*head){
    NODO *temp;
    while(head!= NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}
//Función para eliminar un nodo de la lista
int EliminarNodo(NODO **head, int dato)
{
    NODO *actual = *head, *ant = NULL, *sig = NULL;

    while(actual != NULL)
    {
        if(actual->dato == dato)
        {
            if( actual == *head)
            {
                *head = actual->next;
                if( actual->next != NULL)
                    actual->next->before = NULL;
            }
            else if( actual->next == NULL)
            {
                ant = actual->before;
                actual->before = NULL;
                ant->next = NULL;
            }
            else
            {
                ant = actual->before;
                actual->before = NULL;
                sig = actual->next;
                actual->next = NULL;
                ant->next = sig;
                sig->before = ant;
            }
            free(actual);
            return 1;
        }
        actual = actual->next;
    }
    return 0;
}

//Función para insertar al final de la lista
int InsertarFinal(NODO **head, int dato)
{
    NODO *nuevo = NULL, *nAux = *head;
    nuevo = CrearNodo(dato);
    if (nuevo != NULL)
    {
        while(nAux->next != NULL){ nAux = nAux->next;}
        nuevo->before = nAux;
        nAux->next = nuevo;
        return 1;
    }
    return 0;
}

//Función para imprimir la lista
void ImprimirLista(NODO *cabeza)
{
    NODO *nAux = cabeza;

    while(nAux != NULL)
    {
        printf("%d\n ", nAux->dato);
        nAux = nAux->next;
    }
}

//Función para insertar al inicio de la lista
int InsertarInicio(NODO **head, int dato)
{
    NODO *nuevo = NULL;

    nuevo = CrearNodo(dato);
    if (nuevo != NULL)
    {
        nuevo->next = *head;
        nuevo->before = NULL;
        if( *head != NULL)
            (*head)->before = nuevo;
        *head = nuevo;
        return 1;
    }
    return 0;
}

//Función para crear un nuevo nodo
NODO *CrearNodo(int dato)
{
    NODO* nuevo = NULL;

    nuevo = (NODO*)malloc(sizeof(NODO)); 
    //Se guarda el 
    //espacio para el nodo
    if( nuevo != NULL)
    {
        nuevo->dato = dato;
        nuevo->next = NULL;
        nuevo->before = NULL;
    }
    return nuevo;
}

 
//Funcion para insertar un nuevo nodo despues de un nodo especifico
NODO *insertarDespues(NODO **head, int nuevo, int position) {

	NODO *newP = NULL;
	NODO *temp = *head;
	NODO *temp2 = NULL;
	newP = CrearNodo(nuevo);
//Con el while buscamos en la lista la posicion deseada
	while(position != 1)
	{
		temp = temp ->next;
		position--;
	}
//Con el if se valida que si el siguiente nodo al que estamos buscando es diferente de null, se actualice la informacion del nodo que buscamos
	if (temp ->next == NULL)
	{
		temp ->next = newP;
		newP ->before = temp;
	}
//El else se actualiza los punteros del nodo anterior y siguiente
	else {
		temp2 = temp ->next;
		temp -> next = newP;
		temp2 -> before = newP;
		newP-> next = temp2;
		newP -> before = temp;
	}
	return *head;
}

//Funcion para insertar un nuevo nodo antes de un nodo especifico
NODO *insertarAntes(NODO **head, int nuevo, int position) {

	NODO *newP = NULL;
	NODO *temp = *head;
	NODO *temp2 = NULL;
	newP = CrearNodo(nuevo);
//Con el while buscamos en la lista la posicion deseada
	while(position != 1)
	{
		temp = temp ->next;
		position--;
	}
//Con el if se valida que si el nodo anterior al que estamos buscando es diferente de null, se actualice la informacion del nodo que buscamos
	if (temp ->before == NULL)
	{
		newP ->before = NULL;
		newP ->next = temp;
		temp ->before = newP;
		*head = newP;
	}
//El else se actualiza los punteros del nodo anterior y siguiente	
	else {
		temp2 = temp -> before;
		temp2 -> next = newP;
		temp -> before = newP;
		newP-> before = temp2;
		newP -> next = temp;
	}
	return *head;
}

