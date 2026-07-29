#include "InputManager.h"

InputManager::InputManager() {
	memset(keys_, 0, sizeof(keys_));
	memset(preKeys_, 0, sizeof(preKeys_));
}

void InputManager::Update() {
	memcpy(preKeys_, keys_, sizeof(keys_));

	Novice::GetHitKeyStateAll(keys_);
}

bool InputManager::PushKey(int key) { return keys_[key]; }

bool InputManager::TriggerKey(int key) { return keys_[key] && !preKeys_[key]; }