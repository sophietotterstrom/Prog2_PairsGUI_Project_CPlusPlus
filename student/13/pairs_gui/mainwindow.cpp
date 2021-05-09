#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "card.hh"

#include <cstring>
#include <iostream>
#include <random>

#include <QDebug>

using namespace std;

int NUMBER_OF_CARDS = 24;
int SEED = 374;
int TIMER_INTERVAL_ms = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // connecting buttons
    connect(ui_->resetButton, &QPushButton::clicked, this,
            &MainWindow::on_reset_button_clicked);

    add_cards_to_grid();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::on_card_turned()
{


}


void MainWindow::on_reset_button_clicked()
{
    ui_->resetButton->setAutoFillBackground(true);
}

void MainWindow::add_cards_to_grid()
{
    unsigned int row = 1;
    unsigned int column = 1;
    ask_product_and_calculate_factors(row, column);

    // Drawing a cell to be filled
    default_random_engine randomEng(SEED);
    uniform_int_distribution<int> distr(0, row * column - 1);

    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);

    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for(unsigned int i = 0, c = 'A'; i < row * column - 1; i += 2, ++c)
    {
        // Adding two identical cards (pairs) in the game board
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            //cell = next_free(g_board, cell);
            //g_board.at(cell / columns).at(cell % columns).set_letter(c);
            //g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }

    for (unsigned int i = 0; i<column; i++)
    {
        for (unsigned int j = 0; j<row; j++)
        {
            Card card = Card('*');

            card.button()->setParent(ui_->gridLayoutWidget);

            string name_string = "PushButton" + to_string(j) + to_string(i);
            char name [name_string.length() + 1];
            strcpy(name, name_string.c_str());
            card.button()->setObjectName(name);

            QString name_qstring = QString::fromStdString(name_string);
            card.set_button_name(name_qstring);

            connect(card.button(), &QPushButton::clicked, this,
                    &MainWindow::handle_card_click);

            ui_->cardGridLayout->addWidget(card.button(), j, i);


            map_of_cards_.insert({name_string, card});

        }
    }
}

void MainWindow::in_turn()
{
    ui_->player1Label->setStyleSheet("background-color: yellow");

}

void MainWindow::add_point()
{

}


void MainWindow::handle_card_click()
{
    // Storing global cursor position
    QPoint global_click_position = QCursor::pos();

    // Counting local cursor position, i.e. decreasing
    // Main Window's location from the global one
    int local_x = global_click_position.x() - geometry().x();
    int local_y = global_click_position.y() - geometry().y();
    QWidget* card = QWidget::childAt(local_x, local_y);
    QString found_button_name_qstring = card->objectName();
    string found_button_name = found_button_name_qstring.toStdString();

    // QPushButton *temp_button = dynamic_cast<QPushButton*>(card);

    if (map_of_cards_.find(found_button_name) != map_of_cards_.end())
    {
        // card is in the map, turn the card

        if (can_card_be_turned()) // returns true if only 0 or 1 card is turned
        {
            map_of_cards_.at(found_button_name).turn();
        }
        else {
            // handle what to do if card can't be turned
        }
    }
}

bool MainWindow::can_card_be_turned()
{
    // loop through visibility of all cards
    // if only 1 or 0 cards have visibility OPEN, return true
    // else return false

    int i = 0;
    for (auto& key_value_pair : map_of_cards_)
    {
        Visibility_type visibility = key_value_pair.second.get_visibility();

        if (visibility == OPEN)
        {
            i++;
        }
    }
    if ((i == 0) or (i==1))
    {
        return true;
    }
    else {
        return false;
    }

}

// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void MainWindow::ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = NUMBER_OF_CARDS;


    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

