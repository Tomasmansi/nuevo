
/*
Una imprenta recibe órdenes de trabajo y las asigna a 
cierta máquina para ser impreso.

Se sabe que la imprenta no tiene más de 10 máquinas y que
cada máquina nunca tiene más de 50 órdenes.
*/

#define ORDEN_ESPERANDO 1
#define ORDEN_IMPRIMIENDO 2
#define ORDEN_TERMINADO 3

class OrdenTrabajo {};
class Maquina { /* aquí vector de órdenes */};
class Imprenta { /* aquí vector de máquinas */ };



int main() {
	
	Imprenta * i = new Imprenta();

	i->agregarMaquina(new Maquina("MAQ1"));
	i->agregarMaquina(new Maquina("MAQ2"));

	i->agregarOrden(new OrdenTrabajo("ORDEN1", "MAQ1");
	i->agregarOrden(new OrdenTrabajo("ORDEN2", "MAQ2");
	i->agregarOrden(new OrdenTrabajo("ORDEN3", "MAQ2");

	i->verEstadoOrden("ORDEN1");  // Esperando
	i->comenzar("ORDEN1");
	i->verEstadoOrden("ORDEN1");  // Imprimiendo

	i->comenzar("ORDEN2");

	i->marcarTerminado("ORDEN1");
	i->verEstadoOrden("ORDEN1");  // Terminado

	cout << i->cantOrdenesEsperando("MAQ1"); // 0
	cout << i->cantOrdenesImprimiendo("MAQ1"); // 0
	cout << i->cantOrdenesTerminadas("MAQ1"); // 1
	cout << i->cantOrdenesEsperando("MAQ2"); // 1
	cout << i->cantOrdenesImprimiendo("MAQ2"); // 1
	cout << i->cantOrdenesTerminadas("MAQ2"); // 0

	i->trasladarOrden("ORDEN3", "MAQ1");
	cout << i->cantOrdenesEsperando("MAQ1"); // 1
	cout << i->cantOrdenesEsperando("MAQ2"); // 0

	return 0;
}