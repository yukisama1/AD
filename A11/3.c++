#include <iostream>
#include <vector>
#include <stack>

class Graph {
public:
    enum class Farbe { WEISS, GRAU, SCHWARZ };

private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<Farbe> farbe;
    std::vector<int> parent;
    std::vector<int> zyklus;
    bool zyklusGefunden = false;

public:
    Graph(int knoten)
        : n(knoten),
          adj(knoten),
          farbe(knoten, Farbe::WEISS),
          parent(knoten, -1) {}

    void addKante(int von, int nach) {
        adj[von].push_back(nach);
    }

    bool findeZyklus() {
        for (int i = 0; i < n; ++i) {
            if (farbe[i] == Farbe::WEISS) {
                if (dfs(i)) {
                    return true;
                }
            }
        }
        return false;
    }

    void printZyklus() const {
        if (zyklus.empty()) {
            std::cout << "Kein Zyklus vorhanden.\n";
            return;
        }

        std::cout << "Zyklus gefunden: ";
        for (int v : zyklus) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

private:
    bool dfs(int u) {
        farbe[u] = Farbe::GRAU;

        for (int v : adj[u]) {
            if (farbe[v] == Farbe::WEISS) {
                parent[v] = u;
                if (dfs(v))
                    return true;
            }
            else if (farbe[v] == Farbe::GRAU) {
                // Zyklus rekonstruieren
                rekonstruiereZyklus(u, v);
                return true;
            }
        }

        farbe[u] = Farbe::SCHWARZ;
        return false;
    }

    void rekonstruiereZyklus(int von, int nach) {
        std::stack<int> s;
        s.push(nach);

        for (int v = von; v != nach; v = parent[v]) {
            s.push(v);
        }
        s.push(nach);

        while (!s.empty()) {
            zyklus.push_back(s.top());
            s.pop();
        }
    }
};

int main() {
    Graph g(5);

    g.addKante(0, 1);
    g.addKante(1, 2);
    g.addKante(2, 3);
    g.addKante(3, 1); // Zyklus
    g.addKante(3, 4);

    if (g.findeZyklus()) {
        g.printZyklus();
    } else {
        std::cout << "Kein Zyklus gefunden.\n";
    }

    return 0;
}