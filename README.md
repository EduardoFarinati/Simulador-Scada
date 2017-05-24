# Simulador-Scada
- Trabalho final de Algoritmos e Programação 2016/1
- Simulador Industrial SCADA
-----------------------------------
## Programadores:
- Eduardo Farinati Leite
- Lucas Bortolanza Grazziotim
-----------------------------------

## Guia de Arquivos:

1. Simulador Scada.cpp -> Código Principal do Programa
2. Grazziotim.h -> Biblioteca para simplificar a definição das funções utilizadas no programa
    * (O correto seria criar outro arquivo .c e apenas deixar os cabeçalhos na .h)

3. Desenhos utilizados no programa:
    1. caldeira.txt
    2. esteira.txt
    3. explodiu.txt
    4. quebrou.txt
-----------------------------------

## Guia sobre as funções e as estruturas utilizadas no programa:


* ### Na Grazziotim.h:

struct animacao_caldeira_posic
	//Grava a posição das bolinhas e o ciclo em que se encontram na animação

struct caldeira
	 //Grava os níveis dos insumos e do registro de cada caldeira

typedef struct parametros
	//Parâmetros para todas as simulações, salvos e carregados pela utilização de arquivos binário

int setas()
	//Controle da simulação pelas setas direcionais

void hide_cursor()
	//Esconde o cursor default do prompt

void show_cursor()
	//Mostra novamente o cursor default do prompt

void formatprompt()
	//Formatação e linguagem padrão do programa

void formatprompt_processos()
	//Formatação do prompt para as simulações

void formatprompt_estados()
	//Formatação do prompt para a alteração dos parâmetros e dos estados

void textbackground (int iColor)
	//Altera a cor do fundo para o caracter que será impresso na tela

void textcolor(int ForgC)
	//Função para a coloração do texto

void gotoxy(int x, int y) 
	//Envia o cursor para determinado ponto (x, y) da tela

void delay(unsigned int mseconds)
	//Função delay, pausa o processo

void flushkbhit()
	//Função para "limpar" o buffer após a utilização do kbhit

void slider_f(int selec_x, int selec_y, PARAMETROS *estado_anterior, int *contador)
	//Cria um slider para o controle do nível

void imprime_estado(int x, int y[], PARAMETROS *parametros, const int cor, const int mode)
	//Imprime os atuais parâmetros dos processos

void zera_estados(PARAMETROS *parametros)
	//Zera todos parâmetros para nova simulação

void imprime_esteira()
	//Imprime a esteira da segunda simulação

void imprime_caldeiras()
	//Imprime as caldeiras e o misturador da primeira simulação

int Mini_menu()
	//Menu de controle dentro da simulação

void print_logo()
	//Imprime o logo da caixa dentro da simulação

void mensagem_alarme(int n_caldeira)
	//Avisa o usuário sobre problemas no processo

void mensagem_estado(int v)
	//Indica o estado do processo para o usuário

void calcula_posic(int ciclo[], int x[], int y[], int k[], int l, int ciclo_s[], int x_s[], int y_s[], int k_s[], int *l_s)
	//Copia os parâmetros de posição para outras variáveis

void avalia_volume(PARAMETROS *parametros,int vol[],int *vol_total)
	//Calcula o número de volumes respectivo a cada caldeira e o total de acordo com o os parâmetros

void explosao()
	//Explode o misturador, se voltume total for maior que nove, estado crítico

void quebra()
	//Quebra a esteira, se a velocidade for maior que noventa, estado crítico

void salva_simu(PARAMETROS to_save)
	//Salva a simulação em um arquivo com o nome padrão de "Simulacao.bin"

void escolher_file_salvar(char file_name[])
	//Salva a simulação em um arquivo com o nome escrito pelo usuário

void escolher_file_abrir(char file_name[])
	//Carrega a simulação de nome igual ao entrado pelo usuário, se ela existir

void salvarestados(PARAMETROS to_save)
	//Salva os parâmetros atuais em um arquivo binário de nome escolhido pelo usuário

int carrega_parametros(PARAMETROS *to_read)
	//Carrega os parâmetros de um arquivo binário determinado pelo usuário


* ### No Simulador Scada.cpp:

int main(void)
	//Main da função, determina as opções de: iniciar uma nova simulação, carregar uma simulação ou fechar o programa

int menu_principal()
	//Imprime o seletor para opções no main, com retorno tipado

void menu_nova_simu(PARAMETROS parametros)
	//Menu de nova simulação, Parâmetros Zerados

 void inserirdadosiniciais(PARAMETROS *parametros)
	//Console para inserir dados iniciais, por meio de sliders

int menu_simulacao(PARAMETROS *parametros) 
	//Menu para seleção da simulação 1 (caldeiras e misturador) ou simulação 2(esteira)

int caldeira(PARAMETROS *parametros)
	//Simulação 1, caldeiras e misturador

int esteira(PARAMETROS *parametros)
	//Simulação 2, esteira

void controlarprocessos(PARAMETROS *parametros)
	//Inserir dados atualizados para as simulações, por meio de sliders

void menu_velha_simu(PARAMETROS parametros)
	//Menu para uma simulação carregada de um arquivo ou de simulação com dados iniciais já inseridos

void imprime_parametros(PARAMETROS *parametros)
	//Imprime os atuais parâmetros para o usuário realizar uma leitura

void animacao_caldeira(PARAMETROS *parametros)
	//Função responsável por chamar todas as animações da caldeira e do misturador na simulação 1

void animacao_esteira(PARAMETROS *parametros)
	//Função responsável por chamar todas as animações da esteira na simulação 2
