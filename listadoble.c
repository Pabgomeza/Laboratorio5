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
    NODO *actual = *head, *ant = NULL, *sig = NULL;/*Se crean 2 punteros 
    que van a NULL*/

    while(actual != NULL)
    {
        if(actual->dato == dato) /*Se determina que actual que fue el 
        nodo creado sea el dato dado en la función.*/
        {
            if( actual == *head) //Si el actual es al inicio de la lista
            {
                *head = actual->next;
                if( actual->next != NULL)
                    actual->next->before = NULL; /*Se elimina actual de 
                    la lista poniendo NULL a ambos lados*/
            }
            else if( actual->next == NULL) /* Si el actual es el ultimo, 
            se verifica que siga NULL*/
            {
                ant = actual->before; /*Se apunta ant al before de actual*/
                actual->before = NULL;
                ant->next = NULL;/*Se elimina actual de 
                    la lista poniendo NULL a ambos lados*/
            }
            /*Se definen los punteros como el los nodos que están antes
             *  y despues del nodo que estamos buscando para así poner 
             * NULL a ambos lados del nodo 
             * y volver a conectar la lista.*/
            else{
                ant = actual->before;
                actual->before = NULL;
                sig = actual->next;
                actual->next = NULL;
                ant->next = sig;
                sig->before = ant;
            }
            free(actual); /*Se libera la memoria del dato seleccionado*/
            return 1;
        }
        actual = actual->next;
    }
    return 0;
}

//Función para insertar al final de la lista
int InsertarFinal(NODO **head, int dato)
{
    NODO *nuevo = NULL, *nAux = *head;/*Se crea el valor nuevo como 
    NULL y apntamos nAux al head.*/
    nuevo = CrearNodo(dato);/*Se crea el Nodo con el nuevo dato*/
    if (nuevo != NULL)
    {
        while(nAux->next != NULL){ nAux = nAux->next;}/*Vamos iterando 
        hasta llegar al final de la lista*/
        nuevo->before = nAux;
        nAux->next = nuevo;
        return 1;
    }
    return 0;
}

//Función para imprimir la lista
void ImprimirLista(NODO *head){
    NODO *nAux = head;

    while(nAux != NULL)/*Recorremos la lista mientras imprimimos 
    los elementos.*/
    {
        printf("%d\n ", nAux->dato);/*Imprimimos los datos mientras el 
        nAux va iternado entre los elementos de la lista*/
        nAux = nAux->next;
    }
}

//Función para insertar al inicio de la lista
int InsertarInicio(NODO **head, int dato)
{
    NODO *nuevo = NULL;//Se define el nuevo NODO como NULL

    nuevo = CrearNodo(dato);//Se crea el nodo nuevo como el dato brindado
    if (nuevo != NULL)
    {
        nuevo->next = *head;
        nuevo->before = NULL;
        if( *head != NULL)
            (*head)->before = nuevo;
        *head = nuevo;
        return 1;//Retornamos 1 si se logra instalar el nodo.
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

