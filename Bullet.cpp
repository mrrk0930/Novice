#include "Bullet.h"
#include <Novice.h>

Bullet::Bullet() {
	x_ = 0.0f;
	y_ = 0.0f;

	speed_ = 8.0f;

	size_ = 10.0f;

	isShot_ = false;
}

// 発射
void Bullet::Shot(float x, float y) {
	if (isShot_) {
		return;
	}

	x_ = x;
	y_ = y;

	isShot_ = true;
}

// 更新
void Bullet::Update() {
	if (!isShot_) {
		return;
	}

	// 上へ移動
	y_ -= speed_;

	// 画面外
	if (y_ < 0) {
		isShot_ = false;
	}
}

// 描画
void Bullet::Draw() {
	if (!isShot_) {
		return;
	}

	Novice::DrawBox(
	    (int)(x_ - size_ / 2), (int)(y_ - size_ / 2),

	    (int)size_, (int)size_,

	    0.0f,

	    BLACK,

	    kFillModeSolid);
}

// 発射中？
bool Bullet::IsShot() const { return isShot_; }

// 消す
void Bullet::Destroy() { isShot_ = false; }

float Bullet::GetX() const { return x_; }

float Bullet::GetY() const { return y_; }

float Bullet::GetSize() const { return size_; }