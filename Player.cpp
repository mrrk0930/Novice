#include "Player.h"
#include <Novice.h>

Player::Player() {
	x_ = 640.0f;
	y_ = 600.0f;

	speed_ = 5.0f;
}

void Player::Update(InputManager* input) {
	// 左
	if (input->PushKey(DIK_A)) {
		x_ -= speed_;
	}

	// 右
	if (input->PushKey(DIK_D)) {
		x_ += speed_;
	}

	// 上
	if (input->PushKey(DIK_W)) {
		y_ -= speed_;
	}

	// 下
	if (input->PushKey(DIK_S)) {
		y_ += speed_;
	}

	// 画面外へ出ないようにする
	if (x_ < 20.0f) {
		x_ = 20.0f;
	}

	if (x_ > 1260.0f) {
		x_ = 1260.0f;
	}

	if (y_ < 20.0f) {
		y_ = 20.0f;
	}

	if (y_ > 700.0f) {
		y_ = 700.0f;
	}
}

void Player::Draw() {
	// 白い三角形
	Novice::DrawTriangle(

	    (int)x_, (int)(y_ - 20),

	    (int)(x_ - 20), (int)(y_ + 20),

	    (int)(x_ + 20), (int)(y_ + 20),

	    WHITE, kFillModeSolid);
}

float Player::GetX() const { return x_; }

float Player::GetY() const { return y_; }