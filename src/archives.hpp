#ifndef ARCHIVES_HPP
#define ARCHIVES_HPP

#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> leituraArquivo();

template <typename V>
void escritaArquivo(std::vector<V>& linha){
    std::ofstream arq_saida("output.dat", std::ios::app); 
    
    for (size_t i = 0; i < linha.size(); i++) {
        arq_saida << linha[i];
        if (i < linha.size() - 1){ arq_saida << " "; }
        else {  arq_saida << std::endl; }; 
    }

    arq_saida.close();
}

void limparSaida();
#endif