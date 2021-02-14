#include <iostream>
#include <fstream>

const int TOTAL_USERS_IN_SYSTEM = 100;

std::string usernames[TOTAL_USERS_IN_SYSTEM];
std::string passwords[TOTAL_USERS_IN_SYSTEM];
double balances[TOTAL_USERS_IN_SYSTEM];
int usersSize = 0;

const int MAX_HISTORY_LENGTH = 100;
int historySize = 0;

std::string entries[MAX_HISTORY_LENGTH];
double values[MAX_HISTORY_LENGTH];

void loadUsers(){
    std::ifstream file("users.txt");
    int userIdx = 0;
    if(file.good() and userIdx < TOTAL_USERS_IN_SYSTEM){
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
    std::ofstream file(historyName + ".txt", std::ios::trunc);
    if(file.good()){
        for(int i = 0; i < historySize; i++){
            file << entries[i] << ":" << values[i] << std::endl;
        }
        file.close();
    }
}

int main(){

    loadHistory("tets");
       
    return 0;
}