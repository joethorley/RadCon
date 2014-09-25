#include "TCluster.h"#include "TCalc.h"// JLT 000624#include "wstream.h"extern ostream *logStream;void TCluster::Copy (const TObject& obj){	CHECK (Class () == obj.Class ());		TLeafSet::Copy (obj);	const TCluster& cluster = (const TCluster&)obj;	fWeight = cluster.fWeight;}TCluster& TCluster::operator = (const TCluster& cluster){	TLeafSet::operator = (cluster);	fWeight = cluster.fWeight;		return (*this);}ostream& TCluster::Write (ostream& o, const bool writeWeight) const{	TLeafSet::Write (o);	if (writeWeight)		o << ' ' << fWeight;	return (o);}ostream& TCluster::WriteAsStar (ostream &o, const unsigned int leaves, const bool writeWeight, const bool bordered) const{	TLeafSet leafSet (leaves);	return (WriteAsStar (o, leafSet, writeWeight, bordered));}ostream& TCluster::WriteAsStar (ostream &o, const TLeafSet& leafSet, const bool writeWeight, const bool bordered) const{	if (bordered)	{		writeLeafNumbers (o, leafSet.GetLeaves ());		o << EOLN;		writeBorder (o, leafSet.GetLeaves ());		o << EOLN;	}			unsigned int n = 0;	while (leafSet.IthLeaf (++n))	{		if (IsLeaf (n))			o <<'*';		else 			o <<'.';					if (!(n % 5))      		o << " ";	}	if (writeWeight)		o << ' ' << fWeight;	if (bordered)	{		o << EOLN;		writeBorder (o, leafSet.GetLeaves ());	}	return (o);}void TCluster::WriteToLogAsStar (const TLeafSet& leafSet, const bool writeWeights, const bool bordered) const{// JLT 000624	#ifdef VCLASS 		WriteAsStar (*logStream, leafSet, writeWeights, bordered);		logStream->flush();	#else		Write (cout, name);	#endif}ostream& TCluster::writeBorder (ostream& o, const unsigned int leaves){//	o << "-----";	for (unsigned int i = 1; i <= leaves; ++i)	{		if (i % 5)      		o << "-";      	else      		o << "- ";	}	return (o);}ostream& TCluster::writeLeafNumbers (ostream& o, const unsigned int leaves){	if (100 <= leaves)	{//		o << "     ";		TString string;		for (unsigned int i = 1; i <= leaves; ++i)		{					if (GetUnits (i, 3) != -1)			{				string.AddToThis (GetUnits (i, 3));			}			else				string.AddToThis (' ');			if (!(i % 5))				string.AddToThis (' ');					}		o << string;		o << EOLN;	}	if (10 <= leaves)	{//		o << "     ";		TString string;		for (unsigned int i = 1; i <= leaves; ++i)		{					if (GetUnits (i, 2) != -1)			{				string.AddToThis (GetUnits (i, 2));			}			else				string.AddToThis (' ');			if (!(i % 5))				string.AddToThis (' ');			}		o << string;		o << EOLN;	}//	o << "     ";	TString string;	for (unsigned int i = 1; i <= leaves; ++i)	{				string.AddToThis (GetUnits (i, 1));		if (!(i % 5))			string.AddToThis (' ');				}	o << string;	return (o);	}