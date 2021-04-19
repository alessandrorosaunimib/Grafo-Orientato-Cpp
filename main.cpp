#include "nodes.h" // nodes
#include <iostream>
#include <cassert>
#include <ostream>

struct customType {
    int id1;
    long id2;
};

std::ostream &operator<<(std::ostream &os, const customType &cT) {

		os << cT.id1 << " " << cT.id2 << " ";

	return os;
}

struct compare_int {
	bool operator()(int a, int b) const {
		return a==b;
	}
};

struct compare_double {
	bool operator()(double a, double b) const {
		return a==b;
	}
};

struct compare_customType {
	bool operator()(const customType &cT1, const customType &cT2) const {
		return (cT1.id1 == cT2.id1 && cT1.id2 == cT2.id2);
	}
};

void test_const_iterator_int(const nodes<int, compare_int> &n) {
	nodes<int, compare_int>::const_iterator it, ite;

	for(it=n.begin(),ite=n.end(); it!=ite; ++it) {
        assert(!(it==ite));
		std::cout << *it << std::endl;
	}	
}

void test_const_iterator_double(const nodes<double, compare_double> &n) {
	nodes<double, compare_double>::const_iterator it, ite;

	for(it=n.begin(),ite=n.end(); it!=ite; ++it) {
        assert(!(it==ite));
		std::cout << *it << std::endl;
	}	
}

void test_const_iterator_customType(const nodes<customType, compare_customType> &n) {
	nodes<customType, compare_customType>::const_iterator it, ite;

	for(it=n.begin(),ite=n.end(); it!=ite; ++it) {
        assert(!(it==ite));
		std::cout << *it << std::endl;
	}	
}

void test_nodes_int(){

    std::cout<<"*** TEST NODES.H FOR ID TYPE: INT ***" << std::endl;

    std::cout<<"Costruttore primario: nodes<int> nodi;" << std::endl << std::endl;
    nodes<int, compare_int> nodi;

    std::cout<<"Aggiungo tre nodi:" << std::endl;
    try{
        nodi.add_node(30);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.capacity()==1);
    std::cout << "Aggiunto nodo 60, _capacity: " << nodi.capacity() << std::endl;
    try{
        nodi.add_node(60);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.capacity()==2);
    std::cout << "Aggiunto nodo 30, _capacity: " << nodi.capacity() << std::endl;
    try{
        nodi.add_node(90);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.capacity()==3);
    std::cout << "Aggiunto nodo 90, _capacity: " << nodi.capacity() << std::endl << std::endl;

    std::cout << "Risultato nodi.exists(30): " << nodi.exists(30) << std::endl;
    std::cout << "Risultato nodi.exists(60): " << nodi.exists(60) << std::endl;
    std::cout << "Risultato nodi.exists(90): " << nodi.exists(90) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(30): " << nodi.positionNumber(30) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(60): " << nodi.positionNumber(60) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(90): " << nodi.positionNumber(90) << std::endl << std::endl;

    std::cout << "Risultato nodi.hasEdge(30, 60): " << nodi.hasEdge(30, 60) << std::endl;
    try{
        nodi.add_arc(30, 90);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco 30->90, nodi.hasEdge(30, 90): " << nodi.hasEdge(30, 90) << std::endl;
    try{
        nodi.remove_arc(30, 90);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Rimosso arco 30->90, nodi.hasEdge(30, 90): " << nodi.hasEdge(30, 60) << std::endl;
    try{
        nodi.add_arc(60, 30);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco 60->30, nodi.hasEdge(60, 30): " << nodi.hasEdge(60, 30) << std::endl;
    try{
        nodi.add_arc(30, 30);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }    
    std::cout << "Aggiunto arco 30->30, nodi.hasEdge(30, 30): " << nodi.hasEdge(30, 30) << std::endl;
    try{
        nodi.add_arc(60, 60);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    } 
    std::cout << "Aggiunto arco 60->60, nodi.hasEdge(60, 60): " << nodi.hasEdge(60, 60) << std::endl << std::endl;

    try{
        nodi.remove_node(60);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }     
    std::cout << "Rimosso nodo 60, nodi.capacity(): " << nodi.capacity() << std::endl << std::endl;

    //std::cout << "Risultato nodi.positionNumber(90): " << nodi.positionNumber(90) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(30): " << nodi.positionNumber(30) << std::endl;
    std::cout << "Risultato nodi.hasEdge(30, 90): " << nodi.hasEdge(30, 90) << std::endl << std::endl;

    nodes<int, compare_int> nodi2;
    nodi2 = nodi;
    std::cout << "Assegnamento, capacity: " << nodi2.capacity() << std::endl << std::endl;

    nodes<int, compare_int> nodi3(nodi2);
    std::cout << "Copy constructor, capacity: " << nodi2.capacity() << std::endl << std::endl;

    test_const_iterator_int(nodi);

    std::cout<<"*** FINE TEST NODES.H FOR ID TYPE: INT ***" << std::endl << std::endl;

}

void test_nodes_double(){

    std::cout<<"*** TEST NODES.H FOR ID TYPE: DOUBLE ***" << std::endl;

    std::cout<<"Costruttore primario: nodes<double> nodi;" << std::endl << std::endl;
    nodes<double, compare_double> nodi;

    std::cout<<"Aggiungo due nodi:" << std::endl;
    try{
        nodi.add_node(1.3);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }   
    std::cout << "Aggiunto nodo 1.3, _capacity: " << nodi.capacity() << std::endl;
    try{
        nodi.add_node(60);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }   
    std::cout << "Aggiunto nodo 60, _capacity: " << nodi.capacity() << std::endl;
    try{
        nodi.add_node(90);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }   
    std::cout << "Aggiunto nodo 90, _capacity: " << nodi.capacity() << std::endl << std::endl;

    std::cout << "Risultato nodi.exists(1.3): " << nodi.exists(1.3) << std::endl;
    std::cout << "Risultato nodi.exists(60): " << nodi.exists(60) << std::endl;
    std::cout << "Risultato nodi.exists(90): " << nodi.exists(90) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(1.3): " << nodi.positionNumber(1.3) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(60): " << nodi.positionNumber(60) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(90): " << nodi.positionNumber(90) << std::endl << std::endl;

    std::cout << "Risultato nodi.hasEdge(1.3, 60): " << nodi.hasEdge(1.3, 60) << std::endl;
    
    try{
        nodi.add_arc(1.3, 90);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }   
    std::cout << "Aggiunto arco 1.3->90, nodi.hasEdge(1.3, 90): " << nodi.hasEdge(1.3, 90) << std::endl;
    try{
        nodi.remove_arc(1.3, 90);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }   
    std::cout << "Rimosso arco 1.3->90, nodi.hasEdge(1.3, 90): " << nodi.hasEdge(1.3, 60) << std::endl;
    try{
        nodi.add_arc(60, 1.3);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }   
    std::cout << "Aggiunto arco 60->1.3, nodi.hasEdge(60, 1.3): " << nodi.hasEdge(60, 1.3) << std::endl;
    try{
        nodi.add_arc(1.3, 1.3);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco 1.3->1.3, nodi.hasEdge(1.3, 1.3): " << nodi.hasEdge(1.3, 1.3) << std::endl;
    try{
        nodi.add_arc(60, 60);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco 60->60, nodi.hasEdge(60, 60): " << nodi.hasEdge(60, 60) << std::endl << std::endl;

    try{
        nodi.remove_node(60);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Rimosso nodo 60, nodi.capacity(): " << nodi.capacity() << std::endl << std::endl;

    //std::cout << "Risultato nodi.positionNumber(90): " << nodi.positionNumber(90) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(1.3): " << nodi.positionNumber(1.3) << std::endl;
    std::cout << "Risultato nodi.hasEdge(1.3, 90): " << nodi.hasEdge(1.3, 90) << std::endl << std::endl;

    nodes<double, compare_double> nodi2;
    nodi2 = nodi;
    std::cout << "Assegnamento, capacity: " << nodi2.capacity() << std::endl << std::endl;

    nodes<double, compare_double> nodi3(nodi2);
    std::cout << "Copy constructor, capacity: " << nodi2.capacity() << std::endl << std::endl;

    test_const_iterator_double(nodi2);

    std::cout<<"*** FINE TEST NODES.H FOR ID TYPE: double ***" << std::endl << std::endl;

}

void test_nodes_customType(){

    std::cout<<"*** TEST NODES.H FOR ID TYPE: CUSTOM_TYPE ***" << std::endl;

    std::cout<<"Costruttore primario: nodes<customType, compare_customType> nodi;" << std::endl << std::endl;
    nodes<customType, compare_customType> nodi;

    customType cT1;
    cT1.id1=1;
    cT1.id2=2;

    customType cT2;
    cT2.id1=2;
    cT2.id2=2;

    customType cT3;
    cT3.id1=10;
    cT3.id2=1;

    std::cout << "Aggiungo tre nodi:" << std::endl;
    try{
        nodi.add_node(cT1);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.capacity()==1);
    std::cout << "Aggiunto nodo cT1, _capacity: " << nodi.capacity() << std::endl;
    std::cout << "id1: " << cT1.id1 << std::endl;
    std::cout << "id2: " << cT1.id2 << std::endl;
    try{
        nodi.add_node(cT2);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.capacity()==2);
    std::cout << "Aggiunto nodo cT2, _capacity: " << nodi.capacity() << std::endl;
    std::cout << "id1: " << cT2.id1 << std::endl;
    std::cout << "id2: " << cT2.id2 << std::endl;
    try{
        nodi.add_node(cT3);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.capacity()==3);
    std::cout << "Aggiunto nodo cT3, _capacity: " << nodi.capacity() << std::endl;
    std::cout << "id1: " << cT3.id1 << std::endl;
    std::cout << "id2: " << cT3.id2 << std::endl << std::endl;

    std::cout << "Risultato nodi.exists(cT1): " << nodi.exists(cT1) << std::endl;
    std::cout << "Risultato nodi.exists(cT2): " << nodi.exists(cT2) << std::endl;
    std::cout << "Risultato nodi.exists(cT3): " << nodi.exists(cT3) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(cT1): " << nodi.positionNumber(cT1) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(cT2): " << nodi.positionNumber(cT2) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(cT3): " << nodi.positionNumber(cT3) << std::endl << std::endl;

    std::cout << "Risultato nodi.hasEdge(cT1, cT2): " << nodi.hasEdge(cT1, cT2) << std::endl;
    try{
        nodi.add_arc(cT1, cT3);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco cT1->cT3, nodi.hasEdge(cT1, cT3): " << nodi.hasEdge(cT1, cT3) << std::endl;

    try{
        nodi.remove_arc(cT1, cT3);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Rimosso arco cT1->cT3, nodi.hasEdge(cT1, cT3): " << nodi.hasEdge(cT1, cT2) << std::endl;
    try{
        nodi.add_arc(cT2, cT1);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco cT2->cT1, nodi.hasEdge(cT2, cT1): " << nodi.hasEdge(cT2, cT1) << std::endl;
    try{
        nodi.add_arc(cT1, cT1);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco cT1->cT1, nodi.hasEdge(cT1, cT1): " << nodi.hasEdge(cT1, cT1) << std::endl;
    try{
        nodi.add_arc(cT2, cT2);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco cT2->cT1, nodi.hasEdge(cT2, cT2): " << nodi.hasEdge(cT2, cT2) << std::endl << std::endl;

    try{
        nodi.remove_node(cT2);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Rimosso nodo cT2, nodi.capacity(): " << nodi.capacity() << std::endl << std::endl;

    try{
        nodi.remove_node(cT2);
    }catch(customexception &e){
        std::cout << e.what() << std::endl;
    }

    //std::cout << "Risultato nodi.positionNumber(cT3): " << nodi.positionNumber(cT3) << std::endl;
    //std::cout << "Risultato nodi.positionNumber(cT1): " << nodi.positionNumber(cT1) << std::endl;
    std::cout << "Risultato nodi.hasEdge(cT1, cT3): " << nodi.hasEdge(cT1, cT3) << std::endl << std::endl;

    nodes<customType, compare_customType> nodi2;
    nodi2 = nodi;
    std::cout << "Assegnamento, capacity: " << nodi2.capacity() << std::endl << std::endl;

    nodes<customType, compare_customType> nodi3(nodi2);
    std::cout << "Copy constructor, capacity: " << nodi2.capacity() << std::endl << std::endl;

    test_const_iterator_customType(nodi);

    std::cout<<"*** FINE TEST NODES.H FOR ID TYPE: CUSTOMTYPE ***" << std::endl << std::endl;

}

int main(int argc, char *argv[]) {

	std::cout<<"*** TEST NODES.H ***" << std::endl << std::endl;
    
    //test per int
    test_nodes_int();

    //test per double
    test_nodes_double();

    //test per customType
    test_nodes_customType();

    std::cout<<"*** FINE TEST NODES.H ***" << std::endl;

    return 0;
}