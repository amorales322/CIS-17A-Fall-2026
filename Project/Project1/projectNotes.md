# Project: Chess

## Structures

```c++
struct charAry {
    unsigned char *data;
    unsigned int size;
    unsigned int utilSze;
};

struct player {
    unsigned short nWins;
    unsigned short nLoss;
    string name;
};

struct board {
    const unsigned int vertSze{8};
    const unsigned int horznSz{8};
    piece **board;
    
    player *white;
    unsigned char wFleLoc;
    player *black;
    unsigned char bFleLoc;
    
    bool wFstMve;
    bool bFstMve;
    
    bool chkmte;
    bool stlemte;
    bool deadBrd;
};

struct piece {
    // The board is initialized as a two-dimensional array of piece structs, pieces are moved using a helper function that copys the data from one piece struct to another and eliminates pieces
    bool empty;
    bool isWhite;
    pceID pieceID;
    // Used for determining if a pawn is capable of moving two spaces
    bool fstMove;
    // For pawns, if it is able to be captured by en passant
    bool enPasnt;

    // Valid moves that the piece can go to, including capture positions. For the king, this is any safe position it can move to
    charAry *vldMove;
    
    // King Variables
    bool inCheck;
    // Path capture piece has to king - used for piece iterposer calculation function to determine if any piece can get in the way and stop the check
    charAry *capPth;
};
```

## Enums

```c++
    enum pceID {KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN};
```

## Functions

```c++
    // Determines if the board is dead and if only kings remain
    bool deadBrd(board *board);

    // Piece Interposing Calculation Function
    bool pceIntr(board *board, const unsigned char kingPos, const unsigned char tgtPos, const charAry * const capPath);

    // Used for the king, calculates if the specified space is safe by using the move calculation functions to determine if the king is able to move to this space
    bool sfeSpce(board *board, const unsigned char tgtPos);

    // Move Calculation Functions
    void kingMov(bool rtrPcLc, const unsigned char initPos, charAry *data);
    void lineMov(bool rtrPcLc, const unsigned char initPos, charAry *data);
    void diagMov(bool rtrPcLc, const unsigned char initPos, charAry *data);
    void knitMov(bool rtrPcLc, const unsigned char initPos, charAry *data);
    void pawnMov(bool isFirstMove, bool enPasnt, bool rtrPcLc, const unsigned char initPos, charAry *data);
    void castle(bool rtrPcLc, const unsigned char initPos, charAry *data)

    void mvePce(const unsigned char a, const unsigned char b); 

    // Get move input from player
    unsigned char getMove();

    // Move verification function
    bool vldMove(board *board, const unsigned char tgtMove, const charAry * const vldMves)

    // Function to promote piece
    void pmtePce(board *board, const unsigned char tgtPce);

    // Drawing to and clearing screen
    void drawBrd(board *board);
    void clrScrn();

    // Save Game
    void sveGame(board *board, fstream &file);

    // Allocater Funcitons
    charAry *alloc(const unsigned int size*)
    board *initBrd(bool fromFile, fstream &file);
    board *initPlyr(bool fromFile, fstream &file);
    player *newPlyr()

    // Append Functions
    void appDta(charAry *target, const unsigned char input);
    void appDta(charAry *target, charAry *from, bool dstryFm);

    // Resize Functions
    // 1. If the new capacity is not specified, the size increases by 1. 
    // 2. Does nothing if the new specified capacity is less than the current size, does not truncate data
    void resize(charAry *array, int newCap = -1);

    // Deallocator Functions
    void dealloc(charAry *array);
    void dealloc(board *board)
    void dealloc(player *player);
```

## Board Notes

* Board will be initialized using a board struct & initialization function
    * Board struct contains:
        * Dynamically Allocated two-dimensional array (8x8)
    * Initialization function *initBrd()*
        * Creates a board struct pointer & dynamically allocates the struct
        * Places all the pieces on the board or restores game state from file if specified
        * Returns the board struct pointer

## Player Notes

* Player data will be kept in a player struct and saved to a binary file when the game is saved
* Player struct contains:
    * unsigned short (2-bytes): Number wins
    * unsigned short (2-bytes): Number losses
    * unsigned char (1-byte): Player name length
    * string containing the player name: Maximum 34 characters + null terminator (35 bytes)
        * Uses reserve() method to resize string to capacity
        * Uses data() method to write/read from string

## Player Turn

* Before the player can make their decision, the board is checked to see if only kings remain, signaling a dead
  position (uses the deadBrd() function to calculate this)

* If not, the king is first checked to see if it is in check using the check flag calculated from the move calculation
  functions from the other player's turn

* **If the king is in check:**
    * The program calculates where the king can move using this algorithm:
        * First, it eliminates the surrounding spaces it cannot move to using the data from the other players previous
          turn
        * It checks if the king is being put in check by a queen, rook, or bishop, and uses prediction functions to
          determine if any piece in the area can be moved to interpose between the king and the attacking piece
        * It also checks if there are any pieces surrounding it that it can capture
        * Then, for each remaining space, it searches around the board using the move calculation functions (with the
          find
          mode specified, to check if it is a safe space to move to or and eliminates the space if it is not

    * If there are no more remaining spaces after this elimination process and the king is in check, the game ends in a
      checkmate
    * If there are no more remaining spaces and the king is not in check, then the game ends in a stalemate
    * Otherwise
    * Otherwise, it presents the valid options that the king can move to and prompts the player to move their king to a
      safe
      space
* **If the king is not in check:**
    * The pawns are checked to determine if an en passant capture can be performed,
      reading the data from each of the pawn structs and using the enPasnt() function to calculate which
      piece it can capture and where to move to.


* If none of these apply, then the game continues as normal and prompts the player for their move, using the move
  calculation functions and the vldMove() function to validate player moves

## After player turn

* After a piece is moved, it uses the capKing() function to search if it can capture the king from its final position,
  and write the path data to the capPth attribute of the king piece struct
* The data from the move calculation functions are saved for the next turn
* If a pawn is able to promote, then the promotion process starts
    * The player specifies which piece they would like to replace the pawn with
    * The piece is replaced

## Move Calculation Functions

* Uses 5 functions to calculate the different valid spaces that can be moved to
* Each function takes a start position for where to calculate the valid positions from
* Each function then calculates the position that can be moved to, accounting for obstacle pieces that are in the way
* If the returnPieceLocation flag is set, the function instead searches if there are any pieces at the target locations,
  and returns their positions if the piece is able to move to the original location
* The function "returns" one value through the parameters passed to it
    * If the returnPieceLocation flag is not set
        * An array of all the valid positions that the piece can move to based on its movement pattern and any obstacle
          pieces
    * If the returnPieceLocation flag is set
        * An array of all the pieces at the target locations that are able to move to the initial position

### Calculation Functions

1. kingMov(bool rtrPcLc, const unsigned char initPos, charAry *data)
    * Calculates moves for surrounding places
2. lineMov(bool rtrPcLc, const unsigned char initPos)
    * Calculates moves for vertical and horizontal places
3. diagMov(bool rtrPcLc, const unsigned char initPos)
    * Calculates diagonal moves
4. knitMov(bool rtrPcLc, const unsigned char initPos)
    * Calculates moves for knights
5. pawnMov(bool isFirstMove, bool enPasnt, bool rtrPcLc, const unsigned char initPos)
    * Calculates the moves for pawns based on if it is the first move or not
    * Also checks the diagonals to determine if it can capture and move there (adjusts valid positions array to account
      for this)

## Save Files (Binary File) Notes

### Player Data Save File

* The first 512 bytes is a metadata table containing the offset for where each player's data is stored
* For the game save file, this is where the player data offsets get their values from
* The rest of the bytes contains the player save data

### Game Data Save File

* The first byte of the binary file will specify who's turn it is (white or black)
    * If this value is false, then it is player 1's (always white, second byte) turn
    * If this value is true, then it is player 2's (always black, third byte) turn
* The second byte (unsigned char - 255) will specify the player id to read from the player data from
* The third byte (unsigned char - 255), will, specify the player id to read the player data from
* The rest of the file contains the board data that will be loaded using the board initialization function
