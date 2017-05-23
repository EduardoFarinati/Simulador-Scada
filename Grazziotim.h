/* Trabalho final Programação e Algoritmos 1
Biblioteca Grazziotim.h

Eduardo Farinati Leite
Lucas Bortolanza Grazziotim */

#include <time.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <string.h>

#include <iostream> //Para uso das funções de C++

#define XMAX 39 //Define os máximos da tela
#define YMAX 80

#define CIMA 72
#define BAIXO 80
#define ESQUERDA 75
#define DIREITA 77
#define ENTER 13
#define ESC 27

#define HIGH 2 // defines para os insumos
#define MEDIUM 1
#define LOW 0

#define FORTE 2 //defines para os registros
#define FRACO 1
#define FECHADO 0

#define CRITICO 2 //Estados para a esteira, critico 2x
#define NORMAL 1 // Normal, x

#define STDSPD 25 //Standard Speed para a esteira

#define CONTROLE 0 //Modos para a função imprime estado
#define CALDEIRA 1
#define ESTEIRA  2

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

#define PRETO 0
#define AZUL 1
#define VERDE 2
#define CIANO 3
#define VERMELHO 4
#define ROXO 5
#define AMARELO 6
#define BRANCO 7
#define CINZA 8
#define AZULLIGHT 9
#define VERDELIGHT 10
#define CIANOLIGHT 11
#define VERMELHOLIGHT 12
#define ROXOLIGHT 13
#define AMARELOLIGHT 14
#define BRANCOLIGHT 15

struct animacao_caldeira_posic //Grava a posição das bolinhas e o ciclo em que se encontra na animação
{
    int fim_ciclo[3];
    int x[3];
    int y[3];
    int k[3];
    int l;
    int misturador_y;
};

struct caldeira //Define o nível do registro e dos insumos uma caldeira
{
    int insumo[2]; //insumo 1 ou 2
    int registro;
};

typedef struct parametros //Parametros para todas simulações, salvo e carregado pela utilização de arquivos binário
{
    struct caldeira estado_caldeira[3]; //3 caldeiras, possivel entre LOW, MEDIUM, HIGH; Insumos / registro

    int vel_esteira; //Velocidade da esteira para a 2 simulação
    int num_bolinhas; //numero de bolinhas salvo
    int num_caixas;//numero de caixas salvo

    int bola_posic_x;
    int bola_posic_y;
    struct animacao_caldeira_posic caldeira_posic;//Grava a posição das bolinhas e o ciclo em que se encontra na animação

    int critico_esteira;//Estado critico da caldeira
    int critico_caldeira;//Estado critico da caldeira
    int misturador_explodido = FALSE;//Misturador explodiu, animação para de funcionar
    int esteira_quebrada = FALSE;//Caldeira quebrada, vira true

} PARAMETROS;


int setas()  //Controle pelas setas direcionais
{
    int valor_seta; //Possiveis valores no define, no cabeçalho do programa

    do
        valor_seta = getch();
    while(valor_seta != CIMA && valor_seta != BAIXO && valor_seta != ESQUERDA && valor_seta != DIREITA && valor_seta != ENTER && valor_seta != ESC); //Limita a valores respectivos das setas e Enter

    return valor_seta; //Manda para o main a seta lida
}

void hide_cursor() //Esconde o cursor default do prompt
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); //Esconde o Cursor do console
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void show_cursor() //Mostra novamente o cursor default do prompt
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 20;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void formatprompt() //formatação e linguagem padrão do programa
{
    system("color 03");                             //cor "padrao"
    system("mode 80, 39");                           //Modo para não exceder o buffer
    SMALL_RECT WinRect = {0, 0, XMAX, YMAX};       //Formata o tamanho do prompt
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);

    hide_cursor();
    setlocale(LC_ALL, "Portuguese"); //prompt em português para acentos e afins
}

void formatprompt_processos() //formatação do prompt para as simulações
{
    system("color 03");                             //cor "padrao"
    system("mode 110, 49");                           //Modo para não exceder o buffer
    SMALL_RECT WinRect = {0, 0, 110, 49};       //Formata o tamanho do prompt, nesse caso para o tamanho da simulação
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);
}

void formatprompt_estados() //formatação do prompt para a alteração dos parâmetros e estados
{
    system("color 03");                             //cor "padrao"
    system("mode 80, 41");                           //Modo para não exceder o buffer
    SMALL_RECT WinRect = {0, 0, XMAX, 41};       //Formata o tamanho do prompt
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);
}

void textbackground (int iColor) //Altera a cor do fundo para o caracter que será impresso na tela
{
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x000F;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
}

void textcolor(int ForgC) //Função para a coloração do texto
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void gotoxy(int x, int y)  //envia o cursor para determinado ponto x y
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}

void delay(unsigned int mseconds) //função delay, pausa o processo
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void flushkbhit() //Função para "limpar" o buffer após a utilização do kbhit
{
    while(kbhit())
        getch();//Limpa o buffer pós kbhit
}

void slider_f(int selec_x, int selec_y, PARAMETROS *estado_anterior, int *contador) //Cria um slider para o controle do nivel
{
    int nivel;
    int sair = 0, aux, aux_2;

    if(*contador != 9) //Teste para caldeiras ou esteira
    {
        aux = floor(((*contador)/3));
        aux_2 = (*contador) % 3;

        if(aux_2 == 2) //Caso registro
        {
            nivel = estado_anterior -> estado_caldeira[aux].registro;

            do
            {
                fflush(stdin);

                gotoxy(selec_x, selec_y); //apaga o slider anterior, caso exista
                printf("               ");
                gotoxy(selec_x, selec_y);

                switch(nivel)
                {
                case FORTE:
                    printf(" < FORTE |");
                    break;

                case FRACO:
                    printf(" < FRACO >");
                    break;

                case FECHADO:
                    printf(" | FECHADO >");
                }


                switch(setas())
                {
                case ESQUERDA:
                    if(nivel != FECHADO)
                    {
                        nivel--;
                        Beep(587.33, 50);
                    }
                    break;

                case DIREITA:
                    if(nivel != FORTE)
                    {
                        nivel++;
                        Beep(587.33, 50);
                    }
                    break;

                case CIMA:
                    if(*contador != 0)
                    {
                        estado_anterior -> estado_caldeira[aux].registro = nivel; //salva a mudança no escopo principal, novo estado
                        *contador -= 1;
                        sair = 1;
                    }
                    break;

                case BAIXO:
                    estado_anterior -> estado_caldeira[aux].registro = nivel;  //Não é necessário controle aqui, pois o contador 9 nunca entra na função slider_f
                    *contador += 1;
                    sair = 1;
                    break;

                case ENTER:
                    estado_anterior -> estado_caldeira[aux].registro = nivel;
                    sair = 1;
                }
            }
            while(!sair);
        }

        else //Caso insumo
        {
            nivel = estado_anterior -> estado_caldeira[aux].insumo[aux_2];

            do
            {
                fflush(stdin);

                gotoxy(selec_x, selec_y); //apaga o slider anterior, caso exista
                printf("               ");
                gotoxy(selec_x, selec_y);

                switch(nivel)
                {
                case LOW:
                    printf(" | BAIXO >");
                    break;

                case MEDIUM:
                    printf(" < MEDIO >");
                    break;

                case HIGH:
                    printf(" < ALTO |");
                }


                switch(setas())
                {
                case ESQUERDA:
                    if(nivel != LOW)
                    {
                        nivel--;
                        Beep(587.33, 50);
                    }
                    break;

                case DIREITA:
                    if(nivel != HIGH)
                    {
                        nivel++;
                        Beep(587.33, 50);
                    }
                    break;

                case CIMA:
                    if(*contador != 0)
                    {
                        estado_anterior -> estado_caldeira[aux].insumo[aux_2] = nivel; //salva a mudança no escopo principal, novo estado
                        *contador -= 1;
                        sair = 1;
                    }
                    break;

                case BAIXO:
                    estado_anterior -> estado_caldeira[aux].insumo[aux_2] = nivel;  //Não é necessário controle aqui, pois o contador 9 nunca entra na função slider_f
                    *contador += 1;
                    sair = 1;
                    break;

                case ENTER:
                    estado_anterior -> estado_caldeira[aux].insumo[aux_2] = nivel;
                    sair = 1;
                }
            }
            while(!sair);
        }
    }

    else //caso esteira
    {
        nivel = estado_anterior -> vel_esteira;

        do
        {
            fflush(stdin);

            gotoxy(selec_x, selec_y); //apaga o slider anterior, caso exista
            printf("               ");

            gotoxy(selec_x, selec_y);

            switch(nivel)
            {
                default:printf(" < %3d >", nivel);
                        break;

                case 0:printf(" |   0 >");
                       break;

                case 100:printf(" < 100 |");
            }


            switch(setas())
            {
                case ESQUERDA:if(nivel != 0)
                              {
                                  nivel--;
                              }
                              break;

                case DIREITA:if(nivel != 100)
                             {
                                 nivel++;
                             }
                             break;

                case CIMA:estado_anterior -> vel_esteira = nivel; //salva a mudança no escopo principal, novo estado
                          *contador -= 1;
                          sair = 1;
                          break;

                case BAIXO:estado_anterior -> vel_esteira = nivel;
                           *contador += 1;
                           sair = 1;
                           break;

                case ENTER:estado_anterior -> vel_esteira = nivel;
                           sair = 1;
            }
        }
        while(!sair);

    }
}

void imprime_estado(int x, int y[], PARAMETROS *parametros, const int cor, const int mode) //Imprime os atuais parâmetros dos processos
{
    int i, j, aux = 0; //i e j são contadores para o for, aux é um contador auxiliar para comparar com as posições definidas no array

    if(mode == CALDEIRA || mode == CONTROLE)
    {
        for(i = 0; i < 3; i++) //imprime os estados na tela
        {
            textcolor(cor);
            for(j = 0; j < 2; j++)
            {
                gotoxy(x, y[aux]); //x+2 para imprimir à direita do cursor
                aux++;

                switch(parametros -> estado_caldeira[i].insumo[j])
                {
                case LOW:printf("BAIXO ");
                         break;

                case MEDIUM:printf("MEDIO ");
                            break;

                case HIGH:printf("ALTO ");
                          break;
                default:printf("Bug:%d", parametros -> estado_caldeira[i].insumo[j]); //Caso um erro ocorra temos a impressão do valor incorreto
                }
            }

            textcolor(VERDELIGHT);
            gotoxy(x, y[aux]); //para definir a posição do cursor quanto ao registro

            aux++;//Soma novamente na variável da posição
            switch(parametros -> estado_caldeira[i].registro)
            {
            case FORTE:printf("FORTE ");
                       break;

            case FRACO:printf("FRACO ");
                       break;

            case FECHADO:printf("FECHADO ");
                         break;

            default:printf("Bug:%d", parametros -> estado_caldeira[i].registro); //Caso um erro ocorra temos a impressão do valor incorreto
            }
        }

        if(mode == CALDEIRA) //Apenas neste caso será impresso o numero de bolinhas e de caixas
        {
            textcolor(CINZA);
            gotoxy(x, y[aux]);
            printf("  %3d   ", parametros -> num_bolinhas);//Bolinhas
            aux++;

            gotoxy(x, y[aux]);
            printf("  %3d   ", parametros -> num_caixas);//CAIXAS
            aux++;
        }
    }
    if(mode == ESTEIRA || mode == CONTROLE)
    {
        textcolor(VERDE);
        gotoxy(x, y[aux]); //Define a ultima posição do vetor
        printf("  %3d   ", parametros -> vel_esteira);//Imprime a velocidade da esteira;
        aux++;

        if(mode == ESTEIRA) //Apenas neste caso será impresso o numero de bolinhas e de caixas
        {
            textcolor(CINZA);
            gotoxy(x, y[aux]);
            printf("  %3d   ", parametros -> num_bolinhas);//Bolinhas
            aux++;

            gotoxy(x, y[aux]);
            printf("  %3d   ", parametros -> num_caixas);//CAIXAS
            aux++;
        }
    }
}

void zera_estados(PARAMETROS *parametros) //Zera todos parâmetros para nova simulação
{
    int i, j; // contadores para os for de zera estados

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 2; j++)
            parametros -> estado_caldeira[i].insumo[j] = LOW; //Define os insumos como LOW, BAIXO;
        parametros -> estado_caldeira[i].registro = FECHADO; //Fecha os registros

        parametros -> caldeira_posic.fim_ciclo[i] = FALSE;//Zera os ciclos das caldeiras
        parametros -> caldeira_posic.k[i] = 0;//Zera a variável de comparação dos volumes na animação das caldeiras
        parametros -> caldeira_posic.y[i] = 15;//Default posição para as bolinhas na animação das caldeiras
    }

    parametros -> vel_esteira = STDSPD;//Define a velocidade da esteira como standard (20)
    parametros -> caldeira_posic.l = 0;//Zera a variável de comparação com os volumes totais

    parametros -> num_bolinhas = 0; //Zera o numero de bolinhas
    parametros -> num_caixas = 0; //Zera o numero de caixas

    parametros -> bola_posic_x = 10;//Ajusta a posição inicial da bolinha na esteira para o default
    parametros -> bola_posic_y = 14;
    parametros -> caldeira_posic.x[0] = 12;//Ajusta a posição inicial das bolinhas na caldeira para o default
    parametros -> caldeira_posic.x[1] = 32;
    parametros -> caldeira_posic.x[2] = 52;
    parametros -> caldeira_posic.misturador_y = 34;

    parametros -> critico_esteira = 0; //Zera as variáveis dos estados críticos
    parametros -> critico_caldeira = 0;
}

void imprime_esteira() //Imprime a esteira da segunda simulação
{
    FILE *arq;

    int x = 9, y=35;
    char vet[50];

    arq = fopen("esteira.txt", "r");

    while (!feof(arq))
    {
        gotoxy(x, y);
        y++;

        fgets(vet, 50, arq);

        if(!feof(arq))
            printf("%s", vet);
    }

    fclose(arq);

    /* Imprime a esteira
       _______________________________________
      |O*************************************O|
      ||-------------------------------------||
      ||-------------------------------------||
      |O_____________________________________O|
    */

}

void imprime_caldeiras()//Imprime as caldeiras e o misturador da primeira simulação
{
    FILE *arq;
    char vet[60];
    int y=9;

    arq = fopen("caldeira.txt", "r");

    while(!feof(arq))
    {
        fgets(vet, 62, arq);

        gotoxy(5, y);
        y++;

        if (!feof(arq))
            printf("%s\n", vet);
    }

    fclose(arq);

    /* Imprime as caldeiras
        __________          __________          __________
       /          \        /          \        /          \
      |            |      |            |      |            |
      |            |      |            |      |            |
      |            |      |            |      |            |
      |            |      |            |      |            |
      |            |      |            |      |            |
       \          /        \          /        \          /
        \        /          \        /          \        /
         \      /            \      /            \      /
          |    |              |    |              |    |
          |    |              |    |              |    |
          |    |              |    |              |    |





      \                                                    /
       \                                                  /
        \                                                /
         \                                              /
          \____      __________________________________/
               |     |
               |     |
               |     |

    */
}

int Mini_menu() //Menu de controle dentro da simulação
{
    const int posic_x = 0, posic_y = 2; //Posições iniciais para as impressões do menu
    int x = 9, y[3] = {3, 4, 5}; //impressões na tela do seletor, posições x e y definidas pelos arrays
    int sair, contador = 0;

    textcolor(CIANO);
    gotoxy(posic_x, posic_y);
    printf("|*|*                                                         *|*|");
    gotoxy(posic_x, posic_y+1);
    printf("*|          1. Salvar estados dos processos                    |*");
    gotoxy(posic_x, posic_y+2);
    printf("|*          2. Voltar para o menu da simulação                 *|");
    gotoxy(posic_x, posic_y+3);
    printf("*|          3. Voltar para o menu principal                    |*");
    gotoxy(posic_x, posic_y+4);
    printf("|*                                                             *|");

    do
    {
        sair = 0;
        textcolor(AMARELOLIGHT);
        gotoxy(x, y[contador]);  //seleciona o cursor nas opcoes disponives do vetor
        printf(">");

        flushkbhit();

        switch(setas())
        {
        case CIMA:
            if(contador != 0)
            {
                gotoxy(x, y[contador]);
                printf(" "); //Apaga o cursor previo ao pressionamento da tecla
                contador--;
            }
            break;

        case BAIXO:
            if(contador != 2)
            {
                gotoxy(x, y[contador]);
                printf(" ");
                contador++;
            }
            break;

        case ESC:
            contador = 1; //Esc retorna ao menu anterior, menu simulação, opção 1
        case ENTER:
            sair = 1;
        }
        Beep(587.33, 50);
    }
    while(!sair);

    return contador;
}

void print_logo() //Imprime o logo da caixa dentro da simulação
{
    const int x = 0, y = 2; //Posições iniciais para as impressões do menu

    textcolor(CIANO);
    gotoxy(x, y);
    printf("|*|* - | - | - | - | - | - | - | - | - | - | - | - | - | - | *|*|*");
    gotoxy(x, y+1);
    printf("*| - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # |*");
    gotoxy(x, y+2);
    printf("|* | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - *|");
    gotoxy(x, y+3);
    printf("*| - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # |*");
    gotoxy(x, y+4);
    printf("|* | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - *|");

}

void mensagem_alarme(int n_caldeira)//Avisa o usuário de problemas no processo
{
    n_caldeira++;
    textcolor(VERMELHOLIGHT);
    textbackground(BRANCOLIGHT);
    gotoxy(70, 4+n_caldeira);
    printf("  Alterar dados da Caldeira %d   ", n_caldeira);
    textcolor(CIANO);
    textbackground(PRETO);
}

void mensagem_estado(int v) //Indica o estado do processo para o usuário
{
    textcolor(VERMELHOLIGHT);
    textbackground(BRANCOLIGHT);
    gotoxy(79, 11);

    if(v <= 3)
    {
        printf(" Misturador Desligado ");
    }

    else if(v <= 9)
    {
        textcolor(AZULLIGHT);
        textbackground(VERDE);
        printf(" Funcionamento Normal ");
    }

    else
    {
        printf("       Crítico!       ");

        gotoxy(70, 5);
        printf("            PERIGO!             ");
        gotoxy(70, 6);
        printf("          ATUAR  SOBRE          ");
        gotoxy(70, 7);
        printf("          O  PROCESSO!          ");
    }
    textbackground(PRETO);
    textcolor(ROXOLIGHT);
    gotoxy(100, 14);//Imprime na tela a vazão total
    printf("%d", v);

    textcolor(CIANO);
}

void calcula_posic(int ciclo[], int x[], int y[], int k[], int l, int misturador_y, int ciclo_s[], int x_s[], int y_s[], int k_s[], int *l_s, int *misturador_y_s) //Copia os parâmetros de posição para outras variáveis
{
    //O Subíndice 's' indica as a serem alteradas

    int i;//Contador para o for

    for(i = 0; i < 3; i++)// Iguala todos os fatores que alteram a posição das bolinhas na animação da caldeira
    {
        ciclo_s[i] = ciclo[i];
        x_s[i] = x[i];
        y_s[i] = y[i];
        k_s[i] = k[i];
    }

    *misturador_y_s = misturador_y;
    *l_s = l;
}

void avalia_volume(PARAMETROS *parametros,int vol[],int *vol_total) //Calcula o número de volumes respectivo a cada caldeira e o total de acordo com o os parâmetros
{
    int i;

    for (i=0; i<3; i++)
    {
        vol[i] = 0;

        if (parametros->estado_caldeira[i].registro == FECHADO)
        {
            vol[i] = 0;
        }
        else if (parametros->estado_caldeira[i].registro == FORTE)
        {

            if (parametros->estado_caldeira[i].insumo[0] == HIGH)
            {

                if (parametros->estado_caldeira[i].insumo[1] == HIGH)
                {
                    vol[i] = 4;
                }

                else if (parametros->estado_caldeira[i].insumo[1] == LOW)
                {
                    vol[i] = 2;
                }
                else
                {
                    mensagem_alarme(i);
                }
            }

            if (parametros->estado_caldeira[i].insumo[0] == LOW)
            {

                if (parametros->estado_caldeira[i].insumo[1] == HIGH)
                {
                    vol[i] = 3;
                }

                else
                {
                    mensagem_alarme(i);
                }
            }

            if (parametros->estado_caldeira[i].insumo[0] == MEDIUM)
            {
               if(parametros->estado_caldeira[i].insumo[1] == MEDIUM)
                   vol[i] = 3;
                else
                    mensagem_alarme(i);
            }
        }
        else //Registro fraco
        {

            if (parametros->estado_caldeira[i].insumo[0] == HIGH)
            {

                if (parametros->estado_caldeira[i].insumo[1] == HIGH)
                {
                    vol[i] = 3;
                }

                else if (parametros->estado_caldeira[i].insumo[1] == LOW)
                {
                    vol[i] = 1;
                }

                else
                {
                    mensagem_alarme(i);
                }
            }

            if (parametros->estado_caldeira[i].insumo[0] == LOW)
            {

                if (parametros->estado_caldeira[i].insumo[1] == HIGH)
                {
                    vol[i] = 1;
                }

                else
                {
                    mensagem_alarme(i);
                }
            }

            if (parametros->estado_caldeira[i].insumo[0] == MEDIUM)
            {
                if(parametros->estado_caldeira[i].insumo[1] == MEDIUM)
                    vol[i] = 2;
                else
                    mensagem_alarme(i);
            }
        }

        *vol_total += vol[i];
    }

    mensagem_estado(*vol_total);

    textcolor(CIANO);
    textbackground(PRETO);
}

void explosao() //Explode o misturador, muitos volumes, estado crítico
{
    int minx = 4, miny = 9, maxx = 58, maxy = 44, x, y;
    int cont=0, a, b;

    srand(time(NULL));

    do
    {

        x = minx + (rand() % (maxx - minx + 1));
        y = miny + (rand() % (maxy - miny + 1));

        a = 0 + (rand() % (16));
        b = 0 + (rand() % (16));

        gotoxy(x, y);
        textbackground(a);
        textcolor(b);

        printf("%d", x);

        delay(3);
        cont++;
    }
    while(cont<3000);

    textcolor(VERMELHOLIGHT);
    textbackground(BRANCOLIGHT);
    gotoxy(79, 11);

    gotoxy(70, 5);
    printf("            EXPLODI             ");
    gotoxy(70, 6);
    printf("         EU AVISEI PARA         ");
    gotoxy(70, 7);
    printf("       MUDAR OS PARÂMETROS      ");

    gotoxy(79, 11);
    printf("       Quebrado!       ");


    textcolor(CIANO);
    textbackground(PRETO);

    for(x = minx; x < maxx+2; x++)
    {
        for(y = miny; y < maxy+2; y++)
        {
            gotoxy(x, y);
            printf(" ");
        }
    }

    textcolor(VERMELHOLIGHT);


    FILE *arq;
    char vet[60];
    y=9;

    arq = fopen("explodiu.txt", "r");

    while(!feof(arq))
    {
        fgets(vet, 62, arq);

        gotoxy(5, y);
        y++;

        if (!feof(arq))
            printf("%s\n", vet);
    }

    fclose(arq);


    textcolor(CIANO);
    textbackground(PRETO);
}

void quebra() //Quebra a esteira, velocidade muito alta, estado crítico
{
    FILE *arq;

    int x = 9, y=35;
    char vet[50];

    textcolor(VERMELHOLIGHT);
    textbackground(PRETO);

    arq = fopen("quebrou.txt", "r");

    while (!feof(arq))
    {
        gotoxy(x, y);
        y++;

        fgets(vet, 50, arq);

        if(!feof(arq))
            printf("%s", vet);
    }

    fclose(arq);

    gotoxy(79, 11);
    textcolor(VERMELHOLIGHT);
    textbackground(BRANCO);
    printf("      QUEBROU      ");

    textcolor(CIANO);
    textbackground(PRETO);
}

void salva_simu(PARAMETROS to_save)//Salva a simulação em um arquivo padrão "Simulacao.bin"
{
    FILE *arq;

    arq = fopen("Simulacao.bin", "wb");

    if(arq == NULL)
    {
        gotoxy(12, 3);
        textcolor(VERMELHOLIGHT);
        printf("Erro de abertura do arquivo binário!");
    }
    else
    {
        gotoxy(12, 3);
        printf("                                  ");
        while(fwrite(&to_save, sizeof(PARAMETROS), 1, arq) != 1)
        {
            gotoxy(12, 3);
            textcolor(VERMELHOLIGHT);
            printf("Erro na gravação do arquivo");
            gotoxy(20, 24);
            textcolor(BRANCOLIGHT);
            delay(75);
            printf("Pressione qualquer tecla para tentar novamente...");
            getch();
        }

        gotoxy(12, 3);
        textcolor(VERDELIGHT);
        printf("Salvo!    ");
        delay(100);
        Beep(880, 75);
        delay(100);
    }

    fclose(arq);
}

void escolher_file_salvar(char file_name[])//Aqui o usuário escolhe o nome do arquivo a ser salvo
{
    int x = 16, y = 14;
    system("CLS");   //Limpa a tela para inicialização do menu_simu
    textcolor(CIANO); //cor do texto

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
              << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
              << "*|*                                                                         *|*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                  Entre com o nome da file a ser salva:                    |*\n"
              << "|*                                                                           *|\n"
              << "*|                           (até 30 caracteres)                             |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|             _____________________________________________                 |*\n"
              << "|*            |                                             |                *|\n"
              << "*|            |                                             |                |*\n"
              << "|*            |                                             |                *|\n"
              << "*|            |_____________________________________________|                |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|*                                                                         *|*\n"
              << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
              << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";


        textcolor(AMARELOLIGHT);
        gotoxy(x, y);  //seleciona o cursor nas opcoes disponives do vetor
        printf(" > ");
        show_cursor(); //Imprime o cursor na tela, intuitivo para o usuário

        fflush(stdin);
        textcolor(VERDE);
        fgets(file_name, 30, stdin);
        hide_cursor();
}

void escolher_file_abrir(char file_name[])//Aqui o usuário escolhe o nome do arquivo a ser carregado
{
    int x = 16, y = 14;
    system("CLS");   //Limpa a tela para inicialização do menu_simu
    textcolor(CIANO); //cor do texto

    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
              << "|\\-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-/|\n"
              << "*|*                                                                         *|*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                  Entre com o nome da file a ser aberta:                   |*\n"
              << "|*                                                                           *|\n"
              << "*|                           (até 30 caracteres)                             |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|             _____________________________________________                 |*\n"
              << "|*            |                                             |                *|\n"
              << "*|            |                                             |                |*\n"
              << "|*            |                                             |                *|\n"
              << "*|            |_____________________________________________|                |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|                                                                           |*\n"
              << "|*                                                                           *|\n"
              << "*|*                                                                         *|*\n"
              << "|/-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\\|\n"
              << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";


        textcolor(AMARELOLIGHT);
        gotoxy(x, y);  //seleciona o cursor nas opcoes disponives do vetor
        printf(" > ");
        show_cursor(); //Imprime o cursor na tela, intuitivo para o usuário

        fflush(stdin);
        textcolor(VERDE);
        fgets(file_name, 30, stdin);
        hide_cursor();
}

void salvarestados(PARAMETROS to_save)//Salva os parâmetros atuais em um arquivo binário de nome escolhido pelo usuário
{
    FILE *arq;
    char file_name[35]; //Um caracter a mais para o '\0' e quatro para a extensão ".bin"
    const char file_type[5] = ".bin"; //caso o usuário não insira a extensão, ela é adicionada
    int sair = 1, i, str_size;

    do
    {
        escolher_file_salvar(file_name);
        str_size = strlen(file_name) -  1;//para apagar o '\n', incluido no fgets
        file_name[str_size] = '\0'; //para apagar o '\n', incluido no fgets

        for(i = 0; i < 5; i++)
            if(file_name[str_size - 4 + i] != file_type[i])
            {
                strcat(file_name, file_type);
                i = 5;
            }

        arq = fopen(file_name, "wb");

        if(arq == NULL)
        {
            gotoxy(18, 22);
            textcolor(VERMELHOLIGHT);
            printf("Erro de abertura do arquivo binário!");
            gotoxy(18, 25);
            delay(75);
            textcolor(BRANCOLIGHT);
            printf("Pressione qualquer tecla para tentar novamente...");
            getch();
        }
    }
    while(arq == NULL && sair != ESC);

    while(fwrite(&to_save, sizeof(PARAMETROS), 1, arq) != 1)
    {
        gotoxy(20, 22);
        textcolor(VERMELHOLIGHT);
        printf("Erro na gravação do arquivo");
        gotoxy(20, 24);
        textcolor(BRANCOLIGHT);
        delay(75);
        printf("Pressione qualquer tecla para tentar novamente...");
        getch();
    }

    gotoxy(3, 24);
    textcolor(VERDELIGHT);
    printf("Simulação salva com sucesso com o nome '%s'!", file_name);
    Beep(880, 75);
    gotoxy(3, 27);
    textcolor(BRANCOLIGHT);
    printf("Pressione qualquer tecla para continuar...");
    getch();

    fclose(arq);
}

int carrega_parametros(PARAMETROS *to_read)//Carrega os parâmetros de um arquivo binário determinado pelo usuário
{
    FILE *arq;
    char file_name[35]; //Um caracter a mais para o '\0' e quatro para a extensão ".bin"
    const char file_type[5] = ".bin"; //caso o usuário não insira a extensão, ela é adicionada
    int sair = 1, i, str_size; //Para sair do loop, em caso de não existir file a ser carregada

    do
    {
        escolher_file_abrir(file_name);
        str_size = strlen(file_name) -  1;//para apagar o '\n', incluido no fgets
        file_name[str_size] = '\0'; //para apagar o '\n', incluido no fgets

        for(i = 0; i < 5; i++)
            if(file_name[str_size - 4 + i] != file_type[i])
            {
                strcat(file_name, file_type);
                i = 5;
            }

        arq = fopen(file_name, "rb");

        if(arq == NULL)
        {
            gotoxy(18, 22);
            textcolor(VERMELHOLIGHT);
            printf("Erro de abertura do arquivo binário!");
            gotoxy(18, 25);
            delay(75);
            textcolor(BRANCOLIGHT);
            printf("Pressione qualquer tecla para tentar novamente...");
            gotoxy(18, 27);
            delay(75);
            printf("Pressione ESC para retornar ao menu principal");
            sair = getch();
        }
    }
    while(arq == NULL && sair != ESC);

    while(fread(to_read, sizeof(PARAMETROS), 1, arq) != 1 && sair != ESC)
    {
        gotoxy(20, 22);
        textcolor(VERMELHOLIGHT);
        printf("Erro na leitura do arquivo");
        gotoxy(20, 24);
        textcolor(BRANCOLIGHT);
        delay(75);
        printf("Pressione qualquer tecla para tentar novamente...");
        gotoxy(18, 27);
        delay(75);
        printf("Pressione ESC para retornar ao menu principal");
        sair = getch();
    }

    if(sair != ESC)
    {
        gotoxy(3, 24);
        textcolor(VERDELIGHT);
        printf("Simulação '%s' carregada com sucesso!", file_name);
        Beep(880, 75);
        gotoxy(3, 27);
        textcolor(BRANCOLIGHT);
        printf("Pressione qualquer tecla para continuar...");
        getch();
    }

    fclose(arq);

    return sair;
}
