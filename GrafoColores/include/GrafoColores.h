#ifndef GRAFOCOLORES_H
#define GRAFOCOLORES_H

#include <list>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;
template <typename C>  class GrafoColores
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(string adyacente, const C & costo);
		string devolver_adyacente() const;
		const C & devolver_costo() const;
		void setCosto(C nuevoCosto);
	private:
		string vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	GrafoColores();
	GrafoColores(const GrafoColores & otroGrafo);

	~GrafoColores();

	GrafoColores & operator = (const GrafoColores & otroGrafo);

	bool esta_vacio() const;//listo

	int devolver_longitud() const;//listo

	bool existe_vertice(string vertice) const;//listo

	bool existe_arco(string origen, string destino) const;//listo

	bool buscarDestino( string destino, list<Arco> adyacentes) const;//funcion auxiliar

	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(string origen, string destino) const;//listo

	void devolver_vertices(list<string> & vertices) const;//listo

	void devolver_adyacentes(string origen, list<Arco> & adyacentes) ;//listo

	void agregar_vertice(string vertice,list<Arco> & adyacentes);//listo

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(string vertice);//listo

	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(string origen, string destino, const C & costo);//listo

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregar_arco(string origen, string destino, const C & costo);//listo

	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(string origen, string destino);//listo

	int posicionVacia();

	void DFScolor(const multimap<string, list<Arco>> mapGrafo, string origen, string destino,string color,list<string> & camino);

    void imprimirAdyacentes(list<Arco>);

    void imprimirVector() const;

	void vaciar();//listo

private:
    multimap<string,int>:: iterator it;
    struct marca{
        bool visitado=false;
        string vertice;
    };
    vector<marca> visitados{20};
    multimap<string, list<Arco>> mapGrafo;

}; // class Grafo


/*
 * Arco
 */

template <typename C> GrafoColores<C>::Arco::Arco()
{

}

template <typename C> GrafoColores<C>::Arco::Arco(string adyacente, const C & costo)
{
    this->vertice=adyacente;
    this->costo=costo;
}

template <typename C> string GrafoColores<C>::Arco::devolver_adyacente() const
{
    return this->vertice;
}

template <typename C> const C & GrafoColores<C>::Arco::devolver_costo() const
{
    return this->costo;
}
template <typename C> void GrafoColores<C>::Arco::setCosto(C nuevoCosto)
{
    this->costo=nuevoCosto;
}

/*
 * Grafo
 */

template <typename C> GrafoColores<C>::GrafoColores()
{

}

template <typename C> GrafoColores<C>::GrafoColores(const GrafoColores & otroGrafo)
{

}

template <typename C> GrafoColores<C>::~GrafoColores()
{

}

template <typename C> GrafoColores<C> & GrafoColores<C>::operator = (const GrafoColores & otroGrafo)
{

    return *this;
}

template <typename C> bool GrafoColores<C>::esta_vacio() const
// Devuelve true si la cantidad de vértices es cero
{
    bool vacio = false;
    if(mapGrafo.empty())
        vacio=true;
    return vacio;
}

template <typename C> int GrafoColores<C>::devolver_longitud() const
// Indica la cantidad de vértices del grafo
{
    return mapGrafo.size();
}

template <typename C> bool GrafoColores<C>::existe_vertice(string vertice) const
{
    bool existe = false;
    typename multimap<string, list<Arco>>::const_iterator it = mapGrafo.find(vertice);//esto es porque debe ser constante
    if(it !=mapGrafo.end())
        existe=true;
    return existe;
}
template <typename C> bool GrafoColores<C>::buscarDestino( string destino,list<Arco> ady) const
{
    typename list<Arco>::iterator a = ady.begin();
    bool existe = false;
    while(a != ady.end()and (existe==false)){
        if(a->devolver_adyacente()== destino)
            existe=true;
        ++a;
    }
    return existe;
}
template <typename C> bool GrafoColores<C>::existe_arco(string origen, string destino) const
{
    bool existe = false;
    typename multimap<string,list<Arco>>::const_iterator it = mapGrafo.find(origen);
    if(it != mapGrafo.end()){
        const list<Arco> &ady = it->second;
        if(buscarDestino(destino,ady))
            existe=true;
    }
    return existe;
}

template <typename C> const C & GrafoColores<C>::costo_arco(string origen, string destino) const
{
    static const C costo_vacio = C();
    if(existe_arco(origen,destino)){
        const list<Arco> &ady = mapGrafo.at(origen);
        typename list<Arco>::const_iterator it= ady.begin();
        while ((it != ady.end()) && (it->devolver_adyacente()!= destino)){
            ++it;
        }
        if(it->devolver_adyacente()== destino)
            return it->devolver_costo();
    }
    return costo_vacio;
}

template <typename C> void GrafoColores<C>::devolver_vertices(list<string> & vertices) const
{
    list<string>:: iterator itList;
    typename multimap<string, list<Arco>>::const_iterator it = mapGrafo.begin();
    for(; it!=mapGrafo.end(); ++it){
        vertices.push_back(it->first);
    }
    itList = vertices.begin();
    while(itList != vertices.end()){
        cout<<*itList<<'|';
        ++itList;
    }
}

template <typename C> void GrafoColores<C>::devolver_adyacentes(string origen, list<Arco> & adyacentes)
{
    list<Arco> &ady = mapGrafo[origen];
    imprimirAdyacentes(ady);
}
template <typename C> int GrafoColores<C>::posicionVacia(){
    int i =0;
    while (this->visitados[i].vertice != ""){
        i++;
    }
    return i;
}
template <typename C> void GrafoColores<C>::agregar_vertice(string vertice,list<Arco> & adyacentes)
{
    typename vector<marca>::iterator it = visitados.begin()+ posicionVacia();
    this->mapGrafo.insert(pair<string,list<Arco>>(vertice,adyacentes));
    marca auxMarca;
    auxMarca.vertice=vertice;
    this->visitados.insert(it,auxMarca);
}

template <typename C> void GrafoColores<C>::eliminar_vertice(string vertice)
{
    if (existe_vertice(vertice)){
        typename multimap<string,list<Arco>>::iterator v = mapGrafo.find(vertice);//seteo un iterador en el vertice a eliminar
        typename multimap<string,list<Arco>>::iterator it = mapGrafo.begin();
        while(it !=mapGrafo.end()){
            eliminar_arco(it->first,vertice);
            ++it;
        }
         mapGrafo[vertice].clear();
         mapGrafo.erase(v);
    }
   for (auto const& pair: mapGrafo) {
        cout<<pair.first<< " | ";
   }
}

template <typename C> void GrafoColores<C>::modificar_costo_arco(string origen, string destino, const C & costo)
{
    if(existe_arco(origen,destino)){
        typename list<Arco>::iterator it = mapGrafo[origen].begin();
        while(it !=mapGrafo[origen].end() && (it->devolver_adyacente()!= destino)){
            ++it;
        }
        cout<<"costo antes de modifiarlo: "<<it->devolver_costo()<<"\n";
        it->setCosto(costo);
        cout<<"costo despues de modifiarlo: "<<it->devolver_costo()<<"\n";
    }
}
template <typename C> void GrafoColores<C>::agregar_arco(string origen, string destino, const C & costo)
{
    if((existe_vertice(origen))&& (existe_vertice(destino))){
        typename multimap<string,list<Arco>>::iterator iter = mapGrafo.find(origen);
        if(!existe_arco(origen,destino))
            if(iter != mapGrafo.end())
                iter->second.push_back(Arco(destino,costo));
        else
            cout<<"el arco ya existe";
    }
}

template <typename C> void GrafoColores<C>::eliminar_arco(string origen, string destino)
{
    if(existe_arco(origen,destino)){
        typename list<Arco>:: iterator it = mapGrafo[origen].begin();
        while(it !=mapGrafo[origen].end() && (it->devolver_adyacente()!= destino)){
            ++it;
        }
        list<Arco> &ady = mapGrafo[origen];
        imprimirAdyacentes(ady);
        it = mapGrafo[origen].erase(it);
        list<Arco> &adya = mapGrafo[origen];
        cout<<"asi queda"<<"\n";
        imprimirAdyacentes(adya);
    }
}

template <typename C> void GrafoColores<C>::vaciar()
{
    mapGrafo.clear();
    if(mapGrafo.empty())
        cout<<"vacio";
}
template <typename C> void GrafoColores<C>::imprimirAdyacentes(list<Arco> ady){
    typename list<Arco>::iterator a;
    a= ady.begin();
    while(a != ady.end()){
        cout<<"destino: "<<a->devolver_adyacente()<<" costo: "<<a->devolver_costo()<<"\n";
        ++a;
    }
}
template <typename C> void GrafoColores<C>::DFScolor(const multimap<string, list<Arco>> mapGrafo, string origen, string destino,string color,list<string> & camino){

}
template <typename C> void GrafoColores<C>::imprimirVector() const{
    int i =0;
    while (this->visitados[i].vertice != ""){
        cout<< this->visitados[i].vertice <<"|"<<this->visitados[i].visitado<<" -- ";
        i++;
    }
}
#endif // GRAFOCOLORES_H
