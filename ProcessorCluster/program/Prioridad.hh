/** @file Prioridad.hh
    @brief Especificación de la clase Prioridad
*/

#ifndef _PRIORIDAD_HH_
#define _PRIORIDAD_HH_

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <list>
#include <set>
#include <string>
#endif 

/** @class Prioridad
    @brief Representa una prioridad con los atributos identificador, procesos aceptados y procesos rechazados.
    Contiene además una lista y un conjunto para almacenar procesos.

    Ofrece operaciones para añadir o eliminar procesos además de las operaciones de lectura, escritura y 
    consultoras de datos.
*/

class Prioridad
{
private:

    /**  @brief String que representa el identificador de la prioridad. */
    string idn;

    /**  @brief Entero no negativo que representa el número de procesos aceptados por el cluster. */
    int job_acept;

    /**  @brief Entero no negativo que representa el número de procesos rechazados por el cluster. */
    int job_rechaz;

    /**  @brief Lista que almacena los procesos con esa prioridad por orden de adición de más antiguo a más reciente. */
    list<Proceso> l;

    /**  @brief Conjunto que almacena los identificadores de los procesos de la lista. */
    set<int> s;

public:
    //Constructoras 

    /** @brief Creadora por defecto. 
        \pre <em>cierto</em>
        \post El resultado es una prioridad sin atributos.
    */   
    Prioridad();

    /** @brief Creadora con valores específicos. 
        \pre String s
        \post El resultado es una prioridad con identificador "s".
    */  
    Prioridad(const string& s);

    //Modificadoras

    /** @brief Modificadora que añade un proceso a una prioridad
        \pre Proceso j.
        \post El parámetro implícito ha intentado añadir el proceso "j". 
        Si ya existe un procesador con el mismo identificador, se ha imprimido un mensaje de error.
    */  
    void anadir_job(const Proceso& j);

    /** @brief Modificadora que elimina un proceso a una prioridad
        \pre int idn >= 0.
        \post Se ha intentado eliminar el proceso con identificador "idn" del parámetro implícito.
        Si no existe un proceso con ese identificador, se ha imprimido un mensaje de error.
    */  
    void eliminar_job(int id);

    /** @brief Modificadora del valor de procesos aceptados
        \pre <em>cierto</em>
        \post Se le ha sumado 1 al atributo del parámetro implícito "job_acept".
    */
    void add_acept();

    /** @brief Modificadora del valor de procesos rechazados
        \pre <em>cierto</em>
        \post Se le ha sumado 1 al atributo del parámetro implícito "job_rechaz".
    */
    void add_rechaz();

    /** @brief Modificadora del primer elemento de la lista
        \pre En la lista hay almenos 1 proceso.
        \post Se ha enviado el primer proceso de la lista y se ha eliminado de la lista y el set.
    */
    Proceso send_job();

    //Consultoras

    /** @brief Consultora del tamaño de la lista
        \pre <em>cierto</em>
        \post El resultado es el número de procesos en la lista.
    */
    int size() const;

    // Lectura i escritura

    /** @brief Operación de escritura
        \pre <em>cierto</em>
        \post Se han escrito los atributos del parámetro implícito en el canal
        estándar de salida.
    */
    void imprimir() const;
};
#endif