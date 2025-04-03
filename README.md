# Simulação de Propagação de Incêndios
- [Especificação do Problema (atividade proposta)](#especificacao-do-problema)
- [Compilação (explicação do Makefile)](#compilacao)
- [Entradas e Saídas (o que se espera?)](#entradas-e-saidas)
- [Padrões de Propagação (análise do algoritmo desenvolvido)](#padroes-de-propagacao)
- [Referências](#referencias)
- 
## Especificação do Problema
Tendo a matriz original contida em um arquivo *input.dat*, com a primeira linha informando a proporção da matriz e a localização do foco do incêndio, onde cada algarismo representa um estado de simulação:

>  &nbsp;&nbsp;&nbsp;&nbsp;0 -> Área vazia (não queima)
> 
>  &nbsp;&nbsp;&nbsp;&nbsp;1 -> Árvore saudável 
> 
>  &nbsp;&nbsp;&nbsp;&nbsp;2 -> Árvore em chamas
> 
>  &nbsp;&nbsp;&nbsp;&nbsp;3 -> Árvore queimada (não propaga mais fogo, árvore totalmente queimada)
> 
>  &nbsp;&nbsp;&nbsp;&nbsp;4 -> Presença de água

A cada iteração, a propagação do fogo segue as seguintes regras:

> &nbsp;&nbsp;&nbsp;&nbsp;**1)** Uma árvore saudável (1) entra em chamas (2) se houver ao menos uma árvore
vizinha em chamas (2);
>  
> &nbsp;&nbsp;&nbsp;&nbsp;**2)** Uma árvore em chamas (2) se torna queimada (3) após um ciclo e não propagará mais o fogo.
> 
> &nbsp;&nbsp;&nbsp;&nbsp;**3)** Propagação do fogo ocorre exclusivamente nas direções ortogonais (esquerda, direita,
acima e abaixo).
> 
> &nbsp;&nbsp;&nbsp;&nbsp;**4)** A simulação deve considerar dois estados de propagação do fogo:
>  
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*(a) Sem influência do vento:* o fogo se propaga linearmente nas quatro direções ortogonais.
> 
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*(b) Com influência do vento:* o fogo se propaga apenas em direções ortogonais > específicas, que devem ser configuradas no arquivo *config.h*, podendo ser uma ou mais direções.
> 
> &nbsp;&nbsp;&nbsp;&nbsp;**5)** O processo de propagação do incêndio continua até que não haja mais árvores em
chamas (2) ou que o número máximo de interações, K, seja alcançado.
> 
Dentro desta matriz, há um animal, representado por uma variável externa (escolhi o valor 8), que deve procurar uma posição segura. Sua movimentação segue as seguintes regras:
>  &nbsp;&nbsp;&nbsp;&nbsp;**1)** O animal, quando localizado em uma posição segura (valor 1 ou 0), deve procurar uma nova posição segura nas direções ortogonais, as posições são classificadas da seguinte forma:
>
>  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*(a) Melhor opção:* posição com valor 4 (presença de água).
>
>  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*(b) Opções intermediárias:* posição com valor 0 (área vazia) e posição com valor 1 (árvore saudável).
>
>  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*(c) Pior opção:* posição com valor 3 (árvore queimada).
>
> &nbsp;&nbsp;&nbsp;&nbsp;**2)** Caso o animal se encontre em uma posição segura (valor 0), ele poderá permanecer
nesta posição por até 3 interações.
>
> &nbsp;&nbsp;&nbsp;&nbsp;**3)** Quando o animal alcançar uma posição contendo água, essa deverá ser atualizada para o valor 0 e todas as posições ortogonalmente próximas deverão ser convertidas para o valor 1.

# Compilação
# Entradas e Saídas
# Padrões de Propagação
# Referências
