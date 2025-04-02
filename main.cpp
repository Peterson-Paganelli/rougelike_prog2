/**
    Estrutura inicial para um jogo
    vers�o: 0.1 (Prof. Alex,  Adaptado Prof. Felski)
*/
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

struct player{
    int x, y; //posicao do personagem
    int vida; //vida do personagem
    int forca; //forca do personagem
    int level; //level do personagem
    int exp; //experiencia do personagem
};

int menu(){
    int op=0, auxMenu=0;
    system("cls");
    cout << "--------------------------------\n";
    cout << "1 - Iniciar\n2 - Ajuda\n3 - Creditos:\n";
    cout << "--------------------------------\n";
    cin >> op;
    switch(op)
    {
        case 1:
            cout << "Jogo iniciado\n";
            return op;
        case 2:
            do{
                system("cls");
                cout << "Ajuda\n";
                cout << "1 - Funcionamento\n2 - Itens\n3 - movimentacao\n4 - Voltar\n";
                cout << "Escolha uma opcao: ";
                cin >> auxMenu;
                if(auxMenu == 4) {
                    break;
                }
            } while(auxMenu != 4);
            break;
        case 3:
            cout << "Creditos\n";
            cout << "Um jogo criado por:\n";
            cout << "Som e musica por:\n";
            cout << "Desenvolvimento:\n";
            cout << "Ambientacao:\n";
            cout << "Programacao:\n";
            cout << "Arte:\n";
            cout << "Agradecimentos:\n";
            cout << "Apoio:\n";
            cout << "\nPressione qualquer botao para continuar...:\n";
            cin.ignore();
            cin.get();
            break;
    }
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

    ///Variaveis do jogo
    //--------------------------------------------------//
    int a = 11, b = 11;
    int m[11][11]={ 1,1,1,1,1,1,1,1,1,1,1,
                    1,0,0,0,0,0,0,0,0,1,1,
                    1,0,0,0,1,1,1,1,0,1,1,
                    1,0,0,0,1,0,1,0,0,1,1,
                    1,1,0,0,1,0,1,1,0,1,1,
                    1,0,0,0,0,0,1,0,0,0,1,
                    1,0,1,1,1,1,1,0,0,0,1,
                    1,0,0,0,0,1,1,0,0,0,1,
                    1,0,0,1,0,0,0,0,0,0,2,
                    1,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1,1
                };
    //Variavel auxiliar geral
    int aux=0;
    //auxiliar para a parede funcionar
    int aux1=0, aux2=0;
    //Posicao inicial do personagem no console
    int x=5, y=5;
    //Variavel para tecla precionada
    char tecla;
    //--------------------------------------------------//

    while(aux != 1){
        aux = menu();
    };
    ///Limpa a tela do console
    system("cls");

    ///Criação do personagem - Inicio
    player p1;

    p1.x = x; //posicao inicial do personagem
    p1.y = y; //posicao inicial do personagem
    p1.vida = 100;
    p1.forca = 20;
    p1.level = 15;
    p1.exp = 0;
    ///Criação do personagem - Fim


    while(true){
        ///Posiciona a escrita no iicio do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<a;i++){
            for(int j=0;j<b;j++){
                if(i==p1.x && j==p1.y){
                    //if da parede
                    if(m[i][j]==1){
                        p1.x=aux1;
                        p1.y=aux2;
                    }
                    cout<<char(36); //personagem
                    //auxiliares salvando o lugar do personagem
                    aux1=p1.x; aux2=p1.y;
                }

                else{
                    switch (m[i][j]){
                        case 0: cout<<"."; break; //caminho
                        case 1: cout<<char(219); break; //parede

                        case 2: cout<<char(2); break; //Passagem
                        
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
                    p1.x--;
                break;
                case 80: case 's': ///baixo
                    p1.x++;
                break;
                case 75:case 'a': ///esquerda
                    p1.y--;
                break;
                case 77: case 'd': ///direita
                    p1.y++;
                break;
            }
         }


    } //fim do laco do jogo

    return 0;
} //fim main
