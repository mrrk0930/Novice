#include "MathFunc.h"
#include <Novice.h>
#include <cmath>
#include <imgui.h>


bool IsCollisionLT(const Triangle& triangle, const Segment& segment) {
	Vector3 v0 = triangle.vertices[0];
	Vector3 v1 = triangle.vertices[1];
	Vector3 v2 = triangle.vertices[2];

	// 三角形法線
	Vector3 edge01 = Subtract(v1, v0);
	Vector3 edge12 = Subtract(v2, v1);

	Vector3 normal = Normalize(Cross(edge01, edge12));

	float denominator = Dot(segment.diff, normal);

	// 平行
	if (fabsf(denominator) < 0.00001f) {
		return false;
	}

	float t = (Dot(v0, normal) - Dot(segment.origin, normal)) / denominator;

	// 線分外
	if (t < 0.0f || t > 1.0f) {
		return false;
	}

	// 交点
	Vector3 p = Add(segment.origin, Multiply(t, segment.diff));

	// 辺ベクトル
	Vector3 edge0 = Subtract(v1, v0);

	Vector3 edge1 = Subtract(v2, v1);

	Vector3 edge2 = Subtract(v0, v2);

	// 頂点→交点
	Vector3 vp0 = Subtract(p, v0);

	Vector3 vp1 = Subtract(p, v1);

	Vector3 vp2 = Subtract(p, v2);

	Vector3 c0 = Cross(edge0, vp0);

	Vector3 c1 = Cross(edge1, vp1);

	Vector3 c2 = Cross(edge2, vp2);

	if (Dot(c0, normal) >= 0.0f && Dot(c1, normal) >= 0.0f && Dot(c2, normal) >= 0.0f) {
		return true;
	}

	return false;
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 screen[3];

	for (int i = 0; i < 3; i++) {
		screen[i] = Transform(Transform(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)screen[0].x, (int)screen[0].y, (int)screen[1].x, (int)screen[1].y, color);

	Novice::DrawLine((int)screen[1].x, (int)screen[1].y, (int)screen[2].x, (int)screen[2].y, color);

	Novice::DrawLine((int)screen[2].x, (int)screen[2].y, (int)screen[0].x, (int)screen[0].y, color);
}

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
	Segment segment
	{

	    {-1.0f, 1.0f,  0.0f}, 
	    {2.0f,  -2.0f, 0.0f}  
	
	};

	Triangle triangle{
    {
        {-1.0f,0.0f,0.0f},
        { 1.0f,0.0f,0.0f},
        { 0.0f,2.0f,0.0f}
    }
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
		
		//各辺を結んだベクトルと、頂点と衝突点Pを結んだベクトルのクロス積を取る。
		//すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突

		 ImGui::Begin("Collision");

		ImGui::DragFloat3("SegmentOrigin", &segment.origin.x, 0.01f);

		ImGui::DragFloat3("SegmentDiff", &segment.diff.x, 0.01f);

		ImGui::Separator();

		ImGui::DragFloat3("Vertex0", &triangle.vertices[0].x, 0.01f);

		ImGui::DragFloat3("Vertex1", &triangle.vertices[1].x, 0.01f);

		ImGui::DragFloat3("Vertex2", &triangle.vertices[2].x, 0.01f);

		ImGui::End();

		bool isHit = IsCollisionLT(triangle, segment);

		// 行列
		Matrix4x4 viewProjectionMatrix = MakeViewProjectionMatrix(cameraTranslate, cameraRotate, kWindowWidth, kWindowHeight);

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight, 0.0f, 1.0f);
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

	    DrawTriangle(triangle, viewProjectionMatrix, viewportMatrix, WHITE);

		DrawSegment(segment, viewProjectionMatrix, viewportMatrix, isHit ? RED : WHITE);

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
