/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

//public:
  //Constructoras 
   
    Proceso::Proceso() {}
  
    //Modificadoras

    void Proceso::avanzar_tmp(int t)
    {
        tmp -= t;
    }
  
    //Consultoras

    int Proceso::consul_idn() const
    {
        return idn;
    }

    int Proceso::consul_mem() const
    {
        return mem;
    }

    int Proceso::consul_tmp() const
    {
        return tmp;
    }

    // Lectura i escritura

    void Proceso::leer()
    {
        cin >> idn >> mem >> tmp;
    }

    void Proceso::imprimir() const 
    {
        cout << idn << ' ';
        cout << mem << ' ';
        cout << tmp << endl;
    }