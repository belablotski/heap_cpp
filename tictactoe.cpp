#include <iostream>
#include <vector>
#include <optional>
#include <limits>

enum class Mark {
    X,
    O
};

std::ostream& operator<<(std::ostream& os, Mark mark) {
    if (mark == Mark::X) {
        os << "X";
    } else {
        os << "O";
    }
    return os;
}

using MarkOptional = std::optional<Mark>;

class Board {
public:
    explicit Board(const int n = 3) : _grid(n, std::vector<MarkOptional>(n)) {}

    int size() const {
        return _grid.size();
    }

    void display() const {
        for (const auto& row : _grid) {
            for (const auto& cell : row) {
                if (!cell.has_value()) {
                    std::cout << ".";
                } else if (cell.value() == Mark::X) {
                    std::cout << "X";
                } else {
                    std::cout << "O";
                }
                std::cout << " ";
            }
            std::cout << '\n';
        }
    }

    MarkOptional getCellState(const int row, const int col) const {
        return _grid.at(row).at(col);
    }

    bool setCellState(int row, int col, Mark mark) {
        if (getCellState(row, col).has_value()) {
            throw std::logic_error("Cell is already occupied");
        }
        else {
            _grid[row][col] = mark;
        }
        return checkCompletedLine(row, col, mark);
    }

    bool emptyCellExists() const {
        for (const auto row : _grid)
            for (const auto cell: row)
                if (!cell.has_value())
                    return true;
        return false;
    }

protected:
    bool checkCompletedLine(const int row, const int col, Mark mark) const {
        int vcnt = 0, hcnt = 0, d1cnt = 0, d2cnt = 0;
        for (int i=0; i<size(); i++) {
            if (_grid[i][col] == mark)
                vcnt++;
            if (_grid[row][i] == mark)
                hcnt++;
            if (_grid[i][i] == mark)
                d1cnt++;
            if (_grid[i][_grid.size() - i - 1] == mark)
                d2cnt++;
        }
        return vcnt == size() || hcnt == size() || d1cnt == size() || d2cnt == size();
    }

private:
    std::vector<std::vector<MarkOptional>> _grid;
};

class Player {
public:
    explicit Player(const Mark mark) : _mark {mark} { }
    virtual ~Player() = default;

    Mark getMark() const {
        return _mark;
    }

    virtual std::pair<int, int> makeMove(const Board& board) = 0;

private:
    Mark _mark;
};

class HumanPlayer : public Player {
public:
    explicit HumanPlayer(Mark mark) : Player(mark) {}

    std::pair<int, int> makeMove(const Board& board) override {
        int row, col;
        while (true) {
            std::cout << "Player " << getMark() << ", enter your move (row and column): ";
            std::cin >> row >> col;
            if (!std::cin) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter two integers." << std::endl;
                continue;
            }
            try {
                if (!board.getCellState(row, col).has_value()) {
                    break;
                } else {
                    std::cout << "Cell is already occupied. Try again." << std::endl;
                }
            } catch (std::out_of_range) {
                std::cout << "Invalid cell coordinates. Try again." << std::endl;
                std::cout.flush();
            }
        }
        return {row, col};
    }
};

class MachinePlayer : public Player {
public:
    explicit MachinePlayer(Mark mark) : Player(mark) { }

    virtual std::pair<int, int> makeMove(const Board& board) override {
        int n = board.size();
        int row, col;
        do {
            row = rand() % n;
            col = rand() % n;
        } while (board.getCellState(row, col).has_value());
        std::cout << "Machine player " << getMark() << " moves to: " << row << " " << col << std::endl;
        return {row, col};
    }
};

class Game {
public:
    explicit Game(Player& p1, Player& p2, Board& board)
        : _player1(p1), _player2(p2), _board(board) {}

    /**
     * @brief Runs the main game loop for Tic-Tac-Toe.
     *
     * Alternates turns between two players, allowing each to make a move until the board is full or a player wins.
     * The board is displayed after each move. If a player wins, a pointer to the winning player is returned.
     * If the game ends in a draw (no empty cells remain), returns nullptr.
     *
     * @return Player* Pointer to the winner player, or nullptr if the game is a draw.
     */
    Player* play() {
        Player* currentPlayer = &_player1;

        while (true) {
            _board.display();
            if (!_board.emptyCellExists()) {
                return NULL;
            }
            auto move = currentPlayer->makeMove(_board);
            if (_board.setCellState(move.first, move.second, currentPlayer->getMark())) {
                return currentPlayer;
            }
            currentPlayer = currentPlayer == &_player2 ? &_player1 : &_player2;
        }
    }

private:
    Player& _player1;
    Player& _player2;
    Board& _board;
};

int main() {
    std::cout << "This is a Tic Tac Toe game." << std::endl;
    HumanPlayer player1(Mark::X);
    MachinePlayer player2(Mark::O);
    Board board;
    Game game(player1, player2, board);
    Player* winner = game.play();
    board.display();
    if (winner) {
        std::cout << "Player " << winner->getMark() << " wins!";
    }
    else {
        std::cout << "Draw game!";
    }
    return 0;
}