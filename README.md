# RGBender

## Equipe

### Programadores

* Felipe Osório

* Gustavo Lopes

* Harrison Pedro

### Artistas

* Fernanda Noronha

* Mariana Martins

* Marco Xavier

### Músico

* Henrique

## Tutorial para executar o jogo

* Digite make clean

* Digite make

* Digite make run

## Dependências

* SDL2

* SDL2_image, SDL2_mixer

* zlib(latest)

## Gênero

É uma composição de Boss Fighting, top-down shooter

## Resumo

Protagonista viaja no tempo após pichar um símbolo e vai parar na renascença. Ele decide entrar para à história do mundo da arte como um grande pichador.

## Gameplay

Teclado: WASD + MOUSE + 1 2 3

W: Move para cima

A: Move para esquerda

S: Move para baixo

D: Move para direita

Espaço: Dash(na direção do movimento)

Mouse cursor: Mira

Botão mouse esquerdo: Atira

1: Seleciona cor verde

2: Seleciona cor vermelho

3: Seleciona cor azul

R: Invoke(Combina cores)

## Poderes

O personagem ataca utilizando de tintas, essas que podem ser combinadas como mostradas na figura abaixo:

![Combinação de cores](http://i.imgur.com/DgjUGaQ.png)

## Cenário

Itália Renascentista + Pós-Moderno 

## Organização de elementos do jogo

Vida estilo Zelda (corações)

Área comum: sala de treinamento, mapa simples de navegação entre boss e cutscenes; há um training dummy para testar habilidades

## Condição de vitória e derrota

Após derrotar os 3 bosses, o jogador terá ganhado o jogo. Durante essas lutas caso ele perca todas suas vidas, a personagem morre, e o jogador volta para o início da fase em que ele perdeu a luta.

## Bosses

### 1º Boss: Xuxa Freira

Mecânicas:

	Survival DPS Range

	Padronizada

	100% de vida = Cantoria, canta e crianças em correm em volta dela, servindo como escudo, fica invencível. Quando termina de cantar, à “nuvem” de criança dispersa

	50% de vida = Senta lá Claudia, começa a jogar os bancos da paróquia no jogador

	25% de vida = enrage, berserk, joga criança no jogador

Ao morrer, dropa a tinta azul

### 2º Boss:  Davi, Estátua de Michelangelo, O cara mais bonito da cidade

Mecânicas:

	Lento

	100%: Pular + ataque = area de dano, se cura (pode ser interrompido)

	50%: Disassemble e ganha alcance (arranca um braço para bater em você)

	25%: Enrage (braço bumerangue)

Ao morrer dropa a tinta vermelha

### 3º Boss: Seu rival do futuro

Detalhes da batalha:

	Batalha no topo de um prédio

	Quebra 4ª parede (desliga tela, picha tela, picha mais rápido, etc.)

	Poder igual ao jogador, porém + refinado
