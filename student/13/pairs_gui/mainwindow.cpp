#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "card.hh"

#include <cstring>
#include <iostream>
#include <random>

#include <QDebug>

using namespace std;

int NUMBER_OF_CARDS = 24;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // connecting buttons
    connect(ui_->resetButton, &QPushButton::clicked, this,
            &MainWindow::on_reset_button_clicked);

    add_cards_to_grid();

    this->setWindowTitle("Sophie's Memory Game");
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
    vector<char> vect_of_random_letters = mix_letters();
    int count = 0;

    for (unsigned int i = 0; i<column; i++)
    {
        for (unsigned int j = 0; j<row; j++)
        {
            char letter = vect_of_random_letters.at(count);
            Card card = Card(letter);

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

            // vector_of_cards_.push_back(&card);

            map_of_cards_.insert({name_string, card});
            count++;
        }
    }
}

vector<char> MainWindow::mix_letters()
{
    int number_of_pairs = NUMBER_OF_CARDS/2;

    vector<char> vector_of_letters;
    char character = 'A';
    for (int i = 0; i < number_of_pairs; i++)
    {
        vector_of_letters.push_back(character);
        vector_of_letters.push_back(character);
        character++;
    }

    minstd_rand generator;
    vector<char>::iterator start = vector_of_letters.begin();
    vector<char>::iterator end = vector_of_letters.end();

    shuffle(++start, --end, generator);
    return vector_of_letters;
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

/*
    // QPushButton *temp_button = dynamic_cast<QPushButton*>(card);
    std::cout << found_button_name_qstring.toUtf8().constData() << std::endl;
    std::cout << vector_of_cards_.size() << std::endl;
    for (auto card_pointer: vector_of_cards_) {
        cout << "IN loop" << endl;
        std::cout << card_pointer->get_letter() << std::endl;
        if (card_pointer->get_button_name() == card->objectName())
            std::cout << " FOUND: " << card_pointer->get_button_name().toUtf8().constData() << std::endl;
            card_pointer->turn();
            break;
    }
*/
    if (map_of_cards_.find(found_button_name) != map_of_cards_.end())
    {
        // card is in the map, turn the card

        if (cards_turned() == 0)
        {
            map_of_cards_.at(found_button_name).turn();
        }
        else if (cards_turned() == 1)
        {
            // this is the second card being turned, check for a pair
            map_of_cards_.at(found_button_name).turn();
            check_pairs();

        }
    }
}

int MainWindow::cards_turned()
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
    return i;
}

bool MainWindow::check_pairs()
{
    vector<Card> temp_vect;
    for (auto& key_value_pair : map_of_cards_)
    {
        Visibility_type visibility = key_value_pair.second.get_visibility();
        if (visibility == OPEN)
        {
            temp_vect.push_back(key_value_pair.second);
        }
    }

    if (temp_vect.at(0).get_letter() == temp_vect.at(1).get_letter())
    {
        string name1 = temp_vect.at(0).get_button_name().toStdString();
        map_of_cards_.at(name1).remove_from_game_board();

        string name2 = temp_vect.at(1).get_button_name().toStdString();
        map_of_cards_.at(name2).remove_from_game_board();

        // temp_vect.at(1).remove_from_game_board();
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

