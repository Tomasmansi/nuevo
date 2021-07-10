#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std ;

class Visitante 
{
	public:
			char NOM [30];
			Visitante(char * );
			~Visitante();
			Visitante * SIG;
			int cont;
};

Visitante::Visitante(char * nom)
{
	strcpy(NOM,nom);
	SIG=NULL;
	cont=0;
}

Visitante::~Visitante()
{
	cout << "\nMatando a ... \n" << NOM;
}

class Museo 
{
	public:
			char NOM [30];
			Museo(char * );
			Visitante * PVIS;
			Museo * SIG;
};

Museo::Museo(char * nom)
{
	strcpy(NOM,nom);
	PVIS=NULL;	/*GUARDO EL NULO EN EL PRIMER VISITANTE*/	
}

class RegistroVisitas 
{	
	private:
			Museo * INICIO;
	public:
			RegistroVisitas(); 
			void nuevoMuseo(char * );
			void mirar();
			void registrarVisita(char * , char *); 
			void agregarVisitante(Museo * , Visitante *);
			void verVisitantesPerfectos(); 
			void friend listaAux(char *);
			void borrarMuseosMenosVisitados();
};

class lista
{
	private:
			Visitante * inicio;
	public:
			lista();
			~lista();
			void mirarPerfect(int contadorMuseos);
			void listaAux(char * );
			void borrarLista();
};

lista::lista()
{
	inicio=NULL;	
}

lista::~lista()
{
	cout << "\nDESTRUYENDO LISTA AUX...\n" ;
}

void lista::listaAux(char * nom)
{
	Visitante * nVis;
	Visitante * aux;
	
	if(!inicio) /*NO HAY NADIE EN LA LISTA*/
	{
		nVis= new Visitante(nom);
		nVis->SIG=NULL;
		inicio = nVis;
		nVis->cont++;
		return;
	}
	
	aux=inicio;
	
	while(aux)
	{
		if(!(strcmp(nom,aux->NOM))) /*EL NOMBRE YA ESTA EN LA LISTA LE SUMO 1*/
		{
			aux->cont++;
			return;
		}
		aux=aux->SIG;
	}
	
	/*CREO UN NUEVO NOMBRE EN LA LISTA*/
	aux=inicio;
	
	while(aux->SIG)
		aux=aux->SIG;
	
	nVis= new Visitante(nom);
	nVis->SIG=NULL;
	aux->SIG = nVis;
	nVis->cont++;
}

RegistroVisitas::RegistroVisitas()
{
	INICIO = NULL;
} 

void RegistroVisitas::borrarMuseosMenosVisitados()
{
	Museo * museo, * aux;
	Visitante * visitante,*auxVis;
	int contadorMuseos=0,menorVis,cont=0;
	
	museo=INICIO;
	
	while(museo) /*CUANTOS MUSEOS HAY*/
	{	
		contadorMuseos++;
		museo=museo->SIG;
	}	
	
	museo=INICIO;
	
	while(museo)
	{
		visitante=museo->PVIS;
		while(visitante)
		{
			cont++;
			visitante=visitante->SIG;
		}
		
		if(menorVis>(contadorMuseos+cont))
		{
			menorVis=contadorMuseos-cont;
			aux=museo;
		}
		museo=museo->SIG;
	}
	
	cout << "\n\n\nBorrar a \n" << aux->NOM;
	
	visitante = aux->PVIS;
	
	while(visitante)
	{
		auxVis=visitante;
		delete visitante;
		visitante=auxVis->SIG;
	}
	
	museo = INICIO;
	
	if( aux == INICIO )
	{
		INICIO = aux->SIG;
		delete aux;
		return;
	}
	
	while( museo->SIG != aux)
		museo=museo->SIG;
	
	museo->SIG=aux->SIG;
	
	delete aux;
}

void RegistroVisitas::verVisitantesPerfectos()
{
	Museo * auxMuseo;
	lista * auxLista = new lista();
	
	Visitante * auxVisitante;
	int contadorMuseos=0;
	
	auxMuseo = INICIO;
	
	while(auxMuseo) /*CUANTOS MUSEOS HAY*/
	{	
		contadorMuseos++;
		auxMuseo=auxMuseo->SIG;
	}	
	
	auxMuseo=INICIO;
	
	while(auxMuseo)
	{
		auxVisitante=auxMuseo->PVIS;
		while(auxVisitante)
		{
			auxLista->listaAux(auxVisitante->NOM); /*GUARDO LOS NOMBRES EN OTRA LISTA*/
			auxVisitante=auxVisitante->SIG;
		}
		auxMuseo=auxMuseo->SIG;
	}
	
	/*VEO QUIEN TIENE IGUAL DE MUSEOS VISITADOS QUE CANTIDAD DE MUSEOS*/
	auxLista->mirarPerfect(contadorMuseos);
	
	/*BORRO LA LISTA AUXILIAR*/
	cout << "\n\n	***BORRANDO LISTA AUX ";
	auxLista->borrarLista();
	delete auxLista;
}

void lista::borrarLista()
{
	Visitante * vis, * aux;
	
	vis=inicio;

	while(vis)
	{
		aux=vis;
		delete vis;
		vis=aux->SIG;
	}	
}

void lista::mirarPerfect(int contadorMuseos)
{
	Visitante * vis;
	
	cout << "\nVisitantes perfectos:\n" ;
	vis = inicio;
	
	while(vis)
	{
		if(vis->cont == contadorMuseos)
			cout << "	Nombre:  " << vis->NOM;
		
		vis=vis->SIG;
	}
}

void RegistroVisitas::registrarVisita(char * nomMuseo, char * nomVisitante)
{
	Museo * auxMuseo;
	Visitante * nuevoVisitante = new Visitante(nomVisitante);
	
	nuevoVisitante->SIG = NULL;
	
	auxMuseo=INICIO;
	
	/*BUSCAR EL MUSEO VISITADO*/
	while(auxMuseo)
	{
		if(!(strcmp(auxMuseo->NOM,nomMuseo))) /*ENCUENTRO EL MUSEO*/
		{
			agregarVisitante(auxMuseo,nuevoVisitante);
			return;
		}
		
		auxMuseo=auxMuseo->SIG;
	}
	
	cout << "\n\nNo hay datos del museo ingresado." ;
}

void RegistroVisitas::agregarVisitante(Museo * museo , Visitante * nuevoVisitante)
{
	Visitante * auxVisitante;
	
	if(!museo->PVIS)
	{
		museo->PVIS = nuevoVisitante;
		return;
	}
	
	auxVisitante=museo->PVIS;
	
	while(auxVisitante->SIG)
		auxVisitante=auxVisitante->SIG;
	
	auxVisitante->SIG = nuevoVisitante;
}


void RegistroVisitas::nuevoMuseo(char * nom)
{
	Museo * nuevoMuseo = new Museo(nom);
	Museo * auxMuseo;
	
	nuevoMuseo->SIG=NULL;
	
	if(!INICIO) /*NO HAY MUSEOS CREADOS*/
	{
		INICIO = nuevoMuseo;
		return;
	}
	
	/*AGREGA EL MUSEO POR EL FINAL*/
	auxMuseo=INICIO;
	while(auxMuseo->SIG)
		auxMuseo=auxMuseo->SIG;
		
	auxMuseo->SIG = nuevoMuseo;
}

void RegistroVisitas::mirar()
{
	Museo * mirarMuseo;
	Visitante * mirarVisitante;
	
	mirarMuseo=INICIO;
	
	while(mirarMuseo)
	{
		cout << "\n\nMUSEO :" << mirarMuseo->NOM;
		mirarVisitante=mirarMuseo->PVIS;
		while(mirarVisitante)
		{
			cout << "\n		Nombre: " << mirarVisitante->NOM << "\n";
			mirarVisitante=mirarVisitante->SIG;
		}
		mirarMuseo=mirarMuseo->SIG;
	}
}

int main() 
{          
	RegistroVisitas * lista = new RegistroVisitas;
	
	lista->nuevoMuseo("MALBA");
	lista->nuevoMuseo("MUSEO HISTORICO NAC.");
	lista->nuevoMuseo("MUSEO DE CS. NATURALES");
	
	lista->registrarVisita("MALBA", "Pepe"); 
	lista->registrarVisita("MUSEO HISTORICO NAC.", "Pepe"); 
	lista->registrarVisita("MALBA", "Maria Alvarez"); 
	lista->registrarVisita("MUSEO DE CS. NATURALES", "Pepe"); 
	lista->registrarVisita("MUSEO DE CS. NATURALES", "Roberto Sanchez");
	
	lista->mirar();
	
	lista->verVisitantesPerfectos(); 
	lista->borrarMuseosMenosVisitados(); //borra el historico nacional
	
	lista ->mirar();
	
return 0;
}
