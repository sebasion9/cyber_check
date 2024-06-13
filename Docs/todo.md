## pieces & logic
- defense against check mechanic(from other pieces)
- checkmate
- en passant and castle
- optimize pieces for loops

## state
- add 2nd clocks on separate threads
- handle win condition

## player
- add piece move invoking by method(to support chess engine)
- make moves compatible with invoking and moving by mouse

## general
- optimize the parts where sf objects are initialized

## stockfish

## deadline
1. mechanics
	- pawn ua
	- pawn start attack
	- last fixes on saveable fields
	- add draw
	- add checkmate
	- add castle
2. views
	- add time counters
	- add forfeit/draw button
	- add endscreen after the game
3. menus
- add main menu containing:
	- audio options
	- start the game
		- select time
			-players name
	- leaderboard
4. audio
- on checkmate/draw
