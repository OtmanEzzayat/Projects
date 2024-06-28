/** @file Prioridad.cc
    @brief Código de la clase Prioridad
*/

#include "Prioridad.hh"

    //Constructoras 

    Prioridad::Prioridad() {}

    Prioridad::Prioridad(const string& s) 
    {
        idn = s;
        job_acept = 0;
        job_rechaz = 0;
    }

    //Modificadoras

    void Prioridad::anadir_job(const Proceso& j) 
    {
        set<int>::iterator it = s.find(j.consul_idn());
        if (it == s.end()) {
            l.insert(l.end(), j);
            s.insert(j.consul_idn());
        }
        else cout << "error: ya existe proceso" << endl;
    }

    void Prioridad::eliminar_job(int id) 
    {
        set<int>::iterator it = s.find(id);
        if (it != s.end()) {
            it = s.erase(it);
            list<Proceso>::iterator it2 = l.begin();
            bool found = false;
            while (it2 != l.end() and not found){
                if ((*it2).consul_idn() == id){
                    it2 = l.erase(it2);
                    found = true;
                }
                ++it;
            }
        }
        else cout << "error: no existe proceso" << endl;
    }

    void Prioridad::add_acept() 
    {
        job_acept += 1;
    }

    void Prioridad::add_rechaz() 
    {
        job_rechaz += 1;
    }

    Proceso Prioridad::send_job()
    {
        list<Proceso>::iterator it = l.begin();
        Proceso aux = (*it);
        s.erase(s.find((*it).consul_idn()));
        it = l.erase(it);
        return aux;
    }

    //Consultoras

    int Prioridad::size() const
    {
        return s.size();
    }

    // Lectura i escritura

    void Prioridad::imprimir() const 
    {
        list<Proceso>::const_iterator it = l.begin();
        while (it != l.end()){
            (*it).imprimir();
            ++it;
        }
        cout << job_acept << ' ' << job_rechaz << endl;
    }