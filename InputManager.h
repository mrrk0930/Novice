#pragma once

#include <Novice.h>
#include <cstring>

class InputManager {
public:
	// 初期化
	InputManager();

	// 毎フレーム呼ぶ
	void Update();

	// キーを押している
	bool PushKey(int key);

	// キーを押した瞬間
	bool TriggerKey(int key);

private:
	char keys_[256];
	char preKeys_[256];
};