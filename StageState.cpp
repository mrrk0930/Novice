#include "StageState.h"
#include "ClearState.h"
#include "Game.h"
#include <Novice.h>

StageState::StageState() {}

void StageState::Update(Game* game) {
	// プレイヤー更新
	player_.Update(game->GetInput());

	// 敵更新
	enemy_.Update();

	// 弾更新
	bullet_.Update();

	// Spaceで弾発射
	if (game->GetInput()->TriggerKey(DIK_SPACE)) {
		bullet_.Shot(player_.GetX(), player_.GetY() - 20.0f);
	}

	//========================
	// 当たり判定
	//========================

	if (bullet_.IsShot() && enemy_.IsAlive()) {
		float dx = bullet_.GetX() - enemy_.GetX();
		float dy = bullet_.GetY() - enemy_.GetY();

		float r = enemy_.GetRadius();

		if (dx * dx + dy * dy <= r * r) {
			enemy_.Destroy();

			bullet_.Destroy();

			// クリア画面へ
			game->ChangeState(new ClearState());
		}
	}
}

void StageState::Draw() {
	player_.Draw();

	enemy_.Draw();

	bullet_.Draw();

	Novice::ScreenPrintf(10, 10, "STAGE");
}