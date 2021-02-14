#include <iostream>
#include <fstream>
#include <stdio.h>
#include <filesystem>

const int MAX_USERS_IN_SYSTEM = 100;

std::string usernames[MAX_USERS_IN_SYSTEM];
std::string passwords[MAX_USERS_IN_SYSTEM];
double balances[MAX_USERS_IN_SYSTEM];
int usersSize = 0;

const int MAX_HISTORY_LENGTH = 100;
int historySize = 0;

std::string entries[MAX_HISTORY_LENGTH];
double values[MAX_HISTORY_LENGTH];

const int MAX_USER_PIGGIES = 100;

std::string userPiggies[MAX_USER_PIGGIES];
int piggiesSize = 0;

void loadUsers(){
    std::ifstream file("users.txt");
    int userIdx = 0;
    if(file.good() and userIdx < MAX_USERS_IN_SYSTEM){
        while(!file.eof()){
            std::string line = "";
            std::getline(file, line);
            size_t firstColon = line.find(':', 0);
            size_t secondColon = line.find(':', firstColon + 1);
            std::string username = line.substr(0, firstColon);
            std::string password = line.substr(firstColon + 1, secondColon);
            double balance = std::stod(line.substr(secondColon, line.length()));
            // std::cout << username << " " << password << std::endl;
            usernames[userIdx] = username;
            passwords[userIdx] = password;
            balances[userIdx] = balance;
            userIdx++;
        }
        file.close();
        usersSize = userIdx;
    }
}

void loadHistory(std::string historyName){
    std::ifstream file(historyName + ".txt");
    int entryIdx = 0;
    if(file.good()){
        while(!file.eof()){
            std::string line = "";
            std::getline(file, line);
            size_t firstColon = line.find(':', 0);
            size_t secondColon = line.find(':', firstColon + 1);
            std::string entry = line.substr(0, firstColon);
            std::string value = line.substr(firstColon + 1, secondColon);
            entries[entryIdx] = entry;
            values[entryIdx] = std::stod(value);
        }
        file.close();
        historySize = entryIdx;
    }
}

void loadPiggies(std::string username){
    std::ifstream file(username + ".piggyies");
    int piggyIdx = 0;
    if(file.good()){
        while(!file.eof()){
            getline(file, userPiggies[piggyIdx]);
            piggyIdx++;
        }
        piggiesSize = piggyIdx;
        file.close();
    }
}

void saveUsers(){
    std::ofstream file("users.txt", std::ios::trunc);
    if(file.good()){
        for(int i = 0; i < usersSize; i++){
            file << usernames[i] << ":" << passwords[i] << ":" << balances[i] << std::endl;
        }
        file.close();
    }
}

void saveHistory(std::string historyName){
    std::ofstream file(historyName + ".piggy", std::ios::trunc);
    if(file.good()){
        for(int i = 0; i < historySize; i++){
            file << entries[i] << ":" << values[i] << std::endl;
        }
        file.close();
    }
}

void savePiggies(std::string username){
    std::ofstream file(username + ".piggies");
    if(file.good()){
        for(int i = 0; i < piggiesSize; i++){
            file << userPiggies[i] << std::endl;
        }
        file.close();
    }
}

bool authorize(std::string username, std::string password){
    for(int i = 0; i < usersSize; i++){
        if(usernames[i] == username){
            if(passwords[i] == password) return true;
            else return false;
        }
    }
    return false;
}

void chooseAndLoadPiggy(){
    int response;
    do{
        std::cout << "Load Piggy" << std::endl;
        for(int i = 0; i < usersSize; i++){
            std::cout << i << ". " << userPiggies[i] << std::endl;
        }
        std::cin >> response;
        std::cout << std::endl;
    }while(response > piggiesSize or response < 0);
    
    loadHistory(userPiggies[response]);
}

void addPiggy(){
    std::cout << "Add Piggy" << std::endl;
    std::string piggyName;
    std::cin >> piggyName;
    std::ofstream file(piggyName + ".piggy");
    file.close();
    userPiggies[piggiesSize] = piggyName;
    piggiesSize++;
}

void removePiggy(){
    int response;
    do{
        std::cout << "Remove Piggy" << std::endl;
        for(int i = 0; i < usersSize; i++){
            std::cout << i << ". " << userPiggies[i] << std::endl;
        }
        std::cin >> response;
        std::cout << std::endl;
    }while(response > piggiesSize or response < 0);
    remove((userPiggies[response] + ".piggy").c_str());
    for(int i = response; i < piggiesSize - 1; i++){
        userPiggies[i] = userPiggies[i + 1];
    }
    
}

int username2int(std::string username){
    for(int i = 0; i < MAX_USERS_IN_SYSTEM; i++){
        if(username == usernames[i]) return i;
    }
    return -1;
}

void showHistory(){
    for(int i = 0; i < historySize; i++){
        std::cout << entries[i] << " " << values[i] << "PLN" << std::endl;
    }
    
    std::cout << "Press anything to return" << std::endl;
    getchar();
}

std::string askName(){
    std::string name;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << std::endl;
    return name;
}

double askValue(){
    double value = 0;
    std::cout  << "value: ";
    std::cin >> value;
    std::cout << std::endl;
    return value;
}

void addTransaction(){
    if(historySize >= MAX_HISTORY_LENGTH){
        for(int i = 1; i < MAX_HISTORY_LENGTH; i++){
            entries[i-1] = entries[i];
            values[i-1] = values[i];
        }
        entries[historySize - 1] = askName();
        values[historySize - 1] = askValue();
    }
    else{
        entries[historySize] = askName();
        values[historySize] = askValue();
        historySize++;
    }
}

void showTransactionsMenu(){
    int response;
    do{
        std::cout << "Transactions" << std::endl;
        std::cout << "1.Add Transaction" << std::endl;
        std::cout << "2.istory" << std::endl;    
    }while(response < 1 or response > 2);
    
    switch(response){
        case 1:{
            addTransaction();
            break;
        }
        case 2:{
            showHistory();
            break;
        }
    }
}

void piggyMenu(std::string username){
    int response;
    do{
        std::cout << "PIGGY MENU" << std::endl;
        std::cout << "1.Change balance" << std::endl;
        std::cout << "2.Transactions" << std::endl;    
    }while(response < 0 or response > 3);
    
    switch(response){
        case 1:{
            std::cout << "New Balance is: ";
            double newBalance;
            std::cin >> newBalance;
            balances[username2int(username)] = newBalance;
            std::cout << std::endl;
            break;
        }
        case 2:{
            std::cout << "Transactions Menu";
            showTransactionsMenu();
            break;
        }
    }
    
    
}

int main(){

    loadUsers();
    
    std::string login;
    std::string password;
    
    while(true){
        do{ 
            std::cout << "Login: ";
            std::cin >> login;
            std::cout << std::endl;
            
            std::cout << "Password: ";
            std::cin >> password;
            std::cout << std::endl;
        }while(authorize(login, password));
        
        loadPiggies(login);
        
        
        std::cout << "MAIN MENU" << std::endl;
        std::cout << "1.Load piggy" << std::endl;
        std::cout << "2.Add piggy" << std::endl;
        std::cout << "3.Remove piggy" << std::endl;
        
        int response;
        bool selected = false;
        std::cin >> response;
        std::cout << std::endl;
        
        while(!selected){
            switch(response){
                case 1:{
                    selected = true;
                    chooseAndLoadPiggy();
                    piggyMenu(login);
                    break;
                }
                case 2:{
                    selected = true;
                    addPiggy();
                    break;
                }
                case 3:{
                    selected = true;
                    removePiggy();
                    break;
                }
                default: std::cout << "Wrong number must be in range <1,3>";
            }
        }
        
    }
       
    return 0;
}