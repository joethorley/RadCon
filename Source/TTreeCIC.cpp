#include "TTreeCIC.h"extern BOOL gAborted;void TTreeCIC::AddTree (const TTree& tree){	CHECK_ (tree.GetTreeType () == kStrictCladistic || tree.GetTreeType () == kStrictNestings);	CHECK_ (IsRooted () == tree.IsRooted ());		fLeafSet.AddToThis (tree.GetLeafSet ());	fTrees.AddItem (tree);	fCICs.AddItem (0);}void TTreeCIC::CalcCICs (const bool combined) const{	CHECK_ (!combined);	CHECK_ ((3 < GetLeaves ()) || (IsRooted () && 3 == GetLeaves ()));	CHECK_ (!fTrees.IsEmpty ());	CHECK_ (fTrees.GetItems () == 1);		const TTree& tree = (const TTree&)fTrees[0];	if (((const TTree&)fTrees[0]).GetTreeType () == kStrictCladistic)		((TTreeCIC*)this)->fCICs[0] = tree.GetCIC ();	else if (((const TTree&)fTrees[0]).GetTreeType () == kStrictNestings)	{	//		WatchCursor ();		((TTreeCIC*)this)->fBranchAndBound = new TBranchAndBound (((const TTree&)fTrees[0]).GetLeafSet (), IsRooted ());				((TTreeCIC*)this)->fPermitted = 0;		do 		{			bool permitted = true;			while (permitted && fBranchAndBound->AddNextLeaf ())			{				if (!((const TTree&)fTrees[0]).IsAdamsResolution (fBranchAndBound->Tree ()))					permitted = false;			}			if (permitted)				((TTreeCIC*)this)->fPermitted += 1;		} while (fBranchAndBound->NextBranch () && !gAborted);				delete (fBranchAndBound);				CHECK_ (isfinite (fPermitted));				if (!gAborted)			((TTreeCIC*)this)->fCICs[0] = calcCIC (fPermitted, calcB (((const TTree&)fTrees[0]).GetLeaves ()));		//		ArrowCursor ();	}	else		CHECK_ (0);}TTreeCIC::TTreeCIC (const bool rooted) 	: fCICs (1){	fRooted = rooted;		fBranchAndBound = NULL; }ostream& TTreeCIC::WriteCICs (ostream& dummy) const { 	*Log << EOLN;	((const TTree&)fTrees[0]).WriteToLog ();	*Log << EOLN;	*Log << fCICs[0] << EOLN;	return (dummy); }