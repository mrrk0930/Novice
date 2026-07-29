#include "ClearState.h"
#include "Game.h"
#include "TitleState.h"

#include <Novice.h>

void ClearState::Update(Game* game) {
	// Spaceキーでタイトルへ戻る
	if (game->GetInput()->TriggerKey(DIK_SPACE)) {
		game->ChangeState(new TitleState());
	}
}

void ClearState::Draw() {
	Novice::ScreenPrintf(560, 260, "CLEAR!!");

	Novice::ScreenPrintf(430, 330, "PRESS SPACE KEY TO TITLE");
}