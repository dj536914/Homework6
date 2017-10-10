// Commented by Griffin Jones
// dj536914@ohio.edu

// Brock Ferrell
// CS2401
// November 23, 2015
// Project7

#include "othello.h"

namespace main_savitch_14
{
///
/// Prints the board in its current state
///
void Othello::display_status()const
{
  cout << BLUE << "   _______ _______ _______ _______ _______ _______ _______ _______\n";
  cout << BLUE << "   |  A  | |  B  | |  C  | |  D  | |  E  | |  F  | |  G  | |  H  |" << endl;

  for (int y = 0; y < 8; y++)
  {
    cout << BLUE << "  " << y + 1 << BLUE << '|' << RESET;
    for (int x = 0; x < 8; x++)
    {
      if (!gameBoard[x][y].is_black() && !gameBoard[x][y].is_white())
      {
        cout << B_RED << "     " << RESET;
      }
      else if (gameBoard[x][y].is_black())
      {
        cout << B_BLACK << WHITE << BOLD << "  B  " << RESET;
      }
      else if (gameBoard[x][y].is_white())
      {
        cout << B_WHITE << BLACK << BOLD << "  W  " << RESET;
      }

      if (x == 7)
      {
        cout << BLUE << "|     " << RESET;
      }
      else if (y < 8 && x <= 6)
      {
        cout << BLUE << "| |" << RESET;
      }
    }
    if (y < 8)
    {
      cout << BLUE << endl << "   |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____|\n";
    }
  }
  cout << "\nEnter a move in the format(letter,number) (Ex: A3)" << endl;
}
///
/// Adds a given move to the game board (assumes the move has already been
/// proven to be valid)
/// @param  move: a two character string representing the player's move
///
void Othello::make_move(const string& move) {

  int c, r;
  c = int(toupper(move[0]) - 'A');
  r = int(move[1] - '1');

  if (next_mover() == HUMAN) {
    if (move == "s" || move == "S") {
      make_skips();
    }

    else if (gameBoard[c + 1][r].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c++;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c - 1][r].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c--;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c][r + 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        r++;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c][r - 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        r--;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c + 1][r - 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c++;
        r--;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c - 1][r - 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c--;
        r--;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c - 1][r + 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c--;
        r++;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c + 1][r + 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c++;
        r++;
      } while (gameBoard[c][r].is_white());
    }
  }

  if (next_mover() == COMPUTER) {
    if (move == "s" || move == "S") {
      make_skips();
    }

    else if (gameBoard[c + 1][r].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c++;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c - 1][r].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c--;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c][r + 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        r++;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c][r - 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        r--;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c + 1][r - 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c++;
        r--;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c - 1][r - 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c--;
        r--;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c - 1][r + 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c--;
        r++;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c + 1][r + 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c++;
        r++;
      } while (gameBoard[c][r].is_black());
    }
    skips = 0;
  }
  move_number++;
}

///
/// Resets the game board to the starting position, placing the four pieces in
/// the middle of the board
///
void Othello::restart() {

  gameBoard[3][3].set_white();
  gameBoard[3][4].set_black();
  gameBoard[4][3].set_black();
  gameBoard[4][4].set_white();

  white = 2;
  black = 2;
  skips = 0;
  openSpots = 60;
}
///
/// Checks if a move is legal by travelling in every direction in the board
/// around a given position, seeing if there is a line of the opposing color
/// ending in a piece of the player's color. Returns true if a move is legal.
/// @param  move: A two character string representing the player's move
/// @return bool  true if the move is legal; false if the move is illegal
///
bool Othello::is_legal(const string& move)const {

  int c, r;
  c = int(toupper(move[0]) - 'A');
  r = int(move[1] - '1');

// BLACK'S TURN
  if (next_mover() == HUMAN) {
    if (gameBoard[c][r].is_blank()) {
      if (gameBoard[c][r - 1].is_white()) {
        do {
          r--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());

      }

      if (gameBoard[c][r + 1].is_white()) {
        do {
          r++;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());

      }

      if (gameBoard[c + 1][r].is_white()) {
        do {
          c++;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());

      }

      if (gameBoard[c - 1][r].is_white()) {
        do {
          c--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c + 1][r - 1].is_white()) {
        do {
          c++;
          r--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c - 1][r - 1].is_white()) {
        do {
          c--;
          r--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c - 1][r + 1].is_white()) {
        do {
          c--;
          r++;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c + 1][r + 1].is_white()) {
        do {
          c++;
          r++;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }
    } else {
      return false;
    }
  }

// WHITE'S TURN
  if (next_mover() == COMPUTER) {
    if (gameBoard[c][r].is_blank()) {
      if (gameBoard[c][r - 1].is_white()) {
        do {
          r--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c][r + 1].is_black()) {
        do {
          r++;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c + 1][r].is_black()) {
        do {
          c++;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c - 1][r].is_black()) {
        do {
          c--;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c + 1][r - 1].is_black()) {
        do {
          c++;
          r--;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());

      }

      if (gameBoard[c - 1][r - 1].is_black()) {
        do {
          c--;
          r--;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c - 1][r + 1].is_black()) {
        do {
          c--;
          r++;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c + 1][r + 1].is_black()) {
        do {
          c++;
          r++;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }
    } else {
      return false;
    }
  }
}
///
/// Totals the number of pieces on the board of each color and prints the
/// results
///
void Othello::countingPieces() {

  int black = 0;
  int white = 0;

  for (int b = 0; b < 8; b++) {
    for (int a = 0; a < 8; a++) {
      if (gameBoard[a][b].is_white()) {
        white++;
      } else if (gameBoard[a][b].is_black()) {
        black++;
      }
    }
  }
  cout << "Total move: " << moves_completed() << endl;
  openSpots = 64 - (black + white);
  cout << "Black: "  << black << " ---" << " White: " << white;
  cout << endl;
}
///
/// Checks if any of the triggers to end the game have been reached
/// @return bool  true if the game has ended; false if the game has not.
///
bool Othello::is_game_over()const {

  if (skips == 2 || openSpots == 0 || black == 0 || white == 0) {
    cout << "The game is over.\n";
    return true;
  }
  else {
    return false;
  }
}
///
/// Checks whose turn it is, and prints the result to the screen
///
void Othello::whosTurn() {
  if (next_mover() == COMPUTER) {
    cout << "\nWhite's Turn!" << endl;
  }

  if (next_mover() == HUMAN) {
    cout << "\nBlack's Turn!" << endl;
  }
}
///
/// Increments the number of skips
///
void Othello::make_skips() {
  skips++;
}
///
/// Returns who is winning the game
/// @return last_mover(), next_mover(), or NEUTRAL
///
game::who Othello::winning()const {

  if (black > white) {
    return last_mover();
  } else if (white > black) {
    return next_mover();
  } else {
    return NEUTRAL;
  }
}
///
/// Evaluates who has more pieces, adding 5 to the count for every corner a
/// player has control over
/// @return b   if black has more pieces and corners than white
/// @return w   if white has more pieces and corners than black
///
int Othello::evaluate()const {

  int tmp_white = w;
  int tmp_black = b;

  if (gameBoard[0][0].is_white() || gameBoard[7][7].is_white() || gameBoard[0][7].is_white() || gameBoard[7][0].is_white()) {
    tmp_white += 5;
  }
  if (gameBoard[0][0].is_black() || gameBoard[7][7].is_black() || gameBoard[0][7].is_black() || gameBoard[7][0].is_black()) {
    tmp_black += 5;
  }

  if (b > w) {
    return b;
  } else if (w > b) {
    return w;
  }
}
///
/// Incrementally checks which moves in a list of moves are legal
/// @param  moves: a queue of moves
///
void Othello::compute_moves(std::queue<std::string>& moves)const {
  string r;
  string c;
  string move;

  for (int i = 0; i < 8; i++) {
    c = i + 'A';
    for (int j = 0; j < 8; j++) {
      r = j + '1';
      move = c + r;
      if (is_legal(move)) {
        moves.push(move);
      }
      else {

      }
    }
  }
}

}
