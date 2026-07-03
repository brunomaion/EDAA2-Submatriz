// g++ criarCsv.cpp -o criarCsv
// ./criarCsv

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
  string nomeCsv = "resultados.csv";

  vector<string> colunas = {
      "Execucao",
      "Ordem",
      "Menor Soma Global",
      "IndiceI",
      "IndiceJ",
      "Ordem Submatriz",
      "Submatrizes Percorridas",
      "Tempo Total (s)"
  };
  ofstream arquivo(nomeCsv);
  for (size_t i = 0; i < colunas.size(); i++) {
      arquivo << colunas[i];
      if (i < colunas.size() - 1)
          arquivo << ",";
  }
  arquivo << "\n";
  arquivo.close();
  cout << "Arquivo '" << nomeCsv << "' criado." << endl;
  return 0;
}