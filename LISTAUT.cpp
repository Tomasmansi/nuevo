/* LISTAS SIMPLEMENTE ENLAZADAS */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std ;

class NODO {
		public :
			char NOM[20] ;
			NODO * SIG ;
			NODO ( char * );
			~NODO() ;
};

NODO::NODO(char * S)
{
		strcpy ( NOM , S );
}

NODO::~NODO()
{
		cout << "\n\n   MATANDO A .... " << NOM << "\n";
		getchar() ;
}


class LISTA {
		private :
			NODO * INICIO ;
			void PONER_P(NODO *);
			void PONER_F(NODO *);
			void INSERT(NODO *);
			NODO * MINIMO() ;
			NODO * MAXIMO() ;
			NODO * BUSCAR ( char * );
			void MATAR(NODO *);
			void SACAR(NODO *);
		public :
			LISTA() ;
			~LISTA() ;
			void AGREGAR_P(char *);
			void AGREGAR_F(char *);
			void INSERTAR(char *);
			void MIRAR() ;
			void MENOR() ;
			void MAYOR() ;
			void ELIMINAR(char *);
			void ORDENAR1() ;
			void ORDENAR2() ;
};


LISTA::LISTA()
{
		INICIO = NULL ;
}

LISTA::~LISTA()
{
		cout << "\n\n   DESTRUYENDO TODOS LOS NODOS \n";
		cout << "\n\n   ESTA ES PARA USTEDES !!! .... \n";
		getchar() ;
}


void LISTA::AGREGAR_P(char * S)
{
		NODO * P ;
		P = new NODO(S) ;
	
		PONER_P(P) ;
}

void LISTA::PONER_P(NODO * PN)
{
		PN->SIG = INICIO ;
		INICIO = PN ;
}

void LISTA::AGREGAR_F(char * S)
{
		NODO * P ;
		P = new NODO(S) ;
	
		PONER_F(P) ;
}

void LISTA::PONER_F(NODO * PN)
{
		NODO * P ;
		
		P = INICIO ;		
		PN->SIG = NULL ;
		
		if ( ! INICIO ) {
				/*  LISTA VACIA  */
				INICIO = PN ;
				return ;
		}
		/*  LISTA NO VACIA  */
		while ( P->SIG )
				P = P->SIG ; 	// LLEVO P HASTA EL ULTIMO NODO
		P->SIG = PN ;		
}

void LISTA::INSERTAR(char * S)
{
		NODO * P ;
		P = new NODO(S) ;
	
		INSERT(P) ;
}

void LISTA::INSERT(NODO * PN)
{
		NODO * P , * ANT ;
		
		P = INICIO ;
		ANT = NULL ;
		
		if ( ! INICIO ) {
				/*  LISTA VACIA  */
				PN->SIG = NULL ;
				INICIO = PN ;
				return ;
		}	
		/*   LISTA NO VACIA   */
		while ( P ) {
				if ( strcmp (P->NOM , PN->NOM) < 0 ) {
						/*  BARRIDO  */
						ANT = P ;
						P = P->SIG ;					
				}
				else {
						/*  EUREKA !!! */
						if ( ANT ) {
								/*  NODO INTERMEDIO  */
								PN->SIG = P ;
								ANT->SIG = PN ;
								return ;							
						}
						/*  PRIMER NODO */
						PN->SIG = INICIO ;
						INICIO = PN ;
						return ;				
				} /*  else  */				
		}  /* while  */
		/*  NUEVO ULTIMO NODO  */
		PN->SIG = NULL ;
		ANT->SIG = PN ;			
}


void LISTA::MIRAR()
{
		NODO * P ;
		cout << "\n\n\n\t\t\t CONTENIDO DE LA LISTA \n\n";
		
		P = INICIO ;
		while (P) {
				cout << "\n\n\t\t\t " << P->NOM ;
				P = P->SIG ;			
		}
		getchar();		
}


void LISTA::MENOR()
{
		if ( INICIO ) 
				cout << "\n\n  EL MENOR ES  " << MINIMO()->NOM ;	
}

NODO * LISTA::MINIMO()
{
		NODO * P , * PMIN ;
		PMIN = P = INICIO ;
		
		while ( P ) {
				if ( strcmp (P->NOM,PMIN->NOM) < 0 )
						PMIN = P ;
				P = P->SIG ;
		}
		return PMIN ;		
}

void LISTA::MAYOR()
{
		if ( INICIO ) 
				cout << "\n\n  EL MAYOR ES  " << MAXIMO()->NOM ;	
}

NODO * LISTA::MAXIMO()
{
		NODO * P , * PMAX ;
		PMAX = P = INICIO ;
		
		while ( P ) {
				if ( strcmp (P->NOM,PMAX->NOM) > 0 )
						PMAX = P ;
				P = P->SIG ;
		}
		return PMAX ;		
}

NODO * LISTA::BUSCAR( char * S )
{
		NODO * P ;
		P = INICIO ;
		
		while ( P ) {
				if ( ! strcmp ( P->NOM , S ) )
						return P ;
				P = P->SIG ;
		}
		return NULL ;		
}

void LISTA::ELIMINAR(char * S)
{
		NODO * P ;
		
		P = BUSCAR(S) ;
		
		if ( P )
				MATAR(P) ;
}

void LISTA::MATAR( NODO * PELIM )
{
		NODO * P ;
		P = INICIO ;	
	
		if ( INICIO == PELIM ) {
				/*  PRIMER NODO   */
				INICIO = PELIM->SIG ;
				delete PELIM ;
				return ;
		}
		/*  NO ES PRIMER NODO   */
		while ( P->SIG != PELIM && P )
				P = P->SIG ;
		/*  P APUNTA AL NODO ANTERIOR A PELIM  */
		if (P) {
//				P->SIG = PELIM->SIG ;
				P->SIG = P->SIG->SIG ;
				delete PELIM ;
		}
}


void LISTA::SACAR( NODO * PELIM )
{
		NODO * P ;
		P = INICIO ;	
	
		if ( INICIO == PELIM ) {
				/*  PRIMER NODO   */
				INICIO = PELIM->SIG ;
				return ;
		}
		/*  NO ES PRIMER NODO   */
		while ( P->SIG != PELIM && P )
				P = P->SIG ;
		/*  P APUNTA AL NODO ANTERIOR A PELIM  */
		if (P) 
				P->SIG = P->SIG->SIG ;
}


void LISTA::ORDENAR1()
{
		NODO * P , * AUXINI ;
		AUXINI = NULL ;
		
		while ( INICIO ) {
				P = MAXIMO() ;
				SACAR(P) ;
				P->SIG = AUXINI ;
				AUXINI = P ;			
		}	
		INICIO = AUXINI ;
}

void LISTA::ORDENAR2()
{
		NODO * P ;
		LISTA AUXL ;
				
		while ( INICIO ) {
				SACAR(P = INICIO) ;
				AUXL.INSERT(P) ;
		}	
		INICIO = AUXL.INICIO ;
		AUXL.INICIO = NULL ;
}


char * GENERANOM();

int main()
{
		LISTA L ;
		char BUF[20] ;
		
		strcpy ( BUF , GENERANOM() );
		while ( strcmp(BUF,"FIN") ) {
				L.AGREGAR_F(BUF) ;
			
				strcpy ( BUF , GENERANOM() );
		}
		
		L.MIRAR() ;
		
//		L.MENOR() ;
//		L.MAYOR() ;				
								
//		cout << "\n\n\t NOMBRE A ELIMINAR  :  ";
//		cin >> BUF ;
//		L.ELIMINAR(BUF) ;						
		
		L.ORDENAR2() ;
		
								
		L.MIRAR() ;
								
		printf("\n\n\n\n FIN DEL PROGRAMA\n\n");
		return 0 ;
}

char * GENERANOM()
{
		static int I = 0 ;
		static char NOM[][20] = {"FELIPE","ANA","LAURA","CACHO",
						  "PEPE","LOLA","LUIS","PACO",
						  "LUCRECIA","CAROLINA","ENZO","BETO","FIN"};
		return NOM[I++] ;	
}
