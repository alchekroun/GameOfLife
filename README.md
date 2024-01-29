# GameOfLife

[Conway's Game Of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) implementation in C++ 17.

## Implementation
Three main classes:
- `life`: Calculate all generations and send them to the `gui`
- `gui`: Render each generation stored in its queue
- `game`: Host two threads, one for `life` and one for `gui`

## Demo
Pay attention to `Generation: XX*` when it has an asterisk symbol it means that the game is still calculating future generations. One they are all processed, the asterisk disapears.

![Demo](https://github.com/alchekroun/GameOfLife/raw/master/docs/demo.gif)