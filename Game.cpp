#include "Game.h"
#include "TitleState.h"

Game::Game() {
	// 最初はタイトル画面
	state_ = new TitleState();
}

Game::~Game() { delete state_; }

void Game::Update() {
	// キー入力更新
	input_.Update();

	// 現在のシーン更新
	state_->Update(this);
}

void Game::Draw() {
	// 現在のシーン描画
	state_->Draw();
}

void Game::ChangeState(IState* state) {
	// 古いシーンを削除
	delete state_;

	// 新しいシーンへ
	state_ = state;
}

InputManager* Game::GetInput() { return &input_; }