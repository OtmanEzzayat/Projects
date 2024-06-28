/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

//private;

    //Modificadoras

    void Procesador::anadir_space(int mem, int pos) {
        map<int,set<int>>::iterator it = m_space.find(mem);
        if (it == m_space.end()){
            set<int> s;
            s.insert(pos);
            m_space.insert(make_pair(mem,s));
        }
        else it->second.insert(pos);
    }

    void Procesador::eliminar_space(int mem, int pos) {
        map<int,set<int>>::iterator it = m_space.find(mem);
        if (it != m_space.end()) {
            it->second.erase(pos);
            if (it->second.empty()) it = m_space.erase(it);
        }
    }

    void Procesador::eliminar_job_space(map<int, Proceso>::iterator it) {
            int pos_mem = it->first;
            int pre = 0;
            if (it != m_pos.begin()){
                --it;
                pre = it->first + it->second.consul_mem();
                ++it;
            }
            if (pre != pos_mem) eliminar_space(pos_mem - pre, pre);
            int memoria = it->second.consul_mem();
            pos_mem += memoria;
            mem_space += memoria;
            int post = maxmem;
            ++it;
            if (it != m_pos.end()){
                post = it->first;
            }
            if (post != pos_mem) eliminar_space(post - pos_mem, pos_mem);
            anadir_space(post - pre, pre);
    }

//public:

    //Constructoras

    Procesador::Procesador() {}


    Procesador::Procesador(const string& s)
    {
        idn = s;
    }

    //Modificadoras

    void Procesador::anadir_job(const Proceso& j, int pos)
    {
        if (pos == -1) cout << "error: ya existe proceso" << endl;
        else if (pos == -2) cout << "error: no cabe proceso" << endl;
        else {
            m_pos.insert(make_pair(pos, j));
            m_id.insert(make_pair(j.consul_idn(), pos));

            map<int, Proceso>::iterator it = m_pos.find(pos);
            ++it;
            int post = 0;
            int pos_mem = pos + j.consul_mem();
            if (it == m_pos.end()) post = maxmem;
            else post = it->first;

            mem_space -= j.consul_mem();
            eliminar_space(post - pos, pos);
            if (pos_mem != post) anadir_space(post - pos_mem, pos_mem);
        }
    }

    void Procesador::eliminar_job(int idn)
    {
        map<int,int>::iterator it = m_id.find(idn);
        if (it == m_id.end()) cout << "error: no existe proceso" << endl;
        else {
            map<int, Proceso>::iterator it2 = m_pos.find(it->second);
            eliminar_job_space(it2);
            m_pos.erase(it->second);
            it = m_id.erase(it);
        }
    }

    void Procesador::avanzar_tmp(int t)
    {
        map<int,Proceso>::iterator it = m_pos.begin();
        while (it != m_pos.end()) {
            it->second.avanzar_tmp(t);
            if (it->second.consul_tmp() <= 0) {
                eliminar_job_space(it);
                m_id.erase(it->second.consul_idn());
                it = m_pos.erase(it);
            }
            else ++it;
        }
    }

    void Procesador::compactar_mem()
    {
        map<int,Proceso>::iterator it = m_pos.begin();
        int pos_mem = 0;
        bool desplazar = false;
        while (it != m_pos.end()) {
            if (it->first != pos_mem) desplazar = true;
            if (desplazar) {
                Proceso j = it->second;
                m_id[j.consul_idn()] = pos_mem;
                it = m_pos.erase(it);
                m_pos.insert(make_pair(pos_mem, j));
                pos_mem += j.consul_mem();
            }
            else {
                pos_mem += it->second.consul_mem();
                ++it;
            }
        }
        m_space.clear();
        if (pos_mem != maxmem) anadir_space(maxmem - pos_mem, pos_mem);
    }

    //Consultoras

    string Procesador::consul_idn() const
    {
        return idn;
    }

    int Procesador::consul_space() const
    {
        return mem_space;
    }

    bool Procesador::en_ejecucion() const
    {
        return (not m_pos.empty());
    }

    int Procesador::posicion_optima(Proceso j) const
    {
        int mem = j.consul_mem();

        if (m_id.find(j.consul_idn()) != m_id.end()) return -1;
        else if (maxmem < mem) return -2;
        else if (m_pos.begin() == m_pos.end()) return 0;

        map<int,set<int>>::const_iterator it = m_space.lower_bound(mem);
        if (it == m_space.end()) return -2;
        else return (*it->second.begin());
    }

    int Procesador::espacio_optimo(Proceso j) const
    {
        int mem = j.consul_mem();

        if (m_id.find(j.consul_idn()) != m_id.end() or maxmem < mem) return -1;
        else if (m_pos.begin() == m_pos.end()) return maxmem;

        map<int,set<int>>::const_iterator it = m_space.lower_bound(mem);
        if (it == m_space.end()) return -1;
        else return it->first;
    }

    // Lectura i escritura

    void Procesador::leer()
    {
        cin >> maxmem;
        set<int> s;
        s.insert(0);
        m_space.insert(make_pair(maxmem,s));
        mem_space = maxmem;
    }

    void Procesador::imprimir() const {
        map<int,Proceso>::const_iterator it = m_pos.begin();
        while (it != m_pos.end()) {
            cout << it->first << ' ';
            it->second.imprimir();
            ++it;
        }
    }