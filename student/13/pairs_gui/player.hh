/* Player Class
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * A fairly simple Class for modeling a player in the game.
 * Has attributes for the name and points of a player, and UI elements.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#ifndef PLAYER_HH
#define PLAYER_HH

#include <QMainWindow>
#include <QLabel>
#include <QLCDNumber>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Player
{
public:
    // Default Player constructor.
    Player();

    // Player constructor that assigns the player object a score LCD and label.
    Player(QLCDNumber* lcd_num, QLabel* label);

    // Adds one point to this player.
    void addPoint();

    // Getter methods
    int get_points();
    std::string get_name();

    // UI methods to display the score and the turn indicator.
    void set_score_on_lcdnum();
    void displayInTurn();
    void displayNotInTurn();

private:
    int points_;
    QLCDNumber* point_lcdnum_;
    QLabel* label_;
};

#endif // PLAYER_HH
