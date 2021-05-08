#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QString>

#include <map>
#include "card.hh"


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

    void on_card_turned();
    void handle_card_click();
    void on_reset_button_clicked();
    void add_cards_to_grid();
    void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor);

private:
    Ui::MainWindow *ui_;

    std::map<QString, Card> map_of_cards_;

};
#endif // MAINWINDOW_HH
