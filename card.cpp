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

#include "card.hh"

Card::Card()
{
}

Card::Card(const char c)
{
    // Assigns the letter to the card.
    this->set_letter(c);

    // Creates a pushButton object for the card UI.
    QPushButton* cardButton = new QPushButton();
    this->set_card_button(cardButton);

    // Set UI to face down/ card back.
    turnBack();

    // Allow the card to stretch to fill the grid cell.
    // This makes sure if the global variable NUMBER_OF_CARDS
    // is changed, the game board looks good.
    QSizePolicy cardButton_policy (QSizePolicy::Minimum, QSizePolicy::Minimum);
    cardButton_policy.setHorizontalStretch(1);
    cardButton_policy.setVerticalStretch(1);
    this->button()->setSizePolicy(cardButton_policy);
}

void Card::set_letter(const char c)
{
    letter_ = c;
}

void Card::set_visibility(const Visibility_type visibility)
{
    visibility_ = visibility;
}

void Card::set_card_button(QPushButton *cardButton)
{
    this->cardButton_ = cardButton;
}

void Card::set_button_name(QString button_name_qstr)
{
    button_name_ = button_name_qstr;
}

char Card::get_letter() const
{
    return letter_;
}

QString Card::get_button_name()
{
    return button_name_;
}

Visibility_type Card::get_visibility() const
{
    return visibility_;
}

QPushButton *Card::button()
{
    return this->cardButton_;
}

void Card::turnFace()
{
    // Turn card over to face up

    // Render the card's character text
    cardButton_->setText(QChar(letter_));

    // Remove the icon
    cardButton_->setIcon(QIcon());

    // Disable the button
    cardButton_->setDisabled(true);

    // Update background color and text color
    cardButton_->setStyleSheet(QString("background-color: rgb(231, 174, 36); color: black"));

    // Update visibility to OPEN
    this->set_visibility(OPEN);
}

void Card::turnBack()
{
    // Turn card back to face down

    // Remove the card's character text
    cardButton_->setText(QString());

    // Put the icon back on the card
    cardButton_->setIcon(QIcon("heart.png"));
    cardButton_->setIconSize(QSize(50,50));

    // Enable the button
    cardButton_->setDisabled(false);

    // Update background color to the gradient
    cardButton_->setStyleSheet(QString("background-color: "
                                      "qlineargradient(spread:pad, "
                                      "x1:0, y1:1, x2:0, y2:0, stop:0 "
                                      "rgba(0, 0, 0, 255), stop:0.05 "
                                      "rgba(14, 8, 73, 210), stop:0.36 "
                                      "rgba(28, 17, 145, 162), stop:0.6 "
                                      "rgba(126, 14, 81, 190), stop:0.75 "
                                      "rgba(234, 11, 11, 182), stop:0.79 "
                                      "rgba(244, 70, 5, 199), stop:0.86 "
                                      "rgba(255, 136, 0, 206), stop:0.935 "
                                      "rgba(239, 236, 55, 112))"));

    // Update visibility to HIDDEN
    this->set_visibility(HIDDEN);
}

void Card::remove_from_game_board()
{
    // Remove Card

    // Update the background to grey and the text label to white
    cardButton_->setStyleSheet(QString("background-color: grey; color: white"));

    // Update visibility to FOUND
    this->set_visibility(FOUND);
}
