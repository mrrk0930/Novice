#include "MathFunc.h"
#include <Novice.h>
#include <cmath>
#include <imgui.h>
#include <numbers>

struct Sphere {
	Vector3 center;
	float radius;
};

//========================
// Grid描画
//========================
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {

	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	// 奥→手前
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

		float x = -kGridHalfWidth + xIndex * kGridEvery;

		Vector3 start = {x, 0.0f, -kGridHalfWidth};
		Vector3 end = {x, 0.0f, kGridHalfWidth};

		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);

		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), 0xAAAAAAFF);
	}

	// 左→右
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {

		float z = -kGridHalfWidth + zIndex * kGridEvery;

		Vector3 start = {-kGridHalfWidth, 0.0f, z};
		Vector3 end = {kGridHalfWidth, 0.0f, z};

		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);

		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), 0xAAAAAAFF);
	}
}

//========================
// Sphere描画
//========================
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	const uint32_t kSubdivision = 16;

	const float kLonEvery = 2.0f * std::numbers::pi_v<float> / kSubdivision;

	const float kLatEvery = std::numbers::pi_v<float> / kSubdivision;

	// 緯度
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {

		float lat = -std::numbers::pi_v<float> / 2.0f + kLatEvery * latIndex;

		// 経度
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {

			float lon = lonIndex * kLonEvery;

			Vector3 a{
			    sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon),

			    sphere.center.y + sphere.radius * std::sin(lat),

			    sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon)};

			Vector3 b{
			    sphere.center.x + sphere.radius * std::cos(lat + kLatEvery) * std::cos(lon),

			    sphere.center.y + sphere.radius * std::sin(lat + kLatEvery),

			    sphere.center.z + sphere.radius * std::cos(lat + kLatEvery) * std::sin(lon)};

			Vector3 c{
			    sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon + kLonEvery),

			    sphere.center.y + sphere.radius * std::sin(lat),

			    sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon + kLonEvery)};

			Vector3 aScreen = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);

			Vector3 bScreen = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);

			Vector3 cScreen = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			// AB
			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(bScreen.x), int(bScreen.y), color);

			// AC
			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(cScreen.x), int(cScreen.y), color);
		}
	}
}




const char kWindowTitle[] = "GC2B_05_ムロサキ_リク_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 画面サイズ
	const float kWindowWidth = 1280.0f;
	const float kWindowHeight = 720.0f;

	// カメラ
	Vector3 cameraTranslate{0.0f, 1.9f, -6.4f};
	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};

	// 球
	Sphere sphere{
	    {0.0f, 0.0f, 0.0f},
        1.0f
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

		ImGui::Begin("Window");

		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);

		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);

		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);

		ImGui::End();


		Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, cameraTranslate);

		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, kWindowWidth / kWindowHeight, 0.1f, 100.0f);

		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight, 0.0f, 1.0f);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, WHITE);
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
