
#include "Server/Server.h"
#include "Logic/Player.h"

int main()
{
    Player* p1 = new Player("Jose");
    p1->setMessage("HOLA",1,1,1,4);
    p1->toString();
    string json = p1->serialize();
    cout<<json<<endl;
    Player* p2 = p1->deserealize(json.c_str());
    p2->toString();

    Server server;
    server.run();
    return 0;
}