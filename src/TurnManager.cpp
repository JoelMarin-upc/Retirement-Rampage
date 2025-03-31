#include "TurnManager.h"

void TurnManager::AddPlayer(Player* player) {
    playerList[currentPlayer] = player;
    currentPlayer++;
}

void TurnManager::Start() {
    currentPlayer = 0;
    playerList[currentPlayer]->isTurn = true;
    playerList[currentPlayer]->playerAim.isTurn = true;
}

void TurnManager::End() {
    for (int i = 0; i < playerList.size(); i++)
    {
        playerList[currentPlayer]->isTurn = false;
        playerList[currentPlayer]->playerAim.isTurn = false;
    }
    ended = true;
}

void TurnManager::CheckTurn() {
    if (ended) return;
    if (playerList[currentPlayer]->isTurn == false) {
        if (currentPlayer < (playerNum - 1)) ++currentPlayer;
        else currentPlayer = 0;
        playerList[currentPlayer]->isTurn = true;
        playerList[currentPlayer]->playerAim.isTurn = true;
        std::cout << currentPlayer;
    }
}

void TurnManager::Update() { CheckTurn(); }

void TurnManager::Draw() {
    if (ended) return;
    std::string s = std::to_string(currentPlayer + 1);
    const char* cstr = s.c_str();
    DrawText("player", 300, 20, 20, BLACK);
    DrawText(cstr, 370, 20, 20, BLACK);
}

