#pragma once

// 前方宣言
class Game;

class IState {
public:
	// デストラクタ
	virtual ~IState() {}

	// 更新
	virtual void Update(Game* game) = 0;

	// 描画
	virtual void Draw() = 0;
};