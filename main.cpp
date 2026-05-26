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

		//========================
	// カメラ
	//========================
	Vector3 cameraTranslate{0.0f, 1.9f, -6.4f};

	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};

	//========================
	// 線分
	//========================
	Segment segment{
	    {-2.0f, -1.0f, 0.0f},
        {3.0f,  2.0f,  2.0f}
    };

	//========================
	// 点
	//========================
	Vector3 point{-1.5f, 0.6f, 0.6f};
	
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
		
		//========================
		// ImGui
		//========================
		ImGui::Begin("Window");

		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);

		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		ImGui::DragFloat3("SegmentOrigin", &segment.origin.x, 0.01f);

		ImGui::DragFloat3("SegmentDiff", &segment.diff.x, 0.01f);

		ImGui::DragFloat3("Point", &point.x, 0.01f);

		//========================
		// 計算
		//========================
		Vector3 project = Project(Subtract(point, segment.origin), segment.diff);

		Vector3 closestPoint = ClosestPoint(point, segment);

		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);

		ImGui::InputFloat3("ClosestPoint", &closestPoint.x, "%.3f", ImGuiInputTextFlags_ReadOnly);

		ImGui::End();
		//========================
		// 球
		//========================
		Sphere pointSphere{point, 0.05f};

		Sphere closestPointSphere{closestPoint, 0.05f};

		//========================
		// 行列
		//========================
		Matrix4x4 viewProjectionMatrix = MakeViewProjectionMatrix(cameraTranslate, cameraRotate, kWindowWidth, kWindowHeight);

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight, 0.0f, 1.0f);

		//========================
		// Grid
		//========================
		DrawGrid(viewProjectionMatrix, viewportMatrix);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//========================
		// 線分描画
		//========================
		Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);

		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);

		//========================
		// 球描画
		//========================
		DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, RED);

		DrawSphere(closestPointSphere, viewProjectionMatrix, viewportMatrix, BLACK);
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
