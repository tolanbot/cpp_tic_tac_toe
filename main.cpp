#include <iostream>
#include <string>
#include <vector>

const size_t ROWS = 3;
const size_t COLS = 3;

void run_game();
void initialize_board(std::string game_board[ROWS][COLS]);
void get_input(bool x_turn, std::string game_board[ROWS][COLS]);
bool cell_occupied(std::size_t row, std::size_t col,
                   std::string game_board[ROWS][COLS]);
bool is_board_full(std::string game_board[ROWS][COLS]);
void print_current_board(std::string game_board[ROWS][COLS]);
std::string get_winner(std::string game_board[ROWS][COLS]);

int main() {
  run_game();
  return 0;
}

void run_game() {
  std::string game_board[ROWS][COLS];
  initialize_board(game_board);
  std::cout << "----- TIC TAC TOE -----" << std::endl;
  print_current_board(game_board);
  bool x_turn = true;
  std::string winner = " ";
  bool board_full = false;
  while (winner == " " && !board_full) {
    get_input(x_turn, game_board);
    print_current_board(game_board);
    x_turn = !x_turn;
    board_full = is_board_full(game_board);
    winner = get_winner(game_board);
  }
  if (board_full) {
    std::cout << "No Winner! Board is full." << std::endl;
    return;
  }
  std::cout << "Congratulations " << winner << "!!! You are the winner!"
            << std::endl;
}

void initialize_board(std::string game_board[ROWS][COLS]) {
  for (std::size_t row = 0; row < ROWS; row++) {
    for (std::size_t col = 0; col < COLS; col++) {
      game_board[row][col] = " ";
    }
  }
}

void print_current_board(std::string game_board[ROWS][COLS]) {
  std::cout << std::endl;
  for (std::size_t row = 0; row < ROWS; row++) {
    for (std::size_t col = 0; col < COLS; col++) {
      std::string col_separator = (col != COLS - 1) ? " | " : "\n";
      std::cout << game_board[row][col] << col_separator;
    }
    std::string row_separator = (row != ROWS - 1) ? "- - - - -" : "";
    std::cout << row_separator << std::endl;
  }
}

void get_input(bool x_turn, std::string game_board[ROWS][COLS]) {
  std::string move_prompt = x_turn ? "X to move..." : "O to move...";
  std::string move;
  while (true) {
    std::cout << move_prompt << std::endl
              << "Enter row, then column, separated by a space: ";
    std::getline(std::cin, move);
    if (move.empty() || move.size() > 3) {
      std::cout << "invalid input. try again..." << std::endl;
      continue;
    }
    std::size_t row = move[0] - '0' - 1;
    std::size_t col = move[2] - '0' - 1;
    if (row > ROWS || col > COLS) {
      std::cout << "invalid input. index out of bounds." << std::endl
                << std::endl;
      continue;
    }
    std::string move_value = x_turn ? "X" : "O";
    if (cell_occupied(row, col, game_board)) {
      std::cout << "Cell aleady occupied, please choose again." << std::endl
                << std::endl;
      continue;
    }
    game_board[row][col] = move_value;
    break;
  }
}

bool cell_occupied(std::size_t row, std::size_t col,
                   std::string game_board[ROWS][COLS]) {
  return (game_board[row][col] == "X" || game_board[row][col] == "O");
}

std::string get_winner(std::string game_board[ROWS][COLS]) {
  // row loop
  for (std::size_t row = 0; row < ROWS; row++) {
    std::string prev = game_board[row][0];
    if (prev != " ") {
      for (std::size_t col = 1; col < COLS; col++) {
        std::string curr = game_board[row][col];
        if (prev != curr) {
          break;
        }
        if (col == COLS - 1) {
          return prev;
        }
      }
    }
  }

  // col loop
  for (std::size_t col = 0; col < COLS; col++) {
    std::string prev = game_board[0][col];
    if (prev != " ") {
      for (std::size_t row = 1; row < ROWS; row++) {
        std::string curr = game_board[row][col];
        if (prev != curr) {
          break;
        }
        if (row == ROWS - 1) {
          return prev;
        }
      }
    }
  }

  // diagonals
  std::string prev = game_board[0][0];
  if (prev != " ") {
    if (game_board[1][1] == prev && game_board[2][2] == prev) {
      return prev;
    }
  }
  prev = game_board[0][COLS - 1];
  if (prev != " ") {
    if (game_board[1][1] == prev && game_board[2][0] == prev) {
      return prev;
    }
  }

  return " ";
}

bool is_board_full(std::string game_board[ROWS][COLS]) {
  for (std::size_t row = 0; row < ROWS; row++) {
    for (std::size_t col = 0; col < COLS; col++) {
      if (!cell_occupied(row, col, game_board)) {
        return false;
      }
    }
  }
  return true;
}
