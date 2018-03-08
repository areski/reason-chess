open Game;

let pawnWeight = (player: player, coord: coord) : float => {
  let pieceWeight = 1.0;
  let coefficient = 0.1;
  switch (coord, player) {
  | (Coord(_, 0), White) => 5.0 /* reaching this cell */
  | (Coord(_, 7), Black) => 5.0 /* pawn becomes queen */
  | (Coord(_, y), White) =>
    pieceWeight +. (7.0 -. float_of_int(y)) *. coefficient
  | (Coord(_, y), Black) => pieceWeight +. float_of_int(y) *. coefficient
  };
};

let weight = (player: player, coord: coord, piece: piece) : float =>
  switch (piece) {
  | Pawn => pawnWeight(player, coord)
  | Rook
  | Bishop => 2.0
  | Knight => 3.0
  | Queen => 5.0
  | King => 10.0
  };