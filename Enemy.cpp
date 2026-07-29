#include "Enemy.h"
#include <Novice.h>

Enemy::Enemy() {
	x_ = 640.0f;
	y_ = 100.0f;

	speed_ = 3.0f;

	radius_ = 20.0f;

	isAlive_ = true;
}

void Enemy::Update() {
	if (!isAlive_) {
		return;
	}

	// 下へ移動
	y_ += speed_;

	// 画面外へ行ったら上へ戻る
	if (y_ > 720) {
		y_ = -20;
	}
}

void Enemy::Draw() {
	if (!isAlive_) {
		return;
	}

	Novice::DrawEllipse((int)x_, (int)y_, (int)radius_, (int)radius_, 0.0f, RED, kFillModeSolid);
}

float Enemy::GetX() const { return x_; }

float Enemy::GetY() const { return y_; }

float Enemy::GetRadius() const { return radius_; }

bool Enemy::IsAlive() const { return isAlive_; }

void Enemy::Destroy() { isAlive_ = false; }