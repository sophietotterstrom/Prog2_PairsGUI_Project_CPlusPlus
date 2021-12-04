/* Mainwindow Class
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class models a MainWindow User Interface, which the player interacts with.
 * Includes UI methods, but also methods for setting turns in the game, and
 * other game logic methods.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTime>

#include <map>
#include <vector>
#include <string>
#include <random>

#include "ui_mainwindow.h"
#include "card.hh"
#include "player.hh"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Handles card clicks by turning the card over.
    void on_cardClick();

    // Handles what happens when the next turn button is clicked.
    // Turns the cards back and does other needed actions related to that.
    void on_nextTurnButtonClicked();

    // Resets game board when the reset game button is clicked.
    void on_resetGameButtonClicked();

private:
    Ui::MainWindow *ui_;

    // Map contains card references with keys derived
    // from the row and column of the card.
    std::map<std::string, Card*> map_of_cards_;

    // Pointer to the player taking the current turn.
    Player* current_player_;

    // Player objects.
    Player player1_;
    Player player2_;

    // Generates the initial card grid on app startup.
    void addCardsToGrid();

    // Generates the random letter vector to be assigned to cards.
    std::vector<char> mixLetters();

    // Finds the number of rows and columns for the card grid.
    void askProductAndCalculateFactors(unsigned int& smaller_factor,
                                       unsigned int& bigger_factor);

    // Change the turn of the current player.
    void setTurn(Player* player_in_turn);

    // Update the UI to indicate the current player's turn.
    void setDisplayTurn();

    // Returns the number of cards currently turned to OPEN.
    int numOpenCards();

    // Checks if a pair of cards have been found and awards.
    // points or triggers turn change.
    bool checkPairs();

    // Adds a point to the current_player_.
    void addPoint();

    // Returns a vector of the open cards on the grid.
    std::vector<Card*> openCardVector();

    // Checks if the game is over (all pairs found).
    bool isGameOver();

    // Displays game over message and resets the game.
    void gameOver();
};
#endif // MAINWINDOW_HH
