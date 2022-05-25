/*Ejercicio 2 Javier Frias 40212221*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef char string[40];

typedef struct{
	int numeroTurno;
	string nombrePaciente;
	int localidad;
}tDatosPaciente;

typedef struct nodo{
	tDatosPaciente clientes;
	struct nodo * siguiente;
}tApNodo;

typedef struct{
	tApNodo * principio;
	tApNodo * final;
}tCola;

tCola colaHisopar;
tDatosPaciente C;

void inicializarCola();
void ingresarDatos();
bool colaVacia();
void encolar(tDatosPaciente);
void desencolar();
void visualizarCola();
tDatosPaciente primerPaciente();
int totalFaltante();
int testPorLocalidad(tDatosPaciente );
void menu();



int main(){
	inicializarCola();
	menu();
	return 0;
}

void inicializarCola(){
	colaHisopar.principio = NULL;
	colaHisopar.final = NULL;
}

void ingresarDatos(){
	fflush(stdin);
	printf("Ingrese el numero de turno:  ");
	scanf("%d",&C.numeroTurno);
	fflush(stdin);
	printf("\nIngrese el nombre y apellido del paciente:  ");
	gets(C.nombrePaciente);
	fflush(stdin);
	printf("\nIngrese localidad localidad(1.Capital, 2.Richuelo, 3.Santa Ana, 4.Paso de la Patria, 5.San Cosme):  ");
	scanf("%d",&C.localidad);
	fflush(stdin);	
}

bool colaVacia(){
	if(colaHisopar.final == NULL){
		return true;
	}
	else{
		return false;
	}
}

void encolar(tDatosPaciente p_Datos){
	tApNodo * nuevoPaciente;
	nuevoPaciente = malloc(sizeof(tApNodo*));
	nuevoPaciente->clientes = p_Datos;
	nuevoPaciente->siguiente = NULL;
	if(colaVacia() == true){
		colaHisopar.principio = nuevoPaciente;
		colaHisopar.final = nuevoPaciente;
	}
	else{
		colaHisopar.final->siguiente = nuevoPaciente;
		colaHisopar.final = nuevoPaciente;
	}
	printf("Paciente insertado!\n");
}
	

void desencolar(){
	tApNodo * aux;
	aux = colaHisopar.principio; 
	if(colaVacia()==true){
		printf("La cola esta vacia!");
	}
	else{
		while(aux!=NULL){
			if(colaHisopar.principio == colaHisopar.final){
				free(aux);
				colaHisopar.principio = NULL;
				colaHisopar.final = NULL;
				printf("Cliente borrado!");
			}
			else{
				colaHisopar.principio = aux->siguiente;
				free(aux);
				printf("Cliente borrado!");
			}
			aux = aux->siguiente; 
		}
	}
}

void visualizarCola(){
	tApNodo * aux;
	if(colaVacia()==true){
		printf("Cola vacia!");
	}
	else{
		aux = colaHisopar.principio;
		printf("\n\nTest pendientes de analisis:\n");
		printf("Numero\t\tPaciente\t\tCodigo de localidad:\n");
		while(aux!=NULL){
			printf("%d\t\t",aux->clientes.numeroTurno);
			printf("%s\t\t",aux->clientes.nombrePaciente);
			printf("%d\n",aux->clientes.localidad);
			aux = aux->siguiente;
		}
		printf("\n\n\n");
	}
		
}

int totalFaltante(){
	int contador=0;
	tApNodo * aux;
	if(colaVacia()==true){
		printf("Cola vacia!");
	}
	else{
		aux = colaHisopar.principio;
		while(aux!=NULL){
		contador++;
			aux = aux->siguiente;
		}
	}
	return contador;
}

int testPorLocalidad(tDatosPaciente C){
	tApNodo * aux;
	int personasLocalidad = 0;
	aux = colaHisopar.principio;
	if(colaVacia()!=true){
		while(aux!=NULL){
			if(aux->clientes.localidad == 2){
				personasLocalidad++;
			}
			aux = aux->siguiente;
		}
	}
	printf("La cantidad de test para realidar en la localidad %d es de %d", aux->clientes.localidad, personasLocalidad);
	return personasLocalidad;
	
}

void menu(){
	fflush(stdin);
	int opcion = 0;
	printf("\n*****MENU DE OPCIONES*****\n");
	printf("1) Angregar un paciente a la cola - \n2) Elimine un paciente que ya fue hisopado - \n3) Visualice los pacientes\n");
	printf("4) Mostrar pacientes que faltan hisopar\n");
	printf("7) Pulse 0 p/salir\n");
	printf("Ingresar opcion [ ]\b\b");
	scanf("%d",&opcion);
	fflush(stdin);
	switch(opcion){
		case 1: {
			ingresarDatos();
			encolar(C);
			menu();	
			break;
		}
		case 2:{
			desencolar();
			menu();
			break;
		}
		case 3:{
			visualizarCola();
			menu();
			break;
		}
		case 4:{
			printf("\n\n\nEn total faltan %d pacientes por hispoar\n\n\n", totalFaltante());
			menu();
			break;
		}
	}
}
