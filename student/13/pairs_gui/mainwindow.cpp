/* Mainwindow Class
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class models a MainWindow User Interface, which the player interacts with.
 * Includes UI methods, but also methods for setting turns in the game, and
 * other game logic methods.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#include "mainwindow.hh"

using namespace std;

// Use this global variable to set the number of cards.
int NUMBER_OF_CARDS = 24;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    this->setWindowTitle("Sophie's Memory Game");

    connect(ui_->resetButton, &QPushButton::clicked, this,
            &MainWindow::on_resetGameButtonClicked);

    // Connect button to turn cards back to face down and start the next turn.
    connect(ui_->nextTurnButton, &QPushButton::clicked, this,
            &MainWindow::on_nextTurnButtonClicked);

    // Disable button until turn ends
    ui_->nextTurnButton->setDisabled(true);

    // Generate randomized card grid
    addCardsToGrid();

    // Create Players
    player1_ = Player(ui_->player1ScoreLCDNum, ui_->player1Label);
    player2_ = Player(ui_->player2ScoreLCDNum, ui_->player2Label);

    // Start the game on Player 1
    this->setTurn(&player1_);
    setDisplayTurn();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::on_cardClick()
{

    // Storing global cursor position
    QPoint global_click_position = QCursor::pos();

    // Counting local cursor position, i.e. decreasing
    // Main Window's location from the global one
    int local_x = global_click_position.x() - geometry().x();
    int local_y = global_click_position.y() - geometry().y();

    // Get the card button under the cursor
    QWidget* card = QWidget::childAt(local_x, local_y);
    string found_button_name = card->objectName().toStdString();

    if (map_of_cards_.find(found_button_name)
            != map_of_cards_.end())
    {
        if (numOpenCards() == 0)
        {
            // Turn over the clicked card
            map_of_cards_.at(found_button_name)->turnFace();
        }
        // After two cards are turned, check for pairs
        else if (numOpenCards() == 1)
        {
            map_of_cards_.at(found_button_name)->turnFace();
            // When a match is found, increment the player's
            // points and check if the game is over
            if (checkPairs())
            {
                this->addPoint();
                if (isGameOver())
                {
                    gameOver();
                }
            }
            // If a match isn't found, enable the button to start
            // the next round, and change the turn to the other player
            else
            {
                ui_->nextTurnButton->setDisabled(false);
                if (current_player_ == &player1_)
                {
                    setTurn(&player2_);
                }
                else
                {
                   setTurn(&player1_);
                }
            }
        }
    }
}

void MainWindow::on_nextTurnButtonClicked()
{
    // Get face up cards
    vector<Card*> face_up_cards = openCardVector();

    // Turn cards back over
    for (auto card: face_up_cards) {
        string name = card->get_button_name().toStdString();
        map_of_cards_.at(name)->turnBack();
    }

    // Change turns to the other player
    setDisplayTurn();

    // Enable the button to allow the next player to start their turn
    ui_->nextTurnButton->setDisabled(true);
}

void MainWindow::on_resetGameButtonClicked()
{
    // Get a new vector of random letters
    vector<char> vect_of_random_letters = mixLetters();
    int count = 0;
    for (auto& key_card_pair : map_of_cards_)
    {
        // Refresh each card with a new letter, and turn it back over to hidden.
        Card *card = key_card_pair.second;

        char letter = vect_of_random_letters.at(count);
        card->set_letter(letter);
        count++;

        card->turnBack();
    }

    // Reset player objects
    player1_ = Player(ui_->player1ScoreLCDNum, ui_->player1Label);
    player2_ = Player(ui_->player2ScoreLCDNum, ui_->player2Label);

    // Reset to player 1 turn
    this->setTurn(&player1_);
    setDisplayTurn();

    // Disable Next Turn button
    ui_->nextTurnButton->setDisabled(true);
}


void MainWindow::addCardsToGrid()
{
    unsigned int row = 1;
    unsigned int column = 1;
    // Get grid dimensions based on number of cards
    askProductAndCalculateFactors(row, column);

    // Generate random character list for assigning to cards
    vector<char> vect_of_random_letters = mixLetters();
    int count = 0;

    // Iterate through each cell in the grid
    for (unsigned int i = 0; i<column; i++)
    {
        for (unsigned int j = 0; j<row; j++)
        {
            // Create a new card with a letter from the random letter vector
            char letter = vect_of_random_letters.at(count);
            Card* card = new Card(letter);
            count++;

            // Create a unique name for the button using the row and column
            string name = "PushButton" + to_string(j) + to_string(i);
            card->button()->setObjectName(name.c_str());
            card->set_button_name(QString(name.c_str()));

            // Connect card buttons to click handler
            connect(card->button(), &QPushButton::clicked, this,
                    &MainWindow::on_cardClick);

            // Add the card button to the grid
            card->button()->setParent(ui_->gridLayoutWidget);
            ui_->cardGridLayout->addWidget(card->button(), j, i);

            // Store cards in a map for searching
            map_of_cards_.insert({name, card});
        }
    }
}

vector<char> MainWindow::mixLetters()
{
    int number_of_pairs = NUMBER_OF_CARDS/2;

    // Create a vector of double letters starting at A
    // e.g. AABBCCDD...
    vector<char> vector_of_letters;
    char character = 'A';
    for (int i = 0; i < number_of_pairs; i++)
    {
        vector_of_letters.push_back(character);
        vector_of_letters.push_back(character);
        character++;
    }

    // Shuffle letter vector using current millisecond time as seed
    minstd_rand generator;
    generator.seed(QTime::currentTime().msec());
    vector<char>::iterator start = vector_of_letters.begin();
    vector<char>::iterator end = vector_of_letters.end();

    shuffle(start, end, generator);

    return vector_of_letters;
}

void MainWindow::askProductAndCalculateFactors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = NUMBER_OF_CARDS;

    // Find greatest factors of the given number of cards
    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}


void MainWindow::setTurn(Player* player_in_turn)
{
    current_player_ = player_in_turn;
}

void MainWindow::setDisplayTurn()
{
    if (current_player_ == &player1_)
    {
        player1_.displayInTurn();
        player2_.displayNotInTurn();
    }
    else
    {
        player2_.displayInTurn();
        player1_.displayNotInTurn();
    }
}


int MainWindow::numOpenCards()
{
    int numberTurned = 0;

    // For each card in the map
    for (auto& key_value_pair : map_of_cards_)
    {
        // Get the visibility of the card
        Visibility_type visibility = key_value_pair.second->get_visibility();
        if (visibility == OPEN)
        {
            // Increment number for each turned card
            numberTurned++;
        }
    }
    return numberTurned;
}

bool MainWindow::checkPairs()
{
    // Get face up cards
    vector<Card*> card_vect = openCardVector();

    // If a pair is found, remove the cards from the grid and return true.
    if (card_vect.at(0)->get_letter() == card_vect.at(1)->get_letter())
    {
        string name1 = card_vect.at(0)->get_button_name().toStdString();
        map_of_cards_.at(name1)->remove_from_game_board();

        string name2 = card_vect.at(1)->get_button_name().toStdString();
        map_of_cards_.at(name2)->remove_from_game_board();

        return true;
    }
    // No pair found, return false.
    else {
        return false;
    }
}

void MainWindow::addPoint()
{
    current_player_->addPoint();
}

vector<Card*> MainWindow::openCardVector()
{
    vector<Card*> temp_vect;

    // Add face up cards to a vector
    for (auto& key_value_pair : map_of_cards_)
    {
        Visibility_type visibility = key_value_pair.second->get_visibility();
        if (visibility == OPEN)
        {
            temp_vect.push_back(key_value_pair.second);
        }
    }

    return temp_vect;
}

bool MainWindow::isGameOver()
{
    for (auto& key_value_pair : map_of_cards_)
    {
        // Return false as soon as a not found card is detected
        if (key_value_pair.second->get_visibility() != FOUND)
        {
            return false;
        }
    }
    // Return true if all cards are found
    return true;
}

void MainWindow::gameOver()
{
    // Create a message box to display game over message
    QMessageBox winAlertBox;
    string win_string;
    winAlertBox.setWindowTitle("Game Over!");

    // Determine which player wins, or if a tie occurred.
    if (player1_.get_points() > player2_.get_points())
    {
        win_string = player1_.get_name() + " has won with " + to_string(player1_.get_points()) + " pairs!  ";
    } else if (player2_.get_points() > player1_.get_points())
    {
        win_string = player2_.get_name() + " has won with " + to_string(player2_.get_points()) + " pairs!  ";
    } else
    {
        win_string = "Tie game! Each player has " + to_string(player1_.get_points()) + " pairs.";
    }

    // Write the win_string to the message box
    winAlertBox.setText(QString(win_string.c_str()));
    // Center message box to MainWindow
    winAlertBox.setParent(ui_->centralwidget);
    // Set message box to block all other input until dismissed
    winAlertBox.setWindowModality(Qt::WindowModal);
    // Display the window
    winAlertBox.exec();

    // Reset the game
    on_resetGameButtonClicked();
}

