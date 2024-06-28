/** @mainpage

    Práctica realizada por Otman Ezzayat Maid, con documentación <b> completa</b> (incluyendo elementos privados y código).

    El programa principal se encuentra en el módulo program.cc. Atendiendo al enunciado, necesitaremos inicializar un Cluster en el que se gestionaran los procesadores y un área de Espera para guardar procesos a la espera de ser ejecutados.
    
    En el Cluster podemos encontrarnos Procesadores almacenado en formato de árbol binario, los cuales tienen la función de almacenar y gestionar Procesos a la espera de ser ejecutados.
    
    Finalmente, en el área de Espera podemos encontrar Prioridades que almacenan Procesos.

*/

/** @file program.cc

    @brief Programa principal

    Después de inicializar el Cluster y el área de Espera, podemos ir introduciendo comandos por el canal estándar de entrada para gestionar los elementos de las clases inicializadas.
    Asimismo, si alguna instrucción no es posible de realizar, se enviará un mensaje de error por el canal de salida y también, el mismo canal será usado para imprimir datos.
    Para terminar de ejecutar comandos, habrá que introducir el comando "fin".
*/

#include "Cluster.hh"
#include "Espera.hh"

using namespace std;

void analizar_comando(const string& comando, Cluster& cls, Espera& area) {
    if (comando == "cc" or comando == "configurar_cluster") {
        cout << '#' << comando << endl;
        cls.configurar();
    }
    else if (comando == "mc" or comando == "modificar_cluster") {
        string idn;
        cin >> idn;
        Cluster c;
        c.configurar();
        cout << '#' << comando << ' ' << idn << endl;
        cls.modificar_cluster(idn, c);
    }
    else if (comando == "ap" or comando == "alta_prioridad") {
        string prior;
        cin >> prior;
        cout << '#' << comando << ' ' << prior << endl;
        area.alta_prior(prior);
    }
    else if (comando == "bp" or comando == "baja_prioridad") {
        string prior;
        cin >> prior;
        cout << '#' << comando << ' ' << prior << endl;
        area.baja_prior(prior);
    }
    else if (comando == "ape" or comando == "alta_proceso_espera") {
        string prior;
        cin >> prior;
        Proceso j;
        j.leer();
        cout << '#' << comando << ' ' << prior << ' ' <<  j.consul_idn() << endl;
        area.alta_job_espera(j, prior);          
    }
    else if (comando == "app" or comando == "alta_proceso_procesador") {
        string idn;
        cin >> idn;
        Proceso j;
        j.leer();
        cout << '#' << comando << ' ' << idn << ' ' <<  j.consul_idn() << endl;
        cls.alta_job_prc(j, idn);
    }
    else if (comando == "bpp" or comando == "baja_proceso_procesador") {
        string idn;
        int i;
        cin >> idn >> i;
        cout << '#' << comando << ' ' << idn << ' ' <<  i << endl;
        cls.baja_job_prc(i, idn);
    }
    else if (comando == "epc" or comando == "enviar_procesos_cluster") {
        int n;
        cin >> n;
        cout << '#' << comando << ' ' << n << endl;
        area.enviar_cluster(n, cls);
    }
    else if (comando == "at" or comando == "avanzar_tiempo") {
        int t;
        cin >> t;
        cout << '#' << comando << ' ' << t << endl;
        cls.avanzar_tmp(t);
    }
    else if (comando == "ipri" or comando == "imprimir_prioridad") {
        string prior;
        cin >> prior;
        cout << '#' << comando << ' ' << prior  << endl;
        area.imprimir_prior(prior);
    }
    else if (comando == "iae" or comando == "imprimir_area_espera") {
        cout << '#' << comando << endl;
        area.imprimir();
    }
    else if (comando == "ipro" or comando == "imprimir_procesador") {
        string idn;
        cin >> idn;
        cout << '#' << comando << ' ' << idn << endl;
        cls.imprimir_prc(idn);
    }
    else if (comando == "ipc" or comando == "imprimir_procesadores_cluster") {
        cout << '#' << comando << endl;
        cls.imprimir();
    }
    else if (comando == "iec" or comando == "imprimir_estructura_cluster") {
        cout << '#' << comando << endl;
        cls.imprimir_struct();
    }
    else if (comando == "cmp" or comando == "compactar_memoria_procesador") {
        string idn;
        cin >> idn;
        cout << '#' << comando << ' ' << idn << endl;
        cls.compactar_prc(idn);
    }
    else if (comando == "cmc" or comando == "compactar_memoria_cluster") {
        cout << '#' << comando << endl;
        cls.compactar();
    }
}

int main() {
    Cluster cls;
    cls.configurar();
    Espera area;
    area.inicializar();
    string comando;     //String que indica la función que queremos ejecutar y admite abreviaturas.
    cin >> comando;
    while (comando != "fin") {
        analizar_comando(comando, cls, area);
        cin >> comando;
    }
}