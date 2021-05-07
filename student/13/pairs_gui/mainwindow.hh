#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGridLayout>

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
    void handle_card_click(QGridLayout& grid);
    void on_reset_button_clicked();
    void add_card_to_grid();
    void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_HH
