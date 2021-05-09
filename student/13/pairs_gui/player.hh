#ifndef PLAYER_HH
#define PLAYER_HH

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>

#include <iostream>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Player
{
public:
    Player();
    Player(QLCDNumber* lcd_num, QLabel* label);

    void add_point();
    int get_points();

    void set_score_on_lcdnum();
    void display_in_turn();
    void display_not_in_turn();


private:
    int points_;
    QLCDNumber* point_lcdnum_;
    QLabel* label_;
};

#endif // PLAYER_HH
