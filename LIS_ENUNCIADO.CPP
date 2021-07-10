/*  LA CLASE LISTA TIENE NODOS CON NOMBRE Y PUNTAJE DE PERSONALIDADES  */
/*  QUE COMPITEN EN UN CONCURSO DE POPULARIDAD  */
/*  LA CLASE LISTA NEGRA, TIENE VOTOS NEGATIVOS SOBRE CADA UNO DE LOS  */
/*  CANDIDATOS  */
/*  SE DEBE ACTUALIZAR LISTA HACIENDO QUE POR CADA VOTO NEGATIVO EN    */
/*  LISTANEGRA, SE LE DESCUENTE UN PUNTO AL CANDIDATO. EN CASO QUE ESTE */
/*  NO POSEA MAS PUNTOS, SE LO DEBE DAR DE BAJA  */
/*  CONSTRUIR LA FUNCION IMPUGNA(), CUYO PROTOTIPO SE ADJUNTA, DE FORMA */
/*  QUE REALICE LO PEDIDO */
/*  REALIZAR EL AGREGADO EN LAS CLASES QUE CONSIDERE CONVENIENTE  */


#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define MAX_VOTOS 15 

using namespace std ;
class LISTANEGRA;

class CANDI {
	public :
		char NOM[20];
		int VOTOS ;
		CANDI * SIG ;
};

class LISTA {
	private :
		CANDI * INICIO ;
		CANDI * AUX ;
	public :
		LISTA() ;
		~LISTA();
		void MIRAR() ;
		void friend IMPUGNA ( LISTA & , LISTANEGRA & );
};

LISTA :: LISTA ()
{
	int I ;
	CANDI * P ;
	char NOM[][20] = { "PEPE" , "LOLA" , "LAURA" , "CACHO" ,
			   "ANSELMO" , "MARIANO" , "MONICA" , "ANA" ,
			   "EDELMIRO" , "JOSE" , "MIRTA" , "SUSANA" ,
			   "FELIPE" , "ENZO" , "BETO" , "PACO" } ;
	INICIO = NULL ;
	for ( I=0 ; I<16 ; I++ ) { /*ACA TENEMOS QUE SABER CUANTOS SE INGRESARON */
		P = new CANDI ;
		strcpy ( P->NOM , NOM [ I ] ) ;
		P->VOTOS = 1 + rand()% MAX_VOTOS ; /*QUE ES ESA FUNCION*/
		P->SIG = INICIO ; 
		INICIO = P ;
	}
	
	AUX = INICIO; 
}

LISTA :: ~LISTA ()
{
	CANDI * P ;
	P = AUX ; 
	 
	while ( P )
	{
		if(P->VOTOS<=0)
		{
			cout << "\nDANDO DE BAJA A: " << P->NOM  << "\n";
			delete P ;	
		}	
			
		P=P->SIG ; 
	}
}

void LISTA :: MIRAR ()
{
	CANDI * P ;
	P = INICIO ;

		if( !P)
			P=AUX;
	cout << "\n\n\n" ;
	while ( P ) {
		printf ( "     %-10s%5d" , P->NOM , P->VOTOS) ;
		P = P->SIG ;
	}
	getch();
}

class PERSONA {
	public :
		char NOM[20];
		PERSONA * SIG ;
};

class LISTANEGRA {
	private :
		PERSONA * INICIO ;
	public :
		LISTANEGRA() ;
		void MIRAR() ;
		void friend IMPUGNA ( LISTA & , LISTANEGRA & );
};

LISTANEGRA :: LISTANEGRA ()
{
	int I ;
	PERSONA * P ;
	char NOM[][20] = { "PEPE" , "LOLA" , "LAURA" , "CACHO" ,
			   "ANSELMO" , "MARIANO" , "MONICA" , "ANA" ,
			   "EDELMIRO" , "JOSE" , "MIRTA" , "SUSANA" ,
			   "FELIPE" , "ENZO" , "BETO" , "PACO" } ;
	INICIO = NULL ;
	for ( I=0 ; I<100; I++ ) {
		P = new PERSONA ;
		strcpy ( P->NOM , NOM [ rand()%16 ] ) ;
		P->SIG = INICIO ;
		INICIO = P ;
	}
}

void LISTANEGRA :: MIRAR ()
{
	PERSONA * P ;
	P = INICIO ;
	cout << "\n\n\n" ;
	while ( P ) {
		printf ( "%-10s" , P->NOM ) ;
		P = P->SIG ;
	}
	getch();
}


/*  PROTOTIPO  */
void IMPUGNA ( LISTA & , LISTANEGRA & );

void IMPUGNA ( LISTA & X, LISTANEGRA & Y)
{
	while (Y.INICIO)	/*VA A DEJAR DE COMPARAR CUANDO LISTA NEGRA LLEGUE A NULL*/
	{
		X.INICIO=X.AUX; 
		while(X.INICIO) /*VA SALIR CUANDO LA LISTA LLEGUE A NULL O CUANDO EL NOMBRE SEA IGUAL*/
		{
			if( !strcmp(X.INICIO->NOM, Y.INICIO->NOM))	
			{
				X.INICIO->VOTOS=X.INICIO->VOTOS-1;
				
				//cout << "X:" << X.INICIO->NOM << "	Y:" << Y.INICIO->NOM ;
			}	
			X.INICIO=X.INICIO->SIG;
		}	
		Y.INICIO=Y.INICIO->SIG;
	}
}


int main()
{
	LISTA L ;
	LISTANEGRA N ;
	
	cout << "\n	LISTA ORIGINAL";
	L.MIRAR() ;
	
	//N.MIRAR() ;

    IMPUGNA ( L , N );
	
	cout << "\n\n	LISTA ACTUALIZADA";
	L.MIRAR() ;

	cout << "\n\n\nFIN DEL PROGRAMA  \n" ;
	getch();
	
	
	return 0 ;
}
