#include "simulator.hpp"
#include "config.hpp"

bool atividade_fogo(){
    if (!cnfg.arv_2_3.empty()){ return 1; }
    return 0;   
}

void inicializacao(){
    limparSaida();
    configuracoes();
    int i = 1;
    do{
        std::vector<std::string> mensagem = {"iteracao", std::to_string(i)};
        escritaArquivo<std::string>(mensagem);
    
        animal_movim();
        queimadas();   
        propagacao();
        schrodinger();
        escape();
        salvar();
        
        if(i >= cnfg.iteracoes){return;}
        i++;

    } while (atividade_fogo());
}

void escape(){
    if(cnfg.animVid){
        int x = cnfg.animX, y = cnfg.animY;
        if (cnfg.floresta[x][y] == 2){
            cnfg.animMrt++;
            std::pair<int, int> vizinhos[4] = {{x+1, y}, {x-1, y}, {x, y-1}, {x, y+1}};
            for(auto[i, j] : vizinhos){
                if(i >= 0 && i < cnfg.n && j >= 0 && j < cnfg.m){
                    if(cnfg.floresta[i][j] == 0 || cnfg.floresta[i][j] == 1){ 
                        cnfg.animX = i;
                        cnfg.animY = j;
                        return;
                    } 
                }
            }        
        }
    }
}

bool fog_prox(int x, int y){
    std::pair<int, int> vizinhos[8] = {{x+1, y}, {x+1, y+1}, {x+1, y-1}, {x-1, y}, {x-1, y-1}, {x-1, y+1}, {x, y-1}, {x, y+1}};
    for(auto[i, j] : vizinhos){
        if(i >= 0 && i < cnfg.n && j >= 0 && j < cnfg.m){
            if(cnfg.floresta[i][j] == 2){ return 1; } 
        }
    }   return 0;
}

void animal_movim(){
    if(cnfg.animVid){
        int x = cnfg.animX, y = cnfg.animY, aux = 12, auxX = x, auxY = y;
        if(fog_prox(x, y)){ 
            std::pair<int, int> vizinhos[4] = {{x+1, y}, {x-1, y}, {x, y-1}, {x, y+1}};
            for(auto[i, j] : vizinhos){
                if(i >= 0 && i < cnfg.n && j >= 0 && j < cnfg.m){
                    if(cnfg.floresta[i][j] == 4){
                        animal_agua();
                        cnfg.animX = i; cnfg.animY = j;
                        return;
                    }  
                    int cont = soma_pos(i, j);
                    if (aux > cont){
                        aux = cont;
                        auxX = i;
                        auxY = j;
                    }  
                }
            }
            cnfg.animX = auxX; cnfg.animY = auxY;
            if(auxX != x && auxY!= y){ cnfg.animCnt = 0; }
            else{ cnfg.animCnt++; } cnfg.animMov++;
        } else if (cnfg.animCnt < 2){ cnfg.animCnt++; }
        else {
            std::pair<int, int> vizinhos[4] = {{x+1, y}, {x-1, y}, {x, y-1}, {x, y+1}};
            for(auto[i, j] : vizinhos){
                if(i >= 0 && i < cnfg.n && j >= 0 && j < cnfg.m){
                    int cont = soma_pos(i, j);
                    if (aux > cont){
                        aux = cont;
                        auxX = i;
                        auxY = j;
                    }
                }   
            }
            cnfg.animX = auxX; cnfg.animY = auxY;
            if(auxX != x && auxY!= y){ cnfg.animCnt = 0; }
            else{cnfg.animCnt++;} cnfg.animMov++;
        }
    }
}

int soma_pos(int x, int y){
    std::pair<int, int> vizinhos[4] = {{x+1, y}, {x-1, y}, {x, y-1}, {x, y+1}};
    int cont = 0;
    for(auto[i, j] : vizinhos){
        if(i >= 0 && i < cnfg.n && j >= 0 && j < cnfg.m){
            if(cnfg.floresta[i][j] == 4 || 
               std::make_pair(i, j) == std::make_pair(cnfg.animX, cnfg.animY))continue;
            cont += cnfg.floresta[i][j];
        }
    }
    return cont;
}

void schrodinger(){
    if(cnfg.animVid){
        int x = cnfg.animX, y = cnfg.animY, aux1=0, cont=0;
        std::pair<int, int> vizinhos[8] = {{x+1, y}, {x-1, y}, {x, y-1}, {x, y+1}};
        for(auto[i, j] : vizinhos){
            if(i >= 0 && i < cnfg.n && j >= 0 && j < cnfg.m){
                aux1++, cont++;
                if(cnfg.floresta[i][j] == 2){
                    aux1++;
                }
            }
        }
        if(aux1 == (2*cont)){ 
            cnfg.animVid = 0;
            cnfg.animX = -1; cnfg.animY = -1;
            cnfg.animMrt++;
            return;
        }
    }
}

void animal_agua(){
    int x = cnfg.animX, y = cnfg.animY;
    std::pair<int,int> vizinhos[4] = {{x+1, y}, {x-1, y}, {x, y+1}, {x, y-1}};
    for(auto [i, j] : vizinhos){
        if(i >= 0 && i < cnfg.n && j >= 0 && j < cnfg.m){
            cnfg.floresta[i][j] = 1;
        }
    }
}
