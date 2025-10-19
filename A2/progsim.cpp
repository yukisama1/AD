#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

vector<string> loadProgram(const string &filename) {
    vector<string> program;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line.find(':') != string::npos) line = line.substr(line.find(':') + 1);
        while (!line.empty() && (line.front() == ' ' || line.front() == '\t')) line.erase(line.begin());
        program.push_back(line);
    }
    return program;
}

map<int,int> simulate(const vector<string> &prog, map<int,int> regs) {
    int pc = 0;
    while (pc < (int)prog.size()) {
        string line = prog[pc];
        if (line == "HALT") break;

        stringstream ss(line);
        string tok; ss >> tok;

        if (tok == "IF") {
            string reg, eq, zero, gotoWord; int target;
            ss >> reg >> eq >> zero >> gotoWord >> target;
            int r = reg[1] - '0';
            if (regs[r] == 0) pc = target - 1; else pc++;
        }
        else if (tok == "GOTO") {
            int target; ss >> target;
            pc = target - 1;
        }
        else if (tok[0] == 'R') {
            int r = tok[1] - '0';
            string assign, src, op; ss >> assign >> src;
            if (src[0] == 'R') {
                int r2 = src[1] - '0';
                if (ss >> op) {
                    int val; ss >> val;
                    if (op == "+") regs[r] = regs[r2] + val;
                    else if (op == "-") regs[r] = regs[r2] - val;
                } else regs[r] = regs[r2];
            } else regs[r] = stoi(src);
            pc++;
        }
        else pc++;
    }
    return regs;
}

int main() {
    vector<string> prog = loadProgram("prog.txt");
    map<int,int> regs;
    cout << "Eingabe n: "; cin >> regs[0]; regs[1] = 0;
    regs = simulate(prog, regs);
    cout << "\n--- Simulation beendet ---\n";
    for (auto &[k,v] : regs) cout << "R" << k << " = " << v << endl;
    cout << "Ergebnis (R1): " << regs[1] << endl;
}

