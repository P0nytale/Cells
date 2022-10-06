# Cells
John Conway's game of Life variant with neat color themes and somewhat different rules (2 vars), which leads to almost immortal colonies without them to spread too much.

		Conway's Game of Life variation: Cells!\n\
		Preliminary help\n\n\
		The main difference from the original B3/S23 rule is that when all three colors (arranged in two concurrent sets):\n\
		1. Orange/Red/Yellow and\n\
		2. Cyan/Black/Green\n\
		are met in the Moore's neighborhood of the empty cell: the Magenta (for Set 1) or Purple (for Set 2) cell is born.\n\
		Otherwise all four colors of one set acts as plain black cells in the original Conway's game of life. The color of the newborn, previously empty cell is determined by the plain superiority of the neighborhood's cells colors.\n\n\
		The Magenta/Purple cells are also act like the normal active cells except for the one new rule:\n\
		- Variant 1 (When when gr1/gr2 DryLife checkbox is unchecked): if there are 6 or 7 Magenta/Purple cells respectivaly in the Moore's neighborhood of the cell - the next turn it become one of three color of her Set, determined by the random. This is Conway's B3/S23 variation of the game.\n\n\
		- Variant 2 (When when gr1/gr2 DryLife checkbox is checked): if there are 7 living cells in the Moore's neighborhood and none are Magenta/Purple - the next turn it become one of three color of her Set, determined by the random. This is DryLife B37/S23 variation of the game.\n\n\
		This new rules leads to almost eternal, living population, starting from the very small populations (of course, random-driven mechanics), and not growing very fast, for the other side.\n\n\
		Also notice that Set 1 and Set 2 are just concurrenting for the area and explodees when it meets each other in the one cell neighborhood.\n\n\
		\n\
		Visual effects are just neat-looking graphics effects on the standart cells representation. Nothing special except for the finded by-chance (lucky logic error in the blur algorithm) cool colorings (try all of them, Alt modes also).\n\
		User interface:\n\
		- Draw cell-by-cell mode just at the game area by the left/right mouse button. The color of the cell is determined by the right-menu.\n\
		- Right-click on the fast in-build pattern buttons to cycle between the patterns.\n\
		- Right-click on the \"Load...\" pattern buttons to load pattern from .cells file (can be founded at https://www.conwaylife.com/).\n\
		- Right-menu can be moved if dragged by the upper side in the fullscreeen mode.\n\
		- Press r/R/m/M/p/P keys when putting a pattern at the game area to Rotate/Mirror\n\
		- Press n/N/p/P keys when putting a pattern at the game area to choose the Next/Previous build-in pattern.\n\
		- Press c/C keys to Clear\n\
		- Use your imagination! :)\

C++ Builder 10.4 source code and project.
P.S. Yes, I was too lazy to use separate .cpp/.h files and create their own classes for DrawWorld/NewGen functions, so they are just copypasted in their .h files respectively, included in Unit1.cpp, for convenience. Blame on me :).

© Ponytale 2021
