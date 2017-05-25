#include "game.h"

#include <cassert>
#include <iostream>

#include "cell.h"

namespace mnkgame {
namespace implementation {

	Game::Game(const int length, const int width, const int in_a_row)
			: length_(length),
			width_(width),
			k_(in_a_row),
			board_(std::make_unique<Cell[]>((size_t)(length * width))) {
		// Only allow positive (and non-zero) ints for all three parameters.
		assert(length > 0 && width > 0 && in_a_row > 0);
		InitBoard();
	}

	const Cell Game::CheckRange(const int first,
								const int increment,
								const int numIncrements) {
		const int last = first + (numIncrements * increment);
		// The last index which could potentially have a 'k'-in-a-row for the 
		// remainder of the range.
		int last_possible_start = last - increment * (k_ - 1);
		Cell current = Cell::EMPTY;
		int num_in_a_row = 0;

		for (int pos = first; pos <= last_possible_start;) {
			if (board_[pos] != Cell::EMPTY) {
				num_in_a_row = 1;
				if (k_ == 1) return board_[pos];
				current = board_[pos];
				pos += increment;
				while (board_[pos] == current) {
					pos += increment;
					if (++num_in_a_row == k_)
						return board_[pos];
				}
			}
			else {
				pos += increment;
			}
		}
		return Cell::EMPTY;
	}

	const Cell Game::FindWinner() {

		// Check horizontals.
		for (int y = 0; y < length_; ++y) { // for each row
			const int row_start = y * width_;
			this->CheckRange(row_start, 1, max_x_);
		}

		// Check verticals.
		for (int x = 0; x < width_; ++x) { // for each column
			this->CheckRange(x, width_, max_y_);
		}

		// Check diagonal: top-left to down-and-right.
		{		// TODO: ALL DIAGONALS
			const int shift_dwn_rt = width_ + 1; // the difference to the next diagonal's index (down and right)
			const int smallest_dimension = length_ < width_ ? length_ : width_;
			this->CheckRange(0, shift_dwn_rt, smallest_dimension);
		}

		// Check diagonal: top-right to down-and-left.
		{		// TODO: ALL DIAGONALS
			const int shift_dwn_left = width_ - 1;  // the difference to the next diagonal's index
			const int smallest_dimension = length_ < width_ ? length_ : width_;
			this->CheckRange(max_x_, shift_dwn_left, smallest_dimension);
		}

		// No winner found. (could be a tie)
		return Cell::EMPTY;
	}

	void Game::Print() const {
		for (int y = 0; y < length_; ++y) {
			const int shift = y * width_;
			for (int x = 0; x < width_; ++x) {
				std::cout << ' ' << get_cell_char(board_[x + shift]) << ' ';
				if (x < max_x_)
					std::cout << '|';
			}
			std::cout << std::endl;

			if (y < max_y_) {
				for (int x = 0; x < width_; ++x)
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
		// Cannot play a cell with empty.
		assert(x_or_o == Cell::X || x_or_o == Cell::O);
		// Ensure board has empty cells. Otherwise, may allow infinite while loop
		assert(!this->IsTie());

		int cell_idx;
		while (board_[(cell_idx = rand() % size_)] != Cell::EMPTY) {}
		board_[cell_idx] = x_or_o;
	}

} // namespace implementation
} // namespace tttsolver
