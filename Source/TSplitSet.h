#ifndef __TSPLITSET_H#define __TSPLITSET_H#include "TChecks.h"#include "TFlags.h"#include "TSplit.h"#include "TDList.h"#include "TQuartet.h"#include "TCladistic.h"class TSplitSetIteratorConst;#if PRAGMA_MARK_SUPPORTED#pragma mark -#pragma mark ___ class TSplit ___#endifclass TSplitSet : public TCladistic{	friend class TSplitSetIteratorConst;	public:		enum		{			kEqualLeafSets 		= 0x0010,			kLeafSetsUpdated 	= 0x0020,			kSorted				= 0x0040		};				TSplitSet (const bool rooted = true);		TSplitSet (const TSplitSet& splitSet);		virtual ~TSplitSet (void);		virtual bool								AddSplit (TSplit* split, const bool nonRedundant = false);		virtual bool								AddSplit (const TSplit& split, const bool nonRedundant = false) { return (AddSplit ((TSplit*)split.Clone (), nonRedundant)); };			virtual ClassType							Class (void) const { return (kTSplitSetClass); };		virtual TObject*							Clone (void) const { return (new TSplitSet (*this)); };		virtual void								Copy (const TObject& obj);		virtual bool								CurSplit (void) const { return (fDList.CurItem ()); };		virtual bool								CurSplit (const TSplit*& split) const;		 		virtual void								DeleteAll (void);		virtual void								DeleteCurSplit (void);				virtual void								DetachCurSplit (TSplit*& split); 		virtual bool 								FindSplit (const TSplit& toFind) const { CHECK_ (IsRooted () ? toFind.IsRooted () : !toFind.IsRooted ()); return (fDList.FindItem (toFind)); };		virtual bool 								FindSplit (const TSplit& toFind, const TSplit*& split) const;		virtual bool								FirstSplit (void) const { return (fDList.FirstItem ()); };		virtual bool								FirstSplit (const TSplit*& split) const;		virtual HashValue 							Hash (void) const { return (fDList.Hash ()); };		virtual TSplitSetIteratorConst&				IteratorConst (void) const;								virtual bool								IsCompatible (const TSplit& split) const;		virtual bool								IsEmpty (void) const { return (fDList.IsEmpty ()); };		virtual bool								IsEqual (const TObject& obj) const;		virtual bool								IsEqualLeafSets (void) const { return (GetLeafSet (true) == GetLeafSet (false)); };		virtual bool								IsSplitRedundant (const TSplit& split) const;		virtual void								PruneLeaves (const TLeafSet& leafSet, const bool nonRedundant = false);				virtual bool								IsSorted (void) const { return (IsFlag (kSorted)); };		virtual bool								LastSplit (void) const { return (fDList.LastItem ()); };		virtual bool								LastSplit (const TSplit*& split) const;		virtual const TLeafSet&						GetLeafSet (void) const { return (GetLeafSet (false)); };		virtual const TLeafSet&						GetLeafSet (const bool intersection) const;		virtual unsigned int							GetLeaves (void) const { return (GetLeaves (false)); };		virtual unsigned int							GetLeaves (const bool intersection) const { return (GetLeafSet (intersection).GetLeaves ()); };		virtual bool								NextSplit (void) const { return (fDList.NextItem ()); };		virtual bool								NextSplit (const TSplit*& split) const;		virtual TSplitSet&							operator = (const TSplitSet& splitSet);				virtual void								Sort (void) const;						virtual unsigned int							GetSplits (void) const { return (fDList.GetItems ()); };		virtual ostream& 							Write (ostream& o) const { return (WriteAsNewick (o)); };		virtual ostream& 							WriteAsNewick (ostream& o) const;		virtual void	 							WriteToLogAsTable (const float limit, const bool weight) const;		virtual void	 							WriteToLogAsTable (const TLeafSet& leafSet, const float limit, const bool weight) const;		virtual ostream& 							WriteAsTable (ostream& o, const float limit, const bool weight) const;		virtual ostream& 							WriteAsTable (ostream &o, const TLeafSet& leafSet, const float limit, const bool weight) const;	protected:		virtual void								upDateLeafSets (void) const;		virtual ostream& 							writeBorder (ostream& o, const unsigned int leaves) const;		virtual ostream& 							writeLeafNumbers (ostream& o, const unsigned int leaves) const;		TLeafSet									fIntersection;		TLeafSet									fUnion;		TDList										fDList;};#if PRAGMA_MARK_SUPPORTED#pragma mark -#pragma mark ___ class TSplitSetIteratorConst ___#endifclass TSplitSetIteratorConst{	friend class TSplitSet;	public:	    TSplitSetIteratorConst (const TSplitSet& splitSet);	    TSplitSetIteratorConst (const TSplitSetIteratorConst& splitSetIteratorConst);	    virtual ~TSplitSetIteratorConst (void);		virtual bool							CurSplit (void) const { return (fDListIteratorConst.CurItem ()); };		virtual bool							CurSplit (const TSplit*& split) const;		virtual bool							FirstSplit (void) { return (fDListIteratorConst.FirstItem ()); };		virtual bool							FirstSplit (const TSplit*& split);		virtual bool 							IsReversible (void) const { return (fDListIteratorConst.IsReversible ()); };		virtual bool							LastSplit (void) { return (fDListIteratorConst.LastItem ()); };		virtual bool							LastSplit (const TSplit*& split);				virtual bool							NextSplit (void) { return (fDListIteratorConst.NextItem ()); };		virtual bool							NextSplit (const TSplit*& split);				virtual bool							PrevSplit (void) { return (fDListIteratorConst.PrevItem ()); };		virtual bool							PrevSplit (const TSplit*& split);	protected:		const TSplitSet&						fSplitSet;	    TDListIteratorConst						fDListIteratorConst;};#if PRAGMA_MARK_SUPPORTED#pragma mark -#endifinlineTSplitSetIteratorConst& TSplitSet::IteratorConst (void) const{	return (*(new TSplitSetIteratorConst (*this)));}#if PRAGMA_MARK_SUPPORTED#pragma mark -#endif#endif // __TSPLITSET_H