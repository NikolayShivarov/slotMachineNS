#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>

using namespace std;

class SymbolCounter {
    int count;
    int lastLine;

    public:
    SymbolCounter(){
        count = 0;
        lastLine = 0;
    }
    void restart(){
        count = 0;
        lastLine = 0;
    }
    void addSymbol(int currentLine){
         if(currentLine == lastLine){
            count += 1;
         }
         else{
            count = 1;
            lastLine = currentLine;
         }  
    }

    int getCount(){ 
        return count;
    }


};

class Line {
    vector<int> rowCoordinates;
    vector<int> columnCoordinates;

    public:
    Line(){

    }
    Line(vector<int> rows, vector<int> columns){
        rowCoordinates = rows;
        columnCoordinates = columns;
    }
    Line& operator=(const Line& other){
        if(this == &other) return *this;
        rowCoordinates = other.rowCoordinates;
        columnCoordinates = other.columnCoordinates;
        return *this;
    }

    int getRow(int i){
        return rowCoordinates[i];
    }

    int getColumn(int j){
        return columnCoordinates[j];
    }
};

class Slot {
    vector<char> symbols;
    int numberOfSymbols;
    vector<vector<int>> gameScreen;
    vector<Line> lines;
    vector<SymbolCounter> counter;
    float balance;
    float bet;
    vector<float> multipliyers;

    void insertMoney(float sum){
        balance += sum;
    }

    void betMoney(){
        balance -= bet;
    }

    void changeBetMoney(){
        float amount;
        cout << "Enter the new amount that you want to bet:";
        cin >> amount;
        bet = amount;
        cout << endl; 
    }

    void displayInsertMoney(){
        float money;
        cout << "Please write the sum of money that you want to insert: ";
        cin>>money;
        insertMoney(money);
    }

    void displayGame(){
        for(int i = 0; i < gameScreen.size(); i++){
            for(int j = 0; j < gameScreen[0].size(); j++) cout << symbols[ gameScreen[i][j] ];
            cout << endl; 

        }
             
    }

    void displayHelpMenu(){
        cout << "--------------------------------------------------"<< endl;
        cout << "If you want to change your bet sum press b" << endl;
        cout << "If you want to spin press s" << endl;
        cout << "If you want to insert money press i" << endl;
        cout << "If you want to stop playing press e" << endl;
        cout << "Your bet is " << bet << " and your balance is " << balance << endl;
        cout << "--------------------------------------------------"<< endl;
    }

    void generateRandomSymbols(){
        for(int i = 0; i < gameScreen.size(); i++){
            for(int j = 0; j < gameScreen[0].size(); j++)  gameScreen[i][j] = rand() % numberOfSymbols ;
             

        }
    }

    void spin(){
        if(bet > balance){
            cout << "YOU DONT HAVE ENOUGH MONEY!!!!!!" << endl;
            return;
        }
        betMoney();
        generateRandomSymbols();
        int profit = calculateProfit();
        insertMoney(profit);
        displayGame();
        cout << endl << "YOU HAVE WON: " << profit << endl; 

    }

    float calculateProfit(){
        float sum = 0;
        for(SymbolCounter& s: counter){
             s.restart();
        }
        for(int line = 0; line < lines.size(); line++){
            for(int k = 0; k < gameScreen[0].size(); k++){
                int i = lines[line].getRow(k);
                int j = lines[line].getColumn(k);
                int symbolIndex = gameScreen[i][j];
                counter[symbolIndex].addSymbol(line);
                sum += bet * multipliyers[counter[symbolIndex].getCount()-1]; 

            }     
        }

        return sum;
    }

    public:
    Slot(vector<char>& _symbols, int numberOfRows, int numberOfColumns, vector<Line>& _lines, vector<float>& _multipliyers){
        symbols = _symbols;
        numberOfSymbols = symbols.size();
        gameScreen.resize(numberOfRows);
        for(int i = 0; i < numberOfRows; i++) gameScreen[i].resize(numberOfColumns);
        lines.resize(_lines.size());
        for(int i = 0; i < lines.size(); i++) lines[i] = _lines[i];
        multipliyers = _multipliyers;
        balance = 0.0;
        bet = 10.0;
        counter.resize(symbols.size());

    }

    void play(){
        cout << "------WELCOME TO OUR SLOT!!!!!------" << endl;
        displayInsertMoney();
        bool isPlaying = true;
        while(isPlaying){
                displayHelpMenu();
                string input;
                cin >> input;
                if(input == "s") spin();
                if(input == "i") displayInsertMoney();
                if(input == "b") changeBetMoney();
                if(input == "e") {
                    cout<< "GOOD BYE";
                    isPlaying = false;
                }
               }

    }   

};

int main(){
    vector<char> symbols = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    vector<float> multipliyers = {0.0, 0.0, 1.0, 4.0, 5.0};
    vector<int> line1Rows = {0, 0, 0, 0, 0}; //first row
    vector<int> line1Cols = {0, 1, 2, 3, 4};
    vector<int> line2Rows = {1, 1, 1, 1, 1}; // second row
    vector<int> line2Cols = {0, 1, 2, 3, 4};
    vector<int> line3Rows = {2, 2, 2, 2, 2}; // third row
    vector<int> line3Cols = {0, 1, 2, 3, 4};
    vector<int> line4Rows = {2, 0, 2, 0, 2}; // M
    vector<int> line4Cols = {0, 1, 2, 3, 4};
    vector<int> line5Rows = {0, 2, 0, 2, 0}; // W
    vector<int> line5Cols = {0, 1, 2, 3, 4};
    vector<Line> lines;
    lines.push_back(Line(line1Rows,line1Cols));
    lines.push_back(Line(line2Rows,line2Cols));
    lines.push_back(Line(line3Rows,line3Cols));
    lines.push_back(Line(line4Rows,line4Cols));
    lines.push_back(Line(line5Rows,line5Cols));  

    Slot letterSlot(symbols, 3, 5, lines, multipliyers);
    letterSlot.play();


    
    return 0;
}