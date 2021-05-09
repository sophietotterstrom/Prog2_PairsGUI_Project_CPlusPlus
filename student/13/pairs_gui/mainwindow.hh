#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "card.hh"
#include "player.hh"

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QTimer>

#include <map>
#include <vector>
#include <string>


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

    void handle_card_click();
    void add_cards_to_grid();
    std::vector<char> mix_letters();
    void set_turn(Player* player_in_turn);
    void display_turn();
    void add_point();
    int cards_turned();
    bool check_pairs();
    bool is_game_over();
    void on_turnCardsBackButtonClicked();
    void on_resetGameButtonClicked();
    void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor);

private:
    Ui::MainWindow *ui_;

    std::map<std::string, Card> map_of_cards_;
    std::vector<Card*> vector_of_cards_;

    Player* current_player_;

    Player player1_;
    Player player2_;

};
#endif // MAINWINDOW_HH
