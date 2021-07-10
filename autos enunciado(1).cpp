#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class Auto {
    public:
    Auto(char * , int );
    ~Auto();
    char modelo[30];
    int anio;
    Auto * sig;

};

Auto::Auto(char * mod , int ano)
{
	strcpy(modelo,mod);
	anio=ano;	
}

class Cliente {
	private:
		Auto * inicio;
    public:
    char nombre[30];
    char telefono[20];
    Cliente * sig;
    Auto * primerAuto;
    Cliente(char * nom, char * tel);
    ~Cliente();
    void agregarAuto(char * , int );
};

Cliente::Cliente(char * nom , char * tel )
{
	strcpy(nombre,nom);
	strcpy(telefono,tel);
}

class ListaClientes {
    private:
    Cliente * inicio;

	public:
		ListaClientes();
		~ListaClientes();
		void agregar(char * , char * );
		void mirar();
		Cliente * buscar(char * );
};

ListaClientes::ListaClientes()
{
	inicio=NULL;
}

void ListaClientes::agregar(char * nom, char * tel)
{
	Cliente * nuevoCliente = new Cliente(nom,tel);
	Cliente * aux;
	
	aux=inicio;
	nuevoCliente->sig=NULL;
	nuevoCliente->primerAuto=NULL;
	
	if(!inicio)	/*Si en inicio tengo NULL no hay nodos en la lista*/
	{
		inicio=nuevoCliente;	
		return ;
	}   
	
	else
	{
		while(aux->sig)
			aux=aux->sig;
		
		aux->sig=nuevoCliente;	
	}
}

void ListaClientes::mirar()
{
	Cliente * Cliente;
	Auto * Auto;
	
	Cliente = inicio;
	
	while(Cliente)
	{
		cout << "\n\n	Nombre: " << Cliente->nombre << "    Telefono:"  << Cliente->telefono << "\n";
		
		Auto=Cliente->primerAuto;
		while(Auto)
		{
			cout << "\n		Modelo:" << Auto->modelo << "	Anio:" << Auto->anio << "\n";
			Auto=Auto->sig;
		}
		
		Cliente=Cliente->sig;
	}

}

Cliente * ListaClientes::buscar(char * nom)
{
	Cliente * Cliente;
	Auto * auxAuto;
	
	Cliente = inicio;
	
	while(strcmp(Cliente->nombre,nom))	/*ENCUENTRO EL CLIENTE */
		Cliente=Cliente->sig;
	
	return Cliente;
}

void Cliente::agregarAuto(char * mod, int ano)
{
	Auto * nuevoAuto = new Auto(mod,ano);
	Auto * auxAuto;
	nuevoAuto->sig=NULL;
	
	/*VERIFICAR SI TIENE PRIMER AUTO */
	if(!primerAuto)
	{
		primerAuto=nuevoAuto;
		return;
	}
	
	/*Agrega en auto por el final*/
	auxAuto=primerAuto;
	
	while(auxAuto->sig)
		auxAuto=auxAuto->sig;
		
	auxAuto->sig=nuevoAuto;
}

int main() {
	
	cout << "\n	Iniciando programa...\n" ;
    ListaClientes * lc = new ListaClientes;  // puntero a la direccion del inicio de la lista
    
	lc->agregar("Pepe", "4555-6565");  //agrega Cliente (lista principal)
    lc->agregar("Maria", "4444-3232");
    lc->agregar("Carlos", "5460-1111");

	
    lc->buscar("Pepe")->agregarAuto("Renault 12", 1980);  //agrega Auto a un Cliente (lista secundaria)
    lc->buscar("Pepe")->agregarAuto("Renault Fluence", 2013);
	lc->mirar();
	
    /*printf("\n Pepe tiene %d autos" , lc->buscar("Pepe")->cantAutos() );  //debe dar 2

    lc->buscar("Pepe")->vaciarAutos();

    printf("\n Pepe tiene %d autos" , lc->buscar("Pepe")->cantAutos() );  //debe dar 0
    
    printf("\n La guirnalda tiene %d clientes" , lc->cantClientes() );  //debe dar 3*/

}
