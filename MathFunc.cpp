#include "MathFunc.h"
#include <cmath>
#include <imgui.h>
#include <numbers>


////////////////
///  Vector  ///
////////////////

// ベクトルの加算
Vector3 Add(const Vector3& v1, const Vector3& v2) 
{

	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;

}

// ベクトルの減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) 
{

	Vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;

}

// ベクトルとスカラーの積
Vector3 Multiply(float scalar, const Vector3& v) 
{

	Vector3 result;

	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;

	return result;

}

// 内積
float Dot(const Vector3& v1, const Vector3& v2) 
{
	
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 

}

// クロス積（外積）
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

// ベクトルの長さ
float Length(const Vector3& v) 
{

	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); 

}

// 正規化
Vector3 Normalize(const Vector3& v) 
{

	Vector3 result{};

	float length = Length(v);

	if (length != 0.0f) 
	{
	
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	
	}

	return result;

}

////////////////
///  Matrix  ///
////////////////

// 行列の加法
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

// 行列の減法
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

// 単位行列の作成
Matrix4x4 MakeIdentity4x4() 
{

	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) 
	{
	
		result.m[i][i] = 1.0f;
	
	}

	return result;

}

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) 
{

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

		for (int j = 0; j < 4; j++) 
		{
		
			temp.m[i][j] *= invPivot;
			result.m[i][j] *= invPivot;
		
		}

		for (int k = 0; k < 4; k++) 
		{

			if (k == i) 
			{
			
				continue;
			
			}

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

// 転置行列
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

//////////////////
///  Rotation  ///
//////////////////

// X軸の回転行列
Matrix4x4 MakeRotateXMatrix(float radian) 
{

	Matrix4x4 result = 
	{

	    {{1.0f, 0.0f, 0.0f, 0.0f},
	     {0.0f, static_cast<float>(std::cos(radian)), static_cast<float>(std::sin(radian)), 0.0f},
	     {0.0f, static_cast<float>(-std::sin(radian)), static_cast<float>(std::cos(radian)), 0.0f},
	     {0.0f, 0.0f, 0.0f, 1.0f}}
    
	};

	return result;

}

// Y軸の回転行列
Matrix4x4 MakeRotateYMatrix(float radian) 
{
	Matrix4x4 result = 
	{

	    {{static_cast<float>(std::cos(radian)), 0.0f, static_cast<float>(-std::sin(radian)), 0.0f},
	     {0.0f, 1.0f, 0.0f, 0.0f},
	     {static_cast<float>(std::sin(radian)), 0.0f, static_cast<float>(std::cos(radian)), 0.0f},
	     {0.0f, 0.0f, 0.0f, 1.0f}}
   
	};

	return result;

}

// Z軸の回転行列
Matrix4x4 MakeRotateZMatrix(float radian) 
{

	Matrix4x4 result = 
	{

	    {{static_cast<float>(std::cos(radian)), static_cast<float>(std::sin(radian)), 0.0f, 0.0f},
	     {static_cast<float>(-std::sin(radian)), static_cast<float>(std::cos(radian)), 0.0f, 0.0f},
	     {0.0f, 0.0f, 1.0f, 0.0f},
	     {0.0f, 0.0f, 0.0f, 1.0f}}
   
	};

	return result;

}

///////////////////
///  Transform  ///
///////////////////

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) 
{

	Matrix4x4 result = 
	{
	
		{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {translate.x, translate.y, translate.z, 1.0f}}
    
	};

	return result;

}

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) 
{

	Matrix4x4 result = 
	{
	
		{{scale.x, 0.0f, 0.0f, 0.0f}, {0.0f, scale.y, 0.0f, 0.0f}, {0.0f, 0.0f, scale.z, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    
	};

	return result;

}

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) 
{
	
	Vector3 result;

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	result.x = (vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0]) / w;

	result.y = (vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1]) / w;

	result.z = (vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2]) / w;

	return result;

}

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) 
{

	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);

	Matrix4x4 rotateMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	return Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));

}

////////////////////
///  Projection  ///
////////////////////

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) 
{

	Matrix4x4 result{};

	float f = 1.0f / static_cast<float>(std::tan(fovY / 2.0f));

	result.m[0][0] = f / aspectRatio;
	result.m[1][1] = f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

	return result;

}

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) 
{

	Matrix4x4 result{};

	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;

	return result;

}

// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) 
{

	Matrix4x4 result{};

	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -(height / 2.0f);
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;

}

//////////////
///  Draw  ///
//////////////

// グリッド
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

// 球
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) 
{

	const uint32_t kSubdivision = 16;

	const float kLonEvery = 2.0f * std::numbers::pi_v<float> / kSubdivision;

	const float kLatEvery = std::numbers::pi_v<float> / kSubdivision;

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) 
	{

		float lat = -std::numbers::pi_v<float> / 2.0f + kLatEvery * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) 
		{

			float lon = lonIndex * kLonEvery;

			// a
			Vector3 a
			{
			    sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon),

			    sphere.center.y + sphere.radius * std::sin(lat),

			    sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon)
			};

			// b（緯度方向）
			Vector3 b
			{
			    sphere.center.x + sphere.radius * std::cos(lat + kLatEvery) * std::cos(lon),

			    sphere.center.y + sphere.radius * std::sin(lat + kLatEvery),

			    sphere.center.z + sphere.radius * std::cos(lat + kLatEvery) * std::sin(lon)
			};

			// c（経度方向）
			Vector3 c
			{
			    sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon + kLonEvery),

			    sphere.center.y + sphere.radius * std::sin(lat),

			    sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon + kLonEvery)
			};

			Vector3 aScreen = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);

			Vector3 bScreen = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);

			Vector3 cScreen = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			// 緯度線
			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(bScreen.x), int(bScreen.y), color);

			// 経度線
			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(cScreen.x), int(cScreen.y), color);

		}
	
	}

}

/////////////////
///  Utility  ///
/////////////////

// カメラ
Matrix4x4 MakeViewProjectionMatrix(const Vector3& cameraTranslate, const Vector3& cameraRotate, float windowWidth, float windowHeight) 
{

	Matrix4x4 cameraMatrix = MakeAffineMatrix({1, 1, 1}, cameraRotate, cameraTranslate);

	Matrix4x4 viewMatrix = Inverse(cameraMatrix);

	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, windowWidth / windowHeight, 0.1f, 100.0f);

	return Multiply(viewMatrix, projectionMatrix);

}

// 球ImGui
void UpdateImGui(Vector3& cameraTranslate, Vector3& cameraRotate, Sphere& sphere) 
{

	ImGui::Begin("Window");

	ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);

	ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

	ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);

	ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);

	ImGui::End();

}

////////////////////////
///  GeometryUtility ///
////////////////////////

// 射影
Vector3 Project(const Vector3& v1, const Vector3& v2) {
	float lengthSq = Dot(v2, v2);

	if (lengthSq == 0.0f) {
		return {0.0f, 0.0f, 0.0f};
	}

	float t = Dot(v1, v2) / lengthSq;

	return Multiply(t, v2);
}

// 最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	float lengthSq = Dot(segment.diff, segment.diff);

	if (lengthSq == 0.0f) {
		return segment.origin;
	}

	Vector3 pointVector = Subtract(point, segment.origin);

	float t = Dot(pointVector, segment.diff) / lengthSq;

	// 線分内に制限
	if (t < 0.0f) {
		t = 0.0f;
	}

	if (t > 1.0f) {
		t = 1.0f;
	}

	return Add(segment.origin, Multiply(t, segment.diff));
}

///////////////
///  Move  ////
///////////////

// 移動・回転
void UpdateMove(Vector3& translate, Vector3& rotate, char keys[]) {

	// 移動速度
	const float moveSpeed = 0.125f;

	// 回転速度
	const float rotateSpeed = 0.05f;

	// Y軸回転
	rotate.y += rotateSpeed;

	// 前進
	if (keys[DIK_W]) {
		translate.z += moveSpeed;
	}

	// 後退
	if (keys[DIK_S]) {
		translate.z -= moveSpeed;
	}

	// 右移動
	if (keys[DIK_D]) {
		translate.x += moveSpeed;
	}

	// 左移動
	if (keys[DIK_A]) {
		translate.x -= moveSpeed;
	}

	// 上移動
	if (keys[DIK_Q]) {
		translate.y += moveSpeed;
	}

	// 下移動
	if (keys[DIK_E]) {
		translate.y -= moveSpeed;
	}
}

/////////////////
///  Action  ////
/////////////////

// 球と球の衝突判定
bool IsCollision(const Sphere& s1, const Sphere& s2) {

	Vector3 diff = Subtract(s1.center, s2.center);

	float distance = Length(diff);

	float radiusSum = s1.radius + s2.radius;

	return distance <= radiusSum;
}

///////////////
///  Print  ///
///////////////

// Matrix表示
void MatrixScreenPrintf(int x, int y, const char* label, const Matrix4x4& matrix) 
{

	Novice::ScreenPrintf(x, y, "%s", label);

	for (int row = 0; row < 4; ++row) 
	{

		for (int column = 0; column < 4; ++column) 
		{

			Novice::ScreenPrintf(x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f", matrix.m[row][column]);
		
		}
	
	}

}

// Vector表示
void VectorScreenPrintf(int x, int y, const char* label, const Vector3& vector) { Novice::ScreenPrintf(x, y, "%s : %.02f %.02f %.02f", label, vector.x, vector.y, vector.z); }