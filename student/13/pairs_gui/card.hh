/* Class Card
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class models a card in the memory game.
 * Includes methods for both the UI and game logic.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#ifndef CARD_HH
#define CARD_HH

#include <QPushButton>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

enum Visibility_type {OPEN, HIDDEN, FOUND};

class Card
{
public:
    // Default constructor: creates an empty card.
    Card();

    // Constructor: creates a hidden card with the given character.
    Card(const char c);

    // Obvious setter and getter methods.
    void set_letter(const char c);
    void set_visibility(const Visibility_type visibility);
    void set_card_button(QPushButton *cardButton);
    void set_button_name(QString button_name_qstr);
    char get_letter() const;
    QString get_button_name();
    Visibility_type get_visibility() const;
    QPushButton* button();

    // Turns a card: changes the visibility from hidden to open,
    // and configures button UI to show card.
    void turnFace();

    // Turns a card back: changes visibility from open to hidden,
    // and configures button UI to hide card.
    void turnBack();

    // Removes a card from the game board: changes the visibility to found.
    void remove_from_game_board();

private:
    char letter_;
    Visibility_type visibility_;
    QPushButton *cardButton_;
    QString button_name_;
};

#endif // CARD_HH
