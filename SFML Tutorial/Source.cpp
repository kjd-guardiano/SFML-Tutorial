// SFML Testing Ground!

#include "SFML/Graphics.hpp"
#include "stdlib.h"
#include "time.h"
#include "iostream"

//Define Macros Start
#define _ANSWER_SQUARE_WIDTH 220
#define _ANSWER_SQUARE_HEIGHT 140
#define _PAUSE_INDICATOR_WIDTH 900
#define _PAUSE_INDICATOR_HEIGHT 400
//Define Macros End

/* DEV NOTES:
*   General game loop is as follows:
*   while(game_running){
*       ProcessEventsAndInput();
*       if(!game_paused){
*          UpdateWorld();
*       }
*       DrawWorld();
*   }
*/

//Variable Declaration Start
sf::RenderWindow mainWindow(sf::VideoMode(1440, 900), "The Game", sf::Style::Titlebar | sf::Style::Close); //creates a window w/ graphics rendering, window title, and exit button
bool focus, paused, aCorrect, sCorrect, dCorrect, fCorrect, aSelected, sSelected, dSelected, fSelected, answerCorrect, questionAnswered;
sf::RectangleShape pause_square, a_square, s_square, d_square, f_square; //shapes for displaying "answer" options
int seed;
//Variable Declaration End

//Function Prototype Start
void windowSetup(); //defines window settings, should be outside while loop
void drawScene(); //renders the full scene for user display, occurs during while loop
void wipeScreen(); //clears user display for next frame
void keyCheck(); //check for when a key is pressed on the keyboard while game is in focus
void answerSetup(); //defines the randomized "answer" for the question, outputs correct answer to console
bool checkAnswer(); //checks if selected answer is correct, displays correct/incorrect answers and prevents further selection
//Function Prototype End

int main()
{
    windowSetup();
    answerSetup();
    paused = false;
    while (mainWindow.isOpen()) {
        //checks if window is currently in user focus ("tabbed in")
        focus = mainWindow.hasFocus();
        //for detecting events
        sf::Event event;
        //event detection loop
        while (mainWindow.pollEvent(event)) {
            switch (event.type) {
                //close window
                case sf::Event::Closed:
                    mainWindow.close();
                    break;
                //window out of focus
                case sf::Event::LostFocus:
                    paused = true;
                    std::cout << "OUT OF FOCUS" << std::endl; //outputs to CONSOLE, not SFML window
                    break;
                //window back in focus
                case sf::Event::GainedFocus:
                    paused = false;
                    std::cout << "RETURNED FOCUS" << std::endl; //outputs to CONSOLE, not SFML window
                    break;
                //keyboard use check
                case sf::Event::KeyPressed:
                    keyCheck();
                    break;
                //if none, simply set up for next scene
                default:
                    wipeScreen();
                    break;
            }
            //outside of switch statement
            drawScene();
            mainWindow.display(); //displays to user current scene
        }
        //outside of while loop
    }
    return 0;
}

//defines settings for the game window
void windowSetup() {
    bool focus = mainWindow.hasFocus();
    mainWindow.setVerticalSyncEnabled(true);
    mainWindow.setFramerateLimit(60);
    mainWindow.clear();
    std::cout << "The window has been modified!" << std::endl;
}

void keyCheck() {
    //pause key, pauses the game
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !paused) {
        paused = true;
    }
    //pause key, unpauses the game
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && paused) {
        paused = false;
    }
    //'A' selects the 'A' answer, leftmost box, and deselects all other answers
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !paused && !questionAnswered) {
        aSelected = true;
        sSelected = false;
        dSelected = false;
        fSelected = false;
    }
    //'S' selects the 'S' answer, 1 box from the left, and deselects all other answers
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !paused && !questionAnswered) {
        aSelected = false;
        sSelected = true;
        dSelected = false;
        fSelected = false;
    }
    //'D' selects the 'D' answer, 2nd box from the left, and deselects all other answers
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !paused && !questionAnswered) {
        aSelected = false;
        sSelected = false;
        dSelected = true;
        fSelected = false;
    }
    //'F' selects the 'F' answer, rightmost box, and deselects all other answers
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !paused && !questionAnswered) {
        aSelected = false;
        sSelected = false;
        dSelected = false;
        fSelected = true;
    }
    //'Esc' closes the game and exits the program
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        mainWindow.close();
    }
    //'G' sends in an answer and locks in the selected answer.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && !paused) {
        answerCorrect = checkAnswer();
        std::cout << "Answer checked!" << std::endl;
    }
}

//creates the answer to the question, randomized for the sake of testing
void answerSetup() {
    //randomizes the answer
    srand((unsigned)time(NULL));
    seed = 1 + (rand() % 4);
    std::cout << "The number is " << seed << std::endl;
    //defines correct answer based on randomized number
    switch (seed) {
    case 1:
        std::cout << "A is correct." << std::endl;
        aCorrect = true;
        break;
    case 2:
        std::cout << "S is correct." << std::endl;
        sCorrect = true;
        break;
    case 3:
        std::cout << "D is correct." << std::endl;
        dCorrect = true;
        break;
    case 4:
        std::cout << "F is correct." << std::endl;
        fCorrect = true;
        break;
    default:
        break;
    }
}

//checks if the user-selected answer is the correct answer
bool checkAnswer() {
    //'A' is correct
    if (aCorrect && aSelected) {
        questionAnswered = true;
        std::cout << "The question is checked!" << std::endl;
        return true;
    }
    //'S' is correct
    else if (sCorrect && sSelected) {
        questionAnswered = true;
        std::cout << "The question is checked!" << std::endl;
        return true;
    }
    //'D' is correct
    else if (dCorrect && dSelected) {
        questionAnswered = true;
        std::cout << "The question is checked!" << std::endl;
        return true;
    }
    //'F' is correct
    else if (fCorrect && fSelected) {
        questionAnswered = true;
        std::cout << "The question is checked!" << std::endl;
        return true;
    }
    //default case.
    else {
        questionAnswered = true;
        std::cout << "The question is checked!" << std::endl;
        return false;
    }
}

//clears the screen, technically not necessary since it's only one line, can be edited later down the line for additional purposes
void wipeScreen() {
    mainWindow.clear();
}

//creates the visuals for the scene
void drawScene() {
    mainWindow.clear();
    //Set-up for pause indicator
    pause_square.setSize(sf::Vector2f(_PAUSE_INDICATOR_WIDTH, _PAUSE_INDICATOR_HEIGHT)); //creates basic shape, sizes defined via macros for easier editing
    pause_square.setOutlineColor(sf::Color::White); //define color
    pause_square.setOutlineThickness(5); //define outline thickness
    pause_square.setFillColor(sf::Color::Red); //define fill color
    pause_square.setPosition(280, 250); //define position in window, hard-coded since no resizing of window available
    //Set-up for Answer A
    a_square.setSize(sf::Vector2f(_ANSWER_SQUARE_WIDTH, _ANSWER_SQUARE_HEIGHT   ));
    //toggles outline color based on selection flag, applies to all other answer squares
    if (aSelected)
        a_square.setOutlineColor(sf::Color::Blue);
    else
        a_square.setOutlineColor(sf::Color::White);
    a_square.setOutlineThickness(5);
    //toggles fill color based on answer flag and if correct/incorrect, applies to all other answer squares
    if (questionAnswered && aCorrect)
        a_square.setFillColor(sf::Color::Green);
    else if (questionAnswered && !aCorrect)
        a_square.setFillColor(sf::Color::Red);
    else
        a_square.setFillColor(sf::Color::Black);
    a_square.setPosition(60, 700);
    //Set-up for Answer S
    s_square.setSize(sf::Vector2f(_ANSWER_SQUARE_WIDTH, _ANSWER_SQUARE_HEIGHT));
    if (sSelected)
        s_square.setOutlineColor(sf::Color::Blue);
    else
        s_square.setOutlineColor(sf::Color::White);
    s_square.setOutlineThickness(5);
    if (questionAnswered && sCorrect)
        s_square.setFillColor(sf::Color::Green);
    else if (questionAnswered && !sCorrect)
        s_square.setFillColor(sf::Color::Red);
    else
        s_square.setFillColor(sf::Color::Black);
    s_square.setPosition(440, 700);
    //Set-up for Answer D
    d_square.setSize(sf::Vector2f(_ANSWER_SQUARE_WIDTH, _ANSWER_SQUARE_HEIGHT));
    if (dSelected)
        d_square.setOutlineColor(sf::Color::Blue);
    else
        d_square.setOutlineColor(sf::Color::White);
    d_square.setOutlineThickness(5);
    if (questionAnswered && dCorrect)
        d_square.setFillColor(sf::Color::Green);
    else if (questionAnswered && !dCorrect)
        d_square.setFillColor(sf::Color::Red);
    else
        d_square.setFillColor(sf::Color::Black);
    d_square.setPosition(800, 700);
    //Set-up for Answer F
    f_square.setSize(sf::Vector2f(_ANSWER_SQUARE_WIDTH, _ANSWER_SQUARE_HEIGHT));
    if (fSelected)
        f_square.setOutlineColor(sf::Color::Blue);
    else
        f_square.setOutlineColor(sf::Color::White);
    f_square.setOutlineThickness(5);
    if (questionAnswered && fCorrect)
        f_square.setFillColor(sf::Color::Green);
    else if (questionAnswered && !fCorrect)
        f_square.setFillColor(sf::Color::Red);
    else
        f_square.setFillColor(sf::Color::Black);
    f_square.setPosition(1160, 700);
    //draw all shapes
    if(paused)
        mainWindow.draw(pause_square);
    else {
        mainWindow.draw(a_square);
        mainWindow.draw(s_square);
        mainWindow.draw(d_square);
        mainWindow.draw(f_square);
    }
}