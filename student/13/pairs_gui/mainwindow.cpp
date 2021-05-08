#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "card.hh"
#include <cstring>
#include <iostream>

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

            connect(card.button(), &QPushButton::clicked, this, &MainWindow::handle_card_click);

            ui_->cardGridLayout->addWidget(card.button(), j, i);


        }
    }
}

void MainWindow::handle_card_click()
{
    // Storing global cursor position
    QPoint global_click_position = QCursor::pos();

    // Counting local cursor position, i.e. decreasing
    // Main Window's location from the global one
    int local_x = global_click_position.x() - geometry().x();
    int local_y = global_click_position.y() - geometry().y();


    QWidget::childAt(local_x, local_y);

    QWidget* card = QWidget::childAt(local_x, local_y);
    QString name = card->objectName();

    card->setStyleSheet(QString("background-color: yellow"));
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

