#include "config.hpp"
#include "archives.hpp"
#include <algorithm> 
#include <sstream> 

Config cnfg;

int defVento(){
    bool E = cnfg.vntE, D = cnfg.vntD, C = cnfg.vntC, B = cnfg.vntB;
    bool todos (E && B && C && D);
    if (todos || !todos){ return 0; } //CBDE
    else if (!C && !B && !D && E) { return 1; }//E
    else if (!C && !B && D && !E) { return 2; }//D
    else if (!C && !B && D && E) { return 3; } //DE
    else if (!C && B && !D && !E) { return 4; }//B
    else if (!C && B && !D && E) { return 5; } //BE
    else if (!C && B && D && !E) { return 6; } //BD
    else if (!C && B && D && E) { return 7; }  //BDE
    else if (C && !B && !D && !E) { return 8; }//C
    else if (C && !B && !D && E) { return 9; } //CE
    else if (C && !B && D && !E) { return 10; }//CD 
    else if (C && !B && D && E) { return 11; } //CDE
    else if (C && B && !D && !E) { return 12; }//CB
    else if (C && B && !D && E) { return 13; } //CBE
    else if (C && B && D && !E) { return 14; } //CBD
}

void configuracoes(){
    std::vector<std::string> arquivo;
    arquivo = leituraArquivo();

    if(arquivo.empty()){ return; }
    std::istringstream stream(arquivo[0]);
    arquivo.erase(arquivo.begin());
    int num, numeros[4], i = 0;
    while (stream >> num){
        numeros[i] = num;
        i++;
    }

    cnfg.n = numeros[0]; cnfg.m = numeros[1];
    cnfg.arv_1_2.push_back(std::make_pair(numeros[2], numeros[3]));

    std::vector<std::string> mensagem = {"iteracao", "0"};
    escritaArquivo<std::string>(mensagem);
    while(!arquivo.empty()){
        std::istringstream stream(arquivo[0]);
        arquivo.erase(arquivo.begin());
        
        std::vector<int> linha;
        while (stream >> num){
            linha.push_back(num);
        }
        cnfg.floresta.push_back(linha);
        escritaArquivo<int>(linha);

    }
    
    inicio_animal();

    int x = cnfg.animX, y = cnfg.animY, pas = cnfg.animMov, escp = cnfg.animMrt;
    mensagem = {"Info:", std::to_string(pas), "Passos", std::to_string(escp), 
                "Escapes", "X:", std::to_string(x), "Y", std::to_string(y)};
    escritaArquivo<std::string>(mensagem);

}

void propagacao(){
    std::vector<std::pair<int, int>> vizinhos, auxiliar;
    switch (defVento()){  
        case 0:
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i-1, j}, {i+1, j}, {i, j-1}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 1: // E
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i-1, j}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 2: // D
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i+1, j}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 3: // DE
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i+1, j}, {i-1, j}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 4: // B
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i, j-1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 5: // BE
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i-1, j}, {i, j-1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;        
    case 6: // BD
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i+1, j}, {i, j-1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 8: // BDE
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i-1, j}, {i, j-1}, {i+1, j}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 9: // C
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 10: // CE
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i-1, j}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 11: // CD
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i+1, j}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 12: // CDE
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i-1, j}, {i+1, j}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 13: // CB
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i, j-1}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;
    case 14: // CBE
        while (!cnfg.arv_1_2.empty()){
            auto [i, j] = cnfg.arv_1_2.front(); 
            cnfg.arv_2_3.push_back(cnfg.arv_1_2.front());
            cnfg.arv_1_2.erase(cnfg.arv_1_2.begin()); 
            vizinhos = {{i-1, j}, {i, j-1}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        cnfg.arv_1_2 = auxiliar;
        break;   
    }
}

void prop(int x, int y, std::vector<std::pair<int,int>>& arvores){ 
    if(x >= 0 && x < cnfg.n && y >= 0 && y < cnfg.m){
        if(cnfg.floresta[x][y] == 1){
            cnfg.floresta[x][y] = 2;
            arvores.push_back(std::make_pair(x, y));
        }
    }
}

void salvar(){   
    for(int i = 0; i <cnfg. n; i++){ escritaArquivo<int>(cnfg.floresta[i]); }
    int x = cnfg.animX, y = cnfg.animY, pas = cnfg.animMov, escp = cnfg.animMrt;
    std::vector<std::string> mensagem;
    mensagem = {"Info:", std::to_string(pas), "Passos", std::to_string(escp), 
                "Escapes", "X:", std::to_string(x), "Y", std::to_string(y)};
    escritaArquivo<std::string>(mensagem);
}

void inicio_animal(){ 
    cnfg.animVid = 1; cnfg.animCnt = 0; cnfg.animMrt = 0; cnfg.animMov = 0;
    
    std::random_device rd;
    std::mt19937 aleatorio(rd());
    std::uniform_int_distribution<> linhaSort(0, cnfg.n - 1);
    std::uniform_int_distribution<> colunaSort(0, cnfg.m - 1);

    while (true) {
        int lin = linhaSort(aleatorio);
        int col = colunaSort(aleatorio);
        int v = cnfg.floresta[lin][col];

        if (v == 0 || v == 1) {
            cnfg.animX = lin;
            cnfg.animY = col;
            return;
        }
    }
}

void queimadas(){
    while(!cnfg.arv_2_3.empty()){
        auto [i, j] = cnfg.arv_2_3.front(); 
        cnfg.arv_2_3.erase(cnfg.arv_2_3.begin()); 
        cnfg.floresta[i][j] = 3;
    }
}