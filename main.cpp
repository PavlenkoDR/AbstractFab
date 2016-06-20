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
    LogGateHand summator, sheme;
    summator = LogFact::NewGate(CIRC);
    sheme = LogFact::NewGate(CIRC);
    LogCirc &temp = dynamic_cast<LogCirc&> (*summator);
    LogCirc &temp1 = dynamic_cast<LogCirc&> (*sheme);
    temp.addGate(FICT);//0
    temp.addGate(FICT);//1
    temp.addGate(FICT);//2
    temp.addGate(XOR); //3
    temp.addGate(XOR); //4
    temp.addGate(AND); //5
    temp.addGate(AND); //6
    temp.addGate(OR);  //7
    temp.bind(3, 4);
    temp.bind(2, 4);
    temp.bind(3, 6);
    temp.bind(2, 6);
    temp.bind(4, 5);
    temp.bind(1, 5);
    temp.bind(4, 7);
    temp.bind(1, 7);
    temp.bind(6, 8);
    temp.bind(7, 8);
    tmp.push_back(0);//Начальное смещение
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(0);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    tmp.push_back(1);
    temp1.addGate(summator);
    temp1.addGate(summator);
    temp1.addGate(summator);
    temp1.addGate(summator);
    temp1.addGate(summator);
    temp1.addGate(summator);
    temp1.addGate(summator);
    temp1.addGate(summator);
    //temp1.bind(1, 2);
    //temp1.bind(2, 3);
    temp1.bind(1, 2, 1, 2);
    temp1.bind(2, 3, 1, 2);
    temp1.bind(3, 4, 1, 2);
    temp1.bind(4, 5, 1, 2);
    temp1.bind(5, 6, 1, 2);
    temp1.bind(6, 7, 1, 2);
    temp1.bind(7, 8, 1, 2);
    temp1.run(tmp);
    temp1.PrintGraph("");
    cout << "Solve(" << temp1.numNextPort() << "): ";
    for (int i = 0; i < temp1.numNextPort(); i++)
    	cout << temp1.getNextVect()[i] << " ";
    cout << endl;
    std::cout << "Done!" << std::endl;
    return 0;
}
