# Systems Project 2: Battleship
Created by: Winnie Chen, Yedoh Kang, Jackie Xu (Period 4)

## Launch Instructions

1. Open up the terminal.
2. Follow these instructions:
```
$ git clone https://github.com/jacqxu00/SystemsProject2.git
$ cd SystemsProject2
$ make
$ make run
```
3. Have fun!



## Playing Instructions
There is a setup phase in which you place your ships, then a playing phase in which you and your opponent begin competing. All standard Battleship rules apply. Syntax (aka player input) instructions are also displayed in the game.

Neither you nor your opponent know where each other's ships are placed. You take turns sending missiles to each other's fields trying to sink each other's ships. A ship is sunk when all of the coordinates it occupies are hit. A "miss" occurs when the missile lands in water.

### Setup Phase

You will be asked to input the ship, the starting coordinates of the location, and the direction in which it extends.
1. the available ships
  * A: aircraft, size 5
  * B: battleship, size 4
  * C: cruiser, size 3
  * D: destroyer, size 2
2. the letter and digit corresponding to the column and the row
3. the letter representing the direction
  * L: left
  * R: right
  * U: up
  * D: down

For example: S A0 D will place a submarine occupying A0, A1, and A2

### Playing Phase

You will be asked to input the coordinates of the location you would
like to send a missile to.
* For example: A0

Here is what the board display means:
* `.` (empty slot)
* `*` (missed ship)
* `H` (hit ship)
