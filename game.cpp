#include <iostream>                         //Код написан специально для портфолио на сайте freelancehunt.com !
#include <array>

enum class CellState { Empty, Cross, Circle };

struct Board {
    std::array<std::array<CellState, 3>, 3> cells;

    Board() {
        for (auto& row : cells) {
            row.fill(CellState::Empty);
        }
    }

    bool isFull() const {
        for (const auto& row : cells) {
            for (const auto& cell : row) {
                if (cell == CellState::Empty) {
                    return false;
                }
            }
        }
        return true;
    }

    void print() const {
        std::cout << "  1 2 3\n";
        for (int i = 0; i < 3; i++) {
            std::cout << char('a' + i) << ' ';
            for (int j = 0; j < 3; j++) {
                switch (cells[i][j]) {
                    case CellState::Empty:
                        std::cout << "_ ";
                        break;
                    case CellState::Cross:
                        std::cout << "X ";
                        break;
                    case CellState::Circle:
                        std::cout << "O ";
                        break;
                }
            }
            std::cout << '\n';
        }
    }
};

bool checkWin(const Board& board, CellState symbol) {
    // check rows
    for (int i = 0; i < 3; i++) {
        if (board.cells[i][0] == symbol && board.cells[i][1] == symbol && board.cells[i][2] == symbol) {
            return true;
        }
    }
    // check columns
    for (int j = 0; j < 3; j++) {
        if (board.cells[0][j] == symbol && board.cells[1][j] == symbol && board.cells[2][j] == symbol) {
            return true;
        }
    }
    // check diagonals
    if (board.cells[0][0] == symbol && board.cells[1][1] == symbol && board.cells[2][2] == symbol) {
        return true;
    }
    if (board.cells[0][2] == symbol && board.cells[1][1] == symbol && board.cells[2][0] == symbol) {
        return true;
    }
    return false;
}

int main() {
    std::cout << "Добро пожаловать в игру \"Крестики-нолики\"!\n";
    std::cout << "Игрок 1 (X), введите свое имя: ";
    std::string player1;
    std::getline(std::cin, player1);
    std::cout << "Игрок 2 (O), введите свое имя: ";
    std::string player2;
    std::getline(std::cin, player2);

    Board board;

    CellState currentPlayer = CellState::Cross; // Player 1 goes first
    std::string currentName = player1;

    while (true) {
        board.print();
        std::cout << currentName << " (" << (currentPlayer == CellState::Cross ? "X" : "O") << "), введите координаты ячейки (например, a1): ";
        std::string input;
        std::getline(std::cin, input);
        if (input.size() != 2 || input[0] < 'a' || input[0] > 'c' || input[1] < '1' || input[1] > '3') {
            std::cout << "Некорректный ввод, попробуйте еще раз.\n";
            continue;
        }
        int row = input[0] - 'a';
        int col = input[1] - '1';
        if (board.cells[row][col] != CellState::Empty) {
            std::cout << "Ячейка уже занята, попробуйте еще раз.\n";
            continue;
        }
        board.cells[row][col] = currentPlayer;
        if (checkWin(board, currentPlayer)) {
            std::cout << currentName << " победил!\n";
            break;
        }
        if (board.isFull()) {
            std::cout << "Ничья!\n";
            break;
        }
        // switch players
        currentPlayer = (currentPlayer == CellState::Cross ? CellState::Circle : CellState::Cross);
        currentName = (currentName == player1 ? player2 : player1);
    }

    board.print();

    return 0;
}
