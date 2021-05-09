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

void Player::add_point()
{
    points_++;
    this->set_score_on_lcdnum();
}

int Player::get_points()
{
    return points_;
}

void Player::set_score_on_lcdnum()
{
    point_lcdnum_->display(points_);
}

void Player::display_in_turn()
{
    label_->setStyleSheet(QString("background-color: green; font: 16pt 'Clean';"));
    point_lcdnum_->setStyleSheet(QString("background-color: green"));
}

void Player::display_not_in_turn()
{
    label_->setStyleSheet("background-color: rgb(215, 198, 225); font: 16pt 'Clean';");
    point_lcdnum_->setStyleSheet(QString("background-color: rgb(215, 198, 225)"));

}
