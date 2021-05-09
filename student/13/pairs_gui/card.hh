#ifndef CARD_HH
#define CARD_HH

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>

#include <iostream>

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

    // Turns a card: changes the visibility from open to hidden and vice versa.
    void turn();

    void turn_back();

    // Removes a card from the game board: changes the visibility to empty.
    void remove_from_game_board();

private:
    char letter_;
    Visibility_type visibility_;
    QPushButton *cardButton_;
    QString button_name_;
};

#endif // CARD_HH
