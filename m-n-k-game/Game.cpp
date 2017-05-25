#include "Game.h"
#include "Cell.h"
#include <cassert>
#include <iostream>

namespace mnkgame {
namespace implementation {

	Game::Game(const int length, const int width, const int in_a_row)
		: dim_(dimension),
		board_(std::make_unique<Cell[]>((size_t)(dimension * dimension))) {
		assert(dimension > 0);
		InitBoard();
	}

	const Cell Game::FindWinner() const {

		// Check horizontals.
		for (int y = 0; y < length_; ++y) { // for each row
			const int shift = y * width_;
			int x = 0;
			if (board_[x + shift] != Cell::EMPTY) {
				while (board_[x++ + shift] == board_[x + shift]) {
					if (x == max_coordinate_)
						return board_[shift]; // Return any cell on current horizontal. (since all match)
				}
			}
		}

		// Check verticals.
		for (int x = 0; x < width_; ++x) { // for each column
			int y = 0;
			if (board_[x + y * width_] != Cell::EMPTY) {
				while (board_[x + y++ * width_] == board_[x + y * width_]) {
					if (y == max_coordinate_)
						return board_[x + y * width_]; // Return any cell on current verticle. (since all match)
				}
			}
		}

		// Check diagonal: top-left to down-and-right.
		{
			const int shift_dwn_rt = width_ + 1; // the difference to the next diagonal's index (down and right)
			int i = 0; // top-left cell index
			if (board_[i] != Cell::EMPTY) {
				while (board_[i] == board_[i + shift_dwn_rt]) {
					i += shift_dwn_rt;
					if (i == last_idx_) // if at the end (bottom-right)
						return board_[i];
				}
			}
		}

		// Check diagonal: top-right to down-and-left.
		{
			const int shift_dwn_left = width_ - 1;  // the difference to the next diagonal's index
			int i = max_coordinate_;  // top-right cell index
			const int end = max_coordinate_ * width_; // bottom-left cell index
			if (board_[i] != Cell::EMPTY) {
				while (board_[i] == board_[i + shift_dwn_left]) {
					i += shift_dwn_left;
					if (i == end) // if at the end (bottom-left)
						return board_[i];
				}
			}
		}

		// No winner found. (could be a tie)
		return Cell::EMPTY;
	}

	void Game::Print() const {
		for (int y = 0; y < dim_; ++y) {
			const int shift = y * dim_;
			for (int x = 0; x < dim_; ++x) {
				std::cout << ' ' << get_cell_char(board_[x + shift]) << ' ';
				if (x < max_coordinate_)
					std::cout << '|';
			}
			std::cout << std::endl;

			if (y < max_coordinate_) {
				for (int i = 0; i < dim_; ++i)
					std::cout << "----";
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}

	void Game::InitBoard() {
		for (int i = 0; i < last_idx_; ++i) {
			board_[i] = Cell::EMPTY;
		}
	}

	void Game::PlayRand(const Cell& x_or_o) {
		assert(x_or_o != Cell::EMPTY); // Cannot play a cell with empty, only X or O.
		assert(!this->IsTie()); // Ensure board has empty cells. Otherwise, may allow infinite while loop

		int cell_idx;
		while (board_[(cell_idx = rand() % size_)] != Cell::EMPTY) {}
		board_[cell_idx] = x_or_o;
	}

	//void TicTacToe::PlaySmart(const Cell& x_or_o) {
	//  assert(x_or_o != Cell::EMPTY); // Cannot play a cell with empty, only X or O.
	//  assert(!this->IsTie()); // Ensure board has empty cells. Otherwise, may allow infinite loop in while
	//
	//                          // Make any winning moves.
	//  if (this->PlayWinningMove(x_or_o))
	//    return;
	//
	//  // Prevent imminent loss. (prioritizes one-away losses)
	//  if (this->PlayToSurvive(x_or_o))
	//    return;
	//
	//  // Pick best corner.
	//  if (this->PlayGoodCorner(x_or_o))
	//    return;
	//
	//  // Prevent soon-to-be loss.
	//  if (this->PlayToDefend(x_or_o))
	//    return;
	//}

	//bool TicTacToe::PlayWinningMove(const Cell x_or_o) {
	//
	//}
	//
	//bool TicTacToe::PlayToSurvive(const Cell x_or_o) {
	//}
	//
	//bool TicTacToe::PlayGoodCorner(const Cell x_or_o) {
	//}
	//
	//bool TicTacToe::PlayToDefend(const Cell x_or_o) {
	//}


} // namespace implementation
} // namespace tttsolver
