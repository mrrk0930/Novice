#pragma once

class Bullet {
public:
	// コンストラクタ
	Bullet();

	// 発射
	void Shot(float x, float y);

	// 更新
	void Update();

	// 描画
	void Draw();

	// 発射中か
	bool IsShot() const;

	// 弾を消す
	void Destroy();

	// 座標取得
	float GetX() const;
	float GetY() const;

	// サイズ取得
	float GetSize() const;

private:
	float x_;
	float y_;

	float speed_;

	float size_;

	bool isShot_;
};