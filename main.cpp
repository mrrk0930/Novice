#include <Novice.h>
#include <math.h>
#include <cmath>

const char kWindowTitle[] = "GC2B_05_ムロサキ_リク_タイトル";

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {
	float m[4][4];
};

// 1. 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) 
{

	Matrix4x4 result = 
	{

	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {translate.x, translate.y, translate.z, 1.0f}}
    
	};

	return result;
}

// 2. 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) 
{

	Matrix4x4 result = 
	{

	    {{scale.x, 0.0f, 0.0f, 0.0f}, {0.0f, scale.y, 0.0f, 0.0f}, {0.0f, 0.0f, scale.z, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    
	};

	return result;

}
// 3. 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) 
{

	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];

	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];

	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];

	return result;

}


//表示
static const int kRowHight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const char* label, const Matrix4x4& matrix) 
{
	Novice::ScreenPrintf(x, y, "%s", label);

	for (int row = 0; row < 4; ++row) 
	{
	
		for (int column = 0; column < 4; ++column) 
		{
		
			Novice::ScreenPrintf(x + column * kColumnWidth, y + (row + 1) * kRowHight, "%6.02f", matrix.m[row][column]);

		}

	}

}

void VectorScreenPrintf(int x, int y, const char* label, const Vector3& vector) 
{ 
	
	Novice::ScreenPrintf(x, y, "%s : %.02f %.02f %.02f", label, vector.x, vector.y, vector.z); 

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	

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

		Vector3 translate{4.1f, 2.6f, 0.8f};
		Vector3 scale{1.5f, 5.2f, 7.3f};
		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
		Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
		Vector3 point{2.3f, 3.8f, 1.4f};
		Matrix4x4 transformMatrix = 
		{
			1.0f, 2.0f, 3.0f, 4.0f,
			3.0f, 1.0f, 1.0f, 2.0f, 
			1.0f, 4.0f, 2.0f, 3.0f,
			 2.0f, 2.0f, 1.0f, 3.0f
		};
		Vector3 transformed = Transform(point, transformMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, "transformed", transformed);
		MatrixScreenPrintf(0, kRowHight, "translateMatrix", translateMatrix);
		MatrixScreenPrintf(0, kRowHight * 6, "scaleMatrix", scaleMatrix);

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
