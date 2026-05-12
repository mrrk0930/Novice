#include <Novice.h>
#include <cmath>
#include <math.h>

const char kWindowTitle[] = "GC2B_05_ムロサキ_リク_タイトル";

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {
	float m[4][4];
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

// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m1.m[y][x] + m2.m[y][x];
		}
	}
	return result;
}

// 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m1.m[y][x] - m2.m[y][x];
		}
	}
	return result;
}

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};

	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			result.m[row][column] = m1.m[row][0] * m2.m[0][column] + m1.m[row][1] * m2.m[1][column] + m1.m[row][2] * m2.m[2][column] + m1.m[row][3] * m2.m[3][column];
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

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {

	Matrix4x4 result = MakeIdentity4x4();
	Matrix4x4 temp = m;

	for (int i = 0; i < 4; i++) {

		float pivot = temp.m[i][i];
		if (fabs(pivot) < 1e-6f) {

			return MakeIdentity4x4();
		}

		float invPivot = 1.0f / pivot;

		// 行を正規化
		for (int j = 0; j < 4; j++) {
			temp.m[i][j] *= invPivot;
			result.m[i][j] *= invPivot;
		}

		// 他を消去
		for (int k = 0; k < 4; k++) {
			if (k == i)
				continue;

			float factor = temp.m[k][i];

			for (int j = 0; j < 4; j++) {
				temp.m[k][j] -= factor * temp.m[i][j];
				result.m[k][j] -= factor * result.m[i][j];
			}
		}
	}

	return result;
}

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m.m[x][y];
		}
	}
	return result;
}

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result = {
	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, cosf(radian), sinf(radian), 0.0f}, {0.0f, -sinf(radian), cosf(radian), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	return result;
}

// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result = {
	    {{cosf(radian), 0.0f, -sinf(radian), 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {sinf(radian), 0.0f, cosf(radian), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	return result;
}

// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result = {
	    {{cosf(radian), sinf(radian), 0.0f, 0.0f}, {-sinf(radian), cosf(radian), 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	return result;
}

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {

	Matrix4x4 result = {

	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {translate.x, translate.y, translate.z, 1.0f}}
	};

	return result;
}

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {

	Matrix4x4 result = {

	    {{scale.x, 0.0f, 0.0f, 0.0f}, {0.0f, scale.y, 0.0f, 0.0f}, {0.0f, 0.0f, scale.z, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
	};

	return result;
}
// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {

	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];

	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];

	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];

	return result;
}

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);

	Matrix4x4 rotateMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	return Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));
}

// 表示
static const int kRowHight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const char* label, const Matrix4x4& matrix) {
	Novice::ScreenPrintf(x, y, "%s", label);

	for (int row = 0; row < 4; ++row) {

		for (int column = 0; column < 4; ++column) {

			Novice::ScreenPrintf(x + column * kColumnWidth, y + (row + 1) * kRowHight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const char* label, const Vector3& vector) { Novice::ScreenPrintf(x, y, "%s : %.02f %.02f %.02f", label, vector.x, vector.y, vector.z); }

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

		Vector3 scale{1.2f, 0.79f, -2.1f};
		Vector3 rotate{0.4f, 1.43f, -0.8f};
		Vector3 translate{2.7f, -4.15f, 1.57f};
		Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, "worldMatrix", worldMatrix);

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
