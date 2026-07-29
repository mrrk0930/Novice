#pragma once
#include "IState.h"
#include "InputManager.h"

class Game {
public:
	// コンストラクタ
	Game();

	// デストラクタ
	~Game();

	// 更新
	void Update();

	// 描画
	void Draw();

	// シーン変更
	void ChangeState(IState* state);

	// 入力取得
	InputManager* GetInput();

private:
	// 入力管理
	InputManager input_;

	// 現在のシーン
	IState* state_;
};