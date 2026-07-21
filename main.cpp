#include "MathFunc.h"
#include <Novice.h>
#include <cmath>
#include <imgui.h>
#include <algorithm>

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

	Vector3 controlPoints[3] = {
	    {-0.8f, 0.58f, 1.0f},
        {1.76f,  1.0f, -0.3f},
        {0.94f,  -0.7f, 2.3f}
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

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Matrix4x4 viewProjectionMatrix = MakeViewProjectionMatrix(cameraTranslate, cameraRotate, kWindowWidth, kWindowHeight);

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight, 0.0f, 1.0f);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		UpdateBezierImGui(controlPoints);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);


		Sphere pointSphere;

		pointSphere.radius = 0.01f;

		pointSphere.center = controlPoints[0];
		DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, BLACK);

		pointSphere.center = controlPoints[1];
		DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, BLACK);

		pointSphere.center = controlPoints[2];
		DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, BLACK);

		DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], viewProjectionMatrix, viewportMatrix, BLUE);

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
