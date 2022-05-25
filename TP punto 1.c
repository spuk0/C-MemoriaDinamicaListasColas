/* Ejercicio 1  Javier Frias 40212221*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* Tipos de datos personalizados */
typedef char tString[20];

typedef struct {
	tString diaMes;
	int localidad;
	int casosDia; 
	tString imc;		
} tDatos;


typedef struct nodo {
	tDatos encuestado;
	struct nodo * siguienteEncuestado;
} tListaEncuestados;

tListaEncuestados * encuestados;

/* Declaración de prototipos */
void inicializarListaEncuestados();
bool listaVacia( tListaEncuestados * );

void insertarEncuestado( tDatos );
void eliminarK( int k );


void visualizarElementos( tListaEncuestados * );
void visualizarTotal( tListaEncuestados * );

void mostrarMenu();

/* Bloque principal */
int main() {
	inicializarListaEncuestados(); 
	mostrarMenu();	
	return 0;
}

void inicializarListaEncuestados() {
	encuestados = NULL;
	printf("Lista de casos creada!\n");
}

bool listaVacia( tListaEncuestados * pEncuestados ) {
	return ( pEncuestados == NULL );
}

void insertarEncuestado( tDatos pEncuestado ) {
	tListaEncuestados * nuevoEncuestado;
	
	nuevoEncuestado = ( tListaEncuestados * ) malloc( sizeof( tListaEncuestados ) );
	
	nuevoEncuestado->encuestado = pEncuestado;
	
	if ( listaVacia( encuestados ) ) {
		 nuevoEncuestado->siguienteEncuestado = NULL;
	} else {
		nuevoEncuestado->siguienteEncuestado = encuestados;
	}
	
	encuestados = nuevoEncuestado;
	
	printf("Caso insertado!\n");	
}

void visualizarElementos( tListaEncuestados * pEncuestados ) {
	tListaEncuestados * auxEncuestados;
	
	auxEncuestados = pEncuestados;
	
	if( listaVacia( auxEncuestados ) ) {
		printf("\nNo hay casos!\n");
	} else {
		/* Recorrer la lista */
		printf("\n*************************************************\n");
		printf("Seguimiento de COVID-19 en las localidades de la provincia:\n");
		printf("\nDia\t\tLocalidad\t\tPositivos Detectados\n");
		while ( auxEncuestados != NULL) {
			
			printf( "%s\t\t %d\t\t\t\t %d \n", auxEncuestados->encuestado.diaMes, auxEncuestados->encuestado.localidad, auxEncuestados->encuestado.casosDia  );
			
			auxEncuestados = auxEncuestados->siguienteEncuestado;
		}
		printf("\n*************************************************\n");
	}		
}

void eliminarK( int k ) {	
	tListaEncuestados * aux;
	tListaEncuestados * nodoSuprimir;
	int i;
	
	if ( k==1 ) {
	tListaEncuestados * encuestadoSuprimir;
	
	encuestadoSuprimir = encuestados;
	
	encuestados = encuestados->siguienteEncuestado;
	
	printf( "Registro de localidad %d eliminado!\n", encuestadoSuprimir->encuestado.localidad );
	
	free( encuestadoSuprimir );
	encuestadoSuprimir = NULL;	
	}else{
		
		aux = encuestados;
		
		for ( i=1; i < k-1; i++) {
			aux = aux->siguienteEncuestado;
		}
		
		nodoSuprimir = aux->siguienteEncuestado;
	
		aux->siguienteEncuestado = nodoSuprimir->siguienteEncuestado;
		
		printf( "\Registro de localidad eliminado: %d\n", nodoSuprimir->encuestado.localidad );	
	
		free( nodoSuprimir );	
		nodoSuprimir = NULL;	
	}
	
}

void visualizarTotal( tListaEncuestados * pEncuestados){
	tListaEncuestados * auxEncuestados;
	
	auxEncuestados = pEncuestados;
	int i=0;
	int casos1=0;
	int casos2=0;
	int casos3=0;
	int casos4=0;
	int casos5=0;	
	if( listaVacia( auxEncuestados ) ) {
		printf("\nNo hay encuestados!\n");
	} else {
		/* Recorrer la lista */
		printf("\nTotal de casos positivos por localidad:\n");
		while ( auxEncuestados != NULL) {
			if(auxEncuestados->encuestado.localidad==1){
				casos1=casos1+auxEncuestados->encuestado.casosDia;
			}
			if(auxEncuestados->encuestado.localidad==2){
				casos2=casos2+auxEncuestados->encuestado.casosDia;
			}
			if(auxEncuestados->encuestado.localidad==3){
				casos3=casos3+auxEncuestados->encuestado.casosDia;
			}
			if(auxEncuestados->encuestado.localidad==4){
				casos4=casos4+auxEncuestados->encuestado.casosDia;
			}
			if(auxEncuestados->encuestado.localidad==5){
				casos5=casos5+auxEncuestados->encuestado.casosDia;
			}
			auxEncuestados = auxEncuestados->siguienteEncuestado;
		}
		printf("\n1\t %d", casos1);
		printf("\n2\t %d", casos2);
		printf("\n3\t %d", casos3);
		printf("\n4\t %d", casos4);
		printf("\n5\t %d", casos5);
	}		
	
}

void mostrarMenu() {
	char opcion, agregarOtro;
	tDatos e;	
	int k;
	
	agregarOtro = 's';	
	
	printf("\n\t\t*** MENU ***\n");
	printf("\tOpciones disponibles:\n");
	printf("\ta-Insertar un nodo en la lista. \n\tb-Eliminar un nodo en una posicion especifica de la lista. \n");
	printf("\tc-Visualizar todos los datos que estan en la lista \n\td-Visualizar los totales de casos positivos detectados por localidad \n");
	printf("\tx-Finalizar sesion\n");
	
	printf("\tSeleccione una opcion: ");
	fflush( stdin );
	scanf( "%c", &opcion );
	
	opcion = tolower( opcion );
	
	switch ( opcion ) {
		case 'a': 	/* Agregar caso */
					while ( agregarOtro == 's' ) {
						printf( "Ingrese: \n" );
						printf("\tDia y mes de registro 00/00:" );
						scanf("%s", &e.diaMes);
						printf("\tLocalidad (1.Capital, 2.Richuelo, 3.Santa Ana, 4.Paso de la Patria, 5.San Cosme): " );
						fflush( stdin );
						scanf("%d", &e.localidad);
						printf( "\tCasos por dia " );
						scanf("%d", &e.casosDia);

						insertarEncuestado( e );
						
						printf("\tAgregar otra encuesta? s/n: " );
						fflush( stdin );
						scanf("%c", &agregarOtro);						
					}
				
					mostrarMenu();
					break;
		case 'b': /* Visualizar lista de casos */
					visualizarElementos( encuestados );
					mostrarMenu();
					break;
		case 'c': /* Eliminar caso de posicion determinada  */
					printf( "\tUbicacion del nodo del encuestado que desea eliminar: " );
					scanf("%d", &k);
					eliminarK( k );
					mostrarMenu();
					break;
		case 'd': /* Visualizar total de casos por localidad */
					visualizarTotal( encuestados );
					mostrarMenu();
					break;
		case 'x': printf( "Sesion finalizada\n" );
	}
	
}



