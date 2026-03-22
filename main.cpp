// #include <iostream>
#include <array>
#include "include/Example.h"
// This also works if you do not want `include/`, but some editors might not like it
// #include "Example.h"
//
// int main() {
//     std::cout << "Hello, world!\n";
//     Example e1;
//     e1.g();
//     std::array<int, 100> v{};
//     int nr;
//     std::cout << "Introduceți nr: ";
    // /////////////////////////////////////////////////////////////////////////
    // /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    // /// dați exemple de date de intrare folosind fișierul tastatura.txt
    // /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    // /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    // /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    // /// pentru cât mai multe ramuri de execuție.
    // /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    // /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    // ///
    // /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    // /// pentru a simula date introduse de la tastatură.
    // /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    // ///
    // /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    // /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    // /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    // /// program care merg (și să le evitați pe cele care nu merg).
    // ///
    // /////////////////////////////////////////////////////////////////////////
    // std::cin >> nr;
    // /////////////////////////////////////////////////////////////////////////
    // for(int i = 0; i < nr; ++i) {
    //     std::cout << "v[" << i << "] = ";
    //     std::cin >> v[i];
    // }
    // std::cout << "\n\n";
    // std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    // for(int i = 0; i < nr; ++i) {
    //     std::cout << "- " << v[i] << "\n";
    // }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
//     return 0;
// }
#include <iostream>


enum TipEntitate {
    PRADATOR, PRADA, PLANTA
};

class Pozitie {
private:
    int x;
    int y;

public:
    Pozitie(int valX, int valY) {
        x = valX;
        y = valY;
    }

    friend std::ostream& operator<<(std::ostream& consola, const Pozitie& p) {
        consola << "[" << p.x << ":" << p.y << "]";
        return consola;
    }
};

class Statistici {
private:
    int energie;
    int foame;

public:
    Statistici(int e = 100, int f = 0) {
        energie = e;
        foame = f;
    }

    void consumaEnergie(int cantitate) {
        energie -= cantitate;
        if (energie < 0) energie = 0;
    }

    friend std::ostream& operator<<(std::ostream& consola, const Statistici& s) {
        consola << "[E:" << s.energie << "% | F:" << s.foame << "]";
        return consola;
    }
};

class Entitate {
private:
    std::string nume;
    char simbol;
    Pozitie pos;
    Statistici stats;

public:

    Entitate(std::string n, char s, int x, int y, int e)
        : nume(n), simbol(s), pos(x, y), stats(e) {}

    Entitate(const Entitate& alta)
       : nume(alta.nume + "_copie"),
         simbol(alta.simbol),
         pos(alta.pos),    // Initializam direct prin copiere
         stats(alta.stats) // Initializam direct prin copiere
   {
        std::cout << "[Log] Constructor de copiere apelat pentru " << alta.nume << "\n";
   }


    Entitate& operator=(const Entitate& alta) {
        std::cout << "[Log] Operator= apelat pentru " << alta.nume << "\n";
        if (this != &alta) {
            this->nume = alta.nume;
            this->simbol = alta.simbol;
            this->pos = alta.pos;
            this->stats = alta.stats;
        }
        return *this;
    }

    ~Entitate() {
        std::cout << "[Log] Destructor apelat pentru " << nume << "\n";
    }

    void seDeplaseaza(int nouX, int nouY) {
        std::cout << "--- " << nume << " se misca spre (" << nouX << "," << nouY << ") ---\n";
        pos = Pozitie(nouX, nouY);
        stats.consumaEnergie(10); // Mișcarea obosește animalul
    }


    friend std::ostream& operator<<(std::ostream& consola, const Entitate& e) {
        consola << "Entitate: " << e.nume << " [" << e.simbol << "]\n"
                << "  Locatie: " << e.pos << "\n"
                << "  Status:  " << e.stats << "\n";
        return consola;
    }
};
int main() {
    std::cout << "===== Wildlife Architect v0.1 =====\n\n";
    Entitate lup("Lupul Alpha", 'L', 2, 3, 100);
    std::cout << "Stare initiala:\n" << lup << std::endl;
    lup.seDeplaseaza(4, 5);
    std::cout << "Stare dupa deplasare:\n" << lup << std::endl;

    return 0;
}