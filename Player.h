#pragma once

#include "InputManager.h"

class Player {
public:
	// 初期化
	Player();

	// 更新
	void Update(InputManager* input);

	// 描画
	void Draw();

	// 座標取得
	float GetX() const;
	float GetY() const;

private:
	float x_;
	float y_;

	float speed_;
};