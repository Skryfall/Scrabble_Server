
#include <locale>
#include "Server/Server.h"
#include "Logic/Lists/Dictionary/WordList.h"

using namespace std;

int main(){
    WordList* wordList = WordList::getInstance();

    locale loc;
    string str = "ABALEARIA";
    string nstr;
    for(int i = 0; i < str.length(); ++i){
        nstr += tolower(str[i], loc);
    }

    wordList->searchWord(nstr);

    /*
    Server server;
    server.run();*/
    return 0;
}