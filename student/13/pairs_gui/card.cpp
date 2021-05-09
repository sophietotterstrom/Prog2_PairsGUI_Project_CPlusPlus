#include "card.hh"
#include <iostream>

Card::Card()
{

}

Card::Card(const char c)
{
    this->set_letter(c);

    QPushButton* cardButton = new QPushButton();

    this->set_card_button(cardButton);

    this->button()->setObjectName(QString(c));

    this->button()->setIcon(QIcon("heart.png"));
    this->button()->setIconSize(QSize(50,50));

    this->button()->setStyleSheet(QString("background-color: "
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


    QSizePolicy cardButton_policy (QSizePolicy::Minimum, QSizePolicy::Minimum);
    cardButton_policy.setHorizontalStretch(1);
    cardButton_policy.setVerticalStretch(1);
    this->button()->setSizePolicy(cardButton_policy);

    this->set_visibility(HIDDEN);
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

void Card::turn()
{
    cardButton_->setText(QString(QChar::fromLatin1(letter_)));
    cardButton_->setIcon(QIcon());
    cardButton_->setDisabled(true);
    cardButton_->setStyleSheet(QString("background-color: rgb(231, 174, 36); color: black"));


    if (visibility_ == HIDDEN)
    {
        this->set_visibility(OPEN);
    }
}

void Card::turn_back()
{
    cardButton_->setDisabled(false);
    cardButton_->setText(QString());
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
    cardButton_->setIcon(QIcon("heart.png"));
    cardButton_->setIconSize(QSize(50,50));

    if (visibility_ == OPEN)
    {
        this->set_visibility(HIDDEN);
    }
}

void Card::remove_from_game_board()
{
    cardButton_->setStyleSheet(QString("background-color: grey; color: white"));
    cardButton_->setIcon(QIcon());
    cardButton_->setDisabled(true);

    this->set_visibility(FOUND);
}
