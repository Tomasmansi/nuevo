/* Este pequeño ejercicio simula ser la caja de un supermercado.
En el main ya existen datos predeterminados para hacer las pruebas.
Puede modificarse para que el usuario ingrese los datos si se quiere.*/

/* Estos define indican qué día de la semana tengo descuento si pago con cierta
tarjeta, y el descuento correspondiente (en %). El dia 0 es domingo. */

#define VISA_DIA 2
#define VISA_DESC 20
#define MASTERCARD_DIA 4
#define MASTERCARD_DESC 25

/* Deben completarse estas dos clases y los métodos necesarios
para que funcione el main dado */

class Articulo {
	private:
			char articulo[20];
			int cantidad;
			float precio;
	}

class Supermercado {
	private:
			char articulo[20];
			int cantidad;
			float precio;
	
	public:
			Supermercado();
			~Supermercado();
			
			void agregar(char* , int , float);
			void calcularCantArticulos(void);
			void calcularTotal();
			setDiaDeCompra(int);
			setTarjetaCredito(char*);
}

void agregar(char* nombre, int cant, float valor)
{
	articulo=nombre;
	cantidad=cant;
	precio=valor;
};

void calcularCantArticulos(void)
{

}

int main() {
	
	Supermercado * s = new Supermercado[5];

	s->agregar("Cafe", 1, 124.5);  // nombre, cantidad, precio unitario
	s->agregar("Leche", 2, 55);
	s->agregar("Cerveza", 2, 130.7); //se sabe que la compra nunca tendrá más de 100 productos

	cout << "Cant. artículos: " << s->calcularCantArticulos() << endl;  //debe dar 5
	cout << "Total: $ " << s->calcularTotal() << endl;

	s->setDiaDeCompra(4);  //jueves
	s->setTarjetaCredito("5511222233334444"); 	//tarjetas que comienzan con 4 son visa
												//tarjetas que comienzan con 51, 52, 53, 54 o 55 son mastercard

	if(s->tieneDescuento()) 
		cout << "Total con descuento: $" << s->calcularTotalConDescuento();
	else
		cout << "No tiene descuento con su tarjeta " << s->getNombreTarjeta() << " el dia " << s->getNombreDia();

	return 0;
}
