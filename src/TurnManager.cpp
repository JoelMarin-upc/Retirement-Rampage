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
            playerList[currentPlayer]->generateWind = true;
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
    DrawTexture(topHUD, GetScreenWidth() / 2 - topHUD.width / 2, 0/*750, 250,*/, WHITE);

    std::string s = std::to_string(currentPlayer + 1);
    const char* cstr = s.c_str();
    DrawText("Player", 550, 20, 30, WHITE);
    DrawText(cstr, 655, 20, 30, WHITE);
    const char* cstr2 = playerList[currentPlayer]->currentWeapon.c_str();
    DrawText(cstr2, 550, 50, 30, ORANGE);

    DrawText(TextFormat("Turn: %01i", turns), 100, 20, 30, WHITE);
    DrawText(TextFormat("Time left: %.1f seconds", currentTurnSeconds), 100, 50, 30, RED);

    //draw wind
    DrawRectangle(1500 - 200, 20, 400 + 60, 20, WHITE);
    DrawRectangle(1500, 20, 60, 20, GRAY);
    
    const char* cstr3 = "WIND";
    DrawText(cstr3, 1505, 20, 20, BLACK);

    if (playerList[currentPlayer]->isTurn) {
        if (playerList[currentPlayer]->wind > 0) DrawRectangle(1500 + 60, 20, playerList[currentPlayer]->wind * 20, 20, BLUE);
        else DrawRectangle(1500 + (playerList[currentPlayer]->wind * 20), 20, -playerList[currentPlayer]->wind * 20, 20, BLUE);

        
    }

    //draw charge bar
    DrawRectangle(1500 - 200, 60, 400 + 60, 20, WHITE);
    playerList[currentPlayer]->playerLauncher.DrawBar();
    playerList[currentPlayer]->playerUnderBullet.DrawBar();
   
    (*playerList[currentPlayer]).DrawHUD();
}

void TurnManager::CheckPlayerHit(Explosion exp) {
    for (int i=0;i < playerList.size();++i) {
        if (CheckCollisionCircleRec(exp.position, exp.radius, playerList[i]->GetRectangle())) playerList[i]->GetDamaged(exp.position);
    }

}