#include <Novice.h>
#include "MathFunc.h"
#include <cmath>
#include <math.h>

const char kWindowTitle[] = "GC2B_05_ムロサキ_リク_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	const int KWindowWidth = 1280;
	const int KWindowHeight = 720;

	Vector3 cameraPosition = {0.0f, 0.0f, -5.0f};

	Vector3 KLocalVertices[3] = {
	    {0.0f,  0.25f,  0.0f},
	    {0.25f,  -0.25f, 0.0f},
	    {-0.25f, -0.25f, 0.0f},
	};

	//クロス積の確認用
	Vector3 v1{1.2f, -3.9f, 2.5f};
	Vector3 v2{2.8f, 0.4f, -1.3f};
	Vector3 cross = Cross(v1, v2);

	Vector3 rotate{};
	Vector3 translate{};

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

		// 移動速度
		const float moveSpeed = 0.125f;

		// 回転速度
		const float rotateSpeed = 0.05f;

		// Y軸回転
		rotate.y += rotateSpeed; 
		
		// 前進
		if (keys[DIK_W]) 
		{
			translate.z += moveSpeed;
		}

		// 後退
		if (keys[DIK_S]) 
		{
			translate.z -= moveSpeed;
		}

		// 右移動
		if (keys[DIK_D]) 
		{
			translate.x += moveSpeed;
		}

		// 左移動
		if (keys[DIK_A]) 
		{
			translate.x -= moveSpeed;
		}

		//各種行列の計算
		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(KWindowWidth) / float(KWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(KWindowWidth), float(KWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) 
		{
		
			Vector3 ndcvVertex = Transform(KLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcvVertex, viewportMatrix);

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, "Cross", cross);

		Novice::DrawTriangle(
		    int(screenVertices[0].x), int(screenVertices[0].y), 
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y), 
			RED, kFillModeSolid);

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
