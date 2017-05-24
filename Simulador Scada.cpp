/* Trabalho final Algoritmos e Programação
Simulador industrial, com possibilidade de carregar simulações salvas
MENU, pelas setas direcionais, em C++
Simulação em C

Eduardo Farinati Leite
Lucas Bortolanza Grazziotim */

#include "Grazziotim.h" //Melhor biblioteca já criada

/*  Referência das cores
0 = Black -----------  8 = Gray
1 = Blue ------------  9 = Light Blue
2 = Green ----------- 10 = Light Green
3 = Aqua ------------ 11 = Light Aqua
4 = Red ------------- 12 = Light Red
5 = Purple ---------- 13 = Light Purple
6 = Yellow ---------- 14 = Light Yellow
7 = White ----------- 15 = Bright White
*/

//Protótipos das funções das simulações utilizadas no programa
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

int main(void)//Main da função determina as opções de fechar o programa, carregar uma simulação ou Criar uma nova simulação
{
    int op; //Seleciona a opção a partir do menu principal, contador para o while
    PARAMETROS parametros;

    // Formata o prompt para o tamanho e linguagem desejados
    formatprompt();
    
    // Insere o Titulo do Programa na janela
    system("title Simulador Scada");

    do //mantem o menu em um laço de iteração para sempre poder retornar ao menu por opção do usuario
    {
        op = menu_principal();

        if(op == 0)
        {
            zera_estados(&parametros);//zera os dados para a nova simulação
            menu_nova_simu(parametros); //Nova simulação
        }

        if(op == 1)
        {
            if(carrega_parametros(&parametros) != ESC)//carrega os parâmetros de um arquivo binário, caso a função retorne ESC, o usuário saiu sem carregar o arquivo
                menu_velha_simu(parametros); //Menu com parâmetros salvos em um arquivo binário
        }

    }
    while(op != 2); //caso o valor retornado pelo menu seja 2, o programa é terminado (opção sair)

    system("CLS"); //Limpa a tela

    return 0;
}

int menu_principal()//Aqui é impresso o seletor para opção no main, um retorno tipado
{
    int x =  23, y[3] = {25, 28, 31}; //impressões na tela do seletor, posições x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a seleção e o seletor na tela do usuário

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
                << "*|           .|'''|  .|'''',      /.\\      '||'''|.      /.\\                 |*\n" //Barras duplicadas para poder imprimir o caractér '\'
                << "|*           ||      ||          // \\\\      ||   ||     // \\\\                *|\n"
                << "*|           `|'''|, ||         //...\\\\     ||   ||    //...\\\\               |*\n"
                << "|*            .   || ||        //     \\\\    ||   ||   //     \\\\              *|\n"
                << "*|            |...|' `|....' .//       \\\\. .||...|' .//       \\\\.            |*\n"
                << "|*                                                                           *|\n"
                << "*|                                                                           |*\n"
                << "|*                                                                           *|\n"
                << "*|                                                                           |*\n"
                << "|*                        Selecione uma opção:                               *|\n"
                << "*|                       ----------------------                              |*\n"
                << "|*                                                                           *|\n"
                << "*|                                                                           |*\n"
                << "|*                        1. Nova simulação                                  *|\n"
                << "*|                                                                           |*\n"
                << "|*                                                                           *|\n"
                << "*|                        2. Carregar simulação salva                        |*\n"
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

            case ESC:if(contador != 2)//break dentro do if para fechar o programa caso esc seja apertado na ultima opção
                     {
                         gotoxy(x, y[contador]);// Apaga o slider pré-pressionamento da tecla ESC
                         printf(" ");
                         contador = 2;
                         break;
                     }

            case ENTER:sair = 1;
        }

        Beep(587.33, 50);//Padrão da simulação, Som do pressionamento de uma tecla
    }
    while(!sair);


    return contador; //retorna o contador para o main, assim levando a opção selecionada,
}

                void menu_nova_simu(PARAMETROS parametros) //Menu de nova simulação, Parâmetros Zerados
{

    int x = 18, y[5] = {11, 14, 17, 20, 23}; //impressões na tela do seletor, posições x e y definidas pelos arrays
    int error_posic[2] = {10, 31}; //Posição x e y da mensagem de erro
    int contador = 0, sair, sair_menu = 0; //contador auxiliar para a seleção e o seletor na tela do usuário

    do
    {
        sair = 0;
        fflush(stdin);
        system("CLS");   //Limpa a tela para inicialização do menu_nova_simu
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
                  << "*|                   2. Iniciar Simulação / Visualizar Simulação             |*\n"
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
            Beep(587.33, 50);//Padrão da simulação, Som do pressionamento de uma tecla
        }
        while(!sair);

        switch(contador)
        {
            case 0:inserirdadosiniciais(&parametros);
                   menu_velha_simu(parametros); //Após inserir os dados iniciais, entramos no menu como uma simulação carregada
                   sair_menu = 1;
                   break;

            case 1:gotoxy(error_posic[0], error_posic[1]);
                   textcolor(VERMELHOLIGHT);
                   printf("Insira dados iniciais prévios a simulação!");
                   gotoxy(error_posic[0] + 5, error_posic[1]+2);
                   printf("Pressione qualquer tecla...");
                   getch();//Pausa até o pressionamento de uma tecla
                   break;

            case 2:inserirdadosiniciais(&parametros); //Na opção controlar processos, na nova simulação, funciona como os dados iniciais
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
    int x = 36, y[11] = {8, 10, 12, 16, 18, 20, 24, 26, 28, 33, 36}; //impressões na tela do seletor, posições x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a seleção e o seletor na tela do usuário

    system("CLS");   //Limpa a tela para inicialização do menu_simu
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
            case ESQUERDA:if(contador == 10)//caso o cursor esteja na ultima posição, o uso da setas esquerda ou direita é vetado
                              break;

            case ENTER:if(contador != 10)//Caso o contador seja 9, sair do programa com enter
                       {
                           gotoxy(x, y[contador]);
                           printf("  ");
                           slider_f(x+2, y[contador], parametros, &contador); //slider para definir o estado
                           break; //Retorna ao laço se enter for pressionado em qualquer posição exceto a 9
                       }
            case ESC:sair = 1; //caso ESC seja apertado sai e retorna para o menu da simulacao
        }

        Beep(587.33, 50);
    }
    while(!sair);

    formatprompt();
}

                int menu_simulacao(PARAMETROS *parametros) //Menu para Seleção da simulação 1 (caldeiras+misturador) ou simulação 2(esteira)
{
    int x = 18, y[2] = {13, 16}; //impressões na tela do seletor, posições x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a seleção e o seletor na tela do usuário
    int retornar_menu = FALSE; //Retorno ao menu da simulação

    system("CLS");   //Limpa a tela para inicialização do menu_simu
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
        case 0:retornar_menu = caldeira(parametros); //Iguala ao valor retornado pela função caldeira
               break;

        case 1:retornar_menu = esteira(parametros);
        //o Contador 3, "caso ESC", não precisa ser tratado aqui, pois está preso no outro escopo!
    }

    return retornar_menu;
}

                int caldeira(PARAMETROS *parametros) //Simulação 1, caldeiras e misturador
{
    formatprompt_processos();

    int op; //a opção escolhida no mini menu é representada por essa variável
    int sair_simu = 0, menu_inicial = FALSE; // Variável de retorno ao menu da simulação(sair da simulação) e de retorno ao menu inicial
    int caldeira_x = 82, caldeira_y[11] = {16, 17, 18, 23, 24, 25, 30, 31, 32, 36, 39};  //Variáveis das posições para impressão dos parametros

    system("CLS");   //Limpa a tela para inicialização do menu_simu
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
              << "|*                                                             *|   Caldeira 1        Vazão Total:         |*\n"
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
              << "*|                                                             |*    Número                                |*\n"
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
        animacao_caldeira(parametros); //a função prende um loop até o pressionamento de alguma tecla
        op = Mini_menu(); //Inicia o mini menu

        if(!parametros->misturador_explodido)
        {
            switch(op)
            {
                case 0:salva_simu(*parametros);
                       break;

                case 1:sair_simu = 1; //Assim, sai ds simulação
                       break;

                case 2:sair_simu = 1;
                       menu_inicial = TRUE; //Retorna ao menu principal na opção 2
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
            menu_inicial = TRUE; //Retorna ao menu principal na opção 2
        }
    }
    while(!sair_simu); //Se retornar é TRUE, sai da simulação


    formatprompt(); // Retorna o prompt ao tamanho default
    return menu_inicial;
}

                int esteira(PARAMETROS *parametros)//Simulação 2, Esteira
{
    formatprompt_processos();

    int op; //a opção escolhida no mini menu é representada por essa variável
    int sair_simu = 0, menu_inicial = FALSE; // Variável de retorno ao menu da simulação(sair da simulaçãp) e de retorno ao menu inicial
    int esteira_x = 87, esteira_y[3] = {15, 19, 22}; //Variáveis das posições para impressão dos parametros

    system("CLS");   //Limpa a tela para inicialização do menu_simu
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
              << "|*    ||## ##||                                                *|   Número                                 |*\n"
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

                case 1:sair_simu = 1; //Assim, sai ds simulação
                       break;

                case 2:sair_simu = 1;
                       menu_inicial = TRUE; //Retorna ao menu principal na opção 2
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
            menu_inicial = TRUE; //Retorna ao menu principal na opção 2
        }
    }
    while(!sair_simu); //Se retornar é TRUE, sai da simulação

    formatprompt(); // Retorna o prompt ao tamanho default
    return menu_inicial;
}

                void controlarprocessos(PARAMETROS *parametros)//Inserir dados atualizados para as simulações
{
    int x = 36, y[11] = {8, 10, 12, 16, 18, 20, 24, 26, 28, 33, 36}; //impressões na tela do seletor, posições x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a seleção e o seletor na tela do usuário

    system("CLS");   //Limpa a tela para inicialização do menu_simu
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
            case ESQUERDA:if(contador == 10)//caso o cursor esteja na ultima posição, o uso da setas esquerda ou direita é vetado
                              break;

            case ENTER:if(contador != 10)//Caso o contador seja 9, sair do programa com enter
                       {
                           gotoxy(x, y[contador]);
                           printf("  ");
                           slider_f(x+2, y[contador], parametros, &contador); //slider para definir o estado
                           break; //Retorna ao laço se enter for pressionado em qualquer posição exceto a 9
                       }
            case ESC:sair = 1; //caso ESC seja apertado sai e retorna para o menu da simulacao
        }

        Beep(587.33, 50);
    }
    while(!sair);

    parametros -> critico_esteira = 0;//Zera as variáveis dos estados críticos caso o usuário acesse o menu de controlar processos
    parametros -> critico_caldeira = 0;

    formatprompt();
}

                void menu_velha_simu(PARAMETROS parametros)//Menu para uma simulação carregada de um arquivo
{
    int x = 18, y[5] = {11, 14, 17, 20, 23}; //impressões na tela do seletor, posições x e y definidas pelos arrays
    int contador = 0, sair, sair_menu = 0; //contador auxiliar para a seleção e o seletor na tela do usuário

    do
    {
        sair = 0;
        fflush(stdin);
        system("CLS");   //Limpa a tela para inicialização do menu_simu
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
                  << "|*                   1. Imprimir valores dos parâmetros dos processos        *|\n"
                  << "*|                                                                           |*\n"
                  << "|*                                                                           *|\n"
                  << "*|                   2. Visualizar Simulação / Reiniciar Simulação           |*\n"
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

        case 1:if(menu_simulacao(&parametros)) //Se a função retorna TRUE, retorna ao menu principal
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

                void imprime_parametros(PARAMETROS *parametros)//Imprime os atuais parâmetros para o usuário realizar uma leitura
{
    int x = 36, y[11] = {8, 10, 12, 16, 18, 20, 24, 26, 28, 33, 36}; //impressões na tela do seletor, posições x e y definidas pelos arrays
    int contador = 0, sair = 0; //contador auxiliar para a seleção e o seletor na tela do usuário

    system("CLS");   //Limpa a tela para inicialização do menu_simu
    textcolor(CIANO); //cor do texto
    formatprompt_estados();

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
              << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
              << "*|*                                                                         *|*\n"
              << "|*                 PARÂMETROS ATUAIS DOS PROCESSOS                           *|\n"
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

                void animacao_caldeira(PARAMETROS *parametros)//Função responsável por todas animações da caldeira e do misturador na simulação 1
{
    int vol[3], vol_total=0; //Variáveis para os volumes da animação
    int fim_ciclo[3];
    int fator_estado = NORMAL;

    int k[3], l, i, j = 0; //Contadores auxiliares
    float aux = 0, Crit_note = 311.13;;

    int x[3], y[3]; //Para cada caldeira
    int misturador_x = 19, misturador_y; //Posições de impressão bolinhas
    int num_x = 84, bolinhas_y = 36, caixas_y = 39; //Posições de impresão valores

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
            for(i = 0; i < 5; i++) //Imprime a saída do misturador, desligada!
            {
                if(i%2)
                    printf("x");
                else
                    printf("+");
            }

            getch();//Pausa o processamento até o pressionamento de uma tecla
        }

        else
        {
            if(vol_total >= 10) //Modo Volume resultante 10 ou mais, Estado critico
            {
                fator_estado = CRITICO; //Duplica a velocidade para 2x;
            }

            do
            {
                //Ciclo de impressão das bolinhas nas caldeiras;
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
                        aux = 0;//É zerado aux toda vez que vale 1 ou mais
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
                                k[i] = 0; //Zera a variável de contagem dos volumes
                            }
                            l = 0; //Zera a variável de contagem dos volumes totais
                        }

                        aux = 0;//É zerado aux toda vez que vale 1 ou mais
                    }
                }
                //Fim do ciclo bolinhas saindo do misturador

                //Animação do misturador
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
                //Fim da animação do misturador

            }
            while(!kbhit() && parametros -> critico_caldeira < 10);
            flushkbhit();

            //Salva a posição das bolinhas e os ciclos para o retorno da animação
            calcula_posic(fim_ciclo, x, y, k, l, misturador_y, parametros -> caldeira_posic.fim_ciclo, parametros -> caldeira_posic.x, parametros -> caldeira_posic.y, parametros -> caldeira_posic.k, &(parametros -> caldeira_posic.l), &(parametros -> caldeira_posic.misturador_y));
        }
    }
}

                void animacao_esteira(PARAMETROS *parametros)//Função responsável por todas animações da esteira na simulação 2
{
    int esteira_x = 9, esteira_y = 35;
    int x = parametros -> bola_posic_x, y = parametros -> bola_posic_y;
    int i, j = 0, fator_estado = NORMAL, quebrar = FALSE; //Variáveis auxiliares no calculo das posições na animação e fator do estados para duplicação em caso do estado critico, alem do critico que quebra a esteira se chega a 10
    int num_x = 89, bolinhas_y = 19, caixas_y = 22;
    float aux = 0, Crit_note = 311.13;
    int esteira_v = parametros -> vel_esteira;
    int esteira_spd = (75 - 0.65*(esteira_v)); //Calculo do delay da esteira

    if(esteira_v <= 10) //Modo 10 ou menos, esteira em manutenção
    {
        textcolor(BRANCOLIGHT);
        textbackground(VERMELHO);
        gotoxy(70, 5);
        printf("Esteira em manutenção!");
        gotoxy(86, 11);
        printf("MANUTENÇÃO");
        textbackground(0); //funções simulação

        x = 10; //Necessário zerar a posição do x no estado manutenção

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
            printf("        EM ESTADO CRÍTICO!      ");
            gotoxy(81, 11);
            printf("     CRÍTICO     ");
            textbackground(PRETO);  //Zera o background de volta ao padrão

            fator_estado = CRITICO; //Duplica a velocidade para 2x;

            if(esteira_v > 90) //Com uma  velocidade acima de 90 ela quebra após 10 bolinhas
                quebrar = TRUE;
        }
        else
        {
            textcolor(AZULLIGHT);
            textbackground(VERDE);
            gotoxy(86, 11);
            printf("NORMAL");
            textbackground(PRETO); //Zera o background de volta ao padrão
        }

        do
        {
            //Animação bolinhas em y
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
            //Fim da animação das bolinhas em y
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

                        if(quebrar)//Se ela está em uma velocidade alta o suficiente
                        {
                            Crit_note += 25;
                            parametros->critico_esteira++;
                        }
                    }

                    gotoxy(num_x, bolinhas_y);
                    printf("%3d", parametros -> num_bolinhas);
                }
            }

            //Animação da esteira
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
            //Fim da animação da esteira

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

    parametros -> bola_posic_x = x; //Salva a posição da bolinha para o retorno da simulação
    parametros -> bola_posic_y = y;
}
