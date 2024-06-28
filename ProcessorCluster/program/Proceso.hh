/** @file Proceso.hh
    @brief Especificación de la clase Proceso 
*/

#ifndef _PROCESO_HH_
#define _PROCESO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#endif 

using namespace std;

/** @class Proceso
    @brief Representa una proceso con los atributos identificador, memoria y 
    tiempo previsto de ejecución.

    Ofrece las operaciones básicas de lectura y escritura y consultoras de datos.
    Un proceso es ejecutado cuando su tiempo de ejecución es igual o menor a 0.
*/

class Proceso
{
private:

    /**  @brief Entero no negativo que representa el identificador del proceso. */
    int idn;

    /**  @brief Entero positivo que representa la memoria que ocupa el proceso. */
    int mem;

    /**  @brief Entero positivo que representa el tiempo previsto de ejecución. */
    int tmp;

public:
  //Constructoras 

    /** @brief Creadora por defecto
        \pre <em>cierto</em>
        \post El resultado es un proceso sin atributos.
    */   
    Proceso();
  
    //Modificadoras

    /** @brief Modificadora del tiempo de ejecución del proceso
        \pre t > 0.
        \post El parámetro implícito pasa a tener un tiempo previsto de ejecucion "tmp" - t.
        Si la diferencia es menor o igual a 0, el proceso se habría ejecutado.
    */
    void avanzar_tmp(int t);
  
    //Consultoras

    /** @brief Consultora del identificador del P.I.
        \pre <em>cierto</em>
        \post El resultado es el identificador "idn" del parámetro implícito.
    */
    int consul_idn() const;
 
    /** @brief Consultora de la memoria del P.I.
        \pre <em>cierto</em>
        \post El resultado es la memoria que ocupa "mem" el parámetro implícito.
    */
    int consul_mem() const;

    /** @brief Consultora del tiempo de ejecución del proceso del P.I.
        \pre <em>cierto</em>
        \post El resultado es el tiempo previsto de ejecucion "tmp" del parámetro implícito.
    */
    int consul_tmp() const;

    // Lectura i escritura

    /** @brief Operación de lectura
        \pre Se han preparado al canal estándar de entrada un entero no negativo, que representa 
        el identificador del proceso y dos enteros positivos, que representan la memoria y el 
        tiempo previsto de ejecución.
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