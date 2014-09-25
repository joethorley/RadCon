// Straight translation of COMPONENT 2.0 code/*  A partition of a set S, say [1,.., 9] can be represented as  a vector P. E.g.,  [1..3] [4,5] [6] [7..9] = 123|45|6|789			1 2 3 4 5 6 7 8 9			-----------------	P =   1 1 1 2 2 3 4 4 4  Each element of the same subset has the  same value.  To get the partition product of two partitions we can  compare values in the vector.  For example. Given the partitions  12345 | 6789 and 123 | 456789  the first partition is		  1 2 3 4 5 6 7 8 9		  -----------------	P =  1 1 1 1 1 2 2 2 2	Going through the second partition, we use the	rule that if i in Sj (where Sj is the jth partition of S)	and P[i] = P[i-1] then in the partition product (PP),	i is in the same partition as i-1:		  1 2 3 4 5 6 7 8 9		  -----------------	P1=  1 1 1 1 1 2 2 2 2	PP=  1 1 1 2 2 3 3 3 3	so that PP (P1, P2) = 123 | 45 | 6789.	PartObj uses a [1..2,1..n] array to hold	two partitions, the last partition product (PP)	and the one presently being calculated.	With each new PP, the oldest partition is	overwritten.	If a column is not in the current set it has the value	"0", otherwise its value is the subset of the partition	to which it belongs.*/#if PRAGMA_MARK_SUPPORTED#pragma mark -#endif#include "TPartition.h"// Enter set s into the first row of the partition block. All i in S// will take the value "1"void TPartition::EnterSet (unsigned short leaves, const TLeafSet& leafSet){	CHECK_ (3 <= leaves && leaves <= kMaxLeaves);	CHECK_ (3 <= leafSet.GetLeaves () && leafSet.GetLeaves () <= leaves);	fParts = 0;	fCount = 1;	fLeaves = leaves;	fCurRow = &fArrayA;	fLastRow = &fArrayB;	fCurRow->Fill (0, fLeaves);	fLastRow->Fill (0, fLeaves);		fLeafSet = leafSet;		if (!fLeafSet.IsEmpty ())	{				fParts = 1;		unsigned short leaf;		for (fLeafSet.FirstLeaf (); (leaf = fLeafSet.CurLeaf ()) != 0; fLeafSet.NextLeaf ())		{			fCurRow->IthItemRef (leaf) = 1;			CHECK (leaf <= fLeaves);		}	}}// set up for next partition product by swapping the rowsvoid TPartition::Setup (void){	fParts = 0;	TArray<unsigned short>* temp = fLastRow;	((TPartition*)this)->fLastRow = fCurRow;	((TPartition*)this)->fCurRow  = temp;}// for each i in s, make the partiton product of s with the partition in fLastRow// and store it in fCurRowvoid TPartition::PP (TLeafSet leafSet){	leafSet.IntersectWithThis (fLeafSet);	while (!leafSet.IsEmpty ())	{		unsigned short leaf = leafSet.FirstLeaf ();		const unsigned short code = fLastRow->IthItemRef (leaf);		fCurRow->IthItemRef (leaf) = ++fParts;		leafSet.SubtractFromThis (leaf);		while (++leaf <= fLeaves)		{			if (leafSet.IsLeaf (leaf) && fLastRow->IthItemRef (leaf) == code)			{				fCurRow->IthItemRef (leaf) = fParts;				leafSet.SubtractFromThis (leaf);			}		}	}}// return the ithset of the partition productbool TPartition::IthPart (unsigned short i, TLeafSet& leafSet) const{	if (IthPart (i))	{			leafSet.SetEmpty ();		for (unsigned short leaf = 1; leaf <= fLeaves; ++leaf)			if (fCurRow->IthItemRef (leaf) == i)				leafSet.AddToThis (leaf);		return (true);	}	return (false);}TPartition::TPartition (void)	: fArrayA (kMaxLeaves)	, fArrayB (kMaxLeaves){	CHECK_ (kMaxLeaves <= UINT_MAX);		fCount = 1;	fParts = 0;	fLeaves = 0;	fCurRow = &fArrayA;	fLastRow = &fArrayB;		fCurRow->Fill (0, fLeaves);	fLastRow->Fill (0, fLeaves);}#if PRAGMA_MARK_SUPPORTED#pragma mark -#endif