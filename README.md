# Simulação de Propagação de Incêndios
- [Especificação do Problema](#especificaçãodoproblema)
- [Metodologia](#instalação)
- [Como Usar](#como-usar)

## Especificação do Problema
Este trabalho consiste na implementação de um simulador de propagação de incêndios em matrizes. Tendo a matriz original contida em um arquivo *input.dat*, com a primeira linha informando a proporção da matriz e a localização do foco do incêndio, onde cada algarismo representa um estado de simulação:

>  0 -> Área vazia (não queima)
> 
>  1 -> Árvore saudável 
> 
>  2 -> Árvore em chamas
> 
>  3 -> Árvore queimada (não propaga mais fogo, árvore totalmente queimada)
> 
>  4 -> Presença de água

A cada iteração, a propagação do fogo segue as seguintes regras:
> 1) Uma árvore saudável (1) entra em chamas (2) se houver ao menos uma árvore
vizinha em chamas (2);
> 
> 2) Uma árvore em chamas (2) se torna queimada (3) após um ciclo e não propagará mais o fogo.
>
> 3) Propagação do fogo ocorre exclusivamente nas direções ortogonais (esquerda, direita,
acima e abaixo).
>
> 4) A simulação deve considerar dois estados de propagação do fogo:
> 
> - Sem influência do vento: o fogo se propaga linearmente nas quatro direções ortogonais.
>
> - Com influência do vento: o fogo se propaga apenas em direções ortogonais específicas, que devem ser configuradas no arquivo *config.h*, podendo ser uma ou mais direções.
>
> 5) O processo de propagação do incêndio continua até que não haja mais árvores em
chamas (2) ou que o número máximo de interações, K, seja alcançado.

Dentro desta matriz, há um animal que deve procurar uma posição segura. Sua movimentação segue as seguintes regras:
> O animal, quando localizado em uma posição segura (valor 1 ou 0), deve procurar uma nova posição segura nas direções ortogonais, as posições são classificadas da seguinte forma:
>
> - (a) Melhor opção: posição com valor 4 (presença de água)
>
> - (b) Opções intermediárias: posição com valor 0 (área vazia) e posição com valor 1 (árvore saudável).
>
> - (c) Pior opção: posição com valor 3 (árvore queimada)
> 

# Metodologia 
