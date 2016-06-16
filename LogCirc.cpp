#include "LogicScheme.h"

void LogCirc::Graph::printHandLast()
{
	for (LogVect::iterator i = handLast.begin(); i < handLast.end(); i++)
		std::cout << (*i) << " ";
	std::cout << std::endl;
}

LogVect LogCirc::Graph::run_rec()
{
	LogVect tmp;
	if ((front.size() != 0)&&(handLast.size() == 0))
		for (std::list<t_vector::iterator>::iterator i = front.begin(); i != front.end(); i++)
		{
			tmp =  (**i).run_rec();
			handLast.insert(handLast.end(), tmp.begin(), tmp.end());
		}
	(*hand).run(handLast);
	/*
	for (LogVect::iterator j = (*hand).getLastVect().begin(); j < (*hand).getLastVect().end(); j++)
		std::cout << (*j) << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::copy(handLast.begin(), handLast.end(), std::ostream_iterator<bool>(std::cout," "));
	std::cout << std::endl;
	std::cout << "==========" << std::endl;
	*/
	return (*hand).getNextVect();
}

void LogCirc::PrintGraph()
{
	int k = 0;
	LogGateHand tmp;
	for (t_vector::iterator i = LogVecLast.begin(); i < LogVecLast.end(); i++)
	{
		tmp = (*i).hand;
		std::cout << k << ": " << LogFact::getTypeString(tmp) << std::endl;
		std::cout << "\tHandLast: ";
		for (int j = 0; j < (*tmp).numLastPort(); j++)
			std::cout << (*tmp).getLastVect()[j] << " ";
		std::cout << " | ";
		for (LogVect::iterator j = (*i).handLast.begin(); j < (*i).handLast.end(); j++)
			std::cout << (*j) << " ";
		std::cout << std::endl;
		std::cout << "\tFront   : ";
		for (std::list<t_vector::iterator>::iterator j = (*i).front.begin(); j != (*i).front.end(); j++)
		{
			tmp = (**j).hand;
			std::cout << LogFact::getTypeString(tmp) << "(" << (*tmp).getNextVect()[0] << ") ";

		}
		std::cout << std::endl;
		std::cout << "\tHandNext: ";
		tmp = (*i).hand;
		std::cout << (*tmp).getNextVect()[0] << std::endl;
		std::cout << "\tBack    : ";
		for (std::list<t_vector::iterator>::iterator j = (*i).back.begin(); j != (*i).back.end(); j++)
		{
			tmp = (**j).hand;
			std::cout << LogFact::getTypeString(tmp) << " ";
		}
		std::cout << std::endl;
		k++;
	}
}

long LogCirc::numLastPort()
{
	int k = 0;
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
	{
    		LogGateHand tmp = (*i).hand;
			k += (*tmp).numLastPort() - (*i).front.size();
	}
	Last.resize(k);
	return k;
}

long LogCirc::numNextPort()
{
	int k = 0;
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
	{
    		LogGateHand tmp = (*i).hand;
    		if ((*i).back.size() == 0)
    			k += (*tmp).numNextPort();
	}
	Next.resize(k);
	return k;
}

void LogCirc::clear()
{
	int k = 0;
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
	{
		(*i).handLast.clear();
		LogGateHand tmp = (*i).hand;
		if ((*tmp).numLastPort() > (*i).front.size())
		{
			for (int j = 0; j < (*tmp).numLastPort() - (*i).front.size(); j++)
			{
				if (k < Last.size())
				{
					(*i).handLast.push_back(Last[k]);
    				k++;
				}
				else return;
			}
		}
	}
	Next.clear();
}

void LogCirc::run()
{
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
	{
		(*i).run_rec();
	}
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
	{
		LogGateHand tmp = (*i).hand;
		if ((*i).back.size() == 0)
		{
    		for (int j = 0; j < (*tmp).numNextPort(); j++)
    		{
    			Next.push_back((*tmp).getNextVect()[j]);
    		}
		}
	}
}

void LogCirc::run(const LogVect &v) {
	int k = numLastPort();
	//std::cout << "Last.size: " <<  Last.size() << std::endl;
	if (v.size() != numLastPort())
	{
		std::cout << "inVecSize(" << v.size() << ") != LastVecSize(" << k << ")"<< std::endl;
		return;
	}
	Last = v;
	clear();
	run();
}

void LogCirc::bind(int entrance, int exit)
{
	LogGateHand tmp = LogVecLast[exit].hand;
	if ((entrance < LogVecLast.size())&&(exit < LogVecLast.size()))
	if ((*tmp).numLastPort() > LogVecLast[exit].front.size())
	{
		LogVecLast[entrance].back.push_back(LogVecLast.begin()+exit);
		LogVecLast[exit].front.push_back(LogVecLast.begin()+entrance);
	}
	else
		std::cout << entrance << " and " << exit << " not bind" << std::endl;
	else
		std::cout << entrance << " and " << exit << " not bind" << std::endl;
}

void LogCirc::unbind(int entrance, int exit)
{
	LogGateHand tmp = LogVecLast[exit].hand;
	if ((entrance < LogVecLast.size())&&(exit < LogVecLast.size()))
	{
		LogVecLast[entrance].back.remove(LogVecLast.begin()+exit);
		LogVecLast[exit].front.remove(LogVecLast.begin()+entrance);
	}
	else
		std::cout << entrance << " and " << exit << " not bind" << std::endl;
}

void LogCirc::del(int entrance)
{
	for (std::list<t_vector::iterator>::iterator i = LogVecLast[entrance].back.begin(); i != LogVecLast[entrance].back.end(); i++)
		(**i).front.remove(LogVecLast.begin()+entrance);
	for (std::list<t_vector::iterator>::iterator i = LogVecLast[entrance].front.begin(); i != LogVecLast[entrance].front.end(); i++)
		(**i).back.remove(LogVecLast.begin()+entrance);
	LogVecLast.erase(LogVecLast.begin() + entrance);
}
