#ifndef __TDEBUG_H#define __TDEBUG_H#include<stdio.h>#include<fstream.h>#include "TXception.h"#include "TChecks.h"#ifndef __DEBUG#define __DEBUG 0#endif // __DEBUG#if __DEBUGclass TDebug : public basic_ofstream<char>{	public:		TDebug (const char*);		~TDebug (void);};extern TDebug gDebug;#endif // __DEBUG#endif // __TDEBUG_H