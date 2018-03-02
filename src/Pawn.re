open Coord;

open Game;

let pieceWeight = 1.0;

let coefficient = 0.1;

let weight = (coord: coord, player: player) : float =>
  switch (coord, player) {
  | (Coord(_, y), Black /*cpu*/) =>
    pieceWeight -. float_of_int(y) *. coefficient
  | (Coord(_, y), White /*human*/) =>
    pieceWeight -. (7.0 -. float_of_int(y)) *. coefficient
  };

let isStrikable = (board: board, player: player, coord: coord) : bool =>
  validCoord(coord) && Piece.enemyOf(player, board |> at(coord));

let possibleSouthMoves =
    (coord: coord, board: board, player: player)
    : list(coord) => {
  let forward = coord |> next(South);
  let coords =
    switch coord {
    | Coord(_, 1) => [forward, forward |> next(South)]
    | _ => [forward]
    };
  let strikes =
    [forward, coord |> next(SouthEast), coord |> next(SouthWest)]
    |> List.filter(isStrikable(board, player));
  strikes @ coords;
};

let possibleNorthMoves =
    (coord: coord, board: board, player: player)
    : list(coord) => {
  let forward = coord |> next(North);
  let coords =
    switch coord {
    | Coord(_, 6) => [forward, forward |> next(North)]
    | _ => [forward]
    };
  let strikes =
    [forward, coord |> next(NorthEast), coord |> next(NorthWest)]
    |> List.filter(isStrikable(board, player));
  strikes @ coords;
};

let possibleMoves = (coord: coord, board: board, player: player) : list(coord) => {
  let moves =
    switch player {
    | Black => possibleSouthMoves(coord, board, Black)
    | White => possibleNorthMoves(coord, board, White)
    };
  moves |> List.filter(validCoord);
};