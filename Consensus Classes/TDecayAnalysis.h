#ifndef __TDECAYANALYSIS_H#define __TDECAYANALYSIS_H#include "TQuartetConsensus.h"#include "TReadFile.h"#include "TFuse.h"// this class writes to file (outputs) all the triplets and quartets for decay analysis// it also inputs them all from a PAUP file for LS(DI) and DDA// the limits are for rooted and unrooted trees with <1500 and <500 leaves, respectively// maximum value of unsigned long ULONG_MAX = 4294967295U// unrooted quartets containing a leaf = 499 * 498 * 497/ 6 = 20584249U// rooted quartets containing a leaf = 1499 * 1498 / 2 = 1122751U// but thse depend on the exact values of the decay indices for the quartets which have no upper limit!!// the number are if all quartets have decay indices of 1#if PRAGMA_MARK_SUPPORTED#pragma mark -#pragma mark ___ class TDecayAnalysis ___#endifclass TDecayAnalysis : public TQuartetConsensus{	public:		enum		{			kInput 		= 0x0010,			kTypeSet 	= 0x0020,			kHeuristic	= 0x0040,			kFuse		= 0x0080,			kAborted	= 0x0100 		};		TDecayAnalysis (const TSourceTreesFile* sourceTreesFile);		TDecayAnalysis (const TDecayAnalysis& decayAnalysis);		virtual ~TDecayAnalysis (void);				virtual ClassType 						Class (void) const { return (kTDecayAnalysis); };		virtual TObject*						Clone (void) const { return (new TDecayAnalysis (*this)); };				virtual void							Consensus (void);		virtual void							Output (ostream& o, const TString& outgroupLeaf, const TString& fileName, const bool heuristic, const TString& search);		virtual void							Input (istream& sin, istream& slog, const TString& outgroupLeaf, const TString& inFileName, const TString& logFileName, const unsigned int length, const bool fuse);				virtual bool							IsTypeSet (void) const { return (fOStream || fReadIn); };		virtual bool							IsInput (void) const { return (fReadIn); };		virtual bool							IsFuse (void) const { return (IsFlag (kFuse)); };		virtual bool							IsHeuristic (void) const { return (IsFlag (kHeuristic)); }		virtual bool							IsAborted (void) const { return (IsFlag (kAborted)); }		virtual bool							IsSplits (void) const { return (!fSplitSet.IsEmpty ()); }		virtual void							Fuse (void);		virtual char*							GetName (void) const { return ("Decay Analysis"); };			virtual ostream&						Write (ostream& o) const { return (WriteLeafStabilities (o)); };		virtual ostream& 						WriteLeafStabilities (ostream& o) const;		virtual ostream& 						WriteAsTable (ostream& o) const;					protected:				virtual void							setHeuristic (const bool heuristic = true) { SetFlag (kHeuristic, heuristic); }; 		virtual void							setAborted (const bool aborted = true) { SetFlag (kAborted, aborted); }; 		virtual void 							averageQuartets (void);		virtual void							makeBasicForest (void);				virtual void 							storeQuartets (void);		virtual bool							getNextBackBone (TString& name, TString& backBone);		virtual bool							getNextLength (TString& name, unsigned int& length);		virtual void							writeAsNexusNames (const TQuartet& quartet, TString& backBone) const;				TArray<double>*							fLeafStability;		TFuse*									fFuse;		TSplitSet								fSplitSet;		TReadFile*								fReadIn;		TReadFile*								fReadLog;		TString									fInFileName;		TString									fLogFileName;		unsigned short							fOutgroupLeafNumber;				unsigned int							fBasicTrees;		unsigned int							fLength;		TString									fOutgroupLeaf;		TString 								fFileName;		TString									fHConstraints;		long int								fResolvedQuartets;				ostream*								fOStream;};#if PRAGMA_MARK_SUPPORTED#pragma mark -#endif#endif // __TDECAYANALYSIS_H