
/******************************************************************************
  CÓDIGO DE LISTAS en C/C++ A PARTIR DE NODOS USANDO STRUCTS. Por: byDavid360
******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef int T;

struct Node { //estructura donde definimos el nodo con su valor de tipo T y su puntero al siguiente
    T value;
    Node * next;
};

struct List{ //estructura donde definimos la lista que tendrá un head, un tail y un numero de elementos
    Node* head;
    Node* tail;
    int numElements;
};

Node* crearNode (T valor, Node* siguiente); //funcion crea un nodo pasando de parametro el valor y el nodo siguiente al que apunta
List* crearLista(); //funcion que crea una lista vacia (head y tail apuntan a lo mismo)
void chequearLista(List* lista); //funcion que chequea si existe la lista
void chequearNode(Node* nodo); //funcion que chequea si existe el nodo
void insertarInicio(List* lista, T valor); //funcion que inserta un nodo por el inicio (es eficiente)
void insertarFinal(List* lista, T valor); //funcion que inserta un nodo por el final (es eficiente)
void recorrerLista (List* lista); //funcion que recorre una lista
bool borradoInicio (List* lista); //funcion que borra por el inicio (eficiente)
bool borradoFinal(List* lista); //funcion que borra por el final (no eficiente)
int buscarElemento(List* lista, T posicion); //funcion que devuelve que elemento esta en el nodo posicion
void insertarDespuesElemento(List* lista, T valor, T nuevo); //funcion que inserta el elemento nuevo despues de valor
int contarElementos(List* lista); //funcion que te cuenta los elementos de una lista

int main(){

    int numero, elemento, posicion, despues;
    List* miLista = crearLista(); //creamos la lista 1, 2 y 3. Se pueden crear tantas listas como se quiera
    List *lista2 = crearLista();
    List* lista3 = crearLista();

    cout<<"Cuantos elementos quieres crear en la lista 1: ";
    cin>>numero;
    cout<<endl;
    for(int i = 0; i< numero; i++){
        cout<<"Introduce un elemento: ";
        cin>> elemento;
        insertarInicio(miLista, elemento);
        cout<<endl;
    }

    cout<<"Cuantos elementos quieres crear en la lista 2: ";
    cin>>numero;
    cout<<endl;
    for(int i = 0; i< numero; i++){
        cout<<"Introduce un elemento: ";
        cin>> elemento;
        insertarFinal(lista2, elemento);
        cout<<endl;
    }

    cout<<"La lista 1 se ha hecho con la funcion de insertar por el inicio"<<endl;
    cout<<"La lista 1 es: ";
    recorrerLista(miLista);
    borradoInicio(miLista);
    cout<<endl;

    cout<<"La lista 1 despues de borrar por el inicio es: ";
    recorrerLista(miLista);
    borradoFinal(miLista);
    cout<<endl;

    cout<<"La lista 1 despues de borrar por el final es: ";
    recorrerLista(miLista);

    cout<< "La lista 2 se ha hecho con la funcion de insertar por el final"<<endl;
    cout<<"La lista 2 es: ";
    recorrerLista(lista2);
    borradoInicio(lista2);
    cout<<endl;

    cout<<"La lista 2 despues de borrar por el inicio es: ";
    recorrerLista(lista2);
    borradoFinal(lista2);
    cout<<endl;
    cout<<"La lista 2 despues de borrar por el final es: ";
    recorrerLista(lista2);

    cout<<endl<<endl<<"Cuantos elementos quieres crear en la lista3: ";
    cin>>numero;
    cout<<endl;

    for(int i = 0; i< numero; i++){
        cout<<"Introduce un elemento: ";
        cin>> elemento;
        insertarFinal(lista3, elemento);
        cout<<endl;
    }

    cout<< "La lista 3 se ha hecho con la funcion de insertar por el final"<<endl;
    cout<<"La lista 3 es: ";
    recorrerLista(lista3);
    cout<<endl;

    cout<<"Que elemento de que posicion quieres buscar: ";
    cin>>posicion;
    cout<<endl;

    cout<<"El elemento de esa posicion es el: ";
    cout<<buscarElemento(lista3,posicion);
    cout<<endl<<"Elige un elemento a insertar: ";
    cin>> elemento;

    cout<<endl<<"¿Despues de cual? : ";
    cin>>despues;
    insertarDespuesElemento(lista3,despues,elemento);
    cout<<endl<<"La lista queda de la forma: ";
    recorrerLista(lista3);
    cout<<endl<<"Posicion para borrar su elemento: ";
    cin>>posicion;
    borrarElementoDePosicion(lista3,posicion);
    cout<<endl<<"La lista queda de la forma: ";
    recorrerLista(lista3);

    system("PAUSE");
    return 0;
}

Node* crearNode (T valor, Node* siguiente){
    Node* nuevoNode = (Node*)malloc(sizeof(Node));
    chequearNode(nuevoNode);
    nuevoNode->value = valor;
    nuevoNode->next = siguiente;
    return nuevoNode;
}


List* crearLista(){
    List* miLista = (List*)malloc(sizeof(List));
    chequearLista(miLista);
    miLista ->head = crearNode('-', NULL);
    miLista->tail = miLista->head;
    miLista->numElements = 0;
    return miLista;
}


void insertarInicio (List* lista, T valor){
    chequearLista(lista);
    Node* nuevoNodo = crearNode(valor,lista->head);
    lista->head = nuevoNodo;
    lista->numElements ++;
}


void insertarFinal(List* lista, T valor){
    chequearLista(lista);
    Node* nuevoNodo = lista->tail; // nodo apunta a donde apunta el tail (el centinela original, nos estamos apropiando de el)
    nuevoNodo ->value = valor; //le damos el valor
    nuevoNodo->next = crearNode('-', NULL); //el centinela antiguo, que es el nuevo nodo, apunta a uno nuevo que será el nuevo centinela
    lista->tail = nuevoNodo->next; //el tail ahora apunta al nuevo centinela y no al antiguo ya que el antiguo no es el final de la lista
    lista->numElements++;
}


void recorrerLista (List* lista){
    chequearLista(lista);
    Node* actual = lista->head; //nodo actual apunta al head
    printf("(");
    while(actual != lista->tail){ //mientras que el actual no llegue al tail, imprimimos valor de actual y apuntamos al siguiente
            printf(" %d", actual->value);
            actual =  actual->next;
    }
    printf(" )");
}


bool borradoInicio (List* lista){
    chequearLista(lista);
    Node* auxiliar = lista->head;
    lista->head = auxiliar->next;
    free(auxiliar);
    lista->numElements--;
    return true;
}

bool borradoFinal(List* lista){
    chequearLista(lista);
    Node* ultimo = lista->head; // el nodo "ultimo" empieza apuntando al head
    while(ultimo->next != lista->tail){ //recorremos la lista hasta que el next a ultimo sea el tail
        ultimo = ultimo->next;
    }
    ultimo->next = NULL; //el next de ultimo lo ponemos a null
    free(lista->tail); //liberamos el tail que apuntaba al centinela
    lista->tail = ultimo; //hacemos que el tail apunte ahora al ultimo
    lista->numElements--;
    return true;
}


int buscarElemento(List* lista, T posicion){
    chequearLista(lista);
    Node* auxiliar = lista->head;
    if(posicion>contarElementos(lista)){
        cout<<"No existe ningun elemento en esa posicion";
        return 0;
    }

    for(int i = 1; i<posicion; i++){
        auxiliar = auxiliar->next;
    }
    return auxiliar->value;
}


void insertarDespuesElemento(List* lista, T valor, T nuevo){
    chequearLista(lista);
    Node* actual = lista->head;
    while(actual != lista->tail && actual->value != valor){ // avanzaremos con actual mientras no lleguemos al tail y su valor no sea el del de despues a insertar
        actual = actual->next;
    }
    if(actual->value == valor){ //si hemos llegado a su valor, el nodo next creamos un nodo con valor nuevo y apuntando al siguiente
        actual->next = crearNode(nuevo, actual->next);
    }
    else if (actual == lista->tail){ //si hemos llegado al final (por no existir el numero parametro) lo añadimos al final de la lista con la funcion insertarFinal
        insertarFinal(lista,nuevo);
    }
    lista->numElements++;
}

void chequearLista(List* lista){
    if(lista == NULL){
        printf("Error creando lista\n");
        exit(-1);
    }
}


void chequearNode(Node* nodo){
    if(nodo == NULL){
        printf("Error creando el nodo\n");
        exit(-1);
    }
}


int contarElementos(List* lista){
    chequearLista(lista);
    Node* auxiliar = lista->head;
    int contador = 1; //el planteamiento dice que la posicion inicial de la lista es la 1 y no la 0 (como en el caso de los vectores)
    while(auxiliar!= lista->tail){
        contador+=1;
        auxiliar = auxiliar->next;
    }
    return contador;
}
