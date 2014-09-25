#ifndef __TCLASSTYPES_H#define __TCLASSTYPES_H#include <limits.h>#include <stdio.h>#include "TXception.h"#include "TItemNumber.h"static const unsigned short kMaxElements = USHRT_MAX; static const unsigned short kMaxLeaves = 500;static const unsigned short kMaxInternals = kMaxLeaves - 1;static const unsigned short kMaxNodes = ((unsigned int)kMaxLeaves) + kMaxInternals;		// maximum nodes in a tree internal nodes = MAXLEAVES-1 and leaves = MAXLEAVESstatic const unsigned short kMaxTrees = 10000; // 10000 JLT 000506static const double kMinWeight = 0.001;static const double kDefaultWeight = 1;static const double kMaxWeight = 1000; // assumes that maximum range of weights will be 1000 * 10,000 = 10 * 10^6// to 0.001 a total range of 10,000,000.001 and that double with DBL_DIG = 15// is accurate over this range and that this is sufficient precision// note some rounding may occur as values can be input as fractions i.e. 1/3static const long int kMaxStringLength = BUFSIZ;// these need changing.... as phylogenetic characters and other characters...static const int kFileWidth = 75;		// maximum length of nexus output.....note must be greater than maxnamelengthstatic const long int kMaxNameLength = 127;//static const int kMaxLengthTaxonName = 128; // maximum characters in a leaf labelstatic const int kTabSize = 4;static const int kMaxLeafLabelLength = 16;								// number of characters in tree name written to fileclass EInputError : public TXception {	public:		EInputError () : TXception () { };		EInputError (const char* str) : TXception (str) { };			 }; //class EHelp   { }; //exception class for requesting further information for userenum NexusBlockType { 	kTaxaBlock, 	kDataBlock, 	kTreesBlock, 	kCharactersBlock, 	kStatementsBlock, 	kUnknownBlock, 	kNoBlock };enum CondenseTreesOptionType { 	kWeightSum, 	kWeightMean, 	kWeightMax, 	kWeightMin, 	kWeightBootstrap };enum SetRelations { 	identity, 	disjoint, 	subset, 	superset, 	overlapping };enum StructureType { 	kTriplet, 	kQuartet, 	kComponent, 	kTree };enum AgreementType { 	kStrict, 	kSemiStrict, 	kMajorityRule };enum TreeType { 	kStrictCladistic, 	kSemiStrictCladistic, 	kMajorityRuleCladistic,	kStrictNestings,	kAhoTree,	kDecayIndex};#endif // __TCLASSTYPES_H