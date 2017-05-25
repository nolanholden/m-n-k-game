#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <memory>
#include "Cell.h"
#include "IPrintable.h"

namespace mnkgame {
namespace implementation {

class Game : public interfaces::IPrintable {
public:
	// Construct a new m,n,k-game, specifying length, width, and number in-a-row to win.
	Game(const int length, const int width, const int in_a_row);
	~Game() {}
	// Crudely print board. (provided for novelty only)
	void Print() const;
	void PlayX() {
		PlayRand(Cell::X);
	}
	void PlayO() {
		PlayRand(Cell::O);
	}
	// Return the Cell which has a complete row. If none, returns the empty cell.
	const Cell FindWinner();
	// Returns true if the board is completely full.
	bool IsTie() const {
		for (int i = 0; i < size_; ++i)
			if (board_[i] == Cell::EMPTY)
				return false; // If there are any empty cells, there is not a tie.
		return true;
	}
protected:
	// Board width.
	const int width_;
	// Board length.
	const int length_;
	// Number of in-a-row plays needed to win.
	const int k_;
	// Max value for x coordinate on board (where top left is P(0,0)).
	const int max_x_ = width_ - 1;
	// Max value for y coordinates on board (where top left is P(0,0)).
	const int max_y_ = length_ - 1;
	// Total number of cells on the board (dim_ * dim_).
	const int size_ = length_ * width_;
	// Last index of cells container (size_ - 1).
	const int last_idx_ = size_ - 1;
	// Implements a 2D container. (To access: pieces[x + y * width_])
	const std::unique_ptr<Cell[]> board_;

	// Fills board with Cell::EMPTY.
	void InitBoard();
	// Play the provided Cell in a random, empty cell.
	void PlayRand(const Cell& x_or_o);
	// Check for 'k'-in-a-row's over the specified range. Arguments are:
	// (starting index, increment size, number of increments to traverse)
	const Cell CheckRange(const int start, const int end, const int increment);
};

} // namespace implementation
} // namespace tttsolver

#endif // GAME_H
