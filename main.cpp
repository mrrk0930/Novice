#include <Novice.h>
#include <math.h>
#include <cmath>

const char kWindowTitle[] = "GC2B_05_ムロサキ_リク_タイトル";

struct Vector3 
{
	float x;
	float y;
	float z;
};

struct Matrix4x4 
{
	float m[4][4];
};

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) 
{
	Matrix4x4 result{};

	for (int row = 0; row < 4; row++) 
	{
		for (int column = 0; column < 4; column++) 
		{
			result.m[row][column] = m1.m[row][0] * m2.m[0][column] + m1.m[row][1] * m2.m[1][column] + m1.m[row][2] * m2.m[2][column] + m1.m[row][3] * m2.m[3][column];
		}
	}

	return result;
}

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) 
{
	Matrix4x4 result = 
	{
	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, cosf(radian), sinf(radian), 0.0f}, {0.0f, -sinf(radian), cosf(radian), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	return result;
}

// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) 
{
	Matrix4x4 result = 
	{
	    {{cosf(radian), 0.0f, -sinf(radian), 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {sinf(radian), 0.0f, cosf(radian), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	return result;
}

// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) 
{
	Matrix4x4 result = 
	{
	    {{cosf(radian), sinf(radian), 0.0f, 0.0f}, {-sinf(radian), cosf(radian), 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

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

		Vector3 rotate{0.4f, 1.43f, -0.8f};
		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
		Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, "rotateXMatrix", rotateXMatrix);
		MatrixScreenPrintf(0, kRowHight * 5, "rotateYMatrix", rotateYMatrix);
		MatrixScreenPrintf(0, kRowHight * 5 * 2, "rotateZMatrix", rotateZMatrix);
		MatrixScreenPrintf(0, kRowHight * 5 * 3, "rotateXYZMatrix", rotateXYZMatrix);

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
