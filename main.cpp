#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "GC2B_05_ムロサキ_リク_タイトル";

struct Matrix4x4 
{
	float m[4][4];
};

//行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) 
{
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++) 
		{
			result.m[y][x] = m1.m[y][x] + m2.m[y][x];
		}
	}
	return result;
}

//行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) 
{
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++) 
		{
			result.m[y][x] = m1.m[y][x] - m2.m[y][x];
		}
	}
	return result;
}


//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) 
{
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++) 
		{
			result.m[y][x] = m1.m[y][0] * m2.m[0][x] + m1.m[y][1] * m2.m[1][x] + m1.m[y][2] * m2.m[2][x] + m1.m[y][3] * m2.m[3][x];
		}
	}
	return result;
}

// 単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		result.m[i][i] = 1.0f;
	}
	return result;
}

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {

	Matrix4x4 result = MakeIdentity4x4();
	Matrix4x4 temp = m;

	for (int i = 0; i < 4; i++) 
	{

		
		float pivot = temp.m[i][i];
		if (fabs(pivot) < 1e-6f) 
		{
			
			return MakeIdentity4x4();
		}

		float invPivot = 1.0f / pivot;

		// 行を正規化
		for (int j = 0; j < 4; j++) 
		{
			temp.m[i][j] *= invPivot;
			result.m[i][j] *= invPivot;
		}

		// 他を消去
		for (int k = 0; k < 4; k++) 
		{
			if (k == i)
				continue;

			float factor = temp.m[k][i];

			for (int j = 0; j < 4; j++) 
			{
				temp.m[k][j] -= factor * temp.m[i][j];
				result.m[k][j] -= factor * result.m[i][j];
			}
		}
	}

	return result;
}

//転置行列
Matrix4x4 Transpose(const Matrix4x4& m) 
{
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++) 
		{
			result.m[y][x] = m.m[x][y];
		}
	}
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

	Matrix4x4 m1 = {3.2f, 0.7f, 9.6f, 4.4f,
		            5.5f, 1.3f, 7.8f, 2.1f,
		            6.9f, 8.0f, 2.6f, 1.0f,
		            0.5f, 7.2f, 5.1f, 3.3f};

	Matrix4x4 m2 = {4.1f, 6.5f, 3.3f, 2.2f,
		            8.8f, 0.6f, 9.9f, 7.7f, 
		            1.1f, 5.5f, 6.6f, 0.0f,
		            3.3f, 9.9f, 8.8f, 2.2f};

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

		Matrix4x4 resultAdd = Add(m1, m2);
		Matrix4x4 resultMultiply = Multiply(m1, m2);
		Matrix4x4 resultSubtract = Subtract(m1, m2);
		Matrix4x4 inverseM1 = Inverse(m1);
		Matrix4x4 inverseM2 = Inverse(m2);
		Matrix4x4 transposeM1 = Transpose(m1);
		Matrix4x4 transposeM2 = Transpose(m2);
		Matrix4x4 identity = MakeIdentity4x4();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, "ADD" ,resultAdd);
		MatrixScreenPrintf(0, kRowHight * 5, "Multiply", resultMultiply);
		MatrixScreenPrintf(0, kRowHight * 5 * 2, "Subtract", resultSubtract);
		MatrixScreenPrintf(0, kRowHight * 5 * 3, "inverseM1", inverseM1);
		MatrixScreenPrintf(0, kRowHight * 5 * 4, "inverseM2", inverseM2);
		MatrixScreenPrintf(kColumnWidth * 5, 0, "transposeM1", transposeM1);
		MatrixScreenPrintf(kColumnWidth * 5, kRowHight * 5, "transposeM2", transposeM2);
		MatrixScreenPrintf(kColumnWidth * 5, kRowHight * 5 * 2, "identity", identity);

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
