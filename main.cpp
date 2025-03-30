/**
    Estrutura inicial para um jogo
    vers�o: 0.1 (Prof. Alex,  Adaptado Prof. Felski)
*/
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int menu(){
    int op=0;
    cout << "--------------------------------\n";
    switch(op)
    {
        cout << "1 - Iniciar\n2 - Opcoes\nCreditos";
        case 1:
            break;
        case 2:
           
        case 3:
            break;
    }

    cout << "--------------------------------\n";
};

int main()
{
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
        //INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.
    int a = 11, b = 11;
    int m[11][11]={ 1,1,1,1,1,1,1,1,1,1,1,
                    1,0,0,0,0,0,0,0,0,1,1,
                    1,0,0,0,1,1,1,1,0,1,1,
                    1,0,0,0,1,0,1,0,0,1,1,
                    1,1,0,0,1,0,1,1,0,1,1,
                    1,0,0,0,0,0,1,0,0,0,1,
                    1,0,1,1,1,1,1,0,0,0,1,
                    1,0,0,0,0,1,1,0,0,0,1,
                    1,0,0,1,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1,1
                };
    //auxiliar para a parede funcionar
    int aux1=0, aux2=0;
    //Posicao inicial do personagem no console
    int x=5, y=5;
    //Posicao monstro
    int z=1, p=1;
    //Variavel para tecla precionada
    char tecla;

    while(true){
        ///Posiciona a escrita no iicio do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<a;i++){
            for(int j=0;j<b;j++){
                if(i==x && j==y){
                    //if da parede
                    if(m[i][j]==1){
                        x=aux1;
                        y=aux2;
                    }
                    cout<<char(36); //personagem
                    //auxiliares salvando o lugar do personagem
                    aux1=x; aux2=y;
                }

                else{
                    switch (m[i][j]){
                        case 0: cout<<"."; break; //caminho
                        case 1: cout<<char(219); break; //parede
                        //default: cout<<"-"; //erro
                    } //fim switch
                }

            }

            cout<<"\n";
        } //fim for mapa

        ///executa os movimentos
         if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
                case 72: case 'w': ///cima
                    x--;
                break;
                case 80: case 's': ///baixo
                    x++;
                break;
                case 75:case 'a': ///esquerda
                    y--;
                break;
                case 77: case 'd': ///direita
                    y++;
                break;
            }
         }


    } //fim do laco do jogo

    return 0;
} //fim main
