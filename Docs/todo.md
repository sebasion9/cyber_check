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

## raw thoughts
saving logic
ONLY legal moves, for every piece now, are (piece.legal_moves & SAVEABLE_MOVES)
soo iterate over pieces again and change its legal moves to ^
but kings moves are not changed
include in saveable: 
1. fields that are between attacking piece and king
2. fields that the attacking piece stands on
create the saveable fields in board class
use the enum MoveType to determine the "ray" of attack and append the fields
WINS the !State::turn(), checkmate flag is turned on when:
1. king.legal_fields().size() < 1
2. saveable.size() < 1
3. king.is_checked()
in summary
1. write calc_saveable_fields on board class, containing fields that are on "ray" of attack
and the fields the delivering check piece stands (but if there are more than 2 pieces
delivering check, then dont append them to saveable as its impossible to hit any of them then)
2. determine the checkmate when the 3 conditions are met
3. return the winning player, that is the opposite of current turn
  