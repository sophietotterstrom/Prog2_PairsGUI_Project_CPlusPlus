#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <cstring>
#include <iostream>

using namespace std;

int NUMBER_OF_CARDS = 24;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connecting buttons
    connect(ui->resetButton, &QPushButton::clicked, this,
            &MainWindow::on_reset_button_clicked);


    add_cards_to_grid();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_card_turned()
{


}


void MainWindow::on_reset_button_clicked()
{
    ui->resetButton->setAutoFillBackground(true);
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
            cout << "i: " << i << " j: " << j << endl;

            string card_name_string = "cardButton"+to_string(i)+to_string(j);
            char card_name[card_name_string.length()];
            strcpy(card_name, card_name_string.c_str());

            QPushButton* cardButton = new QPushButton(ui->gridLayoutWidget);
            // int x = cardButton->pos().x();
            // int y = cardButton->pos().y();

            cardButton->setObjectName(QString::fromUtf8(card_name));

            cardButton->setStyleSheet(QString("background-color: "
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

            connect(cardButton, &QPushButton::clicked, this, &MainWindow::handle_card_click);

            ui->cardGridLayout->addWidget(cardButton, j, i);

            QSizePolicy cardButton_policy (QSizePolicy::Minimum, QSizePolicy::Minimum);
            cardButton_policy.setHorizontalStretch(1);
            cardButton_policy.setVerticalStretch(1);
            cardButton->setSizePolicy(cardButton_policy);

        }
    }
}

// To avoid repetitive code, this method implements a general handling
// for both letter and number push button clicks.
void MainWindow::handle_card_click()
{
    // Storing global cursor position
    QPoint global_click_position = QCursor::pos();

    // Counting local cursor position, i.e. decreasing
    // Main Window's location from the global one
    int local_x = global_click_position.x() - geometry().x();
    int local_y = global_click_position.y() - geometry().y();

    QWidget* card = QWidget::childAt(local_x, local_y);
    card->setStyleSheet(QString("background-color: yellow"));
}


// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void MainWindow::ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = NUMBER_OF_CARDS;
    /*
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    } */

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

