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
    if (!betweenTurns && TurnTimePassed()) {
        playerList[currentPlayer]->isTurn = false;
        playerList[currentPlayer]->isActive = false;
        playerList[currentPlayer]->playerAim.isTurn = false;
    }
    if (!betweenTurns && playerList[currentPlayer]->isTurn == false && playerList[currentPlayer]->isActive == false) {
        if (currentPlayer < (playerNum - 1)) ++currentPlayer;
        else {
            currentPlayer = 0;
            turns++;
        }
        betweenTurns = true;
    }
    if (betweenTurns) {
        currentTurnSeconds = 0;
        if (BetweenTurnTimePassed()) {
            betweenTurns = false;
            playerList[currentPlayer]->isTurn = true;
            playerList[currentPlayer]->playerAim.isTurn = true;
            playerList[currentPlayer]->isActive = true;
            playerList[currentPlayer]->teleportActive = true;
            playerList[currentPlayer]->teleporting = false;
            currentTurnSeconds = secondsPerTurn;
            currentBetweenTurnsSeconds = secondsBetweenTurns;
        }
    }
}

bool TurnManager::TurnTimePassed() {
    currentTurnSeconds -= GetFrameTime();
    return currentTurnSeconds <= 0;
}

bool TurnManager::BetweenTurnTimePassed() {
    currentBetweenTurnsSeconds -= GetFrameTime();
    return currentBetweenTurnsSeconds <= 0;
}

void TurnManager::Update() { CheckTurn(); }

void TurnManager::Draw() {
    if (ended) return;
    std::string s = std::to_string(currentPlayer + 1);
    const char* cstr = s.c_str();
    DrawText("player", 300, 20, 20, WHITE);
    DrawText(cstr, 370, 20, 20, WHITE);
    DrawText(TextFormat("Turn: %01i", turns), 20, 20, 20, WHITE);
    DrawText(TextFormat("Time left: %.1f seconds", currentTurnSeconds), 20, 40, 20, WHITE);
}

void TurnManager::CheckPlayerHit(Explosion exp) {
    for (int i=0;i < playerList.size();++i) {
        if (CheckCollisionCircleRec(exp.position, exp.radius, playerList[i]->GetRectangle())) playerList[i]->GetDamaged(exp.position);
    }

}