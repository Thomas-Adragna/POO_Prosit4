#include <iostream>
#include <string>

using namespace std;


class SystemeCentral;// D�claration anticip�e correcte de la classe SystemeCentral

class B {
public:
    void recevoir(string message) {
        cout << "Reception du signal : " << message << endl;
    }
    void abonnement(SystemeCentral& systeme, int Signal);
};

class SystemeCentral {
public:
    void abonne(B* recepteur, int numSignal);
    void diffuser(string message, int numSignal);
private:
    struct Abonnement {
        B* recepteur;
        int numSignal;
    };
    Abonnement abonnes[10];  // Limite de 10 abonn�s pour simplifier
    int nombreAbonnes = 0;   // Compteur pour le nombre d'abonn�s
};

void B::abonnement(SystemeCentral& systeme, int Signal) {
    systeme.abonne(this, Signal);
}

void SystemeCentral::abonne(B* recepteur, int numSignal) {
    if (nombreAbonnes < 10) {
        abonnes[nombreAbonnes].recepteur = recepteur;
        abonnes[nombreAbonnes].numSignal = numSignal;
        nombreAbonnes++;
    }
    else {
        cout << "Limite d'abonn�s atteinte." << endl;
    }
}

void SystemeCentral::diffuser(string message, int numSignal) {
    for (int i = 0; i < nombreAbonnes; i++) {
        if (abonnes[i].numSignal == numSignal) {
            abonnes[i].recepteur->recevoir(message);
        }
    }
}

class A {
public:
    void envoyer(SystemeCentral& systeme, string message, int numSignal) {
        systeme.diffuser(message, numSignal);
    }
};

int main() {
    SystemeCentral systeme;
    A emetteur;
    B recepteur1, recepteur2;

    // Les r�cepteurs s'abonnent � diff�rents signaux
    recepteur1.abonnement(systeme, 1);
    recepteur2.abonnement(systeme, 2);

    // L'�metteur envoie des messages
    emetteur.envoyer(systeme, "Message pour le canal 1", 1);
    emetteur.envoyer(systeme, "Message pour le canal 2", 2);

    return 0;
}
