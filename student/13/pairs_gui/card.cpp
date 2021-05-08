#include "card.hh"

Card::Card()
{

}

Card::Card(const char c)
{
    this->set_letter(c);

    QPushButton* cardButton = new QPushButton();

    this->set_card_button(cardButton);

    this->button()->setObjectName(QString(c));

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
}

void Card::set_letter(const char c)
{

}

void Card::set_visibility(const Visibility_type visibility)
{

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

}

QString Card::get_button_name()
{
    return button_name_;
}

Visibility_type Card::get_visibility() const
{

}

QPushButton *Card::button()
{
    return this->cardButton_;
}

void Card::turn()
{
    // cardButton_->setStyleSheet(QString("background-color: yellow"));

    // this->cardButton_->setText(QString(QChar::fromLatin1(letter_)));
}

void Card::remove_from_game_board()
{

}
