#include "archives.hpp"


std::vector<std::string> leituraArquivo(){
    std::ifstream arq_entrada("input.dat");
    std::vector<std::string> dado;

    std::string line;
    while (std::getline(arq_entrada, line)) {
        dado.push_back(line);
    }

    arq_entrada.close();
    return dado;
}

void limparSaida(){
    std::ofstream arquivo("output.dat", std::ios::trunc);
}

template void escritaArquivo<int>(std::vector<int>&);
template void escritaArquivo<std::string>(std::vector<std::string>&);