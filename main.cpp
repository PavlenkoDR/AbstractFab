#include "LogicScheme.h"

#include <iostream>

using namespace std;

int main()
{
    LogGateHand h1 = LogFact::NewGate(AND);
    LogGateHand h2 = LogFact::NewGate(OR);
    LogGateHand h3 = LogFact::NewGate(NOT);
    LogCirc sheme;
    sheme.addGate(AND); //0
    sheme.addGate(OR);  //1
    sheme.addGate(NOT); //2
    sheme.addGate(OR);  //3
    sheme.addGate(AND); //4
    sheme.addGate(OR);  //5
    sheme.addGate(NOT); //6
    sheme.addGate(AND); //7
    sheme.addGate(OR);  //8
    sheme.addGate(NOT); //9
    //sheme.addGate(h2);
    std::cout << "Sheme size: " << sheme.size() << std::endl;
    LogVect tmp;
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(0);
    tmp.push_back(0);
    sheme.bind(0, 3);
    sheme.bind(1, 3);
    sheme.bind(1, 4);
    sheme.bind(1, 4);
    sheme.bind(1, 5);
    sheme.bind(2, 5);
    sheme.bind(3, 6);
    sheme.bind(4, 7);
    sheme.bind(5, 9);
    sheme.bind(9, 7);
    sheme.bind(6, 8);
    sheme.bind(7, 8);
    sheme.run(tmp);
    sheme.PrintGraph();

    LogCirc sheme2;
    sheme2.addGate(OR);    //8
    sheme2.addGate(NOT);   //9
    cout << "Solve(" << sheme.numNextPort() << "): ";
    for (int i = 0; i < sheme.numNextPort(); i++)
    	cout << sheme.getNextSign(0) << " ";
    cout << endl;
    std::cout << "Done!" << std::endl;
    return 0;
}
