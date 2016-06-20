#ifndef LOGICSCHEME_H_INCLUDED
#define LOGICSCHEME_H_INCLUDED

#include <memory>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <iostream>
#include <iterator>
#include <stdarg.h>

typedef std::vector<bool> LogVect;

const int NOT = 0;
const int OR = 1;
const int AND = 2;
const int XOR = 3;
const int NOR = 4;
const int NAND = 5;
const int XNOR = 6;
const int CIRC = 7;
const int FICT = 8;

const int LOGS = 9;

/***********************	LogGate		***************************/

class LogGate
{
protected:
	LogVect Last;
	LogVect Next;

public:
	inline 	void 	run (const LogVect &v) 			{if (v.size() != numLastPort()) throw 0; Last = v; run(); }
	virtual void 	run() = 0;

	inline long 	numLastPort() 					{ return Last.size(); }
	inline long 	numNextPort() 					{ return Next.size(); }
	inline void 	setLastSign(int i, bool v) 		{ Last[i] = v; }
	inline bool 	getLastSign(int i) 				{ return (i < Last.size())?Last[i]:0; }
	inline bool 	getNextSign(int i) 				{ return (i < Next.size())?Next[i]:0; }
	inline void 	setLastVect(const LogVect &v) 	{ Last = v; }
	inline LogVect 	getLastVect() 					{ return Last; }
	inline LogVect 	getNextVect() 					{ return Next; }

	virtual 		~LogGate(){}
					LogGate(){}
};


struct LogGate_NOT: public LogGate
{
    inline 		LogGate_NOT () 	{ Last.resize(1); Next.resize(1); }  //Ограничить количество входных сигналов до 1. Выходных до 1.
    inline void	run () 			{ Next[0] = !Last[0]; }
};

struct LogGate_FICT: public LogGate
{
    inline 		LogGate_FICT () 	{ Last.resize(1); Next.resize(1); }  //Ограничить количество входных сигналов до 1. Выходных до 1.
    inline void	run () 			{ Next[0] = Last[0]; }
};

struct LogGate_OR: public LogGate
{
    inline		LogGate_OR () 	{ Last.resize(2); Next.resize(1); }  //Ограничить количество входных сигналов до 2. Выходных до 1.
    inline void	run () 			{ Next[0] = Last[0] || Last[1]; }
};

struct LogGate_AND: public LogGate
{
    inline 		LogGate_AND () 	{ Last.resize(2); Next.resize(1); }  //Ограничить количество входных сигналов до 2. Выходных до 1.
    inline void	run () 			{ Next[0] = Last[0]&&Last[1]; }
};

struct LogGate_NOR: public LogGate
{
    inline 		LogGate_NOR () 	{ Last.resize(2); Next.resize(1); }  //Ограничить количество входных сигналов до 2. Выходных до 1.
    inline void	run () 			{ Next[0] = !(Last[0] || Last[1]); }
};

struct LogGate_NAND: public LogGate
{
    inline 		LogGate_NAND ()	{ Last.resize(2); Next.resize(1); }  //Ограничить количество входных сигналов до 2. Выходных до 1.
    inline void	run () 			{ Next[0] = !(Last[0] && Last[1]); }
};

struct LogGate_XOR: public LogGate
{
    inline 		LogGate_XOR () 	{ Last.resize(2); Next.resize(1); }  //Ограничить количество входных сигналов до 2. Выходных до 1.
    inline void	run ()
    {
	    if (Last[0]==Last[1])
            Next[0] = 0;
        else Next[0] = 1;
	}
};

struct LogGate_XNOR: public LogGate
{
    inline 		LogGate_XNOR ()	{ Last.resize(2); Next.resize(1); }  //Ограничить количество входных сигналов до 2. Выходных до 1.
    inline void	run ()
    {
	    if (Last[0]==Last[1])
            Next[0] = 1;
        else Next[0] = 0;
	}
};

typedef std::shared_ptr<LogGate> LogGateHand;

/***********************	LogFact		***************************/

class LogFact {
private:
	static size_t NumGate;
	static std::set<LogGateHand> listGate[LOGS];

	LogFact() {}
public:
	static LogGateHand NewGate(int type);
	static void del(LogGateHand &hand);
	static int getType(LogGateHand &hand);
	static std::string getTypeString(LogGateHand &hand);
	static void printType(LogGateHand &hand);
	static inline long   numGate(int t)	{ return listGate[t].size(); }
	static inline size_t numGate() 		{ return  NumGate; }
};

/***********************	LogCirc		***************************/

class LogCirc : public LogGate
{
	/*
	LogVect Last;
	LogVect Next;
	inline 	void 	run (const LogVect &v) 			{ if (v.size() != numLastPort()) return; Last = v; run(); }
	inline void 	setLastSign(int i, bool v) 		{ Last[i] = v; }
	inline bool 	getLastSign(int i) 				{ return Last[i]; }
	inline bool 	getNextSign(int i) 				{ return Next[i]; }
	inline void 	setLastVect(const LogVect &v) 	{ Last = v; }
	inline LogVect 	getLastVect() 					{ return Last; }
	inline LogVect 	getNextVect() 					{ return Next; }

	virtual 		~LogGate(){}
					LogGate(){}
	*/
	class Graph;
	typedef std::vector<Graph> t_vector;
	typedef std::map<t_vector::iterator, std::vector<int> > t_map;
	class Graph
	{
	private:
		friend class LogCirc;
		bool fool;
		LogGateHand hand;
		std::list<t_vector::iterator> back;
		t_map front;
		int sizefront();
		int sizeback();
		LogVect handLast;
		LogVect handNext;
		void printHandLast();
		LogVect run_rec();
		inline Graph(LogGateHand &h):hand(h){}
	};
	bool SearchCycles(t_vector::iterator);
	bool _SearchCycles(t_vector::iterator);
	t_vector LogVecLast;
	long numLastPortRefresh();
	long numNextPortRefresh();
	void clear();
public:
	void PrintGraph(std::string tabs);
    void run ();
	void run (const LogVect &v);
	inline void addGate(LogGateHand &h)
	{
		LogVecLast.push_back(Graph(h));
		numNextPortRefresh();
		numLastPortRefresh();
	}
	inline void addGate(int type)
	{
		LogGateHand tmp = LogFact::NewGate(type);
		LogVecLast.push_back(Graph(tmp));
		numNextPortRefresh();
		numLastPortRefresh();
	}
	void bind(int entrance, int exit);
	void bind(int entrance, int exit, int port, ...);
	void unbind(int entrance, int exit);
	void unbind(int entrance, int exit, int port, ...);
	void del(int entrance);
	inline long size(){return LogVecLast.size();}
};

typedef std::shared_ptr<LogCirc> LogCircHand;

#endif // LOGICSCHEME_H_INCLUDED
