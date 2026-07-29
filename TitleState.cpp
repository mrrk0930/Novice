#include "TitleState.h"
#include "Game.h"
#include "StageState.h"

#include <Novice.h>

void TitleState::Update(Game* game) {
	// Spaceキーでゲーム開始
	if (game->GetInput()->TriggerKey(DIK_SPACE)) {
		game->ChangeState(new StageState());
	}
}

void TitleState::Draw() {
	Novice::ScreenPrintf(540, 250, "TITLE");

	Novice::ScreenPrintf(470, 320, "PRESS SPACE KEY");
}