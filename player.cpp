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

#include "player.hh"

Player::Player()
{

}

Player::Player(QLCDNumber* lcd_num, QLabel* label)
{
    points_ = 0;
    point_lcdnum_ = lcd_num;
    label_ = label;
    this->set_score_on_lcdnum();
}

void Player::addPoint()
{
    points_++;
    this->set_score_on_lcdnum();
}

int Player::get_points()
{
    return points_;
}

std::string Player::get_name()
{
    return label_->text().toStdString();
}

void Player::set_score_on_lcdnum()
{
    point_lcdnum_->display(points_);
}

void Player::displayInTurn()
{
    // Change score UI elements to green to indicate turn
    label_->setStyleSheet("background-color: green; "
                          "font: 16pt 'Clean';");
    point_lcdnum_->setStyleSheet("background-color: green");
}

void Player::displayNotInTurn()
{
    // Change UI back to standard color to indicate other player's turn
    label_->setStyleSheet("background-color: rgb(215, 198, 225); "
                          "font: 16pt 'Clean';");
    point_lcdnum_->setStyleSheet("background-color: rgb(215, 198, 225)");

}
