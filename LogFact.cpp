#include "LogicScheme.h"

size_t LogFact::NumGate = 0;
std::set<LogGateHand> LogFact::listGate[LOGS];

LogGateHand LogFact::NewGate(int type)
{
   NumGate++;
   LogGateHand hand;
   switch (type)
   {
   case NOT:
       hand = std::make_shared<LogGate_NOT>();
       break;
   case OR:
       hand = std::make_shared<LogGate_OR>();
       break;
   case AND:
       hand = std::make_shared<LogGate_AND>();
       break;
   case XOR:
       hand = std::make_shared<LogGate_XOR>();
       break;
   case NOR:
       hand = std::make_shared<LogGate_NOR>();
       break;
   case NAND:
       hand = std::make_shared<LogGate_NAND>();
       break;
   case XNOR:
       hand = std::make_shared<LogGate_XNOR>();
       break;
   case CIRC:
       hand = std::make_shared<LogCirc>();
       break;
   case FICT:
       hand = std::make_shared<LogGate_FICT>();
       break;
   }
   listGate[type].insert(hand);
   return hand;
}

void LogFact::del(LogGateHand &hand)
{
	if (hand == NULL) return;
	if (typeid(*hand) == typeid(LogGate_NOT)){
			listGate[NOT].erase(hand);
			NumGate--;
			hand = NULL;
	}
	else if (typeid(*hand) == typeid(LogGate_OR)){
		listGate[OR].erase(hand);
		NumGate--;
		hand = NULL;
	}
	else if (typeid(*hand) == typeid(LogGate_AND)){
		listGate[AND].erase(hand);
		NumGate--;
		hand = NULL;
	}
	else if (typeid(*hand) == typeid(LogGate_XOR)){
		listGate[XOR].erase(hand);
		NumGate--;
		hand = NULL;
	}
	else if (typeid(*hand) == typeid(LogGate_NOR)){
		listGate[NOR].erase(hand);
		NumGate--;
		hand = NULL;
	}
	else if (typeid(*hand) == typeid(LogGate_NAND)){
		listGate[NAND].erase(hand);
		NumGate--;
		hand = NULL;
	}
	else if (typeid(*hand) == typeid(LogGate_XNOR)){
		listGate[XNOR].erase(hand);
		NumGate--;
		hand = NULL;
	}
	else if (typeid(*hand) == typeid(LogCirc)){
		listGate[CIRC].erase(hand);
		NumGate--;
		hand = NULL;
	}
	else if (typeid(*hand) == typeid(LogGate_FICT)){
		listGate[FICT].erase(hand);
		NumGate--;
		hand = NULL;
	}
	hand = NULL;
}

int LogFact::getType(LogGateHand &hand)
{
	int result = 0;
	if 		(typeid(*hand) == typeid(LogGate_NOT))	{result = NOT;}
	else if (typeid(*hand) == typeid(LogGate_OR))	{result = OR; }
	else if (typeid(*hand) == typeid(LogGate_AND))	{result = AND;}
	else if (typeid(*hand) == typeid(LogGate_XOR))	{result = XOR;}
	else if (typeid(*hand) == typeid(LogGate_NOR))	{result = NOR;}
	else if (typeid(*hand) == typeid(LogGate_NAND))	{result = NAND;}
	else if (typeid(*hand) == typeid(LogGate_XNOR))	{result = XNOR;}
	else if (typeid(*hand) == typeid(LogCirc))		{result = CIRC;}
	else if (typeid(*hand) == typeid(LogGate_FICT))	{result = FICT; }
	return result;
}

std::string LogFact::getTypeString(LogGateHand &hand)
{
	std::string result;
	switch(getType(hand))
	{
	case(NOT):
			result = "NOT";
			break;
	case(OR):
			result = "OR";
			break;
	case(AND):
			result = "AND";
			break;
	case(XOR):
			result = "XOR";
			break;
	case(NOR):
			result = "NOR";
			break;
	case(NAND):
			result = "NAND";
			break;
	case(XNOR):
			result = "XNOR";
			break;
	case(CIRC):
			result = "CIRC";
			break;
	case(FICT):
			result = "FICT";
			break;
	}
	return result;
}

void LogFact::printType(LogGateHand &hand)
{
	if 		(typeid(*hand) == typeid(LogGate_NOT)) {std::cout << "Type: NOT"  << std::endl;}
	else if (typeid(*hand) == typeid(LogGate_OR))  {std::cout << "Type: OR"   << std::endl;}
	else if (typeid(*hand) == typeid(LogGate_AND)) {std::cout << "Type: AND"  << std::endl;}
	else if (typeid(*hand) == typeid(LogGate_XOR)) {std::cout << "Type: XOR"  << std::endl;}
	else if (typeid(*hand) == typeid(LogGate_NOR)) {std::cout << "Type: NOR"  << std::endl;}
	else if (typeid(*hand) == typeid(LogGate_NAND)){std::cout << "Type: NAND" << std::endl;}
	else if (typeid(*hand) == typeid(LogGate_XNOR)){std::cout << "Type: XNOR" << std::endl;}
	else if (typeid(*hand) == typeid(LogCirc))	   {std::cout << "Type: CIRC" << std::endl;}
	else if (typeid(*hand) == typeid(LogGate_FICT))	   {std::cout << "Type: FICT" << std::endl;}
}
