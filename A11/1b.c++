#include <iostream>
#include <vector>
#include <stdexcept>
#include <stdio.h>

#include <iostream>
#include <vector>
#include <stdexcept>

enum class Farbe {
        WEISS,
        GRAU,
        SCHWARZ
};  

class AdjazenzMatrix {
public: 
    int n;
    bool gerichtet;
    std::vector<std::vector<int>> matrix;
    std::vector<Farbe> farben;

    AdjazenzMatrix(int knoten, bool istGerichtet = false)
        : n(knoten),
          gerichtet(istGerichtet),
          matrix(knoten, std::vector<int>(knoten, 0)),
          farben(knoten, Farbe::WEISS) {}

    void addKante(int von, int nach, int gewicht = 1) {
        if (von < 0 || von >= n || nach < 0 || nach >= n) {
            throw std::out_of_range("Ungültiger Knotenindex");
        }

        matrix[von][nach] = gewicht;

        if (!gerichtet) {
            matrix[nach][von] = gewicht;
        }
    }

    void removeKante(int von, int nach) {
        if (von < 0 || von >= n || nach < 0 || nach >= n) {
            throw std::out_of_range("Ungültiger Knotenindex");
        }

        matrix[von][nach] = 0;

        if (!gerichtet) {
            matrix[nach][von] = 0;
        }
    }

    bool hatKante(int von, int nach) const {
        return matrix[von][nach] != 0;
    }

    int getGewicht(int von, int nach) const {
        return matrix[von][nach];
    }

    void setFarbe(int knoten, Farbe f) {
        if (knoten < 0 || knoten >= n) {
            throw std::out_of_range("Ungültiger Knotenindex");
        }
        farben[knoten] = f;
    }

    Farbe getFarbe(int knoten) const {
        if (knoten < 0 || knoten >= n) {
            throw std::out_of_range("Ungültiger Knotenindex");
        }
        return farben[knoten];
    }

    void resetFarben(Farbe f = Farbe::WEISS) {
        for (int i = 0; i < n; ++i) {
            farben[i] = f;
        }
    }

    void printMatrix() const {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    void printFarben() const {
        for (int i = 0; i < n; ++i) {
            std::cout << "Knoten " << i << ": "
                      << farbeZuString(farben[i]) << "\n";
        }
    }

private:
    static const char* farbeZuString(Farbe f) {
        switch (f) {
            case Farbe::WEISS:   return "WEISS";
            case Farbe::GRAU:    return "GRAU";
            case Farbe::SCHWARZ: return "SCHWARZ";
        }
        return "";
    }
};


void bfs(AdjazenzMatrix matrix) {
    int n = matrix.n;
    matrix.resetFarben();
    for (int i = 0; i < n; i++) {
        matrix.farben[i] = Farbe::WEISS;
    }
}