/*   CONSTRUIR LAS FUNCIONES  :        */
/*
/*   int EQUIPO::GASTOS()       QUE RETORNE EL TOTAL DE SUELDOS DEL EQUIPO       */
/*   void EQUIPO::DEPURA()      QUE ELIMINE JUGADORES (COMENZANDO POR LOS        */
/*                              MAS CAROS) HASTA QUE LOS SUELDOS SEAN MENORES    */
/*                              QUE EL PRESUPUESTO DEL EQUIPO                    */
/*   void GUIRNALDA::DEPURA()   QUE PRODUZCA LA DEPURACION DE TODOS LOS EQUIPOS  */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>

using namespace std;

class JUGADOR {
		public :
			char NOM[20] ;
			int SUELDO ;
			JUGADOR * SIG ;
			JUGADOR(char *);
			~JUGADOR();	
};

JUGADOR::JUGADOR(char * S)
{
		strcpy ( NOM , S ) ;
		int VAL = 10*(rand()%40000); 
		SUELDO = 200000 + VAL ;
		SIG = NULL ;
}
JUGADOR::~JUGADOR()
{
		cout << "\n\n   MATANDO A ... " << NOM << "		DIR:  " << SIG <<"\n\n";
		getchar();
}

class EQUIPO {
		public :
			char NOM[20] ;
			int PRESUPUESTO ;
			JUGADOR * PUNJU ;
			EQUIPO * SIG ;
			EQUIPO ( char * , JUGADOR * ) ;
			~EQUIPO() ;	
			int GASTOS(EQUIPO * INICIO);
			void SUELDOMAX(EQUIPO *);
			void ELIMINAR(EQUIPO * , JUGADOR * ) ;
			void DEPURA(EQUIPO *);
};


EQUIPO::EQUIPO ( char * S , JUGADOR * CAPITAN )
{
		strcpy ( NOM , S ) ;
		PRESUPUESTO = 1000000 + rand()%2000000 ;
		PUNJU = CAPITAN ;
}

EQUIPO::~EQUIPO()
{
		cout << "\n\n   MATANDO A ... TODOS LOS JUGADORES\n\n";
		cout << "\n\n   TAREA PARA USTEDES \n\n";
		getchar();
}

EQUIPO::GASTOS(EQUIPO * DIR)  
{
	EQUIPO * PEQUIPO;
	
	JUGADOR * PJUGADOR;
	
	int GASTOS=0;
	
	PEQUIPO = DIR ; 			//ME PARO EN EL EQUIPO QUE QUIERO SABER EL SUELDO
	
	PJUGADOR=PEQUIPO->PUNJU;		////ME PARO EN EL PRIMER JUGADOR
		
	while(PJUGADOR)	
	{
		GASTOS=GASTOS+PJUGADOR->SUELDO;
			
		PJUGADOR=PJUGADOR->SIG;
	}

	return GASTOS;
}

void EQUIPO::SUELDOMAX(EQUIPO * DIR)
{
	EQUIPO * PEQUIPO;
	
	JUGADOR * PJUGADOR, * PJUGADORAUX ; 				/*EL PUNTERO PJUGADORAUX VA A GUARDAR LA DIRECCION DEL SUELDO MAX*/
	
	int MAX=0;
	
	PEQUIPO=DIR;
	
	PJUGADOR=PEQUIPO->PUNJU;
	
	while(PJUGADOR)
	{
		if(MAX < PJUGADOR->SUELDO)
		{
			MAX=PJUGADOR->SUELDO;
			
			PJUGADORAUX = PJUGADOR;
		}
			
		PJUGADOR=PJUGADOR->SIG;
	} 
	
	cout << "\n\n\n		***EL SUELDO MAXIMO ES: " << MAX << "\n" ;
	
	ELIMINAR(DIR,PJUGADORAUX);
}

void EQUIPO::ELIMINAR(EQUIPO * DIR , JUGADOR * PJUGADORELIM )
{
	EQUIPO * PEQUIPO;
	
	JUGADOR * PJUGADOR;
	
	PEQUIPO=DIR;
	
	PJUGADOR=PEQUIPO->PUNJU;
	
	if(PJUGADORELIM==PJUGADOR)
	{
		PEQUIPO->PUNJU=PJUGADORELIM->SIG ;
		delete PJUGADORELIM;	
	}	
	else 
	{
		while( PJUGADOR->SIG!= PJUGADORELIM ) 	//CASO NO 1ER NODO
		PJUGADOR=PJUGADOR->SIG;
		
		PJUGADOR->SIG=PJUGADORELIM->SIG ;
		
		delete PJUGADORELIM ;
	};
	
	PJUGADOR=PEQUIPO->PUNJU;
	
	while(PJUGADOR)
	{
		printf("\n\n\t\t%-15s%20d" , PJUGADOR->NOM , PJUGADOR->SUELDO ) ;
		
		PJUGADOR=PJUGADOR->SIG;
	}
}

void EQUIPO::DEPURA(EQUIPO * INICIO)
{
	EQUIPO * PEQUIPO;
	
	JUGADOR * PJUGADOR;
	
	PEQUIPO=INICIO;
	
	while(PEQUIPO)
	{
		while( PEQUIPO->PRESUPUESTO < PEQUIPO->GASTOS(PEQUIPO) )
			PEQUIPO->SUELDOMAX(PEQUIPO);
		
	PEQUIPO=PEQUIPO->SIG;
	}
}

class GUIRNALDA {
		private :
			EQUIPO * INICIO ;
			EQUIPO * BUSCAR ( char * );
		public :
			GUIRNALDA() ;
			~GUIRNALDA() ;
			void ARREGLATE(char *);
			void MIRAR();
			void DEPURA();
};

GUIRNALDA::GUIRNALDA()
{
		INICIO = NULL ;
}


GUIRNALDA::~GUIRNALDA()
{
		cout << "\n\n   QUE SE VAYAN TODOS !!! DESTRUYENDO PARTIDOS" ;
		cout << "\n\n   OTRA QUE ES PARA USTEDES " ;
		getchar();
}


EQUIPO * GUIRNALDA::BUSCAR(char * S)
{
		EQUIPO * P ;
		P = INICIO ;
		
		while ( P ) {
				if ( ! strcmp(P->NOM,S) )			
						return P ;			
				P = P->SIG ;			
		}
		return NULL ;
}


void GUIRNALDA::ARREGLATE ( char * S )
{
		char * GENERAEQUIPO() ;				/*  PROTOTIPO  */
		
		JUGADOR * PAL , * P ;
		EQUIPO * PEQUI ;
		char BUF[20] ;
	
		PAL = new JUGADOR(S) ;
		
		strcpy ( BUF, GENERAEQUIPO() );
		
		PEQUI = BUSCAR(BUF) ;

		if ( PEQUI ) {
				/*  PARTIDO EXISTENTE  */
				P = PEQUI->PUNJU ;
				while ( P->SIG )
						P = P->SIG ;  /* VOY HASTA EL ULTIMO ALUMNO */
				P->SIG = PAL ;
				return ;			
		}		
		/*   PARTIDO NUEVO    */
		PEQUI = new EQUIPO(BUF,PAL) ;
		PEQUI->SIG = INICIO ;
		INICIO = PEQUI ;
}

void GUIRNALDA::MIRAR()
{
		EQUIPO * PEQUI ;
		JUGADOR * PAL ;
	
		cout << "\n\n  CONTENIDO DE LA GUIRNALDA\n\n\n";
		PEQUI = INICIO ;
		while ( PEQUI ) {
					printf("\n\n\n\n\t\t%-15s%20d\n" , PEQUI->NOM , PEQUI->PRESUPUESTO ) ;
					
					cout << "\n		GASTOS DEL EQUIPO:	    " << PEQUI->GASTOS(PEQUI) << "\n";
					
					PAL = PEQUI->PUNJU ;
					while ( PAL ) {
							printf("\n\n\t\t%-15s%20d" , PAL->NOM , PAL->SUELDO ) ;
			
							PAL = PAL->SIG ;
					}
					getchar();
						
					PEQUI = PEQUI->SIG ;
		}
}



void GUIRNALDA::DEPURA()
{
	EQUIPO * PEQUIPO;
	
	JUGADOR * PJUGADOR;
	
	PEQUIPO=INICIO;
		/*DEPURA LOS EQUIPOS...VA HACER FUNCIONAR A MI FUNCION EQUIPO::DEPURA*/
	PEQUIPO->DEPURA(INICIO);
}

char * GENERANOM();

int main()
{  
		char BUF[20] ;
		GUIRNALDA G ;
		
		srand(105);
		
		strcpy( BUF , GENERANOM() ) ;
		while ( strcmp (BUF,"FIN") ) {
				G.ARREGLATE(BUF) ;
				
				strcpy( BUF , GENERANOM() ) ;
		}
		
		G.MIRAR() ;		
		
		G.DEPURA() ;		
		G.MIRAR() ;		
		
		printf("\n\n      FIN DEL PROGRAMA");	
		return 0 ;
}


char * GENERANOM()
{
		static char NOM[][20] = {"MARADONA","RONALDO","MESSI",
						  "PELE","MESSI","LABRUNA",
						  "ORTEGA","RIQUELME","ROMA","CARRIZO",
						  "LORENZO","BOBBY MOORE","RONALDINHO","ARMANI",
						  "TARANTINI","RATTIN","ROSSI","ONEGA",
						  "ARTIME","VARACKA","GALLARDO","TEVEZ",
						  "MORETE","ERICO","LABRUNA","MORENO",
						  "PEDERNERA","LOUSTEAU","CAVENAGHI","NAVARRO",
						  "PAVONI","VERON","MESSI","RONALDO",
						  "PERFUMO","MATOSAS","PELE",
						  "CUBILLA","SANTORO","MALBERNAT","BECKENBAUER",
						  "EUSEBIO","PASTORIZA","JAIRZINHO","ROJAS",
						  "MADURGA","PIANETTI","ANDRADA","MARIN",
						  "ROMERO","ALONSO","FRANCESCOLI","DOMINGUEZ",
						  "MAYADA","MORA","MASCHERANO","KRANEVITER",
						  "SOLARI","MATURANA","BOBY MOORE",
						  "HIGUITA","BASILE","FRANCESCOLI",
						  "SARNARI","BILARDO","BATISTUTA","VALENTIM",
						  "CRISTIANO","ZAMORANO","SALAS","ARDILES",
						  "KEMPES","ZANABRIA","OLGUIN","PALACIOS",
						  "MESSI","VERON","FIN"};
		static int I = 0 ;
		return NOM[I++] ;	
}


char * GENERAEQUIPO()
{
		static char NOM[][20] = {"BARCELONA","RIVER","BOCA","JUVENTUS",
						  		 "MILAN","REAL MADRID","DYNAMO",
								 "BOTAFOGO","COLO COLO","PEÑAROL",
								 "RACING","INDEPENDIENTE"  };
		return NOM[rand()%12] ;	
}

