#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Enum para tipos de celulas no mapa
enum CellType {
    WALL = 1,
    FLOOR = 0,
    TRAP = 3,
    STAIRS = 4
};

// Structs para entidades
struct Player {
    int x, y;         // Posicao
    int character;    // Skin (ASCII)
    int health;       // Vida
    int strength;     // Forca
    int level;        // Nivel
    int exp;          // Experiencia
    vector<string> inventory; // Inventario
    int score;        // Pontuacao
};

struct Enemy {
    int x, y;         // Posicao
    int health;       // Vida
    int strength;     // Forca
    int level;        // Nivel
    int expReward;    // Experiencia dada ao jogador
    bool isBoss;      // Indica se e o chefe final
};

struct Item {
    int x, y;         // Posicao
    string type;      // Tipo de item
};

// Funcao para exibir o menu
int menu() {
    int op = 0;
    system("cls");
    cout << "--------------------------------\n";
    cout << "1 - Iniciar\n2 - Ajuda\n3 - Creditos\n";
    cout << "--------------------------------\n";
    cin >> op;
    switch (op) {
        case 1:
            cout << "Jogo iniciado\n";
            Sleep(1000);
            system("cls");
            return op;
        case 2: {
            int auxMenu = 0;
            do {
                system("cls");
                cout << "Ajuda\n";
                cout << "1 - Funcionamento\n2 - Itens\n3 - Movimentacao\n4 - Voltar\n";
                cout << "Escolha uma opcao: ";
                cin >> auxMenu;
                switch (auxMenu) {
                    case 1:
                        system("cls");
                        cout << "Funcionamento\n";
                        cout << "Explore as masmorras, colete itens, lute contra inimigos e avance de nivel utilizando as escadas.\n";
                        cout << "Cuidado com armadilhas que reduzem sua vida.\n";
                        cout << "Derrote todos os inimigos para avancar de nivel.\n";
                        cout << "\nPressione Enter para continuar...\n";
                        cin.ignore();
                        cin.get();
                        break;
                    case 2:
                        system("cls");
                        cout << "Itens\n";
                        cout << "Espada: Aumenta a forca em 5 pontos\n";
                        cout << "Pocao de Cura: Recupera 15 de vida\n";
                        cout << "Totem: Aumenta a pontuacao em 5 pontos\n";
                        cout << "Use itens pressionando 'u' durante o jogo.\n";
                        cout << "\nPressione Enter para continuar...\n";
                        cin.ignore();
                        cin.get();
                        break;
                    case 3:
                        system("cls");
                        cout << "Movimentacao\n";
                        cout << "Use as teclas:\n";
                        cout << "'w' - Mover para cima\n";
                        cout << "'s' - Mover para baixo\n";
                        cout << "'a' - Mover para esquerda\n";
                        cout << "'d' - Mover para direita\n";
                        cout << "'u' - Usar um item\n";
                        cout << "'q' - Sair do jogo\n";
                        cout << "\nPressione Enter para continuar...\n";
                        cin.ignore();
                        cin.get();
                        break;
                }
            } while (auxMenu != 4);
            break;
        }
        case 3:
            system("cls");
            cout << "Creditos\n";
            cout << "Um jogo criado por: Davi, Pedro, Peterson\n";
            cout << "Programacao: Davi, Pedro, Peterson\n";
            cout <<"Ambientação: Davi, Pedro, Peterson\n";
            cout << "Agradecimentos: Prof. Alex Luciano Roesler Rese\n";
            cout << "\nPressione Enter para continuar...\n";
            cin.ignore();
            cin.get();
            break;
    }
    return 0;
}

// Funcao para atualizar o mapa descoberto
void updateDiscoveredMap(vector<vector<int>>& discoveredMap, const vector<vector<int>>& map, int playerX, int playerY, int radius) {
    int rows = map.size();
    int cols = map[0].size();
    for (int i = max(0, playerX - radius); i <= min(rows - 1, playerX + radius); i++) {
        for (int j = max(0, playerY - radius); j <= min(cols - 1, playerY + radius); j++) {
            double distancia = sqrt(pow(i - playerX, 2) + pow(j - playerY, 2));
            if (distancia <= radius) {
                discoveredMap[i][j] = map[i][j];
            }
        }
    }
}

// Funcao para exibir o mapa com fog-of-war
void displayMap(const vector<vector<int>>& map, const vector<vector<int>>& discoveredMap, const Player& player, const vector<Enemy>& enemies, const vector<Item>& items, HANDLE out, int visibleRadius) {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(out, coord);

    int rows = map.size();
    int cols = map[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == player.x && j == player.y) {
                cout << char(player.character);
            } else {
                bool printed = false;
                double distancia = sqrt(pow(i - player.x, 2) + pow(j - player.y, 2));
                if (distancia <= visibleRadius) {
                    for (const auto& enemy : enemies) {
                        if (i == enemy.x && j == enemy.y) {
                            cout << 'E';
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) {
                        for (const auto& item : items) {
                            if (i == item.x && j == item.y) {
                                cout << 'I';
                                printed = true;
                                break;
                            }
                        }
                    }
                }
                if (!printed) {
                    if (discoveredMap[i][j] != -1) {
                        switch (discoveredMap[i][j]) {
                            case WALL: cout << char(219); break;
                            case FLOOR: cout << ' '; break;
                            case TRAP: cout << '^'; break;
                            case STAIRS: cout << '>'; break;
                            default: cout << ' ';
                        }
                    } else {
                        cout << ' ';
                    }
                }
            }
        }
        cout << "\n";
    }
    cout << "Vida: " << player.health << " | Forca: " << player.strength << " | Nivel: " << player.level
         << " | Exp: " << player.exp << " | Pontuacao: " << player.score << "\n";
    cout << "Inventario: ";
    for (const auto& item : player.inventory) cout << item << " ";
    cout << "\n";
}

// Funcao de combate
void combat(Player& player, Enemy& enemy) {
    system("cls");
    cout << "Combate iniciado contra " << (enemy.isBoss ? "Chefe" : "Inimigo") << " (Nivel " << enemy.level << ")!\n";
    while (player.health > 0 && enemy.health > 0) {
        enemy.health -= player.strength;
        if (enemy.health > 0) player.health -= enemy.strength;
        cout << "Sua vida: " << player.health << " | Vida do inimigo: " << enemy.health << "\n";
        Sleep(500);
    }
    if (player.health > 0) {
        cout << "Inimigo derrotado!\n";
    } else {
        cout << "Voce foi derrotado...\n";
    }
    Sleep(1000);
    system("cls");
}

// Funcao para mover o jogador
void movePlayer(Player& player, char direction, vector<vector<int>>& map, vector<Enemy>& enemies, vector<Item>& items) {
    int newX = player.x, newY = player.y;

    if (direction == 'w') newX--; /// Cima
    else if (direction == 's') newX++; ///Baixo
    else if (direction == 'a') newY--; ///Esquerda
    else if (direction == 'd') newY++; ///Direita

    if (newX >= 0 && newX < static_cast<int>(map.size()) && newY >= 0 && newY < static_cast<int>(map[0].size())) {
        if (map[newX][newY] == WALL) {
            cout << "Voce bateu em uma parede!\n";
            Sleep(200);
            return;
        }
        // Coleta itens
        for (auto it = items.begin(); it != items.end(); ) {
            if (newX == it->x && newY == it->y) {
                cout << "Item coletado: " << it->type << "\n";
                Sleep(700);
                system("cls");
                player.inventory.push_back(it->type);
                player.score += 5;
                it = items.erase(it);
            } else {
                ++it;
            }
        }
        // Combate com inimigos
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            if (newX == it->x && newY == it->y) {
                combat(player, *it);
                if (it->health <= 0) {
                    player.exp += it->expReward;
                    player.score += it->level * 10;
                    it = enemies.erase(it);
                } else {
                    ++it;
                }
                return;
            } else {
                ++it;
            }
        }
        // Verifica armadilhas
        if (map[newX][newY] == TRAP) {
            player.health -= 10;
            cout << "Voce pisou em uma armadilha! Vida -10\n";
            Sleep(1000);
        }
        player.x = newX;
        player.y = newY;
    }
}

// Funcao para usar itens
void useItem(Player& player) {
    if (player.inventory.empty()) {
        system("cls");
        cout << "Inventario vazio!\n";
        cout << "Pressione Enter para continuar...\n";
        cin.ignore();
        cin.get();
        system("cls");
        return;
    }
    system("cls");
    cout << "Usar qual item? (Digite o numero)\n";
    for (size_t i = 0; i < player.inventory.size(); i++) {
        cout << i << ": " << player.inventory[i] << "\n";
    }
    int choice;
    cin >> choice;
    if (choice >= 0 && choice < static_cast<int>(player.inventory.size())) {
        string item = player.inventory[choice];
        if (item == "Pocao de Cura") {
            player.health += 15;
            cout << "Pocao de Cura usada! Vida +15\n";
        } else if (item == "Espada") {
            player.strength += 5;
            cout << "Espada equipada! Forca +5\n";
        } else if (item == "Totem") {
            player.score += 5;
            cout << "Totem usado! Pontuacao +5\n";
        }
        player.inventory.erase(player.inventory.begin() + choice);
        cout << "Pressione Enter para continuar...\n";
        cin.ignore();
        cin.get();
    } else {
        cout << "Escolha invalida!\n";
        cout << "Pressione Enter para continuar...\n";
        cin.ignore();
        cin.get();
    }
    system("cls");
}

// Funcao para mover inimigos
void moveEnemies(vector<Enemy>& enemies, const vector<vector<int>>& map) {
    for (auto& enemy : enemies) {
        int attempts = 0;
        while (attempts < 10) {
            int dir = rand() % 4;
            int newX = enemy.x;
            int newY = enemy.y;
            if (dir == 0) newX--; // cima
            else if (dir == 1) newX++; // baixo
            else if (dir == 2) newY--; // esquerda
            else if (dir == 3) newY++; // direita
            if (newX >= 0 && newX < static_cast<int>(map.size()) && newY >= 0 && newY < static_cast<int>(map[0].size()) && map[newX][newY] != WALL) {
                enemy.x = newX;
                enemy.y = newY;
                break;
            }
            attempts++;
        }
    }
}

// Funcao para inicializar o nivel
void initializeLevel(vector<vector<int>>& map, Player& player, vector<Enemy>& enemies, vector<Item>& items, int levelNum) {
    map = {
        {1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,1,0,0,0,1},
        {1,1,1,0,1,0,1,1,0,1,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,0,1},
        {1,0,0,0,0,1,0,0,0,0,1},
        {1,0,1,0,1,0,0,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,4,1}, // Escadas em [9][9]
        {1,1,1,1,1,1,1,1,1,1,1}
    };
    player.x = 1; player.y = 1;
    enemies.clear();
    items.clear();
    srand(time(0));
    for (int i = 0; i < levelNum + 1; i++) {
        Enemy enemy = {rand() % 9 + 1, rand() % 9 + 1, 20 + levelNum * 5, 5 + levelNum * 2, levelNum, 10 + levelNum * 5, false};
        if (map[enemy.x][enemy.y] == FLOOR) enemies.push_back(enemy);
    }
    if (levelNum == 3) {
        Enemy boss = {8, 8, 50, 15, 3, 50, true};
        enemies.push_back(boss);
    }
    items.push_back({3, 3, "Pocao de Cura"});
    items.push_back({5, 5, "Espada"});
    items.push_back({7, 7, "Totem"});
}

int main() {
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
    // Menu inicial
    while (menu() != 1);

    // Inicializacao do jogador
    Player player = {1, 1, 36, 100, 10, 1, 0, {}, 0};
    vector<Enemy> enemies;
    vector<Item> items;
    vector<vector<int>> map;
    vector<vector<int>> discoveredMap;
    int currentLevel = 1;
    int visibleRadius = 3;

    initializeLevel(map, player, enemies, items, currentLevel);
    discoveredMap = vector<vector<int>>(map.size(), vector<int>(map[0].size(), -1));

    bool gameRunning = true;
    bool needsRedraw = true;
    while (gameRunning) {
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == 'q') gameRunning = false;
            else if (tecla == 'u') {
                useItem(player);
                needsRedraw = true;
            } else {
                movePlayer(player, tecla, map, enemies, items);
                updateDiscoveredMap(discoveredMap, map, player.x, player.y, visibleRadius);
                moveEnemies(enemies, map);
                needsRedraw = true;
            }
        }

        // Verifica condicoes de vitoria/derrota
        if (player.health <= 0) {
            system("cls");
            cout << "GAME OVER\nPontuacao Final: " << player.score << "\n";
            gameRunning = false;
        } else if (map[player.x][player.y] == STAIRS && currentLevel < 3) {
            if (enemies.empty()) {
                currentLevel++;
                initializeLevel(map, player, enemies, items, currentLevel);
                discoveredMap = vector<vector<int>>(map.size(), vector<int>(map[0].size(), -1));
                cout << "Subindo para o nivel " << currentLevel << "...\n";
                //Sleep(1000);
                needsRedraw = true;
            } else {
                cout << "Voce deve derrotar todos os inimigos para prosseguir.\n";
                player.x--;
                Sleep(800);
                system("cls");
            }
        } else if (currentLevel == 3 && enemies.empty()) {
            system("cls");
            cout << "VOCE VENCEU!\nPontuacao Final: " << player.score << "\n";
            gameRunning = false;
        }

        if (needsRedraw) {
            displayMap(map, discoveredMap, player, enemies, items, out, visibleRadius);
            needsRedraw = false;
        }
    }

    cout << "Pressione Enter para sair...\n";
    cin.ignore();
    cin.get();
    return 0;
}
