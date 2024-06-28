/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

//private:
    
    //Modificadoras
    bool Cluster::modificar_bintree_procesador(BinTree<string>& a, const string& idn, const Cluster& cl)
    {    
        if (not a.empty()) {
            if (a.value() != idn) {
                BinTree<string> l = a.left();
                BinTree<string> r = a.right();
                bool modified = modificar_bintree_procesador(l, idn, cl);
                if(not modified) modified = modificar_bintree_procesador(r,idn, cl);
                a = BinTree<string> (a.value(), l, r);
                return modified;
            }
            else {
                if (a.left().empty() and a.right().empty()) {
                    map<string,Procesador>::iterator it = d.find(a.value());
                    d.erase(it);
                    a = cl.cls;
                    d.insert(cl.d.begin(), cl.d.end());
                }
                else cout << "error: procesador con auxiliares" << endl;
                return true;
            }
        }
        return false;
    }

    //Consultoras
    void Cluster::buscar_procesador_recursivo(string& idn, const BinTree<string>& a, int size, int& min, const set<string>& posibles) const
    {
        if ((min == -1 or size < min) and not a.empty()) {
            string s = a.value();
            if(posibles.find(s) != posibles.end()) {
                min = size;
                idn = s;
            }
            else {
                buscar_procesador_recursivo(idn, a.left(), size + 1, min, posibles);
                buscar_procesador_recursivo(idn, a.right(), size + 1, min, posibles);
            }
        }
    }

    //Lectura i escritura
    void Cluster::leer_bintree_procesador(BinTree<string>& a) {
        string idn;
        cin >> idn;
        if (idn != "*"){
            Procesador prc(idn);
            prc.leer();
            d.insert(make_pair(idn, prc));
            BinTree<string> l, r;
            leer_bintree_procesador(l);
            leer_bintree_procesador(r);
            a = BinTree<string> (idn,l,r);
        }
    }

    void Cluster::imprimir_bintree_procesador(const BinTree<string>& a) const
    {
        if (not a.empty()) {
            cout << '(' << a.value();
		    imprimir_bintree_procesador(a.left()); 
		    imprimir_bintree_procesador(a.right());
            cout << ')';
        }
        else cout << ' ';
    }

//public:
    //Constructoras 

    Cluster::Cluster() {}
 
    //Modificadoras

    bool Cluster::alta_job(const Proceso& j)
    {
        set<string> posibles;
        map<string,Procesador>::iterator it = d.begin();
        int libre = 0;
        int ajustado = 0;
        while (it != d.end()) {
            int m = it->second.espacio_optimo(j);
            int space = it->second.consul_space();
            if (m != -1 and (ajustado > m or ajustado == 0)) {
                ajustado = m;
                libre = space;
                posibles.clear();
                posibles.insert(it->first);
            }
            else if (ajustado == m and libre < space) {
                libre = space;
                posibles.clear();
                posibles.insert(it->first);
            }
            else if (ajustado == m and libre == space) {
                posibles.insert(it->first);
            }
            ++it;
        }
        string idn = "*";
        if (posibles.empty()) return false;
        else if (posibles.size() == 1) idn = *posibles.begin();
        else {
            int min = -1;
            buscar_procesador_recursivo(idn, cls, 0, min, posibles);
        }
        it = d.find(idn);
        it->second.anadir_job(j,it->second.posicion_optima(j));
        return true;
    }

    void Cluster::alta_job_prc(const Proceso& j, const string& idn)
    {
        map<string, Procesador>::iterator it = d.find(idn);
        if (it == d.end()) cout << "error: no existe procesador" << endl;
        else {
            int pos = it->second.posicion_optima(j);
            it->second.anadir_job(j,pos);
        }
    }

    void Cluster::baja_job_prc(int i, const string& idn)
    {
        map<string, Procesador>::iterator it = d.find(idn);
        if (it == d.end()) cout << "error: no existe procesador" << endl;
        else d[idn].eliminar_job(i); 
    }

    void Cluster::avanzar_tmp(int t) 
    {
        map<string,Procesador>::iterator it = d.begin();
        while (it != d.end()) {
            it->second.avanzar_tmp(t);
            ++it;
        }
    }

    void Cluster::compactar()
    {
        map<string,Procesador>::iterator it = d.begin();
        while (it != d.end()) {
            it->second.compactar_mem();
            ++it;
        }
    }

    void Cluster::compactar_prc(const string& idn)
    {
        map<string,Procesador>::iterator it = d.find(idn);
        if (it == d.end()) cout << "error: no existe procesador" << endl;
        else it->second.compactar_mem();
    }

    void Cluster::modificar_cluster(const string& idn, const Cluster& cl)
    {
        map<string,Procesador>::iterator it = d.find(idn);
        if (it == d.end()) cout << "error: no existe procesador" << endl;
        else if (it->second.en_ejecucion()) cout << "error: procesador con procesos" << endl;
        else modificar_bintree_procesador(cls, idn, cl);
    }  


    // Lectura i escritura

    void Cluster::configurar()
    {
        d.clear();
        BinTree<string> tree;
        leer_bintree_procesador(tree);
        cls = tree;
    }

    void Cluster::imprimir() const
    {
        map<string,Procesador>::const_iterator it = d.begin();
        while (it != d.end()) {
            cout << it->first << endl;
            it->second.imprimir();
            ++it;
        }
    }

    void Cluster::imprimir_struct() const 
    {
        imprimir_bintree_procesador(cls);
        cout << endl;
    }

    void Cluster::imprimir_prc(const string& idn) const
    {
        map<string, Procesador>::const_iterator it = d.find(idn);
        if (it == d.end()) cout << "error: no existe procesador" << endl;
        else it->second.imprimir();
    }