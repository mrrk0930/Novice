#include "MathFunc.h"
#include <Novice.h>
#include <cmath>
#include <imgui.h>


const char kWindowTitle[] = "GC2B_05_ムロサキ_リク_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	const float kWindowWidth = 1280.0f;
	const float kWindowHeight = 720.0f;

	// カメラ
	Vector3 cameraTranslate{0.0f, 1.9f, -6.4f};

	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};

	AABB aabb1{
	    .min{-0.5f, -0.5f, -0.5f},
	    .max{0.0f,  0.0f,  0.0f },
	};

	AABB aabb2{
	    .min{0.2f, 0.2f, 0.2f},
	    .max{1.0f, 1.0f, 1.0f},
	};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 viewProjectionMatrix = MakeViewProjectionMatrix(cameraTranslate, cameraRotate, kWindowWidth, kWindowHeight);

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight, 0.0f, 1.0f);

		UpdateAABBImGui(aabb1, aabb2);

		// min,maxの補正
		if (aabb1.min.x > aabb1.max.x)
			std::swap(aabb1.min.x, aabb1.max.x);
		if (aabb1.min.y > aabb1.max.y)
			std::swap(aabb1.min.y, aabb1.max.y);
		if (aabb1.min.z > aabb1.max.z)
			std::swap(aabb1.min.z, aabb1.max.z);

		if (aabb2.min.x > aabb2.max.x)
			std::swap(aabb2.min.x, aabb2.max.x);
		if (aabb2.min.y > aabb2.max.y)
			std::swap(aabb2.min.y, aabb2.max.y);
		if (aabb2.min.z > aabb2.max.z)
			std::swap(aabb2.min.z, aabb2.max.z);

		bool isHit = IsCollisionAABB(aabb1, aabb2);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, isHit ? RED : WHITE);

		DrawAABB(aabb2, viewProjectionMatrix, viewportMatrix, WHITE);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
};
