#pragma once
#include "IState.h"

// 前方宣言
class Game;

class ClearState : public IState {
public:
	// 更新
	void Update(Game* game) override;

	// 描画
	void Draw() override;
};