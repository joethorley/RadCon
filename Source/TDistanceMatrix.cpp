#include "TDistanceMatrix.h"TDistanceMatrix::TDistanceMatrix (const unsigned int leaves)	: 	fLeafSet (leaves)	,	fMatrix (leaves)	, 	fMaxLeaves (leaves){	for (unsigned int i = 0; i < fMaxLeaves - 1; ++i)		fMatrix[i] = new TArray<unsigned int> ((fMaxLeaves - i) - 1);}TDistanceMatrix::TDistanceMatrix (const TLeafSet& leafSet)	: 	fLeafSet (leafSet)	,	fMatrix (leafSet.GetLeaves ())	, 	fMaxLeaves (leafSet.GetLeaves ()){	for (unsigned int i = 0; i < fMaxLeaves - 1; ++i)		fMatrix[i] = new TArray<unsigned int> ((fMaxLeaves - i) - 1);}TDistanceMatrix::~TDistanceMatrix (void){	for (unsigned int i = 0; i < fMaxLeaves - 1; ++i)		delete fMatrix[i];}