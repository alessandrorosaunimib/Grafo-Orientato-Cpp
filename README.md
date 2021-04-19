# Grafo Orientato C++

Il progetto richiede la progettazione e realizzazione di una classe generica che 
implementa un grafo orientato. Un grafo è costituito da un insieme di nodi e 
archi. I nodi sono rappresentati da un generico identificativo (es. un numero, 
una stringa, un oggetto, ecc...). Gli archi mettono in relazione due nodi 
creando un collegamento tra loro.
Requisito essenziale del progetto è che il grafo deve essere implementato 
mediante matrici di adiacenza come in figura. Non possono essere usate liste.
A parte i metodi essenziali per la classe (tra cui conoscere il numero di nodi e 
archi), devono essere implementate le seguenti funzionalità:
1. La classe deve includere il supporto al solo const_iterator di tipo 
forward sui nodi. L’iteratore itera sull’insieme degli identificativi dei nodi 
contenuti nel grafo e l’ordine con cui vengono ritornati non è rilevante.
2. Deve essere possibile aggiungere e rimuovere nodi e archi. Gestire i casi in 
cui i nodi o gli archi già esistano, si tenti di aggiungere un arco su nodi non 
esistenti, o si tenti di rimuovere un nodo o un arco non esistente.
3. Deve essere possibile interrogare il grafo per sapere se esite un nodo 
tramite un metodo exists e se una coppia di nodi è connessa da un arco 
tramite un metodo hasEdge. Nell’esempio in figura, exists(‘9’)=false, 
hasEdge(‘1’,‘2’)=true, hasEdge(‘4’,‘3’)=false.Possono essere trascurate considerazioni di efficienza di accesso ai dati e di 
occupazione di memoria.

Utilizzare dove opportuno la gestione degli errori tramite asserzioni o eccezioni.
Nota 1: Se non indicato diversamente, nella progettazione della classe, è 
vietato l'uso di librerie esterne e strutture dati container della std library come 
std::vector, std::list e simili. E’ consentito il loro uso nel codice di test nel 
main.
Nota 2: A parte nullptr, non potete utilizzare altri costrutti C++11 e oltre.
Nota 3: Nella classe, è consentito l’uso della gerarchia di eccezioni standard, 
delle asserzioni, la gerarchia degli stream e la funzione std::swap.
Nota 4: Per vostra sicurezza, tutti i metodi dell’interfaccia pubblica che 
implementate devono essere esplicitamente testati nel main anche su tipi 
custom.
Nota 5: Non dimenticate di usare Valgrind per testare problemi di memoria
Nota 6: Evitate di usare "test" come nome dell'eseguibile. Potrebbe dare dei 
problemi sotto msys.
