#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#define X_VAL 1
#define O_VAL -1
#define BLANK 0

int computeScore(vector<vector<int>> &grid) {
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != BLANK)
            return grid[i][0];
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != BLANK)
            return grid[0][i];
    }
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != BLANK)
        return grid[0][0];
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != BLANK)
        return grid[0][2];
    return 0;
}

bool availableMoves(vector<vector<int>> &grid) {
    for (auto &row : grid)
        for (auto cell : row)
            if (cell == BLANK) return true;
    return false;
}

void displayGrid(vector<vector<int>> &grid, int level, int alpha, int beta) {
    cout << "\nLevel " << level << " : Alpha = " << alpha << ", Beta = " << beta << "\n";
    for (auto &row : grid) {
        for (auto cell : row)
            cout << (cell == X_VAL ? "X " : cell == O_VAL ? "O " : ". ");
        cout << "\n";
    }
    cout << "----------------\n";
}

int searchMinimax(vector<vector<int>> &grid, int depth, bool maximize, int alpha, int beta) {
    int score = computeScore(grid);
    if (score == X_VAL) return 10 - depth;
    if (score == O_VAL) return depth - 10;
    if (!availableMoves(grid)) return 0;

    displayGrid(grid, depth, alpha, beta);

    if (maximize) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] == BLANK) {
                    grid[i][j] = X_VAL;
                    best = max(best, searchMinimax(grid, depth + 1, false, alpha, beta));
                    grid[i][j] = BLANK;
                    alpha = max(alpha, best);
                    if (beta <= alpha) {
                        cout << "Cutoff at level " << depth << " : Alpha = " << alpha << ", Beta = " << beta << "\n";
                        return best;
                    }
                }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] == BLANK) {
                    grid[i][j] = O_VAL;
                    best = min(best, searchMinimax(grid, depth + 1, true, alpha, beta));
                    grid[i][j] = BLANK;
                    beta = min(beta, best);
                    if (beta <= alpha) {
                        cout << "Cutoff at level " << depth << " : Alpha = " << alpha << ", Beta = " << beta << "\n";
                        return best;
                    }
                }
        return best;
    }
}

pair<int, int> optimalMove(vector<vector<int>> &grid) {
    int bestScore = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == BLANK) {
                grid[i][j] = X_VAL;
                int moveScore = searchMinimax(grid, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
                grid[i][j] = BLANK;
                if (moveScore > bestScore) {
                    bestMove = {i, j};
                    bestScore = moveScore;
                }
            }
    return bestMove;
}

int main() {
    vector<vector<int>> grid = {
        {X_VAL, O_VAL, BLANK},
        {O_VAL, X_VAL, BLANK},
        {BLANK, BLANK, BLANK}
    };

    displayGrid(grid, 0, numeric_limits<int>::min(), numeric_limits<int>::max());

    pair<int, int> move = optimalMove(grid);
    cout << "\nOptimal move for X is at position (" << move.first << ", " << move.second << ")\n";

    return 0;
}
