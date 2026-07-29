#pragma once

class Enemy {
public:
	// コンストラクタ
	Enemy();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 当たり判定用
	float GetX() const;
	float GetY() const;
	float GetRadius() const;

	// 生存状態
	bool IsAlive() const;

	// 撃破
	void Destroy();

private:
	float x_;
	float y_;

	float speed_;

	float radius_;

	bool isAlive_;
};