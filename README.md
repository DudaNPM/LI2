# Li2_Rastros_2020
# Laboratórios de Informática 2

## Turno: PL3 Grupo: 4

## Elementos do grupo:
* a93321 Duarte Nuno Pereira Moreira
* a93176 Lucas Silva Carvalho
* a93587 Marcos Paulo Ribeiro

## 1ªSemana

Durante esta primeira semana de realização do projeto, o trabalho do grupo reduz-se em duas etapas.

Primeira etapa: criacao dos módulos; 

Para comecar foi necessário a criação de 3 ficheiros.c todos com um papel distinto, ou seja, um com o objetivo de guardar informações tais como structs e outros novos tipos e/ou definições geradas por nós (dados.c), outro para tratar da interação jogador/jogo (interface.c) e por último um módulo para cuidar da parte lógica do programa (logica.c). Para cada um destes ficheiros.c foi criado um outro com extensão.h que contém os protótipos das funções, geradas no ficheiro.c correspondente, para facilitar a organização do código.


Segunda etapa: implementação das funções;

A dificuldade começou a surgir a partir deste ponto. Sentimos uma pequena desorientação na execução da maior parte das funções devido principalmente à falta de conhecimento sobre esta linguagem(C).
A primeira função foi relativamente simples, uma vez que foi apenas necessário defenir os valores que constituem o estado inicial do jogo.
De seguida, foi tratada a função responsável por criar parte da interface do jogo (desenhar o tabuleiro no seu estado inicial) que através de ciclos faz print dos diversos caractéres correspondentes à peça branca("*"), às pecas pretas("#") e aos espacos vazios(".").
Por fim, foram formadas 4 pequenas e simples funçóes. Uma para alterar e outra para obter o estado de uma certa casa do tabuleiro, outra que devolve o número de jogadas executadas até ao momento e uma outra que devolve o número do jogador que deve efetuar a próxima jogada.

## 2ªSemana

Na segunda semana as principais etapas foram:

A criacao de um prompt que dá informação aos jogadores sobre:

  
   -O números de jogadas já efetuadas até ao momento;
  
   -O número do jogador a realizar a jogada;

A implementação das jogadas: sendo este módulo dividido em 3 partes:

	-Verificar se uma jogada é valida, tendo em conta o estado da casa para onde o jogador pretende jogar e também se esta se  encontra na vizinhança da peça atual;
        -Modificar as funções da semana anterior para que seja colocada uma peça preta na ultima posição da peça branca;
        -Verificar se o jogo chegou ao fim, o que acabou por ser a função mais extença que fizemos, uma vez que esta cobre os casos:
		-> a casa branca encontra-se no canto inferior esquerdo: ganha o jogador 1;
         	-> a casa branca encontra-se no canto superior direito: ganha o jogador 2;
		-> a jogada atual colocou a branca num sítio onde o próximo jogador não consegue jogar porque não há nenhuma casa  vizinha livre: o jogador que colocou a branca ganhou;

Por último chegou a parte de adicionar os comandos, onde surgiu o fator dificuldade, uma vez mais devido à falta de conhecimento sobre certas funções. Esta parte final
levou à realização de três comandos:

	-"Q", termina com o jogo;
	-"gr nome_do_ficheiro", permite ao jogador criar um ficheiro e gravar no seu interior o estado atual do tabuleiro;
	-"ler nome_do_ficheiro", permite ao jogador ver o estado do tabuleiro guardado no ficheiro em questão;
	
## 3ªSemana

Durante esta terceira fase do projeto foi-nos proposto:
- Fazer melhorias nos comandos ”gr” e “ler”, de maneira a que estes guardem também, informações sobre as jogadas;
- Criação do comando movs, que tem como objetivo listar as jogadas já feitas;


Terminar o comando “gr” foi simples, uma vez que apenas precisamos de fazer com que, para além de gravar o tabuleiro, este também guardasse as jogadas efetuadas.
Por outro lado, o comando “ler” mostrou-se um desafio pois o seu objetivo é dar procedimento a um jogo gravado a partir de um ficheiro. Isto implica que sejam recriados todos os elementos do estado do tabuleiro e da lista das jogadas, sendo utilizadas para a maioria dos casos estratégias que envolviam o número de caracteres do ficheiro.

Por fim, o comando “movs” mostrou ser também uma tarefa simples. Para o funcionamento deste comando foi necessário a criação uma função auxiliar que, a cada jogada efetuada, atualiza o arreio JOGADAS de modo a que estas informações sejam mais tarde utilizadas no comando "movs".

## 4ªSemana

O trabalho relativo a esta semana do projeto foi simplesmente a implementação do comando "pos". A execução deste novo comando, que recebe apenas um argumento (uma jogada) deve permitir ao utilizador aceder a uma jogada anterior.

O principal desafio deste comando foi, mais uma vez, a criação de uma função que alterasse o estado do jogo mas, que não se mostrou ser muito complicada. Para tal, tivemos em consideração as jogadas que já tinham sido feitas até à jogada passada como argumento e apartir dessa informação "recriou-se" o estado do tabuleiro, assim como, o do arreio de jogadas e as informações acerca dos jogadores.


## 5ªSemana

Neste novo guião foi-nos proposto a criação de um módulo de listas ligadas genérico e, para além disso, a implementação do comando "jog".
A este novo módulo foram acrescentadas várias simples funcões acerca de listas para mais tarde serem usadas no novo comando. Este deve permitir que o jogador atual peça ao computador para jogar por si. Para tal foram-nos fornecidas várias heurísticas da qual foi escolhida a Escolha aleatória.

A estratégia utilizada para a construção desta heurística, baseia-se em calcular o número de casas livres(N) em volta da posição atual do jogador e, posteriormente, utilizá-lo para formação de um número aleatório entre 0 e N. A partir deste, basta apenas escolher a possível jogada a efetuar.

## 6ªSemana

Por fim, nesta última semana de trabalho, o desafio foi semelhante ao da semana anterior mudando apenas a estratégia escolhida. Desta vez, optamos pela implementação da heurística da Distância euclidiana.

A implementação desta estratégia não foi um grande desafio, tirando um pequeno problema encontrado ao tentar inserir elementos numa uma lista ligada. Fora isso, foi apenas necessário calcular as distâncias entre as casas livres rodeadas pelo jogador e a casa vencedora do mesmo. A partir deste ponto, basta apenas escolher a que se encontra mais perto do objetivo.
