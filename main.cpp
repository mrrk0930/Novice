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

	// 球
	Sphere sphere1{
	    {-1.0f, 0.0f, 0.0f},
        0.5f
    };

	Sphere sphere2{
	    {1.0f, 0.0f, 0.0f},
        0.5f
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
		
		// ImGui
		ImGui::Begin("Sphere");

		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		ImGui::Separator();

		ImGui::Text("Sphere1");

		ImGui::DragFloat3("Center1", &sphere1.center.x, 0.01f);

		ImGui::DragFloat("Radius1", &sphere1.radius, 0.01f);

		ImGui::Separator();

		ImGui::Text("Sphere2");

		ImGui::DragFloat3("Center2", &sphere2.center.x, 0.01f);

		ImGui::DragFloat("Radius2", &sphere2.radius, 0.01f);

		ImGui::End();

		// 衝突判定
		bool isHit = IsCollision(sphere1, sphere2);

		// 行列
	
		Matrix4x4 viewProjectionMatrix = MakeViewProjectionMatrix(cameraTranslate, cameraRotate, kWindowWidth, kWindowHeight);

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight, 0.0f, 1.0f);
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		
		// グリッド
	
		DrawGrid(viewProjectionMatrix, viewportMatrix);

	
		// 球描画

		// sphere1
		DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, WHITE);

		// sphere2
		uint32_t sphere2Color = WHITE;

		if (isHit) {
			sphere2Color = RED;
		}

		DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, sphere2Color);

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
}
