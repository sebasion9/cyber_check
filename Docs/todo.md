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
0. ehhhh
	- filesystem
	- ranges
	- regex
	- thread(done)
1. general
	- handle checkmate and ending the game
	- leaderboard
2. games
	- add time counters
	- add forfeit/draw button
	- add endscreen after the game
3. menus
- menu structure:
	- options
		+music slider
		+sounds slider
		- back
	- start the game
		- select time
			+3:00
			+5:00
			+10:00
		- players name
			+input1
			+input2
		- play
		- back
	- leaderboard
		+leaderboard display
		- back
- menu todo:
	1. play
		- inputs, validation for names
		- send time, player names to the game

4. audio
- on checkmate/draw

