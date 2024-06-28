/** @file Procesador.hh
    @brief Especificación de la clase Procesador 
*/

#ifndef _PROCESADOR_HH_
#define _PROCESADOR_HH_

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
#include <string>
#endif 

/** @class Procesador
    @brief Representa un procesador con los atributos identificador, memoria máxima y 
    contiene varios diccionarios para almacenar y gestionar procesos y espacios.

    Además, ofrece varias operaciones para añadir, borrar o gestionar procesos en memoria y otras operaciones
    para consultar datos.
*/

class Procesador
{
private:

    /**  @brief String que representa el identificador del procesador. */
    string idn;

    /**  @brief Entero que representa la memoria total del procesador. */
    int maxmem;

    /** @brief Entero que representa la cantidad de espacio disponible total en el procesador*/
    int mem_space;

    /**  @brief Diccionario que almacena los procesos del procesador cuya clave es su posición en memoria. */
    map<int, Proceso> m_pos;
    
    /**  @brief Diccionario que almacena las posiciones que ocupan los procesos del procesador cuya clave es el idn del proceso. */
    map<int, int> m_id;

    /**  @brief Diccionario que almacena un set de posiciones diferentes donde hay un espacio vacío 
        en memoria y la clave es el tamaño del espacio, que es igual para todas los elementos de ese set en específico.
    */
    map<int, set<int>> m_space;

    //Modificadoras

    /** @brief Modificadora del diccionario m_space 
        \pre int mem > 0, int pos >= 0.
        \post Si no hay una clave "mem" en m_space, entonces se ha creado esa clave y añadido un set
        con el elemento "pos" en esa clave. Si la clave "mem ya existe, entonces solo se ha añadido el 
        elemento "pos" al set que tiene "mem" como clave.
    */
    void anadir_space(int mem, int pos);

    /** @brief Modificadora del diccionario m_space 
        \pre int mem > 0, int pos >= 0.
        \post Si al eliminar la posición "pos" del set cuya clave es "mem" y este set queda vacío,
        entonces se ha eliminado la clave de m_space, si el set aún contiene elementos, entonces solamente
        se ha eliminado el elemento "pos" del set.
    */
    void eliminar_space(int mem, int pos);

    /** @brief Modificadora del diccionario m_space 
        \pre Iterador it de un map<int, Proceso>
        \post Se ha eliminado el posible espacio vacío previo y posterior al proceso que apunta el 
        iterador "it" y se ha añadido un espacio vacío equivalente al que quedaría en total despues 
        de eliminar el proceso.
    */
    void eliminar_job_space(map<int, Proceso>::iterator it);


public:
    //Constructoras 

    /** @brief Creadora por defecto. 
        \pre <em>cierto</em>
        \post El resultado es un procesador sin atributos.
    */   
    Procesador();

    /** @brief Creadora con valores específicos. 
        \pre String s
        \post El resultado es un procesador con identificador "s".
    */   
    Procesador(const string& s);

    //Modificadoras

    /** @brief Modificadora de procesos del P.I.
        \pre Proceso j, int pos >= -2.
        \post El parámetro implícito ha añadido el proceso "j" a su memoria en la posición "pos".
        Si "pos" es negativo no se ha añadido y se imprime un mensaje de error.
    */
    void anadir_job(const Proceso& j, int pos);

    /** @brief Modificadora de procesos del P.I.
        \pre int idn >= 0
        \post El parámetro implícito ha intentado eliminar el proceso con identificador "idn" de su memoria.
    */
    void eliminar_job(int idn);

    /** @brief Modificadora del tiempo de los procesos del P.I.
        \pre int t > 0.
        \post Los procesos del parámetro implícito han pasado a tener un tiempo previsto de ejecucion "tmp" - t.
    */
    void avanzar_tmp(int t);

    /** @brief Modificadora que compacta los procesos del P.I.
        \pre <em>cierto</em>
        \post Se han movido todos los procesos hacia el principio de la memoria del procesador, 
        sin dejar huecos libres, sin solaparse y respetando el orden inicial. 
    */
    void compactar_mem();

    //Consultoras

    /** @brief Consultora de identificador del P.I.
        \pre <em>cierto</em>
        \post El resultado es el identificador "idn" del parámetro implícito.
    */
    string consul_idn() const;

    /** @brief Consultora del espacio disponible de memoria
        \pre <em>cierto</em>
        \post El resultado es el espacio disponible total en memoria del parámetro implícito.
    */
    int consul_space() const;

    /** @brief Consultora de procesos en ejecución
        \pre <em>cierto</em>
        \post El resultado es cierto si hay procesos en el procesador, en caso contrario, será falso.
    */
    bool en_ejecucion() const;

    /** @brief Consultora de la posición óptima en memoria donde pueda caber un proceso
        \pre Proceso j
        \post El resultado es la posición óptima de la memoria en donde se puede colocar el proceso j.
        Si ya existe un proceso con el mismo idn que "j", devolverá el valor -1. Si el proceso no tiene 
        espacio en el procesador devolverá el valor -2.
    */
    int posicion_optima(Proceso j) const;

    /** @brief Consultora del espacio más ajustado en memoria donde pueda caber un proceso
        \pre Proceso j
        \post El resultado es la cantidad de espacio más ajustado en donde se puede colocar el proceso j.
        Si ya existe un proceso con el mismo idn que "j" o si no cabe el proceso j, devolverá el valor -1.
    */
    int espacio_optimo(Proceso j) const;

    // Lectura i escritura

    /** @brief Operación de lectura
        \pre Se han preparado en el canal estándar de entrada un entero positivo, que representa la memoria máxima.
        \post El parámetro implícito contiene los atributos leídos del canal estándar de entrada.
    */
    void leer();

    /** @brief Operación de escritura
        \pre <em>cierto</em>
        \post Se han escrito los atributos del parámetro implícito en el canal estándar de salida. 
    */
    void imprimir() const;
};
#endif