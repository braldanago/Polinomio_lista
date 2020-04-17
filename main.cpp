//BRAYAN STEVEN ALDANA GOMEZ 20152020042	
//DIEGO DAYAN GUERRA 201520200

#include <iostream>
#include <math.h>
#include <conio.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

struct Nodo{
	float coeficiente;
	int expo;
	Nodo *sig;
};

class Polinomio{
	Nodo *cab;
	//Metodos
	void agregar(int,float);
	void ordenar();
	public:
		Polinomio ();
		void cargar();
		void mostrar();
		void operator=(Polinomio);/////
		float evaluar(float);
		void derivada();
		void integrar();
		float integrar(float,float);
		Polinomio operator +(Polinomio);////
		Polinomio operator -(Polinomio);/////
		
};

//Constructor
Polinomio::Polinomio(){
	cab=NULL;
}

//Metodo para agregar terminos al polinomio
void Polinomio::agregar(int expo,float coef){
	Nodo *p= new Nodo;
	p->expo=expo;
	p->coeficiente=coef;
	p->sig=cab;
	cab=p;
}

////Metodo para ordenar terminos del polinomio
void Polinomio::ordenar(){
	Nodo *p=cab,*q;
	int expo;
	float coef;
	while(p->sig){//diferente de nulo
		q=p->sig;
		while(q){
			if(p->expo<q->expo){
				expo=p->expo;
				coef=p->coeficiente;
				p->expo=q->expo;
				p->coeficiente=q->coeficiente;
				q->expo=expo;
				q->coeficiente=coef;
			}
			q=q->sig;
		}
		p=p->sig;
	}
}

//Metodo para cargar terminos al polinomio con la funcion agregrar
void Polinomio::cargar(){
	int expo;
	float coef;
	cout<<"Digite el exponente: "<<endl;
	cin>>expo;
	while(expo>=0){
		cout<<"Digite el coeficiente: "<<endl;
		cin>>coef;
		agregar(expo,coef);
		cout<<"Digite el exponente: "<<endl;
		cin>>expo;
	}
	ordenar();
}

//Metodo para mostrar el polinomio
void Polinomio::mostrar(){
	Nodo *p=cab;
	while(p){//diferente de nulo
		cout<<p->coeficiente<<"x^("<<p->expo<<") + ";
		p=p->sig;
	}
	cout<<"\n";
}

//Metodo para evular polinomio
float Polinomio::evaluar(float valor){
	Nodo *p=cab;
	float resultado=0;
	while(p){
		resultado = resultado + ((p->coeficiente)*pow(valor,p->expo));
		p=p->sig;
	}
	return resultado;
}

//Metodo para derivar al polinomio
void Polinomio::derivada(){
	Nodo *p=cab;
	while(p){
		if(p->expo!=0){
			cout<<p->coeficiente*p->expo<<"x^("<<(p->expo-1)<<") + ";
			p=p->sig;
		}
	}
}

//Metodo para integrar el polinomio polinomio
void Polinomio::integrar(){
	Nodo *p=cab;
	while(p){
		p->expo=(p->expo+1);
		p->coeficiente=(p->coeficiente / p->expo);
		p=p->sig;
	}
}

//Metodo para integrar definidamente polinomio
float Polinomio::integrar(float a, float b){
	float definida=0;
	integrar();
	definida = evaluar(b) - evaluar(a);
	return definida;
}

//SOBRECARGA DEL OPERADOR IGUAL
void Polinomio::operator=(Polinomio p){
	Nodo *q=p.cab;
	while(q){
		Nodo *r = new Nodo;
		r->coeficiente=q->coeficiente;
		r->expo=q->expo;
		r->sig=cab;
		cab=r;
		q=q->sig;	
	}
	ordenar();
}

//Metodo que realiza la suma de polinomios con sobrecarga
Polinomio Polinomio::operator +(Polinomio p){
	Nodo *q = p.cab;
	Nodo *r=cab;
	bool isInside=false;

	while(r){
		q=p.cab;
		while(q){
			if(q->expo==r->expo){
				q->coeficiente=q->coeficiente+r->coeficiente;
				isInside=true;
				
			}else if(q->sig==NULL && isInside==false){
				Nodo *aux = new Nodo;
				aux->coeficiente=r->coeficiente;
				aux->expo=r->expo;
				aux->sig=NULL;
				q->sig=aux;
				isInside=false;
				q=q->sig;
			}
			q=q->sig;
		}
		isInside=false;
		r=r->sig;
	}
	p.ordenar();
	return p;
}

char menu();//Metodo para el menu principal


int main(int argc, char** argv) {
	char opcion;
	Polinomio p;
	do{
		opcion=menu();
		switch(opcion){
			case 'c':
			case 'C':{
				cout<<"Ingrese el polinomio: \n";
				p.cargar();
				break;
			}
			case 'm':
			case 'M':{
				cout<<"Polinomio guardado: "<<endl;
				p.mostrar();
				break;
			}
			case 'e':
			case 'E':{
				float valor;
				cout<<"Ingrese el valor de x para evaluar: "<<endl;
				cin>>valor;
				cout<<"El resultado es: "<<p.evaluar(valor)<<endl;
				break;
			}
			case 'd':
			case 'D':{
				cout<<"La derivada del polinomio es: "<<endl;
				p.derivada();
				break;
			}
			case 'i':
			case 'I':{
				cout<<"Integracion\n";
				p.integrar();
				cout<<"Funcion Integrada\n";
				p.mostrar();
				cout<<endl;
				break;
			}
			case 'n':
			case 'N':{
				int a,b,val;
				cout<<"Integracion Definida\n";
				cout<<"Digite el valor de a: ";
				cin>>a;
				cout<<"Digite el valor de b: ";
				cin>>b;
				val=p.integrar(a,b);
				
				cout<<"Funcion Integral Definida\n";
				cout<<val<<endl;
				cout<<endl;
				break;
			}
			case 's'://PRUEBA DE OPERADOR 
			case 'S':{
				Polinomio s,t;
				cout<<"Ingrese el polinomio a sumar:"<<endl;
				s.cargar();
				cout<<"polinomio ingresado:"<<endl;
				s.mostrar();
				cout<<"se sumara al polinomio: "<<endl;
				p.mostrar();
				t=s+p;
				cout<<"Resultado de la suma: ";
				t.mostrar();
				break;
			}
			
		}
		
	}while(opcion!='t' && opcion!='T');
	return 0;
}

char menu(){
	char opcion;
	cout<<"  \n MENU \n";
	cout<<"(C)argar\n";
	cout<<"(M)ostrar\n";
	cout<<"(E)valuar\n";
	cout<<"(D)erivar\n";
	cout<<"(I)ntegrar\n";
	cout<<"I(N)tegral definida\n";
	cout<<"(S)umar\n";
	cout<<"(R)estar\n";
	cout<<"(T)erminar\n";
	cout<<"Escoja una opcion\n";
	cin>>opcion;
	return opcion;
	
}
