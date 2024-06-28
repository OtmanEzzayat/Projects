/** @file Espera.hh
    @brief Especificación de la clase Espera 
*/

#ifndef _ESPERA_HH_
#define _ESPERA_HH_

#include "Prioridad.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#endif

/** @class Espera
    @brief Representa un área que almacena procesos a la espera de ser ejecutados en el cluster.

    Ofrece operaciones de lectura y escritura y permite gestionar prioridades y enviar procesos al cluster.

*/

class Espera
{
private:

    /**  @brief Mapa que guarda las prioridades del área cuyas claves son sus identificadores. */
    map<string, Prioridad> area;

public:
    //Constructoras

    /** @brief Creadora por defecto. 
        \pre <em>cierto</em>
        \post El resultado es un área de procesos pendientes vacía.
    */   
    Espera();

    //Modificadoras

    /** @brief Modificadora que añade una prioridad
        \pre String idn.
        \post Se ha intentado añadir al area de espera una prioridad con identificador "idn".
        Si la prioridad con identificador "idn" ya existe, se ha imprimido un mensaje de error.
    */  
    void alta_prior(const string& idn);

    /** @brief Modificadora que elimina una prioridad
        \pre String idn.
        \post Se ha intentado eliminar del area de espera una prioridad con identificador "idn".
        Si la prioridad con identificador "idn" no existe o tiene procesos, se ha imprimido un mensaje de error.
    */  
    void baja_prior(const string& idn);

    /** @brief Modificadora que añade un proceso a una prioridad
        \pre Proceso j, string idn.
        \post Se ha intentado añadir un proceso a una prioridad con identificador "idn". 
        Si el proceso ya existía en la prioridad, se ha imprimido un mensaje de error.
    */  
    void alta_job_espera(const Proceso& j, const string& idn);

     /** @brief Modificadora que envia procesos pendientes al cluster
        \pre Entero n >= 0 y Cluster cl.
        \post Se han intentado añadir al cluster los procesos de las prioridades del parámetro implícito,
        eliminando los procesos añadidos de la lista de la prioridad. Si un proceso, no se ha podido anadir
        al cluster, se volverá a añadir a la misma prioridad.
    */
    void enviar_cluster(int n, Cluster& cl);

    // Lectura i escritura

    /** @brief Operación de lectura
        \pre Se han preparado al canal estándar de entrada un entero positivo n, seguido de n
        identificadores de prioridades.
        \post El parámetro implícito contiene n prioridades.
    */
    void inicializar();

    /** @brief Operación de escritura del P.I.
        \pre <em>cierto</em>
        \post Se han escrito los atributos del parámetro implícito en el canal.
        estándar de salida. 
    */
    void imprimir() const;

    /** @brief Operación de escritura de una prioridad
        \pre String idn.
        \post Se han intentado escribir los atributos de la prioridad con identificador "idn" del 
        parámetro implícito en el canal estándar de salida. Si la prioridad no existe, se ha imprimido
        un mensaje de error.
    */
    void imprimir_prior(const string& idn) const;
};
#endif