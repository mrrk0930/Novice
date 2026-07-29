#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "IState.h"
#include "Player.h"

// 前方宣言
class Game;

class StageState : public IState {
public:
	// コンストラクタ
	StageState();

	// 更新
	void Update(Game* game) override;

	// 描画
	void Draw() override;

private:
	Player player_;

	Enemy enemy_;

	Bullet bullet_;
};