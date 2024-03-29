// Clase Subasta
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Subasta {
    private:
      vector<Lote> lotes;
      int cantLotes;
      vector<Person> participantes;
      Person ofertador;

    public:
      // constructor
      Subasta(vector<Lote>, int, vector<Person>, Person);
      //metodos
      void iniciarSubasta();
      vector<Lote> getLotes();
      Person getOfertador();
      void setOfertador(Person newOfertador);
};

Subasta::Subasta(vector<Lote> lotesSubasta, int cantidad, vector<Person> participantesSubasta, Person ofertadorInicial) {
  lotes = lotesSubasta;
  cantLotes = cantidad;
  participantes = participantesSubasta;
  ofertador = ofertadorInicial;
}

vector<Lote> Subasta::getLotes() {
  return lotes;
}

Person Subasta::getOfertador() {
  return ofertador;
}

void Subasta::setOfertador(Person newOfertador) {
  ofertador = newOfertador;
}

void Subasta::iniciarSubasta() {
  for(int i = 5; i > 0; i = i - 1) {
    cout << "La subasta comienza en "<< i << endl;
    sleep(1);
  }

  for(int i = 0; i < lotes.size(); ++i) {
    int azar = 1;
    srand(time(NULL));
    while(azar != 0) {
      // data el ofertador actual para comparar con el siguiente ofertador
      Person currentOfertador = getOfertador();
      int currentOfertadorId = currentOfertador.getId();

      // nuevo ofertador
      Person ofertador = participantes[rand() % participantes.size()];

      if (currentOfertadorId != ofertador.getId() & ofertador.getDineroDisponible() > lotes[i].getPuja()) {
        int puja = rand() % 1000 + lotes[i].getPuja();
        ofertador.hacerOferta(lotes[i], puja);
        setOfertador(ofertador);
        sleep(1);      
      }

      azar = rand() % 30;
    }
    Person ganador = getOfertador();
    ganador.setDineroDisponible(ganador.getDineroDisponible() - lotes[i].getPuja());
    cout << endl;
    cout << "WINNER WINNER CHICKEN DINNER!" << endl;
    cout << ganador.getName() << " ha ganado el lote numero " << i + 1 << endl;
    cout << endl;
    cout << "Pasando al siguiente lote " << endl;
    sleep(3);
  }
  cout << "No hay mas lotes en esta subasta" << endl;
}
