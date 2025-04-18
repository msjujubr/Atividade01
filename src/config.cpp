#include "config.hpp"
#include "archives.hpp"
#include <algorithm> 
#include <sstream> 

Config config;

int defVento(){
    bool E = config.vntE, D = config.vntD, C = config.vntC, B = config.vntB;
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

    config.n = numeros[0]; config.m = numeros[1];
    config.arvores_queimando.push_back(std::make_pair(numeros[2], numeros[3]));

    std::vector<std::string> mensagem = {"iteracao", "0"};
    escritaArquivo<std::string>(mensagem);
    while(!arquivo.empty()){
        std::istringstream stream(arquivo[0]);
        arquivo.erase(arquivo.begin());
        
        std::vector<int> linha;
        while (stream >> num){
            linha.push_back(num);
        }
        config.floresta.push_back(linha);
        escritaArquivo<int>(linha);

    }
    std::vector<std::pair<int, int>> zeros;
    for (int i = 0; i < config.n; ++i) {
        for (int j = 0; j < config.m; ++j) {
            if (config.floresta[i][j] == 0) {
                zeros.push_back({i, j});
            }
        }
    }

    inicio_animal();
    config.animVid = 1;
}

void propagacao(){
    std::vector<std::pair<int, int>> vizinhos, auxiliar;
    switch (defVento()){  
        case 0:
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i-1, j}, {i+1, j}, {i, j-1}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 1: // E
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i-1, j}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 2: // D
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i+1, j}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 3: // DE
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i+1, j}, {i-1, j}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 4: // B
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i, j-1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 5: // BE
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i-1, j}, {i, j-1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;        
    case 6: // BD
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i+1, j}, {i, j-1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 8: // BDE
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i-1, j}, {i, j-1}, {i+1, j}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 9: // C
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 10: // CE
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i-1, j}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 11: // CD
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i+1, j}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 12: // CDE
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i-1, j}, {i+1, j}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 13: // CB
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i, j-1}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;
    case 14: // CBE
        while (!config.arvores_queimando.empty()){
            auto [i, j] = config.arvores_queimando.front(); 
            config.floresta[i][j] = 3;
            config.arvores_queimando.erase(config.arvores_queimando.begin()); 
            vizinhos = {{i-1, j}, {i, j-1}, {i, j+1}};
            for (auto [vi, vj] : vizinhos) { 
                prop(vi, vj, auxiliar);
            }
        }
        config.arvores_queimando = auxiliar;
        break;   
    }
}

void prop(int x, int y, std::vector<std::pair<int,int>>& arvores){
    if(x >= 0 && x < config.n && y >= 0 && y < config.m){
        if(config.floresta[x][y] == 1){
            config.floresta[x][y] = 2;
            arvores.push_back(std::make_pair(x, y));
        }
    }
}

void save_game(){
    std::vector<std::string> mensagem;
    std::cout<< "X: " << config.animPosX << " Y: " << config.animPosY << std::endl;
    int original = config.floresta[config.animPosX][config.animPosY];
    config.floresta[config.animPosX][config.animPosY] = 9;

    for(int i = 0; i <config. n; i++){ escritaArquivo<int>(config.floresta[i]); }
    
    config.floresta[config.animPosX][config.animPosY] = original;

    mensagem = {"Info:", std::to_string(config.animMov), "Passos", std::to_string(config.animMort), "Mortes do Animal"};
    escritaArquivo<std::string>(mensagem);
    mensagem.clear();
}

void inicio_animal(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_linha(0, config.n - 1);
    std::uniform_int_distribution<> dist_coluna(0, config.m - 1);

    while (true) {
        int i = dist_linha(gen);
        int j = dist_coluna(gen);

        if (config.floresta[i][j] == 0 ||config.floresta[i][j] == 1) {
            config.animPosX = i;
            config.animPosY = j;
            return;
        }
    }

}