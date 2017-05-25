#ifndef CELL
#define CELL

namespace mnkgame {
namespace implementation {
	// Represents the three possible conditions of a board cell.
	enum Cell {
		EMPTY,
		X,
		O
	};
	// Return the Cell as a char.
	static char get_cell_char(const Cell cell) {
		if (cell == Cell::EMPTY)
			return ' ';
		return cell == Cell::X ? 'X' : 'O';
	}

} // namespace implementation
} // namespace tttsolver

#endif // CELL
