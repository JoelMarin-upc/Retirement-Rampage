#include "TurnManager.h"

void TurnManager::AddPlayer(Player* player) {
    playerList[currentPlayer] = player;
    currentPlayer++;
}

void TurnManager::Start() {
    currentPlayer = 0;
    turns = 1;
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
    if (TurnTimePassed())
    {
        playerList[currentPlayer]->isTurn = false;
        playerList[currentPlayer]->playerAim.isTurn = true;
    }
    if (playerList[currentPlayer]->isTurn == false) {
        if (currentPlayer < (playerNum - 1)) ++currentPlayer;
        else {
            currentPlayer = 0;
            turns++;
        }
        playerList[currentPlayer]->isTurn = true;
        playerList[currentPlayer]->playerAim.isTurn = true;
        currentTurnSeconds = secondsPerTurn;
        std::cout << currentPlayer;
    }
}

bool TurnManager::TurnTimePassed() {
    currentTurnSeconds -= GetFrameTime();
    return currentTurnSeconds <= 0;
}

void TurnManager::Update() { CheckTurn(); }

void TurnManager::Draw() {
    if (ended) return;
    std::string s = std::to_string(currentPlayer + 1);
    const char* cstr = s.c_str();
    DrawText("player", 300, 20, 20, BLACK);
    DrawText(cstr, 370, 20, 20, BLACK);
    DrawText(TextFormat("Turn: %01i", turns), 20, 20, 20, BLACK);
    DrawText(TextFormat("Time left: %.1f seconds", currentTurnSeconds), 20, 40, 20, BLACK);
}

