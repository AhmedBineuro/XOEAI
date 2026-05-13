#pragma once
#include <vector>
#include <cassert>
#include "../XOEngine.hpp"

class Tester
{
public:
    Tester()
    {
        plays.reserve(5); // The minimum number of plays for a win is 5
    }
    Tester(std::string FileURL) : Tester()
    {
        loadTest(FileURL);
    }
    void loadTest(std::string FileURL)
    {
        plays.clear();
        FILE *f = fopen(FileURL.c_str(), "r");
        if (f == nullptr)
        {
            std::cout << "File path is invalid\n";
            return;
        }
        char c = getc(f);
        std::string currentstr = "";
        while (c != EOF)
        {
            if (c >= 'A' && c <= 'Z')
            {
                currentstr += c;
                if (currentstr == "OUTCOME")
                {
                    c = getc(f); // consume character
                    // Consume white space
                    while (c == ' ')
                    {
                        c = getc(f);
                    }
                    if (c == '-')
                    {
                        std::string outcome;
                        outcome += c;
                        c = getc(f); // consume character
                        if (c != '1')
                            std::cout << "Invalid outcome value";
                        else
                        {
                            outcome += c;
                            this->outcome = (Board::CellState)std::stoi(outcome.c_str());
                            currentstr = "";
                        }
                    }
                    else if (c >= '0' && c <= '2')
                    {
                        std::string outcome;
                        outcome += c;
                        this->outcome = (Board::CellState)std::stoi(outcome.c_str());
                        currentstr = "";
                    }
                    else
                        std::cout << "Invalid outcome value";
                }
                else if (currentstr == "INIT")
                {
                    c = getc(f); // Either X or O
                    // Consume white space
                    while (c == ' ')
                    {
                        c = getc(f);
                    }
                    if (c == 'X')
                        this->first = Board::CellState::X;
                    else if (c == 'O')
                        this->first = Board::CellState::O;
                    else
                        std::cout << "Invalid initial player\n";
                }
            }
            else if (c >= '0' && c <= '9')
            {
                ungetc(c, f);
                parsePlay(f);
            }
            c = getc(f);
        }
        fclose(f);
    }

    // A play is written as row,col (cs is either X or )
    void parsePlay(FILE *f)
    {
        char c = getc(f);
        while (c != '\n' && c != EOF)
        {
            std::string out = "";
            Board::Play p;
            // Can be condensed to single loop but left for readability
            //  Get row
            while (!(c >= '0' && c <= '9') && c != EOF)
            {
                c = getc(f);
            }
            // While we have numbers consume
            while (c >= '0' && c <= '9')
            {
                out += c;
                c = getc(f);
            }
            if (out == "")
                break;
            p.row = std ::stoi(out.c_str());
            out = "";
            // Get column
            while (!(c >= '0' && c <= '9') && c != EOF)
            {
                c = getc(f);
            }
            // While we have numbers consume
            while (c >= '0' && c <= '9')
            {
                out += c;
                c = getc(f);
            }
            p.column = std ::stoi(out.c_str());
            plays.emplace_back(p);
        }
        ungetc(c, f);
    }
    void printTest()
    {
        std::cout << "Outcome: " << outcome << '\n';
        std::cout << "First: " << first << '\n';
        for (long unsigned int i = 0; i < plays.size(); i++)
        {
            printPlay(i);
            std::cout << '\n';
        }
    }
    void printPlay(int index)
    {
        std::cout << "Board::Play " << index << ": " << plays[index].row << " , " << plays[index].column;
    }
    Evaluator::EndCondition runTest(bool printPlays = true, bool printBoard = true)
    {
        xoe.reset(first);
        Evaluator::EndCondition outcome;
        int i = 0;
        for (Board::Play p : plays)
        {
            if (printPlays)
                printPlay(i);
            std::cout << "\t| ";
            outcome = xoe.step(p.row, p.column, false);
            i++;
            if (outcome.ended)
                break;
        }
        if (!sameOutcome(outcome))
        {
            std::cout << "Outcome not correct expected " << this->outcome << " and got " << outcome.winner << '\n';
        }
        else
            std::cout << "Expected outcome met\t" << Evaluator::stringifyPattern(outcome.wp) << '\n';
        if (printBoard)
            xoe.printAsciiBoard();
        return outcome;
    }
    bool sameOutcome(Evaluator::EndCondition ec)
    {
        return (ec.winner == this->outcome);
    }

private:
    XOEngine xoe;
    std::vector<Board::Play>
        plays;
    Board::CellState outcome;
    Board::CellState first = Board::CellState::EMPTY;
};