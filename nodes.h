#ifndef NODES_H
#define NODES_H

#include <ostream>
#include <iostream>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include <stdexcept>
#include <string>

class customexception : public std::runtime_error {
public:
	/**
		Costruttore che prende un messaggio d'errore
	*/
	customexception(const std::string &message): std::runtime_error(message) {}
};

/**
	@brief Classe che rappresenta un insieme di nodi.

	Classe che rappresenta un'insieme di nodi. 
	L'insieme di nodi è implementato come un array di identificativi templati.

	@param T tipo del dato
	@param C funtore di comparazione (uguaglianza)
*/
template <typename T, typename C>
class nodes {

public:

	typedef T id_type; ///< tipo usato per identificativo dei nodi
	typedef unsigned int size_type; ///< tipo usato per le dimensioni dell'insieme nodi
	typedef C comparator; ///< tipo usato per funtore di comparazione
	
private:

	size_type _capacity; ///< numero di nodi nel grafo
	id_type *_groupOfNodes; ///< puntatore all'array di id_type
	bool **_graphArcs; ///< puntatore alla matrice degli archi

public:

	/**
		Costruttore di default.
		Costruisce un'insieme vuota e dimensione zero.
		
		@post _groupOfNodes==nullptr
		@post _graphArcs==nullptr
		@post _capacity==0
	*/
	nodes() : _capacity(0), _groupOfNodes(nullptr), _graphArcs(nullptr) {}

	/**
		Distruttore
	*/
	~nodes() {
		clear();
	}

	/**
		Operatore di assegnamento.

		@param other insieme di nodi da copiare in this 
		@return reference al grafo this 
	*/
	nodes& operator=(const nodes &other) {

		if (this != &other) {
			nodes tmp(other);
			std::swap(this->_capacity,tmp._capacity);
			std::swap(this->_groupOfNodes,tmp._groupOfNodes);
			std::swap(this->_graphArcs,tmp._graphArcs);
		}

		return *this;
	}

	/**
		Copy constructor.

		@param other nodi da copiare in this  

		@throw eccezione di allocazione della memoria
	*/
	nodes(const nodes& other) : _capacity(0), _groupOfNodes(nullptr), _graphArcs(nullptr) {
		try{
			//Insieme di nodi
			_groupOfNodes = new id_type[other._capacity];

			for(size_type i = 0; i < other._capacity; ++i){
				_groupOfNodes[i] = other._groupOfNodes[i];
			}

			//Matrice di archi
			_graphArcs = new bool*[other._capacity];

			for(size_type i = 0; i < other._capacity; ++i){
				_graphArcs[i] = nullptr;
			}

			for(size_type i = 0; i < other._capacity; ++i){
				_graphArcs[i] = new bool[other._capacity];
			}

			for(size_type i = 0; i < other._capacity; ++i){
				for(size_type j = 0; j < other._capacity; ++j){
					_graphArcs[i][j] = other._graphArcs[i][j];
				}
			}

			_capacity = other._capacity;

		}catch(...) {
			clear();
			throw;
		}

	}

	/**
		Getter della dimensione dell'insieme di nodi.

		@return numero di nodi nel grafo
	*/
	size_type capacity() const {
		return _capacity;
	}

	/**
		Cancella il contenuto del grafo
	*/
	void clear(){
		for(size_type i = 0; i < _capacity; ++i){
			delete[] _graphArcs[i];
		}
		delete[] _graphArcs;
		_graphArcs = nullptr;
		delete[] _groupOfNodes;
		_groupOfNodes = nullptr;
		_capacity = 0;
	}

	/**
		Aggiunta di un nodo nell'insieme.

		@param i identificativo del node da aggiungere

		@throw eccezione aggiunta di un nodo con id già esistente
		@throw eccezione di allocazione della memoria
	*/
	void add_node(const id_type &i){
		bool esiste = exists(i);
		if(!esiste){
			if(_capacity==0){

				try{

					//Insieme di nodi
					_groupOfNodes = new id_type[1];
					_groupOfNodes[0]=i;
					++_capacity;

					//Matrice di archi
					_graphArcs = new bool*[_capacity];

					for(size_type c = 0; c < _capacity; ++c){
						_graphArcs[c] = nullptr;
					}
					
					for(size_type c = 0; c < _capacity; ++c){
						_graphArcs[c] = new bool[_capacity];
					}

				}catch(...) {
					clear();
					throw;
				}

				_graphArcs[0][0] = 0;

			}else{

				try{
					//Insieme di nodi
					id_type *tmp = new id_type[_capacity+1];
					
					for(size_type c = 0; c < _capacity; ++c){
						tmp[c] = _groupOfNodes[c];
					}
					tmp[_capacity] = i;
					++_capacity;

					delete[] _groupOfNodes;
					_groupOfNodes = tmp;

					//Matrice di archi
					bool **tmpArcs = new bool*[_capacity];

					for(size_type c = 0; c < _capacity; ++c){
						tmpArcs[c] = nullptr;
					}

					for(size_type c = 0; c < _capacity; ++c){
						tmpArcs[c] = new bool[_capacity];
					}


					for(size_type c = 0; c < _capacity-1; ++c){
						for(size_type j = 0; j < _capacity-1; ++j){
							tmpArcs[c][j] = _graphArcs[c][j];
							
						}
						tmpArcs[c][_capacity-1] = 0;
					}
					for(size_type c = 0; c < _capacity; ++c){
						tmpArcs[_capacity-1][c] = 0;
					}
					
					for(size_type c = 0; c < _capacity-1; ++c){
						delete[] _graphArcs[c];
					}
					delete[] _graphArcs;
					_graphArcs = nullptr;

					_graphArcs = tmpArcs;

				}catch(...){

					/*
					for(size_type i = 0; i < _capacity; ++i){
						delete[] tmpArcs[i];
					}
					delete[] tmpArcs;
					tmpArcs = nullptr;
					delete[] tmp;
					tmp = nullptr;
					*/
					
					clear();
					throw;
				}

			}

		}else{
			throw customexception("Errore: nodo già esistente!");
		}
	}

	/**
		Rimozione di un nodo dall'insime dei nodes.

		@param i identificativo del node da rimuovere

		@throw eccezione rimozione di un nodo con id non esistente
		@throw eccezione di allocazione della memoria
	*/
	void remove_node(const id_type &i){
		bool esiste = exists(i);
		if(esiste){
			if(_capacity==1){
				delete[] _graphArcs[0];
				_graphArcs[0]=nullptr;
				delete[] _graphArcs;
				_graphArcs=nullptr;
				delete[] _groupOfNodes;
				_groupOfNodes=nullptr;
				--_capacity;
			}else{
				size_type posId = positionNumber(i);

				try{

					//Insieme di nodi
					id_type *tmp = new id_type[(this->_capacity)-1];

					size_type d = 0;
					for(size_type c = 0; c < _capacity+1; ++c){
						if(c==posId){
							--_capacity;
						}else{
							tmp[d] = _groupOfNodes[c];
							++d;
						}
					}
					delete[] _groupOfNodes;
					_groupOfNodes = tmp;

					//Matrice di archi
					bool **tmpArcs = new bool*[_capacity];

					for(size_type i = 0; i < _capacity; ++i){
						tmpArcs[i] = nullptr;
					}

					for(size_type i = 0; i < _capacity; ++i){
						tmpArcs[i] = new bool[_capacity];
					}

					size_type cTmp = 0;
					size_type jTmp = 0;
					for(size_type c = 0; c < _capacity+1; ++c){
						jTmp = 0;
						if(posId!=c){
							for(size_type j = 0; j < _capacity+1; ++j){
								if(posId!=j){
								tmpArcs[cTmp][jTmp] = _graphArcs[c][j];
								++jTmp;
								}
							}
							++cTmp;
						}
					}
					
					for(size_type c = 0; c < _capacity+1; ++c){
						delete[] _graphArcs[c];
					}
					delete[] _graphArcs;
					_graphArcs = nullptr;

					_graphArcs = tmpArcs;

				}catch(...){

					/*
					for(size_type i = 0; i < _capacity; ++i){
						delete[] tmpArcs[i];
					}
					delete[] tmpArcs;
					tmpArcs = nullptr;
					delete[] tmp;
					tmp = nullptr;
					*/

					clear();
					throw;
				}
			}
		}else{
			throw customexception("Errore: nodo non esistente!");
		}
	}

	/**
		Aggiunta di un arco nella matrice.

		@param idStarting identificativo del nodo di partenza
		@param idArrival identificativo del nodo di arrivo

		@throw eccezione aggiunta di un arco già esistente
		@throw eccezione aggiunta di un arco ad un nodo non esistente
	*/
	void add_arc(const id_type &idStarting, const id_type &idArrival){
		bool esisteStarting = exists(idStarting);
		bool esisteArrival = exists(idArrival);
		bool esisteArco = hasEdge(idStarting, idArrival);

		if(esisteStarting && esisteArrival && !esisteArco){

			size_type posStarting = positionNumber(idStarting);
			size_type posArrival = positionNumber(idArrival);
			_graphArcs[posStarting][posArrival] = 1;

		}else{
			throw customexception("Errore: arco già esistente!");
		}
	}

	/**
		Rimozione di un arco nella matrice.

		@param idStarting identificativo del nodo di partenza
		@param idArrival identificativo del nodo di arrivo

		@throw eccezione rimozione di un arco non esistente
		@throw eccezione rimozione di un arco da un nodo non esistente
	*/
	void remove_arc(const id_type &idStarting, const id_type &idArrival){
		bool esisteStarting = exists(idStarting);
		bool esisteArrival = exists(idArrival);
		bool esisteArco = hasEdge(idStarting, idArrival);

		if(esisteStarting && esisteArrival && esisteArco){

			size_type posStarting = positionNumber(idStarting);
			size_type posArrival = positionNumber(idArrival);
			_graphArcs[posStarting][posArrival] = 0;

		}else{
			throw customexception("Errore: arco non esistente!");
		}
	}

	/**
		Funzione usata per cercare un nodo all'interno dell'array.

		@param i identificativo del nodo da cercare
		
		@return booleano che indica se l'identificativo è stato trovato
	*/
	bool exists(const id_type &i) const {
		bool trovato = false;
		comparator comp;

		for(size_type c = 0; c < _capacity; ++c){
			if(comp(this->_groupOfNodes[c], i)){
				trovato = true;
			}
		}
		return trovato;
	}

private:
	/**
		Funzione usata per trovare la posizione di un nodo all'interno dell'array.

		@param i identificativo del nodo da cercare
		
		@return size_type che indica la posizione dell'identificativo del nodo
	*/
	size_type positionNumber(const id_type &i) const {
		size_type position = 0;
		comparator comp;

		for(size_type c = 0; c < _capacity; ++c){
			if(comp(this->_groupOfNodes[c], i)){
				position = c;
			}
		}
		return position;
	}

public:
	/**
		Funzione usata per verificare se esiste un arco tra due nodi.

		@param idStarting identificativo del nodo di partenza
		@param idArrival identificativo del nodo di arrivo
		
		@return booleano che indica se esiste l'arco tra i due nodi
	*/
	bool hasEdge(const id_type &idStarting, const id_type &idArrival) const {
		bool esisteArco=false;
		bool esisteStarting = exists(idStarting);
		bool esisteArrival = exists(idArrival);

		if(esisteStarting && esisteArrival){
			size_type posStarting = positionNumber(idStarting);
			size_type posArrival = positionNumber(idArrival);
			esisteArco = _graphArcs[posStarting][posArrival];
		}

		return esisteArco;
	}

	class const_iterator {
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : ptr(nullptr) {
		}
		
		const_iterator(const const_iterator &other) : ptr(other.ptr) {
		}

		const_iterator& operator=(const const_iterator &other) {
			ptr = other.ptr;
			return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return *ptr;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return ptr;
		}
		
		// Operatore di iterazione post-incremento (i++)
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			++ptr;
			return tmp;
		}

		// Operatore di iterazione pre-incremento (++i)
		const_iterator& operator++() {
			++ptr;
			return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return (ptr == other.ptr);
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return (ptr != other.ptr);
		}

	private:
		const T *ptr;

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class nodes; 

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const T* p) : ptr(p) { }
	}; // end class const_iterator

	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_groupOfNodes);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(_groupOfNodes+_capacity);
	}

}; // end class nodes

#endif