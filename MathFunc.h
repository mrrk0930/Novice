#pragma once
#include <Novice.h>
#include <cstdint>

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

//文字の幅高さ
const int kRowHeight = 20;
const int kColumnWidth = 60;

struct Sphere 
{

	Vector3 center;
	float radius;

};

struct Segment 
{

	Vector3 origin;
	Vector3 diff;

};

struct Plane 
{

	Vector3 normal;
	float distance;

};


////////////////
///  Vector  ///
////////////////

//ベクトルの加算
Vector3 Add(const Vector3& v1, const Vector3& v2);

//ベクトルの減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

//ベクトルとスカラーの積
Vector3 Multiply(float scalar, const Vector3& v);

//内積
float Dot(const Vector3& v1, const Vector3& v2);

//クロス積（外積）
Vector3 Cross(const Vector3& v1, const Vector3& v2);

//ベクトルの長さ
float Length(const Vector3& v);

//正規化
Vector3 Normalize(const Vector3& v);

////////////////
///  Matrix  ///
////////////////

//行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

//行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

//単位行列の作成
Matrix4x4 MakeIdentity4x4();

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

//転置行列
Matrix4x4 Transpose(const Matrix4x4& m);

//////////////////
///  Rotation  ///
//////////////////

//X軸の回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

//Y軸の回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

//Z軸の回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

///////////////////
///  Transform  ///
///////////////////

//平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

//3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

////////////////////
///  Projection  ///
////////////////////

//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

//////////////
///  Draw  ///
//////////////

//グリッド
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

//球
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

//平面
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

//線分
void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/////////////////
///  Utility  ///
/////////////////

//カメラ
Matrix4x4 MakeViewProjectionMatrix(const Vector3& cameraTranslate, const Vector3& cameraRotate, float windowWidth, float windowHeight);

//球ImGui
void UpdateImGui(Vector3& cameraTranslate, Vector3& cameraRotate, Sphere& sphere);

//平面ImGui
void UpdatePlaneImGui(Sphere& sphere, Plane& plane);

//線分ImGui
void UpdateSegmentImGui(Segment& segment, Plane& plane);

////////////////////////
///  GeometryUtility ///
////////////////////////

//射影
Vector3 Project(const Vector3& v1, const Vector3& v2);

//最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

///////////////
///  Move  ////
///////////////

//移動・回転
void UpdateMove(Vector3& translate, Vector3& rotate, char keys[]);

/////////////////
///  Action  ////
/////////////////

//球と球の衝突判定
bool IsCollisionSS(const Sphere& s1, const Sphere& s2);

//球と平面の衝突判定
bool IsCollisionSP(const Sphere& sphere, const Plane& plane);

//平面と線分
bool IsCollisionPL(const Segment& segment, const Plane& plane);

/////////////////////
///  Acquisition  ///
/////////////////////

//垂直ベクトル取得
Vector3 Perpendicular(const Vector3& vector);

///////////////
///  Print  ///
///////////////

// Matrix表示
void MatrixScreenPrintf(int x, int y, const char* label, const Matrix4x4& matrix);

// Vector表示
void VectorScreenPrintf(int x, int y, const char* label, const Vector3& vector);