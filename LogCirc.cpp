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
	t_vector::iterator tmpfirst;
	std::vector<int> tmpsecond;
	if ((front.size() != 0)&&(!fool))
		for (t_map::iterator i = front.begin(); i != front.end(); i++)
		{
			tmpfirst = (*i).first;
			tmp =  (*tmpfirst).run_rec();
			tmpsecond = (*i).second;
			if (tmpsecond.size() == 0)
				handLast.insert(handLast.end(), tmp.begin(), tmp.end());
			else
				for (std::vector<int>::iterator j = tmpsecond.begin(); j < tmpsecond.end(); j++)
				{
					handLast.push_back(tmp[*j]);
				}
		}
	fool = true;
	if (LogFact::getType(hand) == CIRC)
		dynamic_cast<LogCirc&> (*hand).run(handLast);
	else
		(*hand).run(handLast);
	handNext = (*hand).getNextVect();
	return handNext;
}

int LogCirc::Graph::sizefront()
{
	t_vector::iterator tmpfirst;
	LogGateHand tmphand;
	std::vector<int> tmpsecond;
	int k = 0;
	for (t_map::iterator i = front.begin(); i != front.end(); i++)
	{
		tmpfirst = (*i).first;
		tmpsecond = (*i).second;
		tmphand = (*tmpfirst).hand;
		//std::cout << "Size front: " << LogFact::getTypeString(tmphand) << ": " << (*tmphand).numNextPort() << std::endl;
		if (tmpsecond.size() == 0)
			k+= (*tmphand).numNextPort();
		else
			k+= tmpsecond.size();
	}
	return k;
}

void LogCirc::PrintGraph(std::string tabs)
{
	int k = 0;
	LogGateHand tmp;
	t_vector::iterator tmpfirst;
	std::vector<int> tmpsecond;
	for (t_vector::iterator i = LogVecLast.begin(); i < LogVecLast.end(); i++)
	{
		tmp = (*i).hand;
		int type = LogFact::getType(tmp);
		std::cout << tabs;
		std::cout << k << ": " << LogFact::getTypeString(tmp) << std::endl;
		std::cout << "\tHandLast: ";
		for (LogVect::iterator j = (*i).handLast.begin(); j < (*i).handLast.end(); j++)
			std::cout << (*j) << " ";
		std::cout << std::endl;
		std::cout << tabs;
		std::cout << "\tFront   : ";
		std::cout << std::endl;
		std::cout << tabs;
		for (t_map::iterator j = (*i).front.begin(); j != (*i).front.end(); j++)
		{
			tmpfirst = (*j).first;
			tmpsecond = (*j).second;
			tmp = (*tmpfirst).hand;
			std::cout << "\t\t" << LogFact::getTypeString(tmp) << ": ";
			if (tmpsecond.size() == 0)
				for (LogVect::iterator m = (*i).handNext.begin(); m < (*i).handNext.end(); m++)
					std::cout << (*m) << " ";
			else
				if ((*i).handNext.size() != 0)
					for (std::vector<int>::iterator m = tmpsecond.begin(); m < tmpsecond.end(); m++)
						std::cout << (*i).handNext[*m] << " ";
			std::cout << std::endl;
			std::cout << tabs;

		}
		std::cout << "\tHandNext: ";
		tmp = (*i).hand;
		for (LogVect::iterator j = (*i).handNext.begin(); j < (*i).handNext.end(); j++)
			std::cout << (*j) << " ";
		std::cout << std::endl;
		std::cout << tabs;
		std::cout << "\tBack    : ";
		for (std::list<t_vector::iterator>::iterator j = (*i).back.begin(); j != (*i).back.end(); j++)
		{
			tmp = (**j).hand;
			std::cout << LogFact::getTypeString(tmp) << " ";
		}
		std::cout << std::endl;
		k++;
		if (type == CIRC)
		{
			std::cout << tabs << "\{" << std::endl;
			dynamic_cast<LogCirc&> (*tmp).PrintGraph(tabs + "\t");
			std::cout << tabs << "\}" << std::endl;
		}
	}
}

long LogCirc::numLastPortRefresh()
{
	int k = 0;
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
	{
    		LogGateHand tmp = (*i).hand;
    		//std::cout << "!" << LogVecLast.size() << ": " << (*tmp).numLastPort() << " " << (*i).sizefront() << std::endl;
			k += (*tmp).numLastPort() - (*i).sizefront();
	}
	//std::cout << "!!!: " << k << std::endl;
	Last.resize(k);
	return k;
}


long LogCirc::numNextPortRefresh()
{
	int k = 0;
	t_vector::iterator tmpfirst;
	LogGateHand tmphand;
	t_map::iterator tmpmap;
	std::vector<int> tmpsecond;
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
	{
    		if ((*i).back.size() == 0)
    		{
    			tmphand = (*i).hand;
    			k += (*tmphand).numNextPort();
    		}
    		else
    		{
    			int closed_ports = 0;
    			tmphand = (*i).hand;
    			int nextSize = (*tmphand).numNextPort();
    			int viz[nextSize];
    			for (int j = 0; j < nextSize; j++)
    				viz[j] = 0;
    			for (std::list<t_vector::iterator>::iterator j = (*i).back.begin(); j != (*i).back.end(); j++)
    			{
    				tmpmap = (**j).front.find(i);
    				if ((*tmpmap).second.size() == 0)
    				{
    					tmpfirst = (*tmpmap).first;
    					tmphand = (*tmpfirst).hand;
    					closed_ports = (*tmphand).numNextPort();
    					break;
    				}
    				else
    				{
    					for (std::vector<int>::iterator m = (*tmpmap).second.begin(); m != (*tmpmap).second.end(); m++)
    					{
    						viz[*m] = 1;
    					}
    				}
    			}
    			if (closed_ports != (*tmphand).numNextPort())
    			{
    				for (int j = 0; j < nextSize; j++)
    					closed_ports+= viz[j];
    			}
    			k+=(*tmphand).numNextPort() - closed_ports;
    		}
	}
	Next.resize(k);
	return k;
}

void LogCirc::clear()
{
	int k = 0;
	Next.clear();
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
	{
		(*i).handLast.clear();
		(*i).handNext.clear();
		(*i).fool = false;
		LogGateHand tmp = (*i).hand;
		t_vector::iterator tmpfirst;
		LogGateHand tmphand;
		int size = 0;
		for (int j = 0; j < (*tmp).numLastPort() - (*i).sizefront(); j++)
		{
			if (k < Last.size())
			{
				(*i).handLast.push_back(Last[k]);
				k++;
			}
			else return;
		}
	}
	if (k != Last.size()) std::cout << "Not plased all ports!" << std::endl;
}

void LogCirc::run()
{
	t_vector::iterator i;
	try{
		for (i = LogVecLast.begin(); i != LogVecLast.end(); i++)
		{
			(*i).run_rec();
		}
	}
	catch (int e) {
		switch(e)
		{
		case 0:
			std::cout << LogFact::getTypeString((*i).hand) << " not runed. handLast.size() != hand.numLastPort()" << std::endl;
			break;
		}
		return;
	}
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
		(*i).fool = false;
	t_vector::iterator tmpfirst;
	LogGateHand tmphand;
	t_map::iterator tmpmap;
	std::vector<int> tmpsecond;
	int k = 0;
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
	{
		tmphand = (*i).hand;
		if ((*i).back.size() == 0)
		{
    		for (int j = 0; j < (*i).handNext.size(); j++)
    		{
    			Next.push_back((*i).handNext[j]);
    		}
		}
		else
		{
			int closed_ports = 0;
			tmphand = (*i).hand;
			int nextSize = (*tmphand).numNextPort();
			int viz[nextSize];
			for (int j = 0; j < nextSize; j++)
				viz[j] = 0;
			for (std::list<t_vector::iterator>::iterator j = (*i).back.begin(); j != (*i).back.end(); j++)
			{
				tmpmap = (**j).front.find(i);
				if ((*tmpmap).second.size() == 0)
				{
					tmpfirst = (*tmpmap).first;
					tmphand = (*tmpfirst).hand;
					closed_ports = (*tmphand).numNextPort();
					break;
				}
				else
				{
					for (std::vector<int>::iterator m = (*tmpmap).second.begin(); m != (*tmpmap).second.end(); m++)
					{
						viz[*m] = 1;
					}
				}
			}
			if (closed_ports != (*tmphand).numNextPort())
			{
				for (int j = 0; j < nextSize; j++)
					if (viz[j] == 0)
						Next.push_back((*i).handNext[j]);
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

bool LogCirc::_SearchCycles(t_vector::iterator entrance)
{
	if ((*entrance).fool) return true;
	(*entrance).fool = true;
	if ((*entrance).back.size() != 0)
		for (std::list<t_vector::iterator>::iterator i = (*entrance).back.begin(); i != (*entrance).back.end(); i++)
			if (_SearchCycles(*i)) return true;
	return false;
}

bool LogCirc::SearchCycles(t_vector::iterator entrance)
{
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
		(*i).fool = false;
	bool result = _SearchCycles(entrance);
	for (t_vector::iterator i = LogVecLast.begin(); i != LogVecLast.end(); i++)
		(*i).fool = false;
	return result;
}

void LogCirc::bind(int entrance, int exit)
{
	entrance--;
	exit--;
	if ((entrance >= LogVecLast.size())||(exit >= LogVecLast.size()))
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. entrance or exit >= sheme size" << std::endl;
		return;
	}
	if ((entrance < 0)||(exit < 0))
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. entrance or exit <= 0" << std::endl;
		return;
	}
	LogGateHand tmp = LogVecLast[exit].hand;
	t_map::iterator tmpmap = LogVecLast[exit].front.find(LogVecLast.begin()+entrance);
	if (tmpmap != LogVecLast[exit].front.end())
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. connection is already bind" << std::endl;
		return;
	}
	if ((*tmp).numLastPort() <= LogVecLast[exit].front.size())
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. full ports" << std::endl;
		return;
	}
	LogVecLast[entrance].back.push_back(LogVecLast.begin()+exit);
	LogVecLast[exit].front.insert(std::make_pair(LogVecLast.begin()+entrance, std::vector<int>()));
	if (SearchCycles(LogVecLast.begin() + exit))
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. create cycles" << std::endl;
		unbind(entrance + 1, exit + 1);
		return;
	}
	numNextPortRefresh();
	numLastPortRefresh();
	std::cout << "Elements binded" << std::endl;
}


void LogCirc::bind(int entrance, int exit, int ports_count, ...)
{
	entrance--;
	exit--;
	if ((entrance >= LogVecLast.size())&&(exit >= LogVecLast.size()))
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. entrance or exit >= sheme size" << std::endl;
		return;
	}
	if ((entrance <= 0)&&(exit <= 0))
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. entrance or exit <= 0" << std::endl;
		return;
	}
	t_map::iterator tmpmap = LogVecLast[exit].front.find(LogVecLast.begin()+entrance);
	if (tmpmap == LogVecLast[exit].front.end())
	{
		bind(entrance + 1, exit + 1);
		tmpmap = LogVecLast[exit].front.find(LogVecLast.begin()+entrance);
	}
	LogGateHand tmp = LogVecLast[exit].hand;
	if ((*tmp).numLastPort() <= LogVecLast[exit].front.size())
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. full ports" << std::endl;
		return;
	}
	if ((*tmp).numLastPort() <= ports_count)
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. ports count >= sheme size" << std::endl;
		return;
	}
	va_list ap; //Указатель на список параметров
	va_start(ap,ports_count); //Настроились на список параметров
	int candidat = -1;
	bool port_finded = false;
	if (LogFact::getType(tmp) == CIRC) dynamic_cast<LogCirc&> (*tmp).numNextPortRefresh();
	for (int i = 0; i < ports_count; i++)
	{
		candidat = va_arg(ap,int);
		if ((candidat <= 0)||(candidat >= (*tmp).numLastPort()))
		{
			std::cout << entrance + 1 << " and " << exit + 1 << " not bind in port " << candidat << ". invalid candidat" << std::endl;
			continue;
		}
		candidat--;
		port_finded = false;
		for (auto j = (*tmpmap).second.begin(); j != (*tmpmap).second.end(); j++)
		{
			if (*j == candidat)
			{
				port_finded = true;
				break;
			}
		}
		if (port_finded)
		{
			std::cout << entrance + 1 << " and " << exit + 1 << " not bind in port " << candidat << ". connection is already bind" << std::endl;
			continue;
		}
		(*tmpmap).second.push_back(candidat);
		if (SearchCycles(LogVecLast.begin() + exit))
		{
			std::cout << entrance + 1 << " and " << exit + 1 << " not bind in port. " << candidat << "create cycles" << std::endl;
			unbind(entrance + 1, exit + 1, 1, candidat);
		}
	}
	numNextPortRefresh();
	numLastPortRefresh();
	va_end(ap); //Завершаем работу с макрокомандами
	std::cout << "Ports binded" << std::endl;
}

void LogCirc::unbind(int entrance, int exit)
{
	entrance--;
	exit--;
	if ((entrance >= LogVecLast.size())||(exit >= LogVecLast.size()))
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. entrance or exit >= sheme size" << std::endl;
		return;
	}
	if ((entrance < 0)||(exit < 0))
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not bind. entrance or exit <= 0" << std::endl;
		return;
	}
	LogGateHand tmp = LogVecLast[exit].hand;
	if (LogVecLast[exit].front.size() == 0)
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not unbind. empty ports" << std::endl;
		return;
	}
	t_map::iterator tmpmap = LogVecLast[exit].front.find(LogVecLast.begin()+entrance);
	if (tmpmap == LogVecLast[exit].front.end())
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not unbind. connection is already unbind" << std::endl;
		return;
	}
	LogVecLast[entrance].back.remove(LogVecLast.begin()+exit);
	LogVecLast[exit].front.erase(LogVecLast.begin()+entrance);
	numLastPortRefresh();
	numNextPortRefresh();
	std::cout << "Elements unbinded" << std::endl;
}

void LogCirc::unbind(int entrance, int exit, int ports_count, ...)
{
	entrance--;
	exit--;
	if ((entrance >= LogVecLast.size())&&(exit >= LogVecLast.size()))
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not unbind. entrance or exit >= sheme size" << std::endl;
		return;
	}
	if ((entrance <= 0)&&(exit <= 0))
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not unbind. entrance or exit <= 0" << std::endl;
		return;
	}
	t_map::iterator tmpmap = LogVecLast[exit].front.find(LogVecLast.begin()+entrance);
	if (tmpmap == LogVecLast[exit].front.end())
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " elements is already unbinded" << std::endl;
		return;
	}
	if (LogVecLast[exit].front.size() == 0)
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not unbind. empty ports" << std::endl;
		return;
	}
	LogGateHand tmp = LogVecLast[exit].hand;
	if ((*tmp).numLastPort() <= ports_count)
	{
		std::cout << entrance + 1 << " and " << exit + 1 << " not unbind. ports count >= sheme size" << std::endl;
		return;
	}
	va_list ap; //Указатель на список параметров
	va_start(ap,ports_count); //Настроились на список параметров
	int candidat = -1;
	bool port_finded = false;
	if (LogFact::getType(tmp) == CIRC) dynamic_cast<LogCirc&> (*tmp).numNextPortRefresh();
	for (int i = 0; i < ports_count; i++)
	{
		candidat = va_arg(ap,int);
		if ((candidat <= 0)||(candidat >= (*tmp).numLastPort()))
		{
			std::cout << entrance + 1 << " and " << exit + 1 << " not bind in port " << candidat << ". invalid candidat" << std::endl;
			continue;
		}
		candidat--;
		port_finded = false;
		for (auto j = (*tmpmap).second.begin(); j != (*tmpmap).second.end(); j++)
		{
			if (*j == candidat)
			{
				port_finded = true;
				break;
			}
		}
		if (!port_finded)
		{
			std::cout << entrance + 1 << " and " << exit + 1 << " not unbind in port " << candidat << ". connection is already unbind" << std::endl;
			continue;
		}
		(*tmpmap).second.erase((*tmpmap).second.begin()+candidat);
	}
	numNextPortRefresh();
	numLastPortRefresh();
	va_end(ap); //Завершаем работу с макрокомандами
	LogVecLast[entrance].back.remove(LogVecLast.begin()+exit);
	LogVecLast[exit].front.erase(LogVecLast.begin()+entrance);
	numLastPortRefresh();
	numNextPortRefresh();
	std::cout << "Ports unbinded" << std::endl;
}

void LogCirc::del(int entrance)
{
	entrance--;
	if (entrance >= LogVecLast.size())
	{
		std::cout << entrance + 1 << " not bind. entrance >= sheme size" << std::endl;
		return;
	}
	if (entrance < 0)
	{
		std::cout << entrance + 1 << " not bind. entrance <= 0" << std::endl;
		return;
	}
	for (std::list<t_vector::iterator>::iterator i = LogVecLast[entrance].back.begin(); i != LogVecLast[entrance].back.end(); i++)
		(**i).front.erase(LogVecLast.begin()+entrance);
	t_vector::iterator tmpp;
	for (std::map<t_vector::iterator, std::vector<int> >::iterator i = LogVecLast[entrance].front.begin(); i != LogVecLast[entrance].front.end(); i++)
	{
		tmpp = (*i).first;
		(*tmpp).back.remove(LogVecLast.begin()+entrance);
	}
	LogVecLast.erase(LogVecLast.begin() + entrance);
	numLastPortRefresh();
	numNextPortRefresh();
	std::cout << "Element deleted" << std::endl;
}
