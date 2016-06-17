#include "LogicScheme.h"

#include <iostream>

using namespace std;

int main()
{
    LogGateHand h1 = LogFact::NewGate(AND);
    LogGateHand h2 = LogFact::NewGate(OR);
    LogGateHand h3 = LogFact::NewGate(NOT);
    LogGateHand h4 = LogFact::NewGate(CIRC);
    LogVect tmp;
    //LogCirc *sheme = dynamic_cast<LogCirc *> (h4.get());//->get();
    /*
    LogCirc &sheme = dynamic_cast<LogCirc&> (*h4);
    sheme.addGate(FICT); //0
    sheme.addGate(FICT);  //1
    sheme.addGate(XOR); //2
    sheme.addGate(AND);  //3
    //sheme.addGate(h2);
    std::cout << "Sheme size: " << sheme.size() << std::endl;
    tmp.push_back(0);
    tmp.push_back(0);
    sheme.bind(0, 2);
    sheme.bind(1, 2);
    sheme.bind(0, 3);
    sheme.bind(1, 3);
    sheme.run(tmp);
    sheme.PrintGraph();
	*/
    //====================================================

    LogGateHand summator[8];
    for (int i = 0; i < 8; i++)
    	summator[i] = LogFact::NewGate(CIRC);
    LogCirc &temp = dynamic_cast<LogCirc&> (*summator[0]);
    temp.addGate(FICT);//0
    temp.addGate(FICT);//1
    temp.addGate(FICT);//2
    temp.addGate(XOR); //3
    temp.addGate(XOR); //4
    temp.addGate(AND); //5
    temp.addGate(AND); //6
    temp.addGate(OR);  //7
    temp.bind(0, 3);
    temp.bind(1, 3);
    temp.bind(0, 5);
    temp.bind(1, 5);
    temp.bind(3, 4);
    temp.bind(2, 4);
    temp.bind(3, 6);
    temp.bind(2, 6);
    temp.bind(5, 7);
    temp.bind(6, 7);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(0);
    temp.run(tmp);
    cout << "Solve(" << temp.numNextPort() << "): ";
    for (int i = 0; i < temp.numNextPort(); i++)
    	cout << temp.getNextVect()[i] << " ";
    cout << endl;
    std::cout << "Done!" << std::endl;
    return 0;
}
