#ifndef ARTURO_H_
#define ARTURO_H_

#include <iostream>
#include <cassert>
using namespace std;

/*
 * IMPORTANTE!
 * Se puede asumir que el tipo T tiene constructor por copia y operator == y operator <<
 * No se puede asumir que el tipo T tenga operator =
 */
template<typename T>
class Arturo
{

    public:

        /*
         * Crea una mesa redonda nueva sin caballeros.
         */
        Arturo();

        /*
         * Una vez copiados, ambos Arturos deben ser independientes,
         * es decir, cuando se borre uno no debe borrar la otra.
         */
        Arturo(const Arturo<T> &);

        /*
         * Acordarse de liberar toda la memoria!
         */
        ~Arturo();

        /*
        * Arturo se sienta siempre primero.
        *
        * PRE: La mesa esta vacía.
        * POST: Arturo está hablando y es el único en la mesa.
        */
        void sentarArturo(const T &a);

        /*
         * Agrega un nuevo caballero a la mesa. El nuevo caballero se sentará
         * a la derecha de Arturo. No se pueden agregar caballeros repetidos.
         *
         * PRE: Arturo esta sentado en la mesa y el nuevo caballero c no está sentado aún
         * POST: El caballero c se sienta a la derecha de Arturo.
         */
        void incorporarCaballero(const T &c);

        /*
         * Elimina de la mesa al caballero pasado por parámetro. En caso de borrar al
         * caballeroActual, pasará a ser el actual que esté sentado a su derecha.
         * Si se expulsa al caballero interrumpido por Arturo, Arturo sigue hablando
         * como si nunca hubiera interrumpido, es decir, el próximo es el de la
         * derecha de Arturo y el anterior es el de la izquierda de Arturo.
         *
         * IMPORTANTE: Sólo se puede borrar a Arturo, si es el único sentado en la mesa.
         *
         * PRE: c puede ser Arturo sólo si la mesa tiene tamaño 1
         * POST: El caballero c no está más sentado en la mesa.
         */
        void expulsarCaballero(const T &c);

        /*
         * Devuelve al caballero que está hablando en este momento.
         *
         * PRE: Hay caballeros sentados en la mesa.
         */
        const T &caballeroActual() const;

        /*
         * Cambia el turno del caballero actual, al de su derecha. Si Arturo
         * interrumpió, el turno pasa al de la derecha del interrumpido.
         * El resultado no tiene interrumpido.
         *
         * PRE: Hay caballeros sentados en la mesa.
         */
        void proximoCaballero();

        /*
         * Cambia el turno del caballero actual, al de su izquierda. Si Arturo
         * interrumpió, el turno pasa al de la izquierda del interrumpido.
         * Esta función puede ser llamada varias veces seguidas.
         * El resultado no tiene interrumpido.
         *
         * PRE: Hay caballeros sentados en la mesa.
         */
        void caballeroAnterior();

        /*
        * Arturo puede elegir que es su turno de hablar en cualquier momento e
        * interrumpir al que está hablando. Arturo termina de hablar por interrupción
        * cuando se pasa al proximoCaballero() o al caballeroAnterior().
        *
        * PRE: Si Arturo está hablando, no se puede interumpir a sí mismo.
        */
        void hablaArturo();

        /*
         * Indica si Arturo está sentado en la mesa.
         */
        bool arturoPresente() const;

        /*
        * Arturo quiere separar un conflicto y por lo tanto cambia su posición y
        * se sienta a la derecha del caballero pasado como parámetro.
        * Tanto como el que está hablando como el interrumpido siguen siendo los mismos.
        * Ejemplos:
        *  cambiarDeLugar(c1) de la mesa: [Arturo(c0), c1, c2] deja la mesa: [Arturo(c0), c2, c1]
        *  cambiarDeLugar(c1) de la mesa: [c1, c2, Arturo(c0)] deja la mesa: [c1, Arturo(c0), c2]
        *  cambiarDeLugar(c2) de la mesa: [c1, c2, Arturo(c0), c3] deja la mesa: [c1, c2, Arturo(c0), c3]
        *
        * PRE: La mesa tiene al menos tamaño 3
        * POST: Arturo está sentado a la derecha de c
        */
        void cambioDeLugar(const T &c);

        /*
         * Dice si la mesa tiene o no caballeros sentados.
         */
        bool esVacia() const;

        /*
         * Devuelve la cantidad de caballeros en la mesa.
         */
        int tamanio() const;

        /*
         * Devuelve true si las mesas son iguales.
         * Dos mesas son iguales cuando todos sus caballeros son iguales,
         * están sentados en las mismas posiciones, y además tanto Arturo,
         * como el que está hablando, como el interrumpido (si hubiera) son iguales.
         */
        bool operator==(const Arturo<T> &) const;
        bool operator!=(const Arturo<T> &) const;

        /*
         * Debe mostrar la mesa por el ostream os (y retornar el mismo).
         * Mesa vacia: []
         * Mesa con caballero c0 como Arturo: [ARTURO(c0)]
         * Mesa con 2 caballeros (Arturo está hablando): [ARTURO(c0), c1]
         * Mesa con 3 caballeros (Arturo está hablando): [ARTURO(c0), c1, c2]
         * Mesa con 3 caballeros (c1 está hablando): [c1, c2, ARTURO(c0)]
         * Mesa con 3 caballeros (c1 fue interrumpido): [ARTURO(c0),*c1,c2]
         */
        ostream &mostrarArturo(ostream &os) const;


    private:
        /*
         * No se puede modificar esta funcion.
         */
        Arturo<T> &operator=(const Arturo<T> &otra)
        {
            assert(false);
            return *this;
        }

        /*
         * Aca va la implementación del nodo.
         */
        struct Nodo {
            Nodo* izq;
            Nodo* der;
            T value;
            Nodo(const T &val): value(val)
            {
                der = this;
                izq = this;
            };
        };

        Nodo* arturo;
        Nodo* hablando;
        bool interrupted;
        int size;
        Nodo* get_node(const T &val);
};

template<class T>
ostream &operator<<(ostream &out, const Arturo<T> &a)
{
    return a.mostrarArturo(out);
}

template<class T>
Arturo<T>::Arturo()
{
    hablando = NULL;
    arturo = NULL;
    size = 0;
    interrupted = false;
}

template<class T>
Arturo<T>::~Arturo()
{
    while (not esVacia()){
        if (tamanio() > 1 and caballeroActual() == arturo->value){
            proximoCaballero();
        }
        expulsarCaballero(caballeroActual());
    }
}


template<class T>
Arturo<T>::Arturo(const Arturo<T> &to_copy)
{
    arturo = NULL;
    hablando = NULL;
    size = 0;
    interrupted = to_copy.interrupted;

    if (to_copy.esVacia()){
        return;
    }

    sentarArturo(to_copy.arturo->value);
    Nodo* you = to_copy.arturo->izq;
    for (int i = 0; i < to_copy.tamanio(); ++i, you = you->izq) {
        incorporarCaballero(you->value);

        if(you->value == to_copy.hablando->value){
            hablando = get_node(you->value);
        }
    }

}

template<class T>
void Arturo<T>::sentarArturo(const T &a)
{
    arturo = new Nodo(a);
    hablando = arturo;
    size++;
}

//se sienta a la derecha de arturo
template<class T>
void Arturo<T>::incorporarCaballero(const T &c)
{
    if (get_node(c) == NULL) {
        Nodo *knight = new Nodo(c);
        Nodo *old_der = arturo->der;
        arturo->der = knight;
        knight->der = old_der;
        knight->izq = arturo;
        old_der->izq = knight;
        size++;
    }
}

template<class T>
void Arturo<T>::expulsarCaballero(const T &c)
{
    Nodo* to_delete = get_node(c);
    if (tamanio() > 1 and arturo == to_delete){
        return;
    }

    if (to_delete == hablando) {
        hablando = interrupted ? arturo : hablando->der;
    }


    to_delete->der->izq = to_delete->izq;
    to_delete->izq->der = to_delete->der;

    delete to_delete;
    size--;

    if (tamanio() == 0){
        hablando = arturo = NULL;
    }

}

template<class T>
void Arturo<T>::cambioDeLugar(const T &c)
{
    Nodo* knight = get_node(c);
    arturo->der->izq = arturo->izq;
    arturo->izq->der = arturo->der;

    arturo->izq = knight;
    arturo->der = knight->der;
    knight->der = arturo;
}

template<class T>
bool Arturo<T>::operator!=(const Arturo<T> &compare) const
{
    return not (*this == compare);
}

template<class T>
bool Arturo<T>::operator==(const Arturo<T> &compare) const
{
    if(tamanio() != compare.tamanio()){
        return false;
    }

    if(interrupted != compare.interrupted){
        return false;
    }

    if (arturo != compare.arturo){
        return false;
    }

    if(hablando != compare.hablando){
        return false;
    }

    Nodo* me = arturo;
    Nodo* you = compare.arturo;

    for (int i = 0; i < tamanio(); ++i, me = me->der, you = you->izq) {
        if (me->value != you->value){
            return false;
        }
    }

    return true;
    
}

template<class T>
const T &Arturo<T>::caballeroActual() const
{
    return interrupted? arturo->value : hablando->value;
}

template<class T>
void Arturo<T>::proximoCaballero()
{
    hablando = hablando->der;
    interrupted = false;
}

template<class T>
void Arturo<T>::caballeroAnterior()
{
    hablando = hablando->izq;
    interrupted = false;
}

template<class T>
void Arturo<T>::hablaArturo()
{
    interrupted = true;
}

template<class T>
bool Arturo<T>::arturoPresente() const
{
    return arturo == NULL;
}

template<class T>
bool Arturo<T>::esVacia() const
{
    return (size == 0);
}

template<class T>
int Arturo<T>::tamanio() const
{
    return size;
}

template<class T>
typename Arturo<T>::Nodo* Arturo<T>::get_node(const T &val)
{
    int i = 0;
    Nodo* iter;

    for (iter = arturo; i < tamanio() && iter->value != val; ++i, iter = iter->der);
    if (i == tamanio()){
        return NULL;
    }
    else{
        return iter;
    }
}

template<class T>
ostream &Arturo<T>::mostrarArturo(ostream &os) const
{

    os << "[";
    Nodo* iter = interrupted ? arturo : hablando;
    for (int i = 0; i < tamanio(); ++i, iter = iter->der) {
        if (iter == arturo){
            os << "Arturo(" << iter->value << "),";
            continue;
        }

        if (interrupted and iter == hablando){
            os << "*";
        }
        os << iter->value << ",";

    }
    os << "]" << endl;

    return os;
}



#endif //ARTURO_H_
