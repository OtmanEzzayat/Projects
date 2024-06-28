/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#include "Procesador.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh" 
#endif

/** @class Cluster
    @brief Representa un cluster de procesadores que almacena procesadores en un formato de árbol binario.

    Ofrece varias operaciones para modificar los procesadores e incluso la estructura del mismo cluster. Además de las operaciones
    de lectura y varias opciones para la escritura.

    Dado que vamos a necesitar leer árboles, definimos el concepto de clúster vacío.
*/

class Cluster
{
private:

    /**  @brief BinTree que almacena los identificadores de los procesadores. */
    BinTree<string> cls;

    /**  @brief Mapa que guarda los procesadores cuyas claves son los identificadores almacenados en el árbol. */
    map<string, Procesador> d;

    //Modificadoras

    /** @brief Modificadora del BinTree del P.I.
        \pre a = cls, string idn, Cluster cl.
        \post Si se ha encontrado en el Bintree "a" el procesador con identificador "idn", se coloca
        en su lugar el Bintree del cluster "cl", en caso contrario, se imprime un mensaje de error.
    */
    bool modificar_bintree_procesador(BinTree<string>& a, const string& idn, const Cluster& cl);

    //Consultoras

    /** @brief Consultora de un identificador del BinTree del P.I.
        \pre String idn, a = cls, int size >= 0, int min >= -1, set<string> posibles. Se garantiza que el set posibles tiene 
        almenos 2 elementos y, por ende, se va a devolver siempre un identificador.
        \post Se busca en el BinTree un string que esté en el set "posibles". Si hay varios string que esten en el set, se
        elige el más cercano a la raíz y si hay empate, el más situado a la izquierda y se coloca en la variable "idn". 
    */
    void buscar_procesador_recursivo(string& idn, const BinTree<string>& a, int size, int& min, const set<string>& posibles) const;

    // Lectura i escritura

    /** @brief Operación de lectura
        \pre BinTree de strings vacío. Además, se ha preparado en el canal estándar de entrada un número de identificadores,
        que representan un árbol binario en preorden, donde el identificador "*" representa un árbol vacío.
        \post El bintree "a" contiene el árbol que había en el canal estándar de entrada.
    */
    void leer_bintree_procesador(BinTree<string>& a);

    /** @brief Operación de escritura
        \pre a = cls.
        \post Se ha escrito en preorden los elementos del BinTree "a" en el canal estándar de salida con paréntesis representando
        la jerarquía del árbol. 
    */
    void imprimir_bintree_procesador(const BinTree<string>& a) const;

public:
    //Constructoras 

    /** @brief Creadora por defecto. 
        \pre <em>cierto</em>
        \post El resultado es un cluster sin atributos.
    */   
    Cluster();
 
    //Modificadoras

    /** @brief Modificadora que añade un proceso al procesador óptimo del P.I.
        \pre Proceso j.
        \post El P.I. intenta añadir el proceso p en un procesador disponible siguiendo unas condiciones 
        si se puede colocar en más de uno. Si se ha añadido devolverá cierto, y falso en caso contrario.
    */
    bool alta_job(const Proceso& j);

    /** @brief Modificadora que añade un proceso en un procesador en específico del P.I.
        \pre Proceso j, string idn.
        \post El P.I. intenta añadir el proceso "j" en el procesador con identificador "idn".
    */
    void alta_job_prc(const Proceso& j, const string& idn);

    /** @brief Modificadora que elimina un proceso de un procesador en específico del P.I.
        \pre int i >= 0, string idn.
        \post El P.I. intenta eliminar el proceso con identificador "i"  del procesador con identificador "idn".
    */
    void baja_job_prc(int i, const string& idn);

    /** @brief Modificadora que avanza el tiempo en todos los procesos de los procesadores del P.I.
        \pre t > 0.
        \post Los procesos de los procesadores del P.I. pasan a tener un tiempo 
        previsto de ejecucion "tmp" - "t". Si esta diferéncia es negativa, se elimina el proceso del procesador.
    */
    void avanzar_tmp(int t);

    /** @brief Modificadora que compacta los procesos de la memoria de los procesadores del P.I.
        \pre <em>cierto</em>
        \post Se han movido todos los procesos hacia el principio de la memoria de todos los 
        procesadores del cluster, sin dejar huecos, sin solaparse y respetando el orden inicial. 
    */
    void compactar();

    /** @brief Modificadora que compacta los procesos de la memoria de un procesador del P.I.
        \pre String idn.
        \post Se han movido todos los procesos hacia el principio de la memoria del procesador de 
        identificador "idn", sin dejar huecos, sin solaparse y respetando el orden inicial. 
    */
    void compactar_prc(const string& idn);

    /** @brief Modificadora que elimina un procesador del P.I. y coloca un nuevo cluster en su lugar
        \pre String idn, Cluster cl.
        \post Se ha intentado sustituir el procesador con string idn por el cluster "cl".
    */
    void modificar_cluster(const string& idn, const Cluster& cl);

    // Lectura i escritura

    /** @brief Operación de lectura
        \pre Se han preparado al canal estándar de entrada los atributos de un número de 
        procesadores, que representan un arbol binario en preorden donde los procesadores
        con idn = "*" representan un árbol vacío.
        \post El P.I. contiene los atributos leídos del canal estándar de entrada.
    */
    void configurar();

    /** @brief Operación de escritura de cluster
        \pre <em>cierto</em>
        \post Se han escrito los atributos del P.I. en el canal
        estándar de salida por orden creciente de identificador.
    */
    void imprimir() const;

    /** @brief Operación de escritura de la estructura del cluster
        \pre <em>cierto</em>
        \post Se han escrito los atributos del P.I. en el canal estándar de salida en preorden. 
    */
    void imprimir_struct() const;

    /** @brief Operación de escritura de un procesador del cluster
        \pre String idn.
        \post Se han escrito los atributos del procesador con identificador "idn" 
        del P.I. en el canal estándar de salida. 
    */
    void imprimir_prc(const string& idn) const;
};
#endif