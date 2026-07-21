#include "MathFunc.h"
#include <cmath>
#include <imgui.h>
#include <numbers>
#include <algorithm>

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

// 二項演算子+
Vector3 Vector3::operator+(const Vector3& v) const { return {x + v.x, y + v.y, z + v.z}; }

// 二項演算子-
Vector3 Vector3::operator-(const Vector3& v) const { return {x - v.x, y - v.y, z - v.z}; }

// 単項演算子
Vector3 Vector3::operator-() const { return {-x, -y, -z}; }

// 複合代入演算子
Vector3& Vector3::operator+=(const Vector3& v) 
{

	x += v.x;
	y += v.y;
	z += v.z;

	return *this;

}

// スカラー倍
Vector3 Vector3::operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }

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

// 加算演算子
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const 
{

	Matrix4x4 result{};

	for (int y = 0; y < 4; y++) 
	{
	
		for (int x = 0; x < 4; x++) 
		{
		
			result.m[y][x] = m[y][x] + other.m[y][x];
		
		}
	
	}

	return result;

}

// 減算演算子
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const 
{

	Matrix4x4 result{};

	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++) 
		{
		
			result.m[y][x] = m[y][x] - other.m[y][x];
		
		}
	
	}

	return result;

}

// 積演算子
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const 
{

	Matrix4x4 result{};

	for (int row = 0; row < 4; row++) 
	{

		for (int column = 0; column < 4; column++) 
		{

			result.m[row][column] = m[row][0] * other.m[0][column] + m[row][1] * other.m[1][column] + m[row][2] * other.m[2][column] + m[row][3] * other.m[3][column];
		
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

// 平面
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) 
{

	Vector3 center = Multiply(plane.distance, plane.normal);

	Vector3 perpendiculars[4];

	perpendiculars[0] = Normalize(Perpendicular(plane.normal));

	perpendiculars[1] = Multiply(-1.0f, perpendiculars[0]);

	perpendiculars[2] = Normalize(Cross(plane.normal, perpendiculars[0]));

	perpendiculars[3] = Multiply(-1.0f, perpendiculars[2]);

	Vector3 corner[4];

	corner[0] = Add(Add(center, Multiply(2.0f, perpendiculars[0])), Multiply(2.0f, perpendiculars[2]));

	corner[1] = Add(Add(center, Multiply(2.0f, perpendiculars[1])), Multiply(2.0f, perpendiculars[2]));

	corner[2] = Add(Add(center, Multiply(2.0f, perpendiculars[1])), Multiply(2.0f, perpendiculars[3]));

	corner[3] = Add(Add(center, Multiply(2.0f, perpendiculars[0])), Multiply(2.0f, perpendiculars[3]));

	Vector3 screen[4];

	for (int i = 0; i < 4; i++) 
	{
	
		screen[i] = Transform(Transform(corner[i], viewProjectionMatrix), viewportMatrix);
	
	}

	Novice::DrawLine((int)screen[0].x, (int)screen[0].y, (int)screen[1].x, (int)screen[1].y, color);

	Novice::DrawLine((int)screen[1].x, (int)screen[1].y, (int)screen[2].x, (int)screen[2].y, color);

	Novice::DrawLine((int)screen[2].x, (int)screen[2].y, (int)screen[3].x, (int)screen[3].y, color);

	Novice::DrawLine((int)screen[3].x, (int)screen[3].y, (int)screen[0].x, (int)screen[0].y, color);

}

// 線分
void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) 
{

	Vector3 start = segment.origin;

	Vector3 end = Add(segment.origin, segment.diff);

	Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);

	Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine((int)startScreen.x, (int)startScreen.y, (int)endScreen.x, (int)endScreen.y, color);

}

// 三角形
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) 
{

	Vector3 screen[3];

	for (int i = 0; i < 3; i++) 
	{
	
		screen[i] = Transform(Transform(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	
	}

	Novice::DrawLine((int)screen[0].x, (int)screen[0].y, (int)screen[1].x, (int)screen[1].y, color);

	Novice::DrawLine((int)screen[1].x, (int)screen[1].y, (int)screen[2].x, (int)screen[2].y, color);

	Novice::DrawLine((int)screen[2].x, (int)screen[2].y, (int)screen[0].x, (int)screen[0].y, color);

}

// AABB
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) 
{

	Vector3 vertices[8] = 
	{
	
		{aabb.min.x, aabb.min.y, aabb.min.z},
        {aabb.max.x, aabb.min.y, aabb.min.z},
        {aabb.max.x, aabb.max.y, aabb.min.z},
        {aabb.min.x, aabb.max.y, aabb.min.z},

	    {aabb.min.x, aabb.min.y, aabb.max.z},
        {aabb.max.x, aabb.min.y, aabb.max.z},
        {aabb.max.x, aabb.max.y, aabb.max.z},
        {aabb.min.x, aabb.max.y, aabb.max.z},
	
	};

	Vector3 screen[8];

	for (int i = 0; i < 8; i++) 
	{
	
		screen[i] = Transform(Transform(vertices[i], viewProjectionMatrix), viewportMatrix);
	
	}

	// 前面
	Novice::DrawLine((int)screen[0].x, (int)screen[0].y, (int)screen[1].x, (int)screen[1].y, color);
	Novice::DrawLine((int)screen[1].x, (int)screen[1].y, (int)screen[2].x, (int)screen[2].y, color);
	Novice::DrawLine((int)screen[2].x, (int)screen[2].y, (int)screen[3].x, (int)screen[3].y, color);
	Novice::DrawLine((int)screen[3].x, (int)screen[3].y, (int)screen[0].x, (int)screen[0].y, color);

	// 背面
	Novice::DrawLine((int)screen[4].x, (int)screen[4].y, (int)screen[5].x, (int)screen[5].y, color);
	Novice::DrawLine((int)screen[5].x, (int)screen[5].y, (int)screen[6].x, (int)screen[6].y, color);
	Novice::DrawLine((int)screen[6].x, (int)screen[6].y, (int)screen[7].x, (int)screen[7].y, color);
	Novice::DrawLine((int)screen[7].x, (int)screen[7].y, (int)screen[4].x, (int)screen[4].y, color);

	// 接続
	Novice::DrawLine((int)screen[0].x, (int)screen[0].y, (int)screen[4].x, (int)screen[4].y, color);
	Novice::DrawLine((int)screen[1].x, (int)screen[1].y, (int)screen[5].x, (int)screen[5].y, color);
	Novice::DrawLine((int)screen[2].x, (int)screen[2].y, (int)screen[6].x, (int)screen[6].y, color);
	Novice::DrawLine((int)screen[3].x, (int)screen[3].y, (int)screen[7].x, (int)screen[7].y, color);

}

// 2次ベジェ曲線
void DrawBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) 
{

	const int kSubdivision = 100;

	Vector3 prevPoint = p0;

	for (int i = 1; i <= kSubdivision; i++) 
	{

		float t = float(i) / float(kSubdivision);

		Vector3 currentPoint = QuadraticBezier(p0, p1, p2, t);

		Vector3 screen0 = Transform(Transform(prevPoint, viewProjectionMatrix), viewportMatrix);

		Vector3 screen1 = Transform(Transform(currentPoint, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(int(screen0.x), int(screen0.y), int(screen1.x), int(screen1.y), color);

		prevPoint = currentPoint;
	
	}

}

void DrawSkeleton(Joint joints[], const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) 
{

	Matrix4x4 shoulderWorld = MakeAffineMatrix(joints[0].scale, joints[0].rotate, joints[0].translate);

	Matrix4x4 elbowLocal = MakeAffineMatrix(joints[1].scale, joints[1].rotate, joints[1].translate);

	Matrix4x4 elbowWorld = Multiply(elbowLocal, shoulderWorld);

	Matrix4x4 handLocal = MakeAffineMatrix(joints[2].scale, joints[2].rotate, joints[2].translate);

	Matrix4x4 handWorld = Multiply(handLocal, elbowWorld);

	Vector3 shoulderPos = Transform({0, 0, 0}, shoulderWorld);
	Vector3 elbowPos = Transform({0, 0, 0}, elbowWorld);
	Vector3 handPos = Transform({0, 0, 0}, handWorld);

	Sphere sphere;
	sphere.radius = 0.05f;

	sphere.center = shoulderPos;
	DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, RED);

	sphere.center = elbowPos;
	DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, GREEN);

	sphere.center = handPos;
	DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, BLUE);

	DrawSegment({shoulderPos, Subtract(elbowPos, shoulderPos)}, viewProjectionMatrix, viewportMatrix, WHITE);

	DrawSegment({elbowPos, Subtract(handPos, elbowPos)}, viewProjectionMatrix, viewportMatrix, WHITE);

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
// 平面ImGui
void UpdatePlaneImGui(Sphere& sphere, Plane& plane) 
{

	ImGui::Begin("Collision");

	ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);

	ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f, 0.01f, 10.0f);

	ImGui::Separator();

	ImGui::DragFloat3("PlaneNormal", &plane.normal.x, 0.01f);

	plane.normal = Normalize(plane.normal);

	ImGui::DragFloat("PlaneDistance", &plane.distance, 0.01f);

	ImGui::End();

}

// 線分ImGui
void UpdateSegmentImGui(Segment& segment, Plane& plane) 
{

	ImGui::Begin("Collision");

	ImGui::DragFloat3("SegmentOrigin", &segment.origin.x, 0.01f);

	ImGui::DragFloat3("SegmentDiff", &segment.diff.x, 0.01f);

	ImGui::Separator();

	ImGui::DragFloat3("PlaneNormal", &plane.normal.x, 0.01f);

	plane.normal = Normalize(plane.normal);

	ImGui::DragFloat("PlaneDistance", &plane.distance, 0.01f);

	ImGui::End();

}

// 三角形ImGui
void UpdateTriangleImGui(Segment& segment, Triangle& triangle) 
{

	ImGui::Begin("Collision");

	ImGui::DragFloat3("SegmentOrigin", &segment.origin.x, 0.01f);

	ImGui::DragFloat3("SegmentDiff", &segment.diff.x, 0.01f);

	ImGui::Separator();

	ImGui::DragFloat3("Vertex0", &triangle.vertices[0].x, 0.01f);

	ImGui::DragFloat3("Vertex1", &triangle.vertices[1].x, 0.01f);

	ImGui::DragFloat3("Vertex2", &triangle.vertices[2].x, 0.01f);

	ImGui::End();

}

// AABBImGui
void UpdateAABBImGui(AABB& aabb1, AABB& aabb2) 
{

	ImGui::Begin("AABB Collision");

	ImGui::Text("AABB1");

	ImGui::DragFloat3("Min1", &aabb1.min.x, 0.01f);
	ImGui::DragFloat3("Max1", &aabb1.max.x, 0.01f);

	ImGui::Separator();

	ImGui::Text("AABB2");

	ImGui::DragFloat3("Min2", &aabb2.min.x, 0.01f);
	ImGui::DragFloat3("Max2", &aabb2.max.x, 0.01f);

	ImGui::End();

}

// 球とAABBImGui
void UpdateAABBSphereImGui(AABB& aabb, Sphere& sphere) 
{

	ImGui::Begin("AABB & Sphere");

	ImGui::Text("AABB");

	ImGui::DragFloat3("AABB Min", &aabb.min.x, 0.01f);

	ImGui::DragFloat3("AABB Max", &aabb.max.x, 0.01f);

	ImGui::Separator();

	ImGui::Text("Sphere");

	ImGui::DragFloat3("Sphere Center", &sphere.center.x, 0.01f);

	ImGui::DragFloat("Sphere Radius", &sphere.radius, 0.01f, 0.01f, 10.0f);

	ImGui::End();

}

// 線分とAABBImGui
void UpdateAABBLineImGui(AABB& aabb, Segment& segment) 
{

	ImGui::Begin("AABB & Segment");

	ImGui::Text("AABB");

	ImGui::DragFloat3("Min", &aabb.min.x, 0.01f);
	ImGui::DragFloat3("Max", &aabb.max.x, 0.01f);

	ImGui::Separator();

	ImGui::Text("Segment");

	ImGui::DragFloat3("Origin", &segment.origin.x, 0.01f);
	ImGui::DragFloat3("Diff", &segment.diff.x, 0.01f);

	ImGui::End();

}

// ベジェ曲線ImGui
void UpdateBezierImGui(Vector3 controlPoints[3]) 
{

	ImGui::Begin("Bezier");

	ImGui::DragFloat3("P0", &controlPoints[0].x, 0.01f);
	ImGui::DragFloat3("P1", &controlPoints[1].x, 0.01f);
	ImGui::DragFloat3("P2", &controlPoints[2].x, 0.01f);

	ImGui::End();

}

// 階層構造ImGui
void UpdateJointImGui(Joint joints[]) 
{

	ImGui::Begin("Joint");

	ImGui::Text("Shoulder");
	ImGui::DragFloat3("Shoulder Translate", &joints[0].translate.x, 0.01f);
	ImGui::DragFloat3("Shoulder Rotate", &joints[0].rotate.x, 0.01f);

	ImGui::Separator();

	ImGui::Text("Elbow");
	ImGui::DragFloat3("Elbow Translate", &joints[1].translate.x, 0.01f);
	ImGui::DragFloat3("Elbow Rotate", &joints[1].rotate.x, 0.01f);

	ImGui::Separator();

	ImGui::Text("Hand");
	ImGui::DragFloat3("Hand Translate", &joints[2].translate.x, 0.01f);

	ImGui::End();

}

// 演算子ImGui
void UpdateOperatorImGui(
    Vector3& vector1, Vector3& vector2, float& scalar, Vector3& scalarResult, Vector3& addResult, Vector3& subResult, Vector3& minusResult, Vector3& addEqualResult,
	Matrix4x4& m1, Matrix4x4& m2, Matrix4x4& addMatrix, Matrix4x4& subMatrix, Matrix4x4& mulMatrix) 
{

	ImGui::Begin("Operator Overload");

	ImGui::Text("Vector");

	ImGui::DragFloat3("Vector1", &vector1.x, 0.01f);
	ImGui::DragFloat3("Vector2", &vector2.x, 0.01f);

	ImGui::DragFloat("Scalar", &scalar, 0.01f);

	ImGui::Separator();

	ImGui::Text("Vector * Scalar");
	ImGui::Text("(%.2f %.2f %.2f)", scalarResult.x, scalarResult.y, scalarResult.z);

	ImGui::Separator();

	ImGui::Text("Vector + Vector");
	ImGui::Text("(%.2f %.2f %.2f)", addResult.x, addResult.y, addResult.z);

	ImGui::Separator();

	ImGui::Text("Vector - Vector");
	ImGui::Text("(%.2f %.2f %.2f)", subResult.x, subResult.y, subResult.z);

	ImGui::Separator();

	ImGui::Text("-Vector");
	ImGui::Text("(%.2f %.2f %.2f)", minusResult.x, minusResult.y, minusResult.z);

	ImGui::Separator();

	ImGui::Text("Vector +=");
	ImGui::Text("(%.2f %.2f %.2f)", addEqualResult.x, addEqualResult.y, addEqualResult.z);

	ImGui::Separator();

	ImGui::Text("Matrix");

	if (ImGui::TreeNode("Matrix1")) 
	{
	
		ImGui::DragFloat4("M1 Row0", m1.m[0], 0.01f);
		ImGui::DragFloat4("M1 Row1", m1.m[1], 0.01f);
		ImGui::DragFloat4("M1 Row2", m1.m[2], 0.01f);
		ImGui::DragFloat4("M1 Row3", m1.m[3], 0.01f);
		ImGui::TreePop();
	
	}

	if (ImGui::TreeNode("Matrix2")) 
	{
	
		ImGui::DragFloat4("M2 Row0", m2.m[0], 0.01f);
		ImGui::DragFloat4("M2 Row1", m2.m[1], 0.01f);
		ImGui::DragFloat4("M2 Row2", m2.m[2], 0.01f);
		ImGui::DragFloat4("M2 Row3", m2.m[3], 0.01f);
		ImGui::TreePop();
	
	}

	ImGui::Separator();

	ImGui::Text("Matrix + Matrix");

	for (int y = 0; y < 4; y++) 
	{
	
		ImGui::Text("%.2f %.2f %.2f %.2f", addMatrix.m[y][0], addMatrix.m[y][1], addMatrix.m[y][2], addMatrix.m[y][3]);
	
	}

	ImGui::Separator();

	ImGui::Text("Matrix - Matrix");

	for (int y = 0; y < 4; y++) 
	{
	
		ImGui::Text("%.2f %.2f %.2f %.2f", subMatrix.m[y][0], subMatrix.m[y][1], subMatrix.m[y][2], subMatrix.m[y][3]);
	
	}

	ImGui::Separator();

	ImGui::Text("Matrix * Matrix");

	for (int y = 0; y < 4; y++) 
	{
	
		ImGui::Text("%.2f %.2f %.2f %.2f", mulMatrix.m[y][0], mulMatrix.m[y][1], mulMatrix.m[y][2], mulMatrix.m[y][3]);
	
	}

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
Vector3 ClosestPoint(const Vector3& point, const Segment& segment) 
{

	float lengthSq = Dot(segment.diff, segment.diff);

	if (lengthSq == 0.0f) 
	{
	
		return segment.origin;
	
	}

	Vector3 pointVector = Subtract(point, segment.origin);

	float t = Dot(pointVector, segment.diff) / lengthSq;

	// 線分内に制限
	if (t < 0.0f) 
	{
	
		t = 0.0f;
	
	}

	if (t > 1.0f) 
	{
	
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
bool IsCollisionSS(const Sphere& s1, const Sphere& s2) {

	Vector3 diff = Subtract(s1.center, s2.center);

	float distance = Length(diff);

	float radiusSum = s1.radius + s2.radius;

	return distance <= radiusSum;
}

// 球と平面の衝突判定
bool IsCollisionSP(const Sphere& sphere, const Plane& plane) 
{

	float distance = Dot(sphere.center, plane.normal) - plane.distance;

	return fabsf(distance) <= sphere.radius;

}

// 平面と線分の衝突判定
bool IsCollisionPL(const Segment& segment, const Plane& plane) 
{

	float denominator = Dot(segment.diff, plane.normal);

	// 平行
	if (fabsf(denominator) < 0.00001f) 
	{
	
		return false;
	
	}

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / denominator;

	return (t >= 0.0f && t <= 1.0f);

}

// 三角形と線分の衝突判定
bool IsCollisionLT(const Triangle& triangle, const Segment& segment) 
{

	Vector3 v0 = triangle.vertices[0];
	Vector3 v1 = triangle.vertices[1];
	Vector3 v2 = triangle.vertices[2];

	Vector3 edge01 = Subtract(v1, v0);
	Vector3 edge12 = Subtract(v2, v1);

	Vector3 normal = Normalize(Cross(edge01, edge12));

	float denominator = Dot(segment.diff, normal);

	if (fabsf(denominator) < 0.00001f) 
	{
	
		return false;
	
	}

	float t = (Dot(v0, normal) - Dot(segment.origin, normal)) / denominator;

	if (t < 0.0f || t > 1.0f) 
	{

		return false;
	
	}

	Vector3 p = Add(segment.origin, Multiply(t, segment.diff));

	Vector3 edge0 = Subtract(v1, v0);
	Vector3 edge1 = Subtract(v2, v1);
	Vector3 edge2 = Subtract(v0, v2);

	Vector3 vp0 = Subtract(p, v0);
	Vector3 vp1 = Subtract(p, v1);
	Vector3 vp2 = Subtract(p, v2);

	Vector3 c0 = Cross(edge0, vp0);
	Vector3 c1 = Cross(edge1, vp1);
	Vector3 c2 = Cross(edge2, vp2);

	return Dot(c0, normal) >= 0.0f && Dot(c1, normal) >= 0.0f && Dot(c2, normal) >= 0.0f;

}

// AABB衝突判定
bool IsCollisionAABB(const AABB& aabb1, const AABB& aabb2) 
{

	if (aabb1.max.x < aabb2.min.x || aabb1.min.x > aabb2.max.x) 
	{
	
		return false;
	
	}

	if (aabb1.max.y < aabb2.min.y || aabb1.min.y > aabb2.max.y) 
	{
	
		return false;
	
	}

	if (aabb1.max.z < aabb2.min.z || aabb1.min.z > aabb2.max.z) 
	{
	
		return false;
	
	}

	return true;

}

// AABBと球の衝突判定
bool IsCollisionABS(const AABB& aabb, const Sphere& sphere) 
{

	Vector3 closestPoint;

	closestPoint.x = std::clamp(sphere.center.x, aabb.min.x, aabb.max.x);

	closestPoint.y = std::clamp(sphere.center.y, aabb.min.y, aabb.max.y);

	closestPoint.z = std::clamp(sphere.center.z, aabb.min.z, aabb.max.z);

	Vector3 diff = Subtract(closestPoint, sphere.center);

	float distance = Length(diff);

	return distance <= sphere.radius;

}

// AABBと線分の衝突判定
bool IsCollisionAABBSegment(const AABB& aabb, const Segment& segment) 
{

	float tMin = 0.0f;
	float tMax = 1.0f;

	// X軸
	if (segment.diff.x != 0.0f) 
	{
	
		float tx1 = (aabb.min.x - segment.origin.x) / segment.diff.x;
		float tx2 = (aabb.max.x - segment.origin.x) / segment.diff.x;

		tMin = (std::max)(tMin, (std::min)(tx1, tx2));
		tMax = (std::min)(tMax, (std::max)(tx1, tx2));
	
	} else if (segment.origin.x < aabb.min.x || segment.origin.x > aabb.max.x) {
	
		return false;
	
	}

	// Y軸
	if (segment.diff.y != 0.0f) 
	{
	
		float ty1 = (aabb.min.y - segment.origin.y) / segment.diff.y;
		float ty2 = (aabb.max.y - segment.origin.y) / segment.diff.y;

		tMin = (std::max)(tMin, (std::min)(ty1, ty2));
		tMax = (std::min)(tMax, (std::max)(ty1, ty2));
	
	} else if (segment.origin.y < aabb.min.y || segment.origin.y > aabb.max.y) {
	
		return false;
	
	}

	// Z軸
	if (segment.diff.z != 0.0f) 
	{
	
		float tz1 = (aabb.min.z - segment.origin.z) / segment.diff.z;
		float tz2 = (aabb.max.z - segment.origin.z) / segment.diff.z;

		tMin = (std::max)(tMin, (std::min)(tz1, tz2));
		tMax = (std::min)(tMax, (std::max)(tz1, tz2));
	
	} else if (segment.origin.z < aabb.min.z || segment.origin.z > aabb.max.z) {
	
		return false;
	
	}

	return tMin <= tMax;

}

// AABBと半直線の衝突判定
bool IsCollisionAABBRay(const AABB& aabb, const Ray& ray) 
{

	float tMin = 0.0f;
	float tMax = FLT_MAX;

	float tx1 = (aabb.min.x - ray.origin.x) / ray.diff.x;
	float tx2 = (aabb.max.x - ray.origin.x) / ray.diff.x;

	tMin = (std::max)(tMin, (std::min)(tx1, tx2));
	tMax = (std::min)(tMax, (std::max)(tx1, tx2));

	float ty1 = (aabb.min.y - ray.origin.y) / ray.diff.y;
	float ty2 = (aabb.max.y - ray.origin.y) / ray.diff.y;

	tMin = (std::max)(tMin, (std::min)(ty1, ty2));
	tMax = (std::min)(tMax, (std::max)(ty1, ty2));

	float tz1 = (aabb.min.z - ray.origin.z) / ray.diff.z;
	float tz2 = (aabb.max.z - ray.origin.z) / ray.diff.z;

	tMin = (std::max)(tMin, (std::min)(tz1, tz2));
	tMax = (std::min)(tMax, (std::max)(tz1, tz2));

	return tMin <= tMax;

}

// AABBと直線の衝突判定
bool IsCollisionAABBLine(const AABB& aabb, const Line& line) 
{

	float tMin = -FLT_MAX;
	float tMax = FLT_MAX;

	float tx1 = (aabb.min.x - line.origin.x) / line.diff.x;
	float tx2 = (aabb.max.x - line.origin.x) / line.diff.x;

	tMin = (std::max)(tMin, (std::min)(tx1, tx2));
	tMax = (std::min)(tMax, (std::max)(tx1, tx2));

	float ty1 = (aabb.min.y - line.origin.y) / line.diff.y;
	float ty2 = (aabb.max.y - line.origin.y) / line.diff.y;

	tMin = (std::max)(tMin, (std::min)(ty1, ty2));
	tMax = (std::min)(tMax, (std::max)(ty1, ty2));

	float tz1 = (aabb.min.z - line.origin.z) / line.diff.z;
	float tz2 = (aabb.max.z - line.origin.z) / line.diff.z;

	tMin = (std::max)(tMin, (std::min)(tz1, tz2));
	tMax = (std::min)(tMax, (std::max)(tz1, tz2));

	return tMin <= tMax;

}

/////////////////////
///  Acquisition  ///
/////////////////////

// 垂直ベクトル取得
Vector3 Perpendicular(const Vector3& vector) 
{

	if (vector.x != 0.0f || vector.y != 0.0f) 
	{
	
		return {-vector.y, vector.x, 0.0f};
	
	}

	return {0.0f, -vector.z, vector.y};

}

//////////////////////
///  Bezier curve  ///
//////////////////////

// 線形補間
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) 
{

	Vector3 result;

	result.x = (1.0f - t) * v1.x + t * v2.x;
	result.y = (1.0f - t) * v1.y + t * v2.y;
	result.z = (1.0f - t) * v1.z + t * v2.z;

	return result;

}

// 2次ベジェ曲線上の点を求める
Vector3 QuadraticBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t) 
{

	Vector3 p01 = Lerp(p0, p1, t);
	Vector3 p12 = Lerp(p1, p2, t);

	return Lerp(p01, p12, t);

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