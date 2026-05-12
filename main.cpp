#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "GC2B_05_ムロサキ_リク_タイトル";

struct Vector3 {
	float x;
	float y;
	float z;
};

// ベクトルの加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

// ベクトルの減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

// ベクトルとスカラーの積
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;

	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;

	return result;
}

// 内積
float Dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

// ベクトルの長さ
float Length(const Vector3& v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }

// 正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result{};

	float length = Length(v);

	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}

	return result;
}
static const int kColumnWidth = 60;
static const int kColumnHight = 20;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 v1{1.0f, 3.0f, -5.0f};
	Vector3 v2{4.0f, -1.0f, 2.0f};
	float k = {4.0f};

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

		Vector3 resultAdd = Add(v1, v2);
		Vector3 resultSubtract = Subtract(v1, v2);
		Vector3 resultMultiply = Multiply(k, v2);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vector3 resultNormalize = Normalize(v2);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0, 0, resultAdd, "Add");
		VectorScreenPrintf(0, kColumnHight, resultSubtract, "Subtract");
		VectorScreenPrintf(0, kColumnHight * 2, resultMultiply, "Multiply");

		Novice::ScreenPrintf(0, kColumnHight * 3, "%.02f Dot", resultDot);
		Novice::ScreenPrintf(0, kColumnHight * 4, "%.02f Length", resultLength);

		VectorScreenPrintf(0, kColumnHight * 5, resultNormalize, "Normalize");

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