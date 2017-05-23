/* Trabalho final Algoritmos e Programa��o
Simulador industrial, com possibilidade de carregar simula��es salvas
MENU, pelas setas direcionais, em C++
Simula��o em C

Eduardo Farinati Leite
Lucas Bortolanza Grazziotim */

#include "Grazziotim.h" //Melhor biblioteca j� criada

/*  Refer�ncia das cores
0 = Black -----------  8 = Gray
1 = Blue ------------  9 = Light Blue
2 = Green ----------- 10 = Light Green
3 = Aqua ------------ 11 = Light Aqua
4 = Red ------------- 12 = Light Red
5 = Purple ---------- 13 = Light Purple
6 = Yellow ---------- 14 = Light Yellow
7 = White ----------- 15 = Bright White
*/

//Prot�tipos das fun��es das simula��es utilizadas no programa
int menu_principal();
void imprime_parametros(PARAMETROS*);
void menu_nova_simu(PARAMETROS);
void inserirdadosiniciais(PARAMETROS*);
int menu_simulacao(PARAMETROS*);
int caldeira(PARAMETROS*);
int esteira(PARAMETROS*);
void controlarprocessos(PARAMETROS*);
void menu_velha_simu(PARAMETROS);
void animacao_caldeira(PARAMETROS*);
void animacao_esteira(PARAMETROS*);

int main(void)//Main da fun��o determina as op��es de fechar o programa, carregar uma simula��o ou Criar uma nova simula��o
{
    int op; //Seleciona a op��o a partir do menu principal, contador para o for
    PARAMETROS parametros;

    formatprompt();
    system("title Simulador Scada");

    do //mantem o menu em um la�o de itera��o para sempre poder retornar por op��o do usuario
    {
        op = menu_principal();

        if(op == 0)
        {
            zera_estados(&parametros);//zera os dados para a nova simula��o
            menu_nova_simu(parametros); //Nova simula��o
        }

        if(op == 1)
        {
            if(carrega_parametros(&parametros) != ESC)//carrega os par�metros de um arquivo bin�rio, caso a fun��o retorne ESC, o usu�rio saiu sem carregar o arquivo
                menu_velha_simu(parametros); //Menu com par�metros salvos em um arquivo bin�rio
        }

    }
    while(op != 2); //caso o valor retornado pelo menu seja 2, o programa � terminado (op��o sair)

    system("CLS"); //Limpa a tela

    return 0;
}

int menu_principal()//Aqui � impresso o seletor para op��o no main, um retorno tipado
{
    int x =  23, y[3] = {25, 28, 31}; //impress�es na tela do seletor, posi��es x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a sele��o e o seletor na tela do usu�rio

    system("CLS");            //Limpa a tela para retorno do menu!
    textcolor(VERDE);          //cor do texto

    std::cout   << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
                << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
                << "*|*                                                                         *|*\n"
                << "|*                                                                           *|\n"
                << "*|                                                                           |*\n"
                << "|*     .|'''|                           '||`             ||`                 *|\n"
                << "*|     ||       ''                       ||              ||                  |*\n"
                << "|*     `|'''|,  ||  '||),,(||' '||  ||`  ||   '''|.  .|''||  .|''|, '||''|   *|\n"
                << "*|      .   ||  ||   || || ||   ||  ||   ||  .|''||  ||  ||  ||  ||  ||      |*\n"
                << "|*      |...|' .||. .||    ||.  `|..'|. .||. `|..||. `|..||. `|..|' .||.     *|\n"
                << "*|                                                                           |*\n"
                << "|*                                                                           *|\n"
                << "*|           .|'''|  .|'''',      /.\\      '||'''|.      /.\\                 |*\n" //Barras duplicadas para poder imprimir o caract�r '\'
                << "|*           ||      ||          // \\\\      ||   ||     // \\\\                *|\n"
                << "*|           `|'''|, ||         //...\\\\     ||   ||    //...\\\\               |*\n"
                << "|*            .   || ||        //     \\\\    ||   ||   //     \\\\              *|\n"
                << "*|            |...|' `|....' .//       \\\\. .||...|' .//       \\\\.            |*\n"
                << "|*                                                                           *|\n"
                << "*|                                                                           |*\n"
                << "|*                                                                           *|\n"
                << "*|                                                                           |*\n"
                << "|*                        Selecione uma op��o:                               *|\n"
                << "*|                       ----------------------                              |*\n"
                << "|*                                                                           *|\n"
                << "*|                                                                           |*\n"
                << "|*                        1. Nova simula��o                                  *|\n"
                << "*|                                                                           |*\n"
                << "|*                                                                           *|\n"
                << "*|                        2. Carregar simula��o salva                        |*\n"
                << "|*                                                                           *|\n"
                << "*|                                                                           |*\n"
                << "|*                        3. Sair                                            *|\n"
                << "*|                                                                           |*\n"
                << "|*                                                                           *|\n"
                << "*|                                                                           |*\n"
                << "*|*                                                                         *|*\n"
                << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
                << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";


    textcolor(VERMELHOLIGHT); //Cor do cursor!

    do
    {
        gotoxy(x, y[contador]);     //seleciona o cursor nas opcoes disponives do vetor
        printf(">");

        fflush(stdin);

        switch(setas())
        {
            case CIMA:if(contador != 0)
                          {
                              gotoxy(x, y[contador]);
                              printf(" "); //Apaga o cursor previo ao pressionamento da tecla
                              contador--;
                          }
                          break;

            case BAIXO:if(contador != 2)
                           {
                               gotoxy(x, y[contador]);
                               printf(" ");
                               contador++;
                           }
                           break;

            case ESC:if(contador != 2)//break dentro do if para fechar o programa caso esc seja apertado na ultima op��o
                     {
                         gotoxy(x, y[contador]);// Apaga o slider pr�-pressionamento da tecla ESC
                         printf(" ");
                         contador = 2;
                         break;
                     }

            case ENTER:sair = 1;
        }

        Beep(587.33, 50);//Padr�o da simula��o, Som do pressionamento de uma tecla
    }
    while(!sair);


    return contador; //retorna o contador para o main, assim levando a op��o selecionada,
}

                void menu_nova_simu(PARAMETROS parametros) //Menu de nova simula��o, Par�metros Zerados
{

    int x = 18, y[5] = {11, 14, 17, 20, 23}; //impress�es na tela do seletor, posi��es x e y definidas pelos arrays
    int error_posic[2] = {10, 31}; //Posi��o x e y da mensagem de erro
    int contador = 0, sair, sair_menu = 0; //contador auxiliar para a sele��o e o seletor na tela do usu�rio

    do
    {
        sair = 0;
        fflush(stdin);
        system("CLS");   //Limpa a tela para inicializa��o do menu_nova_simu
        textcolor(CIANO); //cor do texto

        std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
                  << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
                  << "*|*                                                                         *|*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                   1. Inserir dados iniciais dos processos                 *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                   2. Iniciar Simula��o / Visualizar Simula��o             |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                   3. Controlar Processos                                  *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                   4. Salvar estados dos processos                         |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                   5. Voltar para o menu principal                         *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|*                                                                         *|*\n"
                  << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
                  << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";


        textcolor(AMARELOLIGHT);      //cor do cursor

        do
        {
            gotoxy(x, y[contador]);  //seleciona o cursor nas opcoes disponives do vetor
            printf(">");

            fflush(stdin);

            switch(setas())
            {
                case CIMA:if(contador != 0)
                          {
                              gotoxy(x, y[contador]);
                              printf(" "); //Apaga o cursor previo ao pressionamento da tecla
                              contador--;
                          }
                          break;

                case BAIXO:if(contador != 4)
                           {
                               gotoxy(x, y[contador]);
                               printf(" ");
                               contador++;
                           }
                           break;

            case ESC:contador = 4; //caso ESC seja apertado sair e retorna para o menu principal
            case ENTER:sair = 1;
            }
            Beep(587.33, 50);//Padr�o da simula��o, Som do pressionamento de uma tecla
        }
        while(!sair);

        switch(contador)
        {
            case 0:inserirdadosiniciais(&parametros);
                   menu_velha_simu(parametros); //Ap�s inserir os dados iniciais, entramos no menu como uma simula��o carregada
                   sair_menu = 1;
                   break;

            case 1:gotoxy(error_posic[0], error_posic[1]);
                   textcolor(VERMELHOLIGHT);
                   printf("Insira dados iniciais pr�vios a simula��o!");
                   gotoxy(error_posic[0] + 5, error_posic[1]+2);
                   printf("Pressione qualquer tecla...");
                   getch();//Pausa at� o pressionamento de uma tecla
                   break;

            case 2:inserirdadosiniciais(&parametros); //Na op��o controlar processos, na nova simula��o, funciona como os dados iniciais
                   menu_velha_simu(parametros);
                   sair_menu = 1;
                   break;

            case 3:salvarestados(parametros);
                   break;

            case 4:sair_menu = 1;
        }
        Beep(587.33, 50);
    }
    while(!sair_menu);
}

                void inserirdadosiniciais(PARAMETROS *parametros) //Console para inserir dados iniciais, por meio de sliders
{
    int x = 36, y[11] = {8, 10, 12, 16, 18, 20, 24, 26, 28, 33, 36}; //impress�es na tela do seletor, posi��es x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a sele��o e o seletor na tela do usu�rio

    system("CLS");   //Limpa a tela para inicializa��o do menu_simu
    textcolor(CIANO); //cor do texto
    formatprompt_estados();

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
              << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
              << "*|*                                                                         *|*\n"
              << "|*                   INSERIR DADOS INICIAIS DO PROCESSO                      *|\n"
              << "*|                  ------------------------------------                     |*\n"
              << "|*                                                                           *|\n"
              << "*|             Caldeira 1                                                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  A:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  B:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                        Registro:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|             Caldeira 2                                                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  A:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  B:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                        Registro:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|             Caldeira 3                                                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  A:                                          |*\n"
              << "|*                                                                           *|\n"
              << "|*                       Insumo  B:                                          *|\n"
              << "*|                                                                           |*\n"
              << "|*                        Registro:                                          *|\n"
              << "*|                                                                           |*\n"
              << "*|                                                                           |*\n"
              << "*|             Esteira                                                       |*\n"
              << "|*                                                                           *|\n"
              << "*|              Velocidade (0-100):                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                      Salvar estados iniciais              *|\n"
              << "*|*                                                                         *|*\n"
              << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
              << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

    imprime_estado(x+3, y, parametros, CIANO, CONTROLE);//+3 para imprimir na frente do cursor


    textcolor(AMARELOLIGHT);      //cor do cursor

    do
    {
        gotoxy(x, y[contador]);  //seleciona o cursor nas opcoes disponives do vetor
        printf("->");

        fflush(stdin);

        switch(setas())
        {
            case CIMA:if(contador != 0)
                        {
                              gotoxy(x, y[contador]);
                              printf("  "); //Apaga o cursor previo ao pressionamento da tecla
                              contador--;
                        }
                        break;

                case BAIXO:if(contador != 10)
                           {
                               gotoxy(x, y[contador]);
                               printf("  ");
                               contador++;
                           }
                           break;

            case DIREITA:
            case ESQUERDA:if(contador == 10)//caso o cursor esteja na ultima posi��o, o uso da setas esquerda ou direita � vetado
                              break;

            case ENTER:if(contador != 10)//Caso o contador seja 9, sair do programa com enter
                       {
                           gotoxy(x, y[contador]);
                           printf("  ");
                           slider_f(x+2, y[contador], parametros, &contador); //slider para definir o estado
                           break; //Retorna ao la�o se enter for pressionado em qualquer posi��o exceto a 9
                       }
            case ESC:sair = 1; //caso ESC seja apertado sai e retorna para o menu da simulacao
        }

        Beep(587.33, 50);
    }
    while(!sair);

    formatprompt();
}

                int menu_simulacao(PARAMETROS *parametros) //Menu para Sele��o da simula��o 1 (caldeiras+misturador) ou simula��o 2(esteira)
{
    int x = 18, y[2] = {13, 16}; //impress�es na tela do seletor, posi��es x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a sele��o e o seletor na tela do usu�rio
    int retornar_menu = FALSE; //Retorno ao menu da simula��o

    system("CLS");   //Limpa a tela para inicializa��o do menu_simu
    textcolor(CIANO); //cor do texto

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
              << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
              << "*|*                                                                         *|*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                   Escolher o processo a ser simulado:                     |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                   1. Caldeiras                                            *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                   2. Esteira de produtos                                  |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|*                                                                         *|*\n"
              << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
              << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";


    textcolor(AMARELOLIGHT);      //cor do cursor

    do
    {
        gotoxy(x, y[contador]);  //seleciona o cursor nas opcoes disponives do vetor
        printf(">");

        fflush(stdin);

        switch(setas())
        {
            case CIMA:if(contador != 0)
                      {
                          gotoxy(x, y[contador]);
                          printf(" "); //Apaga o cursor previo ao pressionamento da tecla
                          contador--;
                      }
                      break;

            case BAIXO:if(contador != 1)
                       {
                           gotoxy(x, y[contador]);
                           printf(" ");
                           contador++;
                       }
                       break;

            case ESC:contador = 3; //Com esc retorna para o menu anterior
            case ENTER:sair = 1;
        }

        Beep(587.33, 50);
    }
    while(!sair);


    switch (contador)
    {
        case 0:retornar_menu = caldeira(parametros); //Iguala ao valor retornado pela fun��o caldeira
               break;

        case 1:retornar_menu = esteira(parametros);
        //o Contador 3, "caso ESC", n�o precisa ser tratado aqui, pois est� preso no outro escopo!
    }

    return retornar_menu;
}

                int caldeira(PARAMETROS *parametros) //Simula��o 1, caldeiras e misturador
{
    formatprompt_processos();

    int op; //a op��o escolhida no mini menu � representada por essa vari�vel
    int sair_simu = 0, menu_inicial = FALSE; // Vari�vel de retorno ao menu da simula��o(sair da simula��o) e de retorno ao menu inicial
    int caldeira_x = 82, caldeira_y[11] = {16, 17, 18, 23, 24, 25, 30, 31, 32, 36, 39};  //Vari�veis das posi��es para impress�o dos parametros

    system("CLS");   //Limpa a tela para inicializa��o do menu_simu
    textcolor(CIANO); //cor do texto

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
              << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
              << "|*|* - | - | - | - | - | - | - | - | - | - | - | - | - | - | *|*|*                                        *|*\n"
              << "*| - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # |*            Mensagens do sistema:         *|\n"
              << "|* | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - *|     ________________________________     |*\n"
              << "*| - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # |*    |                                |    *|\n"
              << "|* | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - *|    |                                |    |*\n"
              << "*|-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|*    |________________________________|    *|\n"
              << "|*                                                             *|                                          |*\n"
              << "*|                                                             |*   Processo:         CALDEIRA             *|\n"
              << "|*                                                             *|                                          |*\n"
              << "*|                                                             |*   Estado:                                *|\n"
              << "|*                                                             *|                                          |*\n"
              << "*|                                                             |*                                          *|\n"
              << "|*                                                             *|   Caldeira 1        Vaz�o Total:         |*\n"
              << "*|                                                             |*                                          *|\n"
              << "|*                                                             *|       Insumo 1:                          |*\n"
              << "*|                                                             |*       Insumo 2:                          *|\n"
              << "|*                                                             *|       Registro:                          |*\n"
              << "*|                                                             |*                                          *|\n"
              << "|*                                                             *|                                          |*\n"
              << "*|                                                             |*   Caldeira 2                             *|\n"
              << "|*                                                             *|                                          |*\n"
              << "*|                                                             |*       Insumo 1:                          *|\n"
              << "|*                                                             *|       Insumo 2:                          |*\n"
              << "*|                                                             |*       Registro:                          *|\n"
              << "|*                                                             *|                                          |*\n"
              << "*|                                                             |*                                          *|\n"
              << "|*                                                             *|   Caldeira 3                             |*\n"
              << "*|                                                             |*                                          |*\n"
              << "|*                                                             *|       Insumo 1:                          *|\n"
              << "*|                                                             |*       Insumo 2:                          |*\n"
              << "|*                                                             *|       Registro:                          *|\n"
              << "*|                                                             |*                                          |*\n"
              << "|*                                                             *|                                          *|\n"
              << "*|                                                             |*    N�mero                                |*\n"
              << "|*           \\\\         //                                     *|    de Bolinhas:                          *|\n"
              << "*|            \\\\       //                                      |*                                          |*\n"
              << "|*             ||## ##||                                       *|                                          *|\n"
              << "*|             ||## ##||                                       |*  Caixas prontas:                         |*\n"
              << "|*             ||## ##||                                       *|                                          *|\n"
              << "*|             ||## ##||                                       |*    (10 Bolinhas -> 1 Caixa)              |*\n"
              << "|*             ||#####||                                       *|                                          *|\n"
              << "*|             ||#####||                                       |*                                          |*\n"
              << "|*             ||#####||                                       *|    Pressione qualquer tecla para o menu! *|\n"
              << "*|*            ||#####||                                       |*                                         *|*\n"
              << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
              << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";


    imprime_caldeiras();
    imprime_estado(caldeira_x, caldeira_y, parametros, CIANOLIGHT, CALDEIRA); //Imprime os estados dos parametros na caixa ao lado

    do
    {
        print_logo();
        animacao_caldeira(parametros); //a fun��o prende um loop at� o pressionamento de alguma tecla
        op = Mini_menu(); //Inicia o mini menu

        if(!parametros->misturador_explodido)
        {
            switch(op)
            {
                case 0:salva_simu(*parametros);
                       break;

                case 1:sair_simu = 1; //Assim, sai ds simula��o
                       break;

                case 2:sair_simu = 1;
                       menu_inicial = TRUE; //Retorna ao menu principal na op��o 2
            }
        }
        else
        {
            gotoxy(9, 3);
            printf("         ERRO! MISTURADOR EXPLODIDO!         ");
            gotoxy(9, 4);
            printf("         PRESSIONE ENTER             ");
            gotoxy(9, 5);
            printf("         RETORNAR AO MENU INICIAL...       ");

            do
            {
                fflush(stdin);
            }
            while(getch() != ENTER);

            sair_simu = 1;
            menu_inicial = TRUE; //Retorna ao menu principal na op��o 2
        }
    }
    while(!sair_simu); //Se retornar � TRUE, sai da simula��o


    formatprompt(); // Retorna o prompt ao tamanho default
    return menu_inicial;
}

                int esteira(PARAMETROS *parametros)//Simula��o 2, Esteira
{
    formatprompt_processos();

    int op; //a op��o escolhida no mini menu � representada por essa vari�vel
    int sair_simu = 0, menu_inicial = FALSE; // Vari�vel de retorno ao menu da simula��o(sair da simula��p) e de retorno ao menu inicial
    int esteira_x = 87, esteira_y[3] = {15, 19, 22}; //Vari�veis das posi��es para impress�o dos parametros

    system("CLS");   //Limpa a tela para inicializa��o do menu_simu
    textcolor(CIANO); //cor do texto

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
              << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
              << "|*|* - | - | - | - | - | - | - | - | - | - | - | - | - | - | *|*|*                                        *|*\n"
              << "*| - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # |*            Mensagens do sistema:         *|\n"
              << "|* | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - *|     ________________________________     |*\n"
              << "*| - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # |*    |                                |    *|\n"
              << "|* | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - *|    |                                |    |*\n"
              << "*|-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|*    |________________________________|    *|\n"
              << "|*    ||#####||                                                *|                                          |*\n"
              << "*|    ||#####||                                                |*   Processo:         ESTEIRA              *|\n"
              << "|*    ||#####||                                                *|                                          |*\n"
              << "*|    ||#####||                                                |*   Estado:                                *|\n"
              << "|*    ||#####||                                                *|                                          |*\n"
              << "*|    ||#####||                                                |*                                          *|\n"
              << "|*    ||## ##||                                                *|   Velocidade                             |*\n"
              << "*|    ||## ##||                                                |*   da Esteira:                            *|\n"
              << "|*    ||## ##||                                                *|                                          |*\n"
              << "*|    ||## ##||                                                |*                                          *|\n"
              << "|*    ||## ##||                                                *|   N�mero                                 |*\n"
              << "*|    ||## ##||                                                |*   de Bolinhas:                           *|\n"
              << "|*    ||## ##||                                                *|                                          |*\n"
              << "*|    ||## ##||                                                |*                                          *|\n"
              << "|*    ||## ##||                                                *|   Caixas prontas:                        |*\n"
              << "*|    ||## ##||                                                |*                                          *|\n"
              << "|*   //       \\\\                                               *|   (10 Bolinhas -> 1 Caixa)               |*\n"
              << "*|  //         \\\\                                              |*                                          *|\n"
              << "|*                                                             *|                                          |*\n"
              << "*|                                                             |*                                          *|\n"
              << "|*                                                             *|                                          |*\n"
              << "*|                                                             |*                                          |*\n"
              << "|*                                                             *|                                          *|\n"
              << "*|                                                             |*                                          |*\n"
              << "|*                                                             *|                                          *|\n"
              << "*|                                                             |*                                          |*\n"
              << "|*                                                             *|                                          *|\n"
              << "*|                                                             |*                                          |*\n"
              << "|*                                                             *|                                          *|\n"
              << "*|                                                             |*                                          |*\n"
              << "|*                                                             *|                                          *|\n"
              << "*|                                                             |*                                          |*\n"
              << "|*                                                             *|                                          *|\n"
              << "*|                                                             |*                                          |*\n"
              << "|*                                               \\\\       //   *|                                          *|\n"
              << "*|                                                ||## ##||    |*                                          |*\n"
              << "|*                                                ||## ##||    *|   Pressione qualquer tecla para o menu!  *|\n"
              << "*|*                                               ||## ##||    |*                                         *|*\n"
              << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
              << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";


    imprime_esteira();
    imprime_estado(esteira_x, esteira_y, parametros, CIANOLIGHT, ESTEIRA); //Imprime os estados dos parametros na caixa ao lado

    do
    {
        print_logo();
        animacao_esteira(parametros);
        op = Mini_menu(); //Inicia o mini menu

        if(!parametros->esteira_quebrada)
        {
            switch(op)
            {
                case 0:salva_simu(*parametros);
                       break;

                case 1:sair_simu = 1; //Assim, sai ds simula��o
                       break;

                case 2:sair_simu = 1;
                       menu_inicial = TRUE; //Retorna ao menu principal na op��o 2
            }
        }

        else
        {
            gotoxy(9, 3);
            printf("         ERRO! ESTEIRA QUEBRADA         ");
            gotoxy(9, 4);
            printf("         PRESSIONE ENTER             ");
            gotoxy(9, 5);
            printf("         RETORNAR AO MENU INICIAL...       ");

            do
            {
                fflush(stdin);
            }
            while(getch() != ENTER);

            sair_simu = 1;
            menu_inicial = TRUE; //Retorna ao menu principal na op��o 2
        }
    }
    while(!sair_simu); //Se retornar � TRUE, sai da simula��o

    formatprompt(); // Retorna o prompt ao tamanho default
    return menu_inicial;
}

                void controlarprocessos(PARAMETROS *parametros)//Inserir dados atualizados para as simula��es
{
    int x = 36, y[11] = {8, 10, 12, 16, 18, 20, 24, 26, 28, 33, 36}; //impress�es na tela do seletor, posi��es x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a sele��o e o seletor na tela do usu�rio

    system("CLS");   //Limpa a tela para inicializa��o do menu_simu
    textcolor(CIANO); //cor do texto
    formatprompt_estados();

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
              << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
              << "*|*                                                                         *|*\n"
              << "|*                 INSERIR DADOS ATUALIZADOS DOS PROCESSOS                   *|\n"
              << "*|                -----------------------------------------                  |*\n"
              << "|*                                                                           *|\n"
              << "*|             Caldeira 1                                                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  A:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  B:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                        Registro:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|             Caldeira 2                                                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  A:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  B:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                        Registro:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|             Caldeira 3                                                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                       Insumo  A:                                          |*\n"
              << "|*                                                                           *|\n"
              << "|*                       Insumo  B:                                          *|\n"
              << "*|                                                                           |*\n"
              << "|*                        Registro:                                          *|\n"
              << "*|                                                                           |*\n"
              << "*|                                                                           |*\n"
              << "*|             Esteira                                                       |*\n"
              << "|*                                                                           *|\n"
              << "*|              Velocidade (0-100):                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                      Salvar estados atualizados           *|\n"
              << "*|*                                                                         *|*\n"
              << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
              << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

    imprime_estado(x+3, y, parametros, CIANO, CONTROLE);//+3 para imprimir na frente do cursor


    textcolor(AMARELOLIGHT);      //cor do cursor

    do
    {
        gotoxy(x, y[contador]);  //seleciona o cursor nas opcoes disponives do vetor
        printf("->");

        fflush(stdin);

        switch(setas())
        {
            case CIMA:if(contador != 0)
                      {
                          gotoxy(x, y[contador]);
                          printf("  "); //Apaga o cursor previo ao pressionamento da tecla
                          contador--;
                      }
                      break;

            case BAIXO:if(contador != 10)
                       {
                           gotoxy(x, y[contador]);
                           printf("  ");
                           contador++;
                       }
                       break;

            case DIREITA:
            case ESQUERDA:if(contador == 10)//caso o cursor esteja na ultima posi��o, o uso da setas esquerda ou direita � vetado
                              break;

            case ENTER:if(contador != 10)//Caso o contador seja 9, sair do programa com enter
                       {
                           gotoxy(x, y[contador]);
                           printf("  ");
                           slider_f(x+2, y[contador], parametros, &contador); //slider para definir o estado
                           break; //Retorna ao la�o se enter for pressionado em qualquer posi��o exceto a 9
                       }
            case ESC:sair = 1; //caso ESC seja apertado sai e retorna para o menu da simulacao
        }

        Beep(587.33, 50);
    }
    while(!sair);

    parametros -> critico_esteira = 0;//Zera as vari�veis dos estados cr�ticos caso o usu�rio acesse o menu de controlar processos
    parametros -> critico_caldeira = 0;

    formatprompt();
}

                void menu_velha_simu(PARAMETROS parametros)//Menu para uma simula��o carregada de um arquivo
{
    int x = 18, y[5] = {11, 14, 17, 20, 23}; //impress�es na tela do seletor, posi��es x e y definidas pelos arrays
    int contador = 0, sair, sair_menu = 0; //contador auxiliar para a sele��o e o seletor na tela do usu�rio

    do
    {
        sair = 0;
        fflush(stdin);
        system("CLS");   //Limpa a tela para inicializa��o do menu_simu
        textcolor(CIANO); //cor do texto



        std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
                  << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
                  << "*|*                                                                         *|*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                   1. Imprimir valores dos par�metros dos processos        *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                   2. Visualizar Simula��o / Reiniciar Simula��o           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                   3. Controlar Processos                                  *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                   4. Salvar estados dos processos                         |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                   5. Voltar para o menu principal                         *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|*                                                                         *|*\n"
                  << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
                  << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";


        textcolor(AMARELOLIGHT);      //cor do cursor

        do
        {
            gotoxy(x, y[contador]);  //seleciona o cursor nas opcoes disponives do vetor
            printf(">");

            fflush(stdin);

            switch(setas())
            {
                case CIMA:if(contador != 0)
                          {
                              gotoxy(x, y[contador]);
                              printf(" "); //Apaga o cursor previo ao pressionamento da tecla
                              contador--;
                          }
                          break;

                case BAIXO:if(contador != 4)
                           {
                               gotoxy(x, y[contador]);
                               printf(" ");
                               contador++;
                           }
                           break;

                case ESC:contador = 4; //Retorna ao menu principal
                case ENTER:sair = 1;
            }
            Beep(587.33, 50);
        }
        while(!sair);


        switch (contador)
        {
        case 0:imprime_parametros(&parametros);
               break;

        case 1:if(menu_simulacao(&parametros)) //Se a fun��o retorna TRUE, retorna ao menu principal
                   sair_menu = 1;
               break;

        case 2:controlarprocessos(&parametros);
               break;

        case 3:salvarestados(parametros);
               break;

        case 4:sair_menu = 1;
        }

    }
    while(!sair_menu);
}

                void imprime_parametros(PARAMETROS *parametros)//Imprime os atuais par�metros para o usu�rio realizar uma leitura
{
    int x = 36, y[11] = {8, 10, 12, 16, 18, 20, 24, 26, 28, 33, 36}; //impress�es na tela do seletor, posi��es x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a sele��o e o seletor na tela do usu�rio

    system("CLS");   //Limpa a tela para inicializa��o do menu_simu
    textcolor(CIANO); //cor do texto
    formatprompt_estados();

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
              << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
              << "*|*                                                                         *|*\n"
              << "|*                 PAR�METROS ATUAIS DOS PROCESSOS                           *|\n"
              << "*|                ---------------------------------                          |*\n"
              << "|*                                                                           *|\n"
              << "*|             Caldeira 1                                                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                  Insumo 1 (A/B):                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                  Insumo 2 (A/B):                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                        Registro:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|             Caldeira 2                                                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                  Insumo 1 (A/B):                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                  Insumo 2 (A/B):                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                        Registro:                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|             Caldeira 3                                                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                  Insumo 1 (A/B):                                          |*\n"
              << "|*                                                                           *|\n"
              << "|*                  Insumo 2 (A/B):                                          *|\n"
              << "*|                                                                           |*\n"
              << "|*                        Registro:                                          *|\n"
              << "*|                                                                           |*\n"
              << "*|                                                                           |*\n"
              << "*|             Esteira                                                       |*\n"
              << "|*                                                                           *|\n"
              << "*|              Velocidade (0-100):                                          |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                      Retornar ao menu anterior            *|\n"
              << "*|*                                                                         *|*\n"
              << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
              << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

    imprime_estado(x+2, y, parametros, BRANCOLIGHT, CONTROLE);
    textcolor(AMARELOLIGHT);      //cor do cursor

    do
    {
        gotoxy(x, y[contador]);  //seleciona o cursor nas opcoes disponives do vetor
        printf(">");

        fflush(stdin);

        switch(setas())
        {
            case CIMA:if(contador != 0)
                          {
                              gotoxy(x, y[contador]);
                              printf(" "); //Apaga o cursor previo ao pressionamento da tecla
                              contador--;
                          }
                          break;

                case BAIXO:if(contador != 10)
                           {
                               gotoxy(x, y[contador]);
                               printf(" ");
                               contador++;
                           }
                           break;

            case ESC:contador = 10; //Para retornar ao meu com o caso ENTER
            case ENTER:if(contador == 10)
                           sair = 1;
                       else
                       {
                           gotoxy(x, y[contador]);
                           printf("  ");
                           contador = 10;
                       }
        }
        Beep(587.33, 50);
    }
    while(!sair);

    formatprompt();
}

                void animacao_caldeira(PARAMETROS *parametros)//Fun��o respons�vel por todas anima��es da caldeira e do misturador na simula��o 1
{
    int vol[3], vol_total=0; //Vari�veis para os volumes da anima��o
    int fim_ciclo[3];
    int fator_estado = NORMAL;

    int k[3], l, i, j = 0; //Contadores auxiliares
    float aux = 0, Crit_note = 311.13;;

    int x[3], y[3]; //Para cada caldeira
    int misturador_x = 19, misturador_y; //Posi��es de impress�o bolinhas
    int num_x = 84, bolinhas_y = 36, caixas_y = 39; //Posi��es de impres�o valores

    avalia_volume(parametros, vol, &vol_total);
    calcula_posic(parametros -> caldeira_posic.fim_ciclo, parametros -> caldeira_posic.x, parametros -> caldeira_posic.y, parametros -> caldeira_posic.k, parametros -> caldeira_posic.l, parametros -> caldeira_posic.misturador_y, fim_ciclo, x, y, k, &l, &misturador_y);

    if(parametros -> critico_caldeira == 10)
        {
            //explode o misturador KABOOM!
            Beep(Crit_note, 1200);
            explosao();
            parametros->misturador_explodido = TRUE;
        }

    else//Misturador ainda funcional
    {

        if(vol_total <= 3) //Modo Misturador desligado
        {
            textcolor(CIANOLIGHT);
            gotoxy(17, 33);
            for(i = 0; i < 5; i++) //Imprime a sa�da do misturador, desligada!
            {
                if(i%2)
                    printf("x");
                else
                    printf("+");
            }

            getch();//Pausa o processamento at� o pressionamento de uma tecla
        }

        else
        {
            if(vol_total >= 10) //Modo Volume resultante 10 ou mais, Estado critico
            {
                fator_estado = CRITICO; //Duplica a velocidade para 2x;
            }

            do
            {
                //Ciclo de impress�o das bolinhas nas caldeiras;
                textcolor(AMARELOLIGHT);
                if(fim_ciclo[0] != TRUE || fim_ciclo[1] != TRUE || fim_ciclo[2] != TRUE)
                {
                    aux += fator_estado * 0.75; //Compensa o delay do misturador
                    if(floor(aux))
                    {
                        for(i = 0; i < 3; i++)
                        {
                            if(k[i] < vol[i])
                            {
                                gotoxy(x[i], y[i]);
                                printf(" ");
                                y[i]++;
                                gotoxy(x[i], y[i]);
                                printf("O");

                                if(y[i] > 20)
                                {
                                    gotoxy(x[i], y[i]);
                                    printf(" ");
                                    y[i] = 15;
                                    k[i]++;
                                    Beep(880, 50);
                                }
                            }
                            else if(fim_ciclo[i] != TRUE)
                            {
                                fim_ciclo[i] = TRUE; //Termina o ciclo de uma caldeira
                            }
                        }
                        aux = 0;//� zerado aux toda vez que vale 1 ou mais
                    }
                }
                //Fim do Ciclo Bolinha saindo das caldeiras

                //Ciclo bolinhas saindo do misturador
                else
                {
                    aux += fator_estado * 0.75; //Compensa o delay do misturador
                    if(floor(aux))
                    {
                        if(l < vol_total)
                        {
                            textcolor(VERDELIGHT);
                            gotoxy(misturador_x, misturador_y);
                            printf(" ");
                            misturador_y++;
                            gotoxy(misturador_x, misturador_y);
                            printf("O");

                            if(misturador_y > 40)
                            {
                                gotoxy(misturador_x, misturador_y);
                                printf(" ");

                                textcolor(AMARELOLIGHT);
                                parametros -> num_bolinhas++;
                                if(parametros -> num_bolinhas == 10)
                                {
                                    parametros -> num_bolinhas = 0;

                                    parametros -> num_caixas++;
                                    gotoxy(num_x, caixas_y);
                                    printf("%3d", parametros -> num_caixas);
                                    Beep(587.33, 100);
                                }
                                else
                                    Beep(440, 100);

                                if(vol_total > 10)
                                {
                                    parametros -> critico_caldeira++;
                                    Beep(Crit_note, 100);
                                    Beep(Crit_note, 100);
                                    Crit_note += 25;
                                }

                                gotoxy(num_x, bolinhas_y);
                                printf("%3d", parametros -> num_bolinhas);
                                misturador_y = 34;
                                l++;
                            }
                        }

                        else
                        {
                            for(i = 0; i < 3; i++)
                            {
                                fim_ciclo[i] = FALSE; //Retorna ao ciclo das bolinhas
                                k[i] = 0; //Zera a vari�vel de contagem dos volumes
                            }
                            l = 0; //Zera a vari�vel de contagem dos volumes totais
                        }

                        aux = 0;//� zerado aux toda vez que vale 1 ou mais
                    }
                }
                //Fim do ciclo bolinhas saindo do misturador

                //Anima��o do misturador
                textcolor(CIANOLIGHT);
                gotoxy(17, 33);
                for(i = j; i < 5+j; i++)
                {
                    if(i%2)
                        printf("x");
                    else
                        printf("+");
                }
                delay(50);
                if(j == 0)
                    j = 1;
                else
                    j = 0;
                //Fim da anima��o do misturador

            }
            while(!kbhit() && parametros -> critico_caldeira < 10);
            flushkbhit();

            //Salva a posi��o das bolinhas e os ciclos para o retorno da anima��o
            calcula_posic(fim_ciclo, x, y, k, l, misturador_y, parametros -> caldeira_posic.fim_ciclo, parametros -> caldeira_posic.x, parametros -> caldeira_posic.y, parametros -> caldeira_posic.k, &(parametros -> caldeira_posic.l), &(parametros -> caldeira_posic.misturador_y));
        }
    }
}

                void animacao_esteira(PARAMETROS *parametros)//Fun��o respons�vel por todas anima��es da esteira na simula��o 2
{
    int esteira_x = 9, esteira_y = 35;
    int x = parametros -> bola_posic_x, y = parametros -> bola_posic_y;
    int i, j = 0, fator_estado = NORMAL, quebrar = FALSE; //Vari�veis auxiliares no calculo das posi��es na anima��o e fator do estados para duplica��o em caso do estado critico, alem do critico que quebra a esteira se chega a 10
    int num_x = 89, bolinhas_y = 19, caixas_y = 22;
    float aux = 0, Crit_note = 311.13;
    int esteira_v = parametros -> vel_esteira;
    int esteira_spd = (75 - 0.65*(esteira_v)); //Calculo do delay da esteira

    if(esteira_v <= 10) //Modo 10 ou menos, esteira em manuten��o
    {
        textcolor(BRANCOLIGHT);
        textbackground(VERMELHO);
        gotoxy(70, 5);
        printf("Esteira em manuten��o!");
        gotoxy(86, 11);
        printf("MANUTEN��O");
        textbackground(0); //fun��es simula��o

        x = 10; //Necess�rio zerar a posi��o do x no estado manuten��o

        do
        {

            textcolor(AMARELOLIGHT);
            aux += fator_estado*(0.01 * esteira_spd); //Compensa o delay da velocidade da esteira
            if(floor(aux))
            {
                gotoxy(x-2, y);
                printf(" ");
                y++;
                gotoxy(x-2, y);
                printf("O");
                aux = 0;

                delay(75);

                if(y > 44)
                {
                    gotoxy(x-2, y);
                    printf(" ");
                    y = 14;
                    Beep(440, 75);
                    Beep(369.99, 100);
                }
            }
        }
        while(!kbhit());

        gotoxy(x-2, y);
        printf(" ");
        y = 14;
    }

    else
    {
        if(esteira_v >= 81) //Modo 81 ou mais, Estado critico
        {
            textcolor(BRANCOLIGHT);
            textbackground(VERMELHO);
            gotoxy(70, 5);
            printf("             CUIDADO!           ");
            gotoxy(70, 6);
            printf("       ESTEIRA FUNCIONANDO      ");
            gotoxy(70, 7);
            printf("        EM ESTADO CR�TICO!      ");
            gotoxy(81, 11);
            printf("     CR�TICO     ");
            textbackground(PRETO);  //Zera o background de volta ao padr�o

            fator_estado = CRITICO; //Duplica a velocidade para 2x;

            if(esteira_v > 90) //Com uma  velocidade acima de 90 ela quebra ap�s 10 bolinhas
                quebrar = TRUE;
        }
        else
        {
            textcolor(AZULLIGHT);
            textbackground(VERDE);
            gotoxy(86, 11);
            printf("NORMAL");
            textbackground(PRETO); //Zera o background de volta ao padr�o
        }

        do
        {
            //Anima��o bolinhas em y
            if(y < 34 && x != 49)
            {
                textcolor(AMARELOLIGHT);
                aux += fator_estado*(0.01 * esteira_spd); //Compensa o delay da velocidade da esteira
                if(floor(aux))
                {
                    gotoxy(x, y);
                    printf(" ");
                    y+= 1 * fator_estado;
                    gotoxy(x, y);
                    printf("O");
                    aux = 0;

                    if(y > 34)
                        y = 34;
                }
            }
            //Fim da anima��o das bolinhas em y
            else if(x < 49)
            {
                textcolor(AMARELOLIGHT);
                gotoxy(x, y);
                printf(" ");
                x++;
                gotoxy(x, y);
                printf("O");
            }

            else
            {
                textcolor(AMARELOLIGHT);
                gotoxy(x, y);
                printf(" ");
                x++;
                y+=2;
                gotoxy(x, y);
                printf("O");

                if(y == 44)
                {
                    gotoxy(x, y);
                    printf(" ");
                    x = 10;
                    y = 14;

                    parametros -> num_bolinhas++;

                    if(parametros -> num_bolinhas == 10)
                    {
                        parametros -> num_bolinhas = 0;

                        parametros -> num_caixas++;

                        gotoxy(num_x, caixas_y);
                        printf(" ");
                        gotoxy(num_x, caixas_y);
                        printf("%3d", parametros -> num_caixas);
                        Beep(587.33, 100);
                    }
                    else
                        Beep(440, 100);

                    if(fator_estado == CRITICO)
                    {

                        Beep(Crit_note, 100);
                        Beep(Crit_note, 100);

                        if(quebrar)//Se ela est� em uma velocidade alta o suficiente
                        {
                            Crit_note += 25;
                            parametros->critico_esteira++;
                        }
                    }

                    gotoxy(num_x, bolinhas_y);
                    printf("%3d", parametros -> num_bolinhas);
                }
            }

            //Anima��o da esteira
            textcolor(CIANOLIGHT);
            gotoxy(esteira_x+j, esteira_y);
            for(i = j; i < 40; i++)
            {
                if((i-j)%2)
                    printf("_");
                else
                    printf(" ");
            }
            delay(esteira_spd);
            if(j == 0)
                j = 1;
            else
                j = 0;
            //Fim da anima��o da esteira

        }
        while(!kbhit() && parametros -> critico_esteira != 10);
    }
    flushkbhit();

    if(parametros -> critico_esteira == 10)
    {
        Beep(Crit_note, 1200);
        quebra(); //Quebra a esteira
        parametros->esteira_quebrada = TRUE;
    }

    parametros -> bola_posic_x = x; //Salva a posi��o da bolinha para o retorno da simula��o
    parametros -> bola_posic_y = y;
}
