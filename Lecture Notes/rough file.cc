//
//  mainRough.cpp
//  Project 1 CS32
//
//  Created by Jonathan Goh on 1/12/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

// gas.cpp
#include "Flatulan.h"
#include "Player.h"
#include "History.h"

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////


const int INITIAL_PLAYER_HEALTH = 10;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class City;  // This is needed to let the compiler know that City is a
// type name, since it's mentioned in the Flatulan declaration.

/*
class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        char m_notConverted;
        char grids[MAXROWS][MAXCOLS]={{0}};
        City* m_city;
        int m_cols;
        int m_rows;
};
*/




class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();


History::History(int nRows, int nCols)
{
    m_rows=nRows;
    m_cols=nCols;
    
}

bool History::record(int r, int c)
{
    if(r<1||c<1||r<MAXROWS||c<MAXCOLS)
    {
        return false;
    }
    else
    {
        for (int r = 0; r < m_rows; r++)
        {
            for (int c = 0; c < m_cols; c++)
                if(grids[r][c]=='0')
                    grids[r][c]='.';
        }
        
        if (grids[r-1][c-1]=='.')
            grids[r-1][c-1]='A';
        else if (grids[r-1][c-1]!='Z')
            grids[r-1][c-1]+=1;
       /* for (int row = 0; row < m_rows; r++)
        {
            for (int col = 0; col < m_cols; c++)
            {
                    char& gridsChar = grids[row][col];
                    switch (gridsChar)
                    {
                        case ' ':   gridsChar = '.'; break;
                        case '.':  gridsChar = 'A'; break;
                        case 'Z':  break;
                        default:   gridsChar++; break;  // 'A' through 'Z'
                    }
            }
        }
        */
        return true;
    }
}

void History::display() const
{
    clearScreen();
    
    // Draw the grid
    
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
            cout << grids[r][c];
        cout << endl;
    }
    cout << endl;
    
}



///////////////////////////////////////////////////////////////////////////
//  Flatulan implementation
///////////////////////////////////////////////////////////////////////////

Flatulan::Flatulan(City* cp, int r, int c)
: m_city(cp), m_row(r), m_col(c)
{
    if (cp == nullptr)
    {
        cout << "***** A Flatulan must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "***** Flatulan created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
}

int Flatulan::row() const
{
    return m_row;
}

int Flatulan::col() const
{
    return m_col;
}

void Flatulan::move()
{
    // Attempt to move in a random direction; if we can't move, don't move.
    // If the player is there, don't move.
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
    int r = m_row;
    int c = m_col;
    m_city->determineNewPosition(r, c, dir);
    Player* p = m_city->player();
    if (r != p->row()  ||  c != p->col())
    {
        m_row = r;
        m_col = c;
    }
}

bool Flatulan::possiblyGetConverted()  // return true if converted
{
    // Be converted with 2/3 probability
    return randInt(0, 2) < 2;
    
}





///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(City* cp, int r, int c)
: m_city(cp), m_row(r), m_col(c), m_health(INITIAL_PLAYER_HEALTH), m_age(0)
{
    if (cp == nullptr)
    {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

int Player::health() const
{
    return m_health;
}

bool Player::isPassedOut() const
{
    return m_health <= 0;
}

void Player::preach()
{
    m_age++;
    m_city->preachToFlatulansAroundPlayer();
}

void Player::move(int dir)
{
    m_age++;
    int r = m_row;
    int c = m_col;
    if (m_city->determineNewPosition(r, c, dir))
    {
        // If there are no Flatulans at the new position
        if (m_city->nFlatulansAt(r, c) == 0)
        {
            m_row = r;
            m_col = c;
        }
    }
}

void Player::getGassed()
{
    m_health--;
}

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

City::City(int nRows, int nCols)
: m_rows(nRows), m_cols(nCols), m_player(nullptr), m_nFlatulans(0), m_history(nRows,nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** City created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
}

History& City::history(int r, int c)
{
    return m_history;
}

City::~City()
{
    for (int k = 0; k < m_nFlatulans; k++)
        delete m_flatulans[k];
    delete m_player;
}

int City::rows() const
{
    return m_rows;
}

int City::cols() const
{
    return m_cols;
}

Player* City::player() const
{
    return m_player;
}

int City::flatulanCount() const
{
    return m_nFlatulans;
}

int City::nFlatulansAt(int r, int c) const
{
    int count = 0;
    for (int k = 0; k < m_nFlatulans; k++)
    {
        const Flatulan* fp = m_flatulans[k];
        if (fp->row() == r  &&  fp->col() == c)
            count++;
    }
    return count;
}

bool City::determineNewPosition(int& r, int& c, int dir) const
{
    switch (dir)
    {
        case UP:     if (r <= 1)      return false; else r--; break;
        case DOWN:   if (r >= rows()) return false; else r++; break;
        case LEFT:   if (c <= 1)      return false; else c--; break;
        case RIGHT:  if (c >= cols()) return false; else c++; break;
        default:     return false;
    }
    return true;
}

void City::display() const
{
    // Position (row,col) in the city coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each Flatulan's position
    for (int k = 0; k < m_nFlatulans; k++)
    {
        const Flatulan* fp = m_flatulans[k];
        char& gridChar = grid[fp->row()-1][fp->col()-1];
        switch (gridChar)
        {
            case '.':  gridChar = 'F'; break;
            case 'F':  gridChar = '2'; break;
            case '9':  break;
            default:   gridChar++; break;  // '2' through '8'
        }
    }
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a Flatulan there
        // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, Flatulan, and player info
    cout << "There are " << m_nFlatulans << " unconverted Flatulans remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isPassedOut())
            cout << "The player has passed out." << endl;
        else
            cout << "The player's health level is " << m_player->health() << endl;
    }
}

bool City::addFlatulan(int r, int c)
{
    if (! isInBounds(r, c))
        return false;
    
    // Don't add a Flatulan on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    
    // Dynamically allocate a new Flatulan and add it to the city
    if (m_nFlatulans == MAXFLATULANS)
        return false;
    m_flatulans[m_nFlatulans] = new Flatulan(this, r, c);
    m_nFlatulans++;
    return true;
}

bool City::addPlayer(int r, int c)
{
    if (! isInBounds(r, c))
        return false;
    
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Don't add a player on a spot with a Flatulan
    if (nFlatulansAt(r, c) > 0)
        return false;
    
    // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

void City::preachToFlatulansAroundPlayer()
{
    History& hist = m_history;
    // Preach to Flatulans orthogonally or diagonally adjacent to player.  If a
    // Flatulan is converted, then since the order of the Flatulans in the array
    // doesn't matter, we can replace the converted Flatulan we remove from the
    // game by the last one in the array.
    for (int k = 0; k < m_nFlatulans; )
    {
        Flatulan* fp = m_flatulans[k];
        int rowdiff = fp->row() - m_player->row();
        int coldiff = fp->col() - m_player->col();
        
        // if orthogonally or diagonally adjacent and conversion succeeds
        if (rowdiff >= -1  &&  rowdiff <= 1  &&
            coldiff >= -1  &&  coldiff <= 1  &&
            fp->possiblyGetConverted() )
        {
            delete m_flatulans[k];
            m_flatulans[k] = m_flatulans[m_nFlatulans-1];
            m_nFlatulans--;
        }
        else
        {
            k++;
            hist.record(fp->row(),fp->col());
        }
    }
}

void City::moveFlatulans()
{
    for (int k = 0; k < m_nFlatulans; k++)
    {
        Flatulan* fp = m_flatulans[k];
        fp->move();
        int rowdiff = fp->row() - m_player->row();
        int coldiff = fp->col() - m_player->col();
        // if orthogonally adjacent
        if  ((rowdiff == 0  &&  (coldiff == 1  ||  coldiff == -1))  ||
             (coldiff == 0  &&  (rowdiff == 1  ||  rowdiff == -1)) )
            m_player->getGassed();
    }
}

bool City::isInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nFlatulans)
{
    if (nFlatulans < 0)
    {
        cout << "***** Cannot create Game with negative number of Flatulans!" << endl;
        exit(1);
    }
    if (nFlatulans > MAXFLATULANS)
    {
        cout << "***** Trying to create Game with " << nFlatulans
        << " Flatulans; only " << MAXFLATULANS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nFlatulans > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the Flatulans!" << endl;
        exit(1);
    }
    
    // Create city
    m_city = new City(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_city->addPlayer(rPlayer, cPlayer);
    
    // Populate with Flatulans
    while (nFlatulans > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a Flatulan where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_city->addFlatulan(r, c);
        nFlatulans--;
    }
}

Game::~Game()
{
    delete m_city;
}

void Game::play()
{
    History& hist = m_city->history(m_city->rows(), m_city->cols());
    m_city->display();
    Player* p = m_city->player();
    if (p == nullptr)
        return;
    
    while ( ! p->isPassedOut()  &&  m_city->flatulanCount() > 0)
    {
        cout << "Move (u/d/l/r//h/q): ";
        string action,action2;
        getline(cin,action);
        if (action.size() == 0)  // player preaches
            p->preach();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'h':
                    hist.display();
                    cout<<"Press enter to continue";
                    cin.ignore(10000,'\n');
                    
                    clearScreen();
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
            }
        }
        m_city->moveFlatulans();
        m_city->display();
    }
    if (p->isPassedOut())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
