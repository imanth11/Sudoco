#include <iostream>
#include <fstream>
#include <cstring>
#include "clui.h"
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <thread>
#include  <chrono>
#include <vector>
#include <conio.h>  

using namespace std;
int row = get_window_rows();

    int col = get_window_cols();

const int Maxlength = 50;

void print_scores(const string& filename = "scores.txt") {
    ifstream infile(filename);

    string name;
    int score;
    if (infile.is_open()) {

        cursor_to_pos(1,col/2);
clear_screen();
        cout << "Current Scores:" << endl;
int i=0;
        while (infile >> name >> score) {
            cursor_to_pos(i+3,col/2);
            change_color_rgb(6, 67, 128);
            cout << name << " " << score << endl;
            reset_color();
            i++;
        }
delay(3000);
        infile.close();
    } else {
        cout << "Error opening file!" << endl;
    }
}


struct User {
    string username;
    int score;
};


void bubbleSort(vector<User>& users) {
    int n = users.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {

            if (users[j].score < users[j + 1].score) { 

                swap(users[j], users[j + 1]);
            }
        }
    }
}

void save_score(const string& username, int score, const string& filename = "scores.txt") {
    vector<User> users;
    ifstream infile(filename);

    
    if (infile.is_open()) {
        string name;
        int user_score;
        while (infile >> name >> user_score) {
            users.push_back({name, user_score});
        }
        infile.close();
    }

    
    users.push_back({username, score});

    
    bubbleSort(users);

    
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const auto& user : users) {
            outfile << user.username << " " << user.score << endl;
        }
        outfile.close();
    } else {
        cout << "Error opening file!" << endl;
    }
}



bool is_repeatative(const char* name, const char* list_of_name) {
    ifstream file(list_of_name);

    char existingName[Maxlength];

    while (file >> existingName) {
        if (strcmp(existingName, name) == 0) {
            return true;
        }
    }
    file.close();
    return false;
}


void savename(const char* name, const char* list_of_name) {
    ofstream file(list_of_name, ios::app);

    file << name << endl;
    file.close();
}


bool isValidMove(int grid[9][9], int row, int col, int num) {
    
    for (int i = 0; i < 9; ++i) {
        if (grid[row][i] == num) return false;
    }
 
    for (int i = 0; i < 9; ++i) {
        if (grid[i][col] == num) return false;
    }
 
  
    return true;
}
bool is_valid(int grid[9][9],int row,int col ,int value){
    for ( int i = 0; i < 9; i++)
    {
        if(grid[row][i]==value){
            return false;
        }
    }
    for ( int j = 0; j < 9; j++)
    {
        if(grid[j][col]==value){
            return false;
        }
    }
    return true;
    

}


void printSudokuDirectly(int grid[9][9], int row, int col, int cursorX = -1, int cursorY = -1) {
    int center_row = row / 2;

    int center_col = col / 2;

    for (int i = 0; i < 9; ++i) {
        cursor_to_pos(center_row + i, center_col);
        for (int j = 0; j < 9; ++j) {

            if (cursorX == i && cursorY == j) {
                change_color_rgb(255, 0, 0); 

                cout << "|" << (grid[i][j] == 0 ? " " : to_string(grid[i][j])) << "|";

                reset_color();
            } else {
                cout << "|" << (grid[i][j] == 0 ? " " : to_string(grid[i][j])) << "|";
            }
        }
        cout << endl;
    }
}

void print(const string& filename,int arr1[9][9],bool arr2[9][9], int& error, int& time){

    ifstream file(filename);

    string line;
    int linecount=0;

    while(getline(file,line)&&linecount<18){
stringstream ss(line);

int value;
int colcount=0;
while(ss >> value){
    if (linecount<9){
        arr1[linecount][colcount]=value;

    }
    else{
        arr2[linecount-9][colcount]=value;
    }
    
    colcount++;
}
linecount++;

    }
    if(getline(file,line)){
        stringstream ss(line);
        ss>>error;
    }
    if(getline(file,line)){
        stringstream ss(line);
        ss>>time;
    }
    file.close();
}

int timeRemaining = 300;

void generateSudokuGrid(int grid[9][9], bool fixed[9][9]) {
    srand(time(0));
    for (int i = 0; i < 9; ++i) {

        for (int j = 0; j < 9; ++j) 
        {
            if (rand() % 100 < 30) { 
                int value;
                bool valid=false;

                while(!valid){

                    value=rand()%9+1;

                    if(is_valid(grid,i,j,value)){
                        valid=true;
                    }

                }
                grid[i][j]=value;
                fixed[i][j]=true;
            } else {
                grid[i][j] = 0; 
                fixed[i][j] = false;
            }
        }
    }
}



void loadGame(int grid[9][9], bool fixed[9][9], int &errors, int &timeRemaining) {
    ifstream file("sudoku_save.txt");

    if (file.is_open()) {
        
        for (int i = 0; i < 9; ++i) {

            for (int j = 0; j < 9; ++j) {
                file >> grid[i][j];
            }
        }

        
        for (int i = 0; i < 9; ++i) {

            for (int j = 0; j < 9; ++j) {
                file >> fixed[i][j];
            }
        }

        
        file >> errors >> timeRemaining;
        file.close();

        cout << "Game loaded successfully!" << endl;
    } else {
        cout << "No saved game found!" << endl;
    }
}

bool fileexist(const string& filename){
    ifstream file(filename);
    return file.good();
}

void savename(const string& filename){

ofstream nameFile("usernames.txt", ios::app); 

    if (nameFile.is_open()) {

        nameFile << filename << endl;  

        nameFile.close();  
cursor_to_pos(row/2+4,col/2);
     change_color_rgb(205, 219, 15);
        cout << "Your name has been saved successfully!" << endl;
        reset_color();
    } else {
        cout << "Error saving your name!" << endl;
    }}
void saveGame(int grid[9][9], bool fixed[9][9], int errors, int timeRemaining) {
     int row = get_window_rows();

    int col = get_window_cols();
   string filename;

clear_screen();

cursor_to_pos(row/2,col/2);

change_color_rgb(148, 15, 219);

   cout<<"Enter your file name with .txt"<<endl;
   reset_color();
   cursor_to_pos(row/2+1,col/2);
   change_color_rgb(148, 15, 219);
   cin>>filename;
   reset_color();

   savename(filename);

   if(!fileexist(filename)){
    ofstream file(filename);


    if (file.is_open()) {
        
        for (int i = 0; i < 9; ++i) {

            for (int j = 0; j < 9; ++j) {
                file << grid[i][j] << " ";
            }
            file << endl;
        }

       
        for (int i = 0; i < 9; ++i) {

            for (int j = 0; j < 9; ++j) {
                file << fixed[i][j] << " ";
            }
            file << endl;
        }

        file << errors << " " <<endl<< timeRemaining << endl;
        file.close();

        change_color_rgb(205, 219, 15);
        cursor_to_pos(row/2+3,col/2);
        cout << "Game saved successfully!" << endl;
        reset_color();
        delay(2000);
    } else {
        cout << "Error saving the game!" << endl;
        
       
    }
}
else{cout<<"the name is repetative";}
delay(4000);



}



void play_save_Sudoku(int grid[9][9], bool fixed[9][9], int row, int col,int error) {
    int x = 0, y = 0;       

    int errors =0 ;         
    bool gamePaused = false;  
    bool gameOver = false;    


    string playerName = "Player"; 
    
    
   

    int previousTime = time(0);  

    while (errors < 5 && timeRemaining > 0 && !gameOver) {   
        int currentTime = time(0);
        int elapsedTime = currentTime - previousTime;  

       
        if (elapsedTime >= 1) {
            if (!gamePaused) {  
                timeRemaining--;  
            }
            previousTime = currentTime;  
        }

      
        if (gamePaused) {
            clear_screen();  
            cursor_to_pos(row / 2, col / 2);  

            change_color_rgb(255, 255, 0);

            cout << "Game Paused. Press ESC to resume."; 
            reset_color();
         
            char input = _getch(); 

            if (input == 27) {
                gamePaused = false; 

                continue;  
            }

          
            continue;
        }

       

        
        char input = _getch();  

        
        if (input == 27) {
            gamePaused = true;  
            continue; 
        }
   clear_screen();  

        printSudokuDirectly(grid, row, col, x, y);  
        cursor_to_pos(row + 1, col / 2); 

        cout << "Errors: " << errors << " / 5";

        cursor_to_pos(row + 2, col / 2);  

        cout << "Time Remaining: " << timeRemaining / 60 << "m " << timeRemaining % 60 << "s";
    
        if (input == 'i' || input == 'I') {
            clear_screen();

            cursor_to_pos(row / 2, col / 2);

            change_color_rgb(255, 255, 0);  

            cout << "Game Information" << endl;
           
            cout << "Errors: " << errors << " / 5" << endl;

            cout << "Time Remaining: " << timeRemaining / 60 << "m " << timeRemaining % 60 << "s" << endl;
            cout << "Press any key to return to the game...";  

            reset_color();
            _getch(); 
            continue;  
        }

        
        if (input == 'z' || input == 'Z') {
            saveGame(grid, fixed,  errors, timeRemaining);
            
            continue;  
        }
        if(input=='q')
{break;}
        


            if (input == 'w'&& x > 0) x--;      
            else if (input == 's' && x < 8) x++; 
            else if (input == 'a' && y > 0) y--; 
            else if (input == 'd' && y < 8) y++; 
     

        
        if (!gamePaused) {
            if (input >= '1' && input <= '9') { 
                if (!fixed[x][y]) { 

                    int num = input - '0'; 

                    if (isValidMove(grid, x, y, num)) {

                        grid[x][y] = num; 
                    } else {
                        errors++;
                    }
                }
            }
        }
    }

    
    if (errors == 5) {
        clear_screen();

        cursor_to_pos(row / 2, col / 2);

        change_color_rgb(255, 0, 0);  

        cout << "Game Over! Too many errors.";
        reset_color();
        _getch();  
    }
    
}



#include <iostream>
#include <ctime>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

 

void updateTimer() {
    int previousTime = time(0);  
    while (timeRemaining > 0) {
        int currentTime = time(0);
        int elapsedTime = currentTime - previousTime;  
        if (elapsedTime >= 1) {
            timeRemaining--;  
            previousTime = currentTime;  
        }
        
        this_thread::sleep_for(chrono::seconds(1)); 
    }
}
void menu();
void playSudoku(int grid[9][9], bool fixed[9][9], int row, int col, const char* name) {
    int point = 0;
    int x = 0, y = 0;      
    int errors = 0;         
    bool gamePaused = false;  
    bool gameOver = false;    

    string playerName = name;  
    
    
    thread timerThread(updateTimer);

    while (errors < 5 && timeRemaining > 0 && !gameOver) {
       
        clear_screen();  
        printSudokuDirectly(grid, row, col, x, y);  
        cursor_to_pos(row + 1, col / 2);  
        cout << "Errors: " << errors << " / 5";
        cursor_to_pos(row + 2, col / 2);  
        cout << "Time Remaining: " << timeRemaining / 60 << "m " << timeRemaining % 60 << "s";

        
        char input = _getch();  

        
        if (input == 27) {  
            clear_screen();
            
            cursor_to_pos(row/2,col/2);

              change_color_rgb(227, 216, 9);
            cout<<"Game Paused";
            reset_color();
            gamePaused = true; 
              char input = _getch();
              if(input==27)
            

              
            continue;  
        }

       
        if (input == 'i' || input == 'I') {
            clear_screen();
            cursor_to_pos(row / 2, col / 2);
            change_color_rgb(255, 255, 0); 
            cout << "Game Information" << endl;
            cout << "Player: " << name << endl;
            cout << "Errors: " << errors << " / 5" << endl;
            cout << "Time Remaining: " << timeRemaining / 60 << "m " << timeRemaining % 60 << "s" << endl;
            cout << "Press any key to return to the game...";  
            reset_color();
            _getch();  
            continue;  
        }
if(input=='q'){
    exit(0);
}
        
        if (input == 'z' || input == 'Z') {
            saveGame(grid, fixed, errors, timeRemaining);
            continue;  
        }

if(input=='m'){
    clear_screen();
    menu();}
        if (input == 'q') {
            break;
        }

        
        if (input == 'w' && x > 0) x--;      
        else if (input == 's' && x < 8) x++; 
        else if (input == 'a' && y > 0) y--; 
        else if (input == 'd' && y < 8) y++; 

        
        if (!gamePaused) {
            if (input >= '1' && input <= '9') { 
                if (!fixed[x][y]) { 
                    int num = input - '0'; 
                    if (isValidMove(grid, x, y, num)) { 
                        grid[x][y] = num;
                        point++; 
                    } else {
                        errors++;
                        point--; 
                    }
                }
            }
        }
    }

    
    if (errors == 5) {
        save_score(name, point);
        cout << point;
        delay(4000);
        clear_screen();
        cursor_to_pos(row / 2, col / 2);
        change_color_rgb(255, 0, 0);  
        cout << "GameOver! Too many errors.";
        reset_color();
        exit(0);  
    }

   
    timerThread.join();
}







void level_time(int level, int row, int col,char* name) {
    int grid[9][9] = {{0}}; 
    bool fixed[9][9] = {{false}}; 
   int timeremaining;
      switch (level)
    {
    case 1:
       
       timeremaining=300;
        break;
    case 2: timeremaining=180;break;

    case 3: timeremaining=120;break;
    default:

        break;
    }

   
   
generateSudokuGrid(grid,  fixed);
    
    
    playSudoku(grid, fixed, row, col,name);
    
}



void menu() {
    int row = get_window_rows();

    int col = get_window_cols();

    const char* list_of_name = "names.txt";

    char name[Maxlength];

    int number;
change_color_rgb(6, 128, 6);
    cout << "Please enter your name: ";

    cin >> name;
reset_color();
    if (is_repeatative(name, list_of_name)) 
    {
        cout << "This name is already taken! You are not allowed to proceed." << endl;

    } else {
        savename(name, list_of_name);

        cursor_to_pos(row / 4, col / 2);

        change_color_rgb(136, 252, 3);
        
        cout << "IN HIS SUBLIME NAME" << endl;
        reset_color();

        change_color_rgb(191, 13, 13);

        cursor_to_pos(row / 3, col / 2);

        cout << "Let's Play Sudoku" << endl;

        reset_color();


        change_color_rgb(136, 252, 3);

        cursor_to_pos(row / 2.7, col);

        cout << " You Logged in as " << name;

        reset_color();

        change_color_rgb(21, 15, 79);

        cursor_to_pos(row / 2.4, col / 1.9);

        cout << "<Game Option>" << endl << endl;

        reset_color();
        int start;
cursor_to_pos(2,col/2);
       change_color_rgb(23, 32, 212);
        cout << "1: " << "Start a New game" << endl
        ;
        cursor_to_pos(3,col/2);
        cout << "2: " << "Play a saved game" << endl;

cursor_to_pos(4,col/2);
        cout << "3: " << "Leaderboard" << endl;

cursor_to_pos(5,col/2);
        cout << "4: " << "Exit the game" << endl << endl;
        cursor_to_pos(6,col/2);
        cin >> start;
reset_color();

        if (start == 1) {
            delay(1000);

            clear_screen();
cursor_to_pos(1,col/2);
            cout << "Press a number from 1 to 3: " << endl;
           
                
                int level;

                cursor_to_pos(5,col/2);
                
                change_color_rgb(212, 23, 36);
                cout << "Select the level: " << endl ;
                   cursor_to_pos(6,col/2);
                cout<< "1: " << "Easy" << endl;
                 cursor_to_pos(7,col/2);
                cout << "2: " << "Medium" << endl;
                 cursor_to_pos(8,col/2);
                cout << "3: " << "Hard" << endl;
                cursor_to_pos(10,col/2);
                cin >> level;
                
                clear_screen();
reset_color();
                level_time(level, row, col,name);
            
        }
        if(start==2){

ifstream nameFile("usernames.txt");
    string name;

    if (nameFile.is_open()) {
cursor_to_pos(row,col/2);
        cout << "Usernames in the file:" << endl;
int i=0;
        while (getline(nameFile, name)) {
            cursor_to_pos(row+1+i,col/2);
            change_color_rgb(255,50,0);
            cout << name << endl;
            i++;
            reset_color();
            
        }
        nameFile.close();
    } else {
        cout << "Error opening the usernames file!" << endl;
    }

            int savegame[9][9];

            bool stable[9][9];

            int error,time;
change_color_rgb(0,200,10);
            cout<<"Enter a name of file with .txt";
            reset_color();
            string filename;
cursor_to_pos(18,40);
            cin>>filename;

            if(fileexist(filename)){

print(filename,savegame,stable,error,time);
clear_screen();

playSudoku(savegame,stable,row,col,"iman");


            }
        }

if(start==3){
    print_scores();

}


if(start==4){
    exit(0);
}



  
}
}
int main(){
    menu(
    );
    return 0;
}

















































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































