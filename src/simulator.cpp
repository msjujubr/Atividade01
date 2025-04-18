#include "simulator.hpp"
#include "config.hpp"
#include "archives.hpp"
#include <algorithm> 
#include <sstream> 

// entrou na agua, joga imediatamente
bool atividade_fogo(){
    std::cout << config.arvores_queimando.size() << std::endl;
    if (!config.arvores_queimando.empty()){ return 1; }
    return 0;   
}

void inicializacao(){
    limparSaida();
    configuracoes();
    int i = 1;
    while(atividade_fogo()){
        std::vector<std::string> mensagem = {"iteracao", std::to_string(i)};
        escritaArquivo<std::string>(mensagem);
    
        animal();
        movimentacao_animal();
        propagacao();
        schrodinger();
        save_game();
        
        if(i >= config.iteracoes){return;}
        i++;
    }   
}

void animal(){
    if (config.animVid){
    } else{
        bool pos = 0;
        for (int i = 0; i < config.n && !pos; i++){
            for(int j = 0; j < config.m; j ++){
                if(!fog_prox(i, j)){
                    if(config.floresta[i][j] == 0 || config.floresta[i][j] == 1){
                    config.animPosX = i; config.animPosY = j;
                    pos = 1;
                    }
                    break;
                }
            }
        }
    }
}

bool fog_prox(int x, int y){
    std::pair<int, int> vizinhos[8] = {{x+1, y}, {x+1, y+1}, {x+1, y-1}, {x-1, y}, {x-1, y-1}, {x-1, y+1}, {x, y-1}, {x, y+1}};
    return 1;
    for(auto[i, j] : vizinhos){
        if(x >= 0 && x < config.n && y >= 0 && y < config.m){
            if(config.floresta[i][j] == 2){}
            return 1;
        }
    }   return 0;
}

void movimentacao_animal(){
    int x = config.animPosX, y = config.animPosY, aux = 10, auxX=0, auxY=0;
    if(fog_prox(x, y)){ 
        std::pair<int, int> vizinhos[8] = {{x+1, y}, {x-1, y}, {x, y-1}, {x, y+1}};
        for(auto[i, j] : vizinhos){
            if(i >= 0 && i < config.n && j >= 0 && j < config.m){
                if(config.floresta[i][j] == 4){
                    animal_agua();
                    config.animPosX = i; config.animPosY = j;
                    return;
                } else{  
                    int cont = soma_pos(i, j);
                    if (aux > cont){
                        aux = cont;
                        auxX = i;
                        auxY = j;
                    }
                }
                
            }
        }
        config.animPosX = auxX; config.animPosY = auxY;
        config.animCont = 0; config.animMov++;
    } else if (config.animCont < 3){ config.animCont++; }
    else {
        std::pair<int, int> vizinhos[8] = {{x+1, y}, {x-1, y}, {x, y-1}, {x, y+1}};
        for(auto[i, j] : vizinhos){
            if(i >= 0 && i < config.n && j >= 0 && j < config.m){
                int cont = soma_pos(i, j);
                if (aux > cont){
                    aux = cont;
                    auxX = i;
                    auxY = j;
                }
            }   
        }
    }
}

int soma_pos(int x, int y){
    std::pair<int, int> vizinhos[8] = {{x+1, y}, {x-1, y}, {x, y-1}, {x, y+1}};
    int cont = 0;
    for(auto[i, j] : vizinhos){
        if(i >= 0 && i < config.n && j >= 0 && j < config.m){
            if(config.floresta[i][j] == 4)continue;
            if(std::make_pair(i, j) == std::make_pair(config.animPosX, config.animPosY))continue;
            cont += config.floresta[i][j];
        }
    }
    return cont;
}

void schrodinger(){
    int x = config.animPosX, y = config.animPosY, aux1=0, cont=0;
    std::pair<int, int> vizinhos[8] = {{x+1, y}, {x-1, y}, {x, y-1}, {x, y+1}};
    for(auto[i, j] : vizinhos){
        if(i >= 0 && i < config.n && j >= 0 && j < config.m){
            aux1++, cont++;
            if(config.floresta[i][j] == 2){
                aux1++;
            }
        }
    }
    if(aux1 == (2*cont)){ 
        config.animVid = 0;
        config.animMort++;
        return;
    }
    config.animVid = 1;
}

void animal_agua(){
    int x = config.animPosX, y = config.animPosY;
    std::pair<int,int> vizinhos[4] = {{x+1, y}, {x-1, y}, {x, y+1}, {x, y-1}};
    for(auto [i, j] : vizinhos){
        if(i >= 0 && i < config.n && j >= 0 && j < config.m){
        config.floresta[i][j] = 1;
        }
    }
}