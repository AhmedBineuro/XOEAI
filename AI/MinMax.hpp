#pragma once
#include "../Board.hpp"
#include "../Evaluator.hpp"
#include <climits>

class MinMaxAi
{
public:
    struct Decision
    {
        Board::Play play = {-1, -1};
        int score = 0;
    };
    MinMaxAi() {}
    Decision evaluate(Board b, int depth = 0, bool max = true)
    {
        Evaluator::EndCondition ec = ev.isEnd(b);
        Decision output;
        if (ec.ended||this->maxDepth==depth)
        {
            Board::CellState ocs = (this->cs == Board::CellState::X) ? Board::CellState::O : Board::CellState::X;
            if (ec.winner == this->cs)
            {
                output.score = 10;
            }
            else if (ec.winner == ocs)
            {
                output.score = -10;
            }
            else
            {
                output.score = 0;
            }
        }
        else if (max)
        {
            std::vector<Board::Play> empty = b.getEmptySlots();
            int val = INT_MIN;
            Board::Play p;
            for (auto play : empty)
            {
                b.setCellValue(play.row, play.column, this->cs);
                Decision score = evaluate(b, depth + 1, false);

                // if (depth == 0)
                // {
                //     std::cout << "____________Depth " << depth << "____________\n";
                //     std::cout << "\tPlay: " << play.row << "," << play.column << " Score:" << score.score << '\n';
                //     b.printAscii();
                // }
                b.setCellValue(play.row, play.column, Board::CellState::EMPTY);
                if (score.score > val)
                {
                    val = score.score;
                    p = play;
                }
            }
            output.score = val;
            output.play = p;
        }
        else
        {
            std::vector<Board::Play> empty = b.getEmptySlots();
            int val = INT_MAX;
            Board::Play p;
            for (auto play : empty)
            {
                Board::CellState c = (this->cs == Board::CellState::X) ? Board::CellState::O : Board::CellState::X;
                b.setCellValue(play.row, play.column, c);
                Decision score = evaluate(b, depth + 1, true);
                // if (depth == 0)
                // {
                //     std::cout << "____________Depth " << depth << "____________\n";
                //     std::cout << "\tPlay: " << play.row << "," << play.column << " Score:" << score.score << '\n';
                //     b.printAscii();
                // }
                b.setCellValue(play.row, play.column, Board::CellState::EMPTY);
                if (score.score < val)
                {
                    val = score.score;
                    p = play;
                    ;
                }
            }
            output.score = val;
            output.play = p;
        }
        return output;
    }
    void setState(Board::CellState state = Board::CellState::X)
    {
        cs = state;
    }
    Board::Play decidePlay(Board b)
    {
        std::vector<Board::Play> empty = b.getEmptySlots();
        int val = -1 * INT_MAX;
        Board::Play p;
        for (auto play : empty)
        {
            b.setCellValue(play.row, play.column, this->cs);
            Decision score = evaluate(b, 0, false);
            b.setCellValue(play.row, play.column, Board::CellState::EMPTY);
            if (score.score > val)
            {
                val = score.score;
                p = play;
                ;
            }
        }
        return p;
    }
    void setDepthLimit(int newDepth){
        this->maxDepth=newDepth;
    }
private:
    Evaluator ev;
    Board::CellState cs;
        int maxDepth=INT_MAX;
};