/** @file Espera.cc
    @brief Código de la clase Espera
*/

#include "Espera.hh"

//public

    //Constructoras

    Espera::Espera() {}

    //Modificadoras

    void Espera::alta_prior(const string& idn)
    {
        map<string,Prioridad>::iterator it = area.find(idn);
        if (it != area.end()) cout << "error: ya existe prioridad" << endl;
        else area.insert(make_pair(idn, Prioridad(idn)));
    }

    void Espera::baja_prior(const string& idn)
    {
        map<string,Prioridad>::iterator it = area.find(idn);
        if (it == area.end()) cout << "error: no existe prioridad" << endl;
        else if (it->second.size() != 0) cout << "error: prioridad con procesos" << endl;
        else it = area.erase(it);
    }

    void Espera::alta_job_espera(const Proceso& j, const string& idn)
    {
        map<string,Prioridad>::iterator it = area.find(idn);
        if (it == area.end()) cout << "error: no existe prioridad" << endl;
        else it->second.anadir_job(j);
    }

    void Espera::enviar_cluster(int n, Cluster& cl)
    {
        map<string,Prioridad>::iterator it = area.begin();
        int size = -1;
        while (n > 0 and it != area.end()) {
            if (size == -1) {
                size = it->second.size();
            }
            if (size != 0) {
                Proceso j = it->second.send_job();
                if (cl.alta_job(j)) {
                    it->second.add_acept();
                    --n;
                }
                else {
                    it->second.anadir_job(j);
                    it->second.add_rechaz();
                }
            }
            else ++it;
            --size;
        }
    }

    // Lectura i escritura

    void Espera::inicializar()
    {
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            string idn;
            cin >> idn;
            area.insert(make_pair(idn, Prioridad(idn)));
        }
    }

    void Espera::imprimir() const
    {
        map<string,Prioridad>::const_iterator it = area.begin();
        while (it != area.end()) {
            cout << it->first << endl;
            it->second.imprimir();
            ++it;
        }
    }

    void Espera::imprimir_prior(const string& idn) const
    {
        map<string,Prioridad>::const_iterator it = area.find(idn);
        if (it == area.end()) cout << "error: no existe prioridad" << endl;
        else it->second.imprimir();
    }