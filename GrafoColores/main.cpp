#include "GrafoColores.h"

#include "iostream"

using namespace std;

template <typename C>
ostream & operator << (ostream & salida, const GrafoColores<C> & grafo)
{
	// Recorremos todos los vertices
	list<string> vertices;
	grafo.devolver_vertices(vertices);
	list<string>::iterator v = vertices.begin();
	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list<typename GrafoColores<C>::Arco> adyacentes;
		grafo.devolver_adyacentes(*v, adyacentes);
		typename list<typename GrafoColores<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "    " << *v << "-> " << ady->devolver_adyacente() << " (" << ady->devolver_costo() << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}

int main(int argc, char **argv)
{
	GrafoColores<string> g;
    list<GrafoColores<string>::Arco> adyacentes;

	// Cargamos un grafo dirigido
	// Primero los vértices
	g.agregar_vertice("rojo",adyacentes);
	g.agregar_vertice("verde",adyacentes);
	g.agregar_vertice("azul",adyacentes);
	g.agregar_vertice("blanco",adyacentes);
	g.agregar_vertice("gris",adyacentes);
	g.agregar_vertice("rojo",adyacentes);
	g.agregar_vertice("rojo",adyacentes);

	// Luego los arcos
	/*g.agregar_arco(1, 2, 1);
	g.agregar_arco(1, 3, 1);
	g.agregar_arco(1, 4, 1);
	g.agregar_arco(2, 6, 2);
	g.agregar_arco(3, 5, 3);
	g.agregar_arco(4, 7, 4);
	g.agregar_arco(5, 6, 5);*/
    /*list<string> a;
    g.devolver_vertices(a);*/
    g.imprimirVector();

	return 0;
}
