#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

/*             0     1    2     3   4      5      6      7         8  */
typedef enum{black,blue,green,cyan,red,magenta,brown,lightgray,darkgray,   /* nome das cores */
lightblue,lightgreen,lightcyan,lightred,lightmagenta,yellow,white} colors;
/*  9         10         11        12        13         14    15 */

static int __BACKGROUND = 1/*BLACK*/;/*pode ser o numero ou o nome da cor*/
static int __FOREGROUND = lightgray;

void textcolor_2 (int letras, int fundo){/*para mudar a cor de fundo mude o background*/
    __FOREGROUND = letras;
    __BACKGROUND = fundo;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letras + (__BACKGROUND << 4));
}
                  /* y = linha de 0 a 24 , x = coluna de 0 a 80 */
void gotoxy_2(int x, int y){/*imprimir na linha e coluna desejada */
  COORD c;
  c.X = x;
  c.Y = y;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Movement();
void desenha (int co_i, int li_i, int caract[], int w );
void circle();
void apaga_bola(int ant_cs, int ant_sn);
void desenha_bola(int cs, int sn);
int flag,rj,b,a_c,w,w2,ant_l;
int ant_cs,ant_sn;
int flag,rj,b,a_c,w,w2,ant_l,mov,mov2=6;
int ant_cs,ant_sn;
float circulo,cs[3],sn[3];
int bola[3]={6,9,6};
int carac2[70]={
    124,130,130,126,  2,130,124,/* Digito  9 */   //  01111100 --|
    124,130,124,130,130,130,124,/* Digito  8 */   //  10000010   |
    254,  2, 12, 16, 96, 64, 64,/* Digito  7 */   //  10000010   |
    124,128,188,194,130,130,124,/* Digito  6 */   //  01111110   |-- Digito Nove
    252,128,252,  2,  2,130,124,/* Digito  5 */   //  00000010   |
     28, 36, 68,132,252,  4, 62,/* Digito  4 */   //  10000010   |
    124,130,  2, 28,  2,130,124,/* Digito  3 */   //  01111100 --|
    124,130,  2, 28, 96,128,252,/* Digito  2 */
     16, 112, 16, 16,16, 16,124,/* Digito  1 */
     56, 68,138,146,162, 68, 56 /* Digito  0 */
};
void botoes_de_baixo(int col){
    if( flag ){
    if(col==40){
        gotoxy_2(37,11);printf("  Autores Nomes  ");
        gotoxy_2(37,13);printf(" Autores   Info  ");
    }
    else
        if(col!= 70){
            gotoxy_2(col-2,11);printf(" Regras    ");
            gotoxy_2(col-2,13);printf(" Pontuacao ");
            gotoxy_2(col-2,15);printf(" Listar    ");
            gotoxy_2(col-2,17);printf(" Buscar    ");
        }
    }
    gotoxy_2(59,1);
}
void menu2(int col){
    textcolor_2(15,9);
    for(b=11;b<18;b++){
        gotoxy_2(37,b);
        printf("                                ");
    }
    gotoxy_2(38,9);
    textcolor_2(0,24);
    /*printf("  Aluno     Pilha     Fila      Sobre");*/
    printf(" Autores  Orienta%c%ces  Jogar   Sair    ",135,228);//printf("menu2");
    botoes_de_baixo(col);
    gotoxy_2(59,1);
}
void Menu(int col){
    textcolor_2(white,lightblue);
    for(b=8;b<25;b++){
        gotoxy_2(35,b);
        printf("%c                                           %c",186,186);
    }
    for(b=36;b<79;b++){
        for(w=8;w<11;w+=2){
            gotoxy_2(b,w);
            printf("%c",205);
            gotoxy_2(b,w+14);
            printf("%c",205);
        }
    }
    textcolor_2(white,8);
    gotoxy_2(36,9);
    printf("                                           ");
    menu2(col);
    textcolor_2(white,9);
    gotoxy_2(35,24);printf("%c",200);
    gotoxy_2(35, 8);printf("%c",201);
    gotoxy_2(79, 8);printf("%c",187);
    gotoxy_2(79,24);printf("%c",188);
    gotoxy_2(35,10);printf("%c",204);
    gotoxy_2(35,22);printf("%c",204);
    gotoxy_2(79,10);printf("%c",185);
    gotoxy_2(79,22);printf("%c",185);
    botoes_de_baixo(col);
    gotoxy_2(59,1);w=0;
}
#define esquerda 75
#define direita  77
#define abaixo   80
#define acima    72
#define ESC      27
#define enter    13
#define pi 3.141592

void botao(int col, int lin){           /* colorir botão de vermelho    */
    if(ant_l==9){       /* imprime os botões da linha 9 */
        if     (a_c==40){gotoxy_2(39,9);printf("Autores ");}
        else if(a_c==50){gotoxy_2(48,9);printf("Orienta%c%ces",135,228);}
        else if(a_c==60){gotoxy_2(59,9);printf("  Jogar  ");}
        else if(a_c==70){gotoxy_2(69,9);printf("Sair ");}
    }
    else{
        if(ant_l==11){  /* imprime os botões da linha 11 */
            if(a_c==40){gotoxy_2(37,11);printf("  Autores Nomes  ");}
            else{
                if(a_c==50 || a_c==60){
                    gotoxy_2(a_c-2,11);
                    printf(" Regras    ");
                }
            }
        }
        else
            if(ant_l==13){/* imprime os botões da linha 13 */
                if(a_c==40){gotoxy_2(37,13);printf(" Autores   Info  ");}
                else{
                    if(a_c==50 || a_c==60){
                        gotoxy_2(a_c-2,13);
                        printf(" Pontuacao ");
                    }
                }
            }
            else
                if(ant_l==15){/* imprime os botões da linha 15 */
                    if(a_c==50 || a_c==60){
                        gotoxy_2(a_c-2,15);
                        printf(" Listar  ");
                    }
                }
                else
                    if(ant_l==17){/* imprime os botões da linha 17 */
                        if(a_c==50 || a_c==60){
                            gotoxy_2(a_c-2,17);
                            printf(" Buscar  ");
                        }
                    }
        }
}
void autor_nome(){
    printf("esta no Autores Nome , Apenas para hum teste !\n   Espere !");
    Sleep(2000);
}
void autores_info(){
    printf("esta no autores info , Apenas para hum teste !\n   Espere !");
    Sleep(2000);
}
void incluir_pilha(){
    printf("esta no incluir Pilha Apenas para hum teste !\n   Espere !");
    Sleep(2000);
}
void incluir_fila(){
    printf("esta no incluir Fila Apenas para hum teste !\n   Espere !");
    Sleep(2000);
}
void listar_pilha(){
    printf("esta no listar Pilha Apenas para hum teste !\n   Espere !");
    Sleep(2000);
}
void listar_fila(){
    printf("esta no listar Fila Apenas para hum teste !\n   Espere !");
    Sleep(2000);
}
void excluir_pilha(){
    printf("esta no excluir Pilha Apenas para hum teste !\n   Espere !");
    Sleep(2000);
}
void excluir_fila(){
    printf("esta no excluir fila para Apenas hum teste !\n   Espere !");
    Sleep(2000);
}
void buscar_pilha(){
    printf("esta no buscar Pilha Apenas para hum teste !\n   Espere !");
    Sleep(2000);
}

void buscar_fila(){
    printf("esta no buscar fila Apenas para hum teste !\n   Espere !");
    Sleep(2000);
}
void sair(int col){
    gotoxy_2(0,1);
    textcolor_2(15,12);
    gotoxy_2(60,11);
    printf("Esse Programa Ainda");
    gotoxy_2(60,12);
    printf("Esta Sendo Criado !");
    gotoxy_2(60,14);
    printf("  Tecle ! ");
    getch();
    exit( 0 );
}
int main(){
    printf("\nUse As Setas Do Teclado Para Mover.   Tecle ESC Para Sair");
    int a,col=40,lin=9,temp;
    Menu(col)                                              ;/* desenha a tela                       */
    do{
        a=0                                                ;/* para cancelar o botão anterior       */
        temp=0                                             ;/* para não ir nas funções menu e botao */
        a_c=col                                            ;/* cuoluna anterior igual coluna atual  */
        ant_l=lin                                          ;/* linha anterior igual linha atual     */
        gotoxy_2(col,lin)                                  ;/* na posição do botão selecionado      */
        textcolor_2(15,12)                                ;/* letras brancas com fundo vermelho    */
        void botao(int col, int lin)                                     ;/* botão selecionado fica vermelho      */
        if(kbhit())  a = getch()                           ;/* pega a tecla digitadsa               */
        if(a == 224 )a = getch()                           ;/* se pegar caractere inválido          */
        if(a == enter){                                     /* se presionar enter                   */
            textcolor_2(15,0);gotoxy_2(1,60);gotoxy_2(1,50);/* branco com fundo preto na linha 48   */
            if(lin==9){if(flag==0)flag=1;else flag=0;      }/* mostrar ou não os botões de baixo    */
            if     (lin== 9 && col == 70)     sair(col     );/* bot sair  selec ir para a funç sobre */
            else if(lin==11 && col == 40)   autor_nome(    );/* bot at nm selec ir para a funç cadas */
            else if(lin==13 && col == 40) autores_info(    );/* bot info  selec ir para a funç mos d */
            else if(lin==11 && col == 50)incluir_pilha(    );/* bot inc p selec ir para a funç inc p */
            else if(lin==13 && col == 50)excluir_pilha(    );/* bot exc p selec ir para a funç exc p */
            else if(lin==15 && col == 50) listar_pilha(    );/* bot lis p selec ir para a funç lis p */
            else if(lin==17 && col == 50) buscar_pilha(    );/* bot bus p selec ir para a funç bus p */
            else if(lin==11 && col == 60)incluir_fila(     );/* bot inc f selec ir para a funç inc f */
            else if(lin==13 && col == 60)excluir_fila(     );/* bot exc f selec ir para a funç exc f */
            else if(lin==15 && col == 60) listar_fila(     );/* bot lis f selec ir para a funç lis f */
            else if(lin==17 && col == 60) buscar_fila(     );/* bot bus f selec ir para a funç bus f */
            temp=1;
            gotoxy_2(1,3);
            textcolor_2(15,0);
            printf("                                              \n           ");
        }
        else
            if(a == direita ){
                col+=10;                   // Move o cursor para a direita
                if(lin==9)flag=0;          /* não mostrar botões de baixo */
            }
            else
                if(a == esquerda){
                    col-=10;               // Move o cursor para a esquerda
                    if(lin==9)flag=0;      /* não mostrar botões de baixo */
                }
                else
                    if(a == abaixo  ){     /* mover para baixo                       */
                        lin+=2;            /* move o cursor para baixo               */
                        if(lin==11){
                            flag=1;        /* para mostrar os botões de baixo        */
                            temp=1;        /* para ir na função menu e botao         */
                        }
                    }
                    else
                        if(a == acima  ){  /* mover para cima                        */
                            lin-=2;        /* move o cursor para cima                */
                            if(lin<=9){    /* estiver na linha do menu ou acima dela */
                                flag=0;    /* para não mostrar os botões de baixo    */
                                temp=1;    /* para ir na função menu e botao         */
                                ant_l=lin; /* para limpar o botão anterior de baixo  */
                            }
                        }
        if(temp){menu2(col); void botao(int col, int lin);}/* vai nas funções menu e botao           */
        if(col==70 || ! flag )lin=ant_l;   /* o botão sobre não pode mover para baixo e nem para cima        */
        if(lin > 9)col=a_c;                /* se estiver nos botões de baixo não pode mover para os lados    */
        if(col<40)col=70;                  /* se cursor passou da lateral direita volta para o lado esquerdo */
        else
            if(col>70)col=40;              /* se cursor passou da lateral esquerda volta para o lado direita */
        if(lin<9)lin=9;                    /* se cursor passou da linha de cima volta para a linha de baixo  */
        else
            if(lin>13 && col == 40)lin=13; /* se passou abaixo dos botõe abaixo de aluno , volta para cima   */
            else
                if(lin>17 && (col == 50||col==60))/*se passou abaixo dos botõe abaixo de pilha ou fila       */
                    lin=17;               /*  volta para cima                                                */
        if(a_c != col || ant_l != lin){
            menu2(col);
            gotoxy_2(a_c,lin);
            void botao(int col, int lin);
        }
        gotoxy_2(59,1);
        mov++;
        if(mov==300){
            Movement();
            mov=0;
        }
        if(b==mov)circle();
    }while( a != 27 );
    textcolor_2(7,0);
    gotoxy_2(0,25);
    return 0;
}
void Movement(){
    textcolor_2(14,0);             /* primeiro a cor da letra , segundo a cor de fundo */
    gotoxy_2(8,12);
    if(mov>299)mov2++;
    if(mov2>5){
        desenha(20,10,carac2,w2);  /* são os dígitos                                   */
        mov2=0;
        w2+=7;
        if(w2 > 69)w2=0;
    }                            /* contagem decrescente                              */
    textcolor_2(10,0);            /*printf("valor w = %d",w);getch();                  */
    w+=7;
    if(w > 104)w=0;
    rj++;
    if(rj>9)rj=0;
    gotoxy_2(59,1);
}
void circle(){
    int x1,grau=0;
    textcolor_2(11,0);
    for(x1=0;x1<3;x1++){
        if(sn[x1]==0 && cs[x1]==0){
            ant_sn=12;
            ant_cs=22;
        }
        else{
            ant_cs=cs[x1];
            ant_sn=sn[x1];
        }
        gotoxy_2(ant_cs,ant_sn);
        apaga_bola(ant_cs,ant_sn);
        sn[x1]=(float)sin((circulo+grau)*pi/180)*11+13;
        cs[x1]=(float)cos((circulo+grau)*pi/180)*13+14;
        gotoxy_2(cs[x1],sn[x1]);
        desenha_bola(cs[x1],sn[x1]);
        grau+=120;
    }
    circulo+=8;
    if(circulo>360)circulo=0;
    b+=200;
    if(b>299)b=0;
    gotoxy_2(59,1);
}
void apaga_bola(int ax, int ay){
    int j,y;
    for(j=0;j<3;j++){
        for(y=0;y<4;y++){
            gotoxy_2(ax+y,ay+j);
            printf(" ");
        }
    }
    gotoxy_2(59,1);
}
void desenha_bola(int x, int y){
    int j,m,s,n=0;
    for(j=0;j<3;j++){
        s=bola[n];
        for(m=0;m<4;m++){
            gotoxy_2(x+m,y+j);
            if(s%2==0)printf(" ");
            else printf("%c",219);
            s/=2;
        }
        n++;
    }
}
void desenha(int co_i, int li_i, int caract[],int w){
    int x,y,q,co,li;
    li=li_i;
    for(x=0;x<7;x++){                  /* linhas */
        co=co_i;
        q=caract[x+w];
        for(y=0;y<8;y++){              /* colunas */
            gotoxy_2(co,li);
            if(q % 2==0)printf(" ");
            else   printf("%c",219);
            co--;
            q/=2;
        }
        li++;
    }
}