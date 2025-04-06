/**
    Estrutura inicial para um jogo
    vers o: 0.1 (Prof. Alex,  Adaptado Prof. Felski)
*/
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cmath>

using namespace std;

void alterarMatriz(int matriz[][11], int x, int y, int raio, int linhas, int colunas, int m[][11]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            // Calculando a distância euclidiana do ponto (i, j) até o centro (x, y)
            double distancia = sqrt(pow(i - x, 2) + pow(j - y, 2));
            // Se a distância for menor ou igual ao raio, alteramos o valor
            if (distancia <= raio) {
                matriz[i][j] = m[i][j];
            }
        }
    }
}

struct player{
    int x, y; //posicao do personagem
    int character; //Skin do personagem
    int vida; //vida do personagem
    int forca; //forca do personagem
    int level; //level do personagem
    int exp; //experiencia do personagem
};

struct monstro{
    int x, y; //posicao do monstro
    int vida; //vida do monstro
    int forca; //forca do monstro
    int level; //level do monstro
    int expToPlayer; //experiencia que o monstro da para o player
};

struct bau{
    int x, y; //posicao do item
    string item; //item que o bau tem
};

int menu(){
    int op=0, auxMenu=0;
    system("cls");
    cout << "--------------------------------\n";
    cout << "1 - Iniciar\n2 - Ajuda\n3 - Creditos:\n";
    cout << "--------------------------------\n";
    cin >> op;
    switch(op){
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
                switch(auxMenu){
                    case 1: break;
                    case 2:
                        system("cls");
                        cout << "Espada: Aumenta a forca do personagem em 5 pontos\n";
                        cout << "Pocao de cura: Recupera a vida em 15\n";
                        cout << "Chave: Abre portas trancadas\n";
                        cout << "Totem: Aumenta a pontuacao em 5 pontos\n";
                        cout << "\nPressione qualquer botao para continuar...:\n";
                        cin.ignore();
                        cin.get();
                        break;
                    case 3: break;
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
    int M_aux[11][11]={4};
    //Variavel auxiliar geral
    int aux=0;
    //auxiliar para a parede funcionar
    int aux1=0, aux2=0;
    //Posicao inicial do personagem no console
    int x=5, y=5;
    //Variavel para tecla precionada
    char tecla;
     // Alterando a matriz com base na coordenada e no raio
    int raio=3;
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
    p1.character = 36; //skin do personagem
    p1.vida = 100;
    p1.forca = 20;
    p1.level = 15;
    p1.exp = 0;
    ///Criação do personagem - Fim


    while(true){
        ///Posiciona a escrita no iicio do console
        int x=p1.x, y=p1.y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        alterarMatriz(M_aux, x, y, raio, 11, 11, m);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<a;i++){
            for(int j=0;j<b;j++){
                if(i==p1.x && j==p1.y){
                    //if da parede
                    if(M_aux[i][j]==1){
                        p1.x=aux1;
                        p1.y=aux2;
                    }
                    cout<<char(p1.character); //personagem
                    //auxiliares salvando o lugar do personagem
                    aux1=p1.x; aux2=p1.y;
                }

                else{
                    switch (M_aux[i][j]){
                        case 0: cout<<" ";break; //caminho não descoberto
                        case 1: cout<<char(219); break; //parede

                        case 2: cout<<char(2); break; //Porta
                        //case 3: cout<<":"; break; //Passagem
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