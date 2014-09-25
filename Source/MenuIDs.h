#ifndef __MENUIDS_H#define __MENUIDS_H// the IDs of these menus are defined in VAppID.h// #define mFile 				129// #define mEdit 				130// #define mStyle 				131// #define mWindow 				132// #define mSize 				151// #define mFont 				152#define mTrees 					133#define mSource 				134#define mConsensus				135#define mRooting 				153#define mConventionalConsensus 	154#define mSuperTreeConsensus 	155#define mInformation		 	156#define mWeightTrees			158#define mSelectTrees			159#define mTreeMeasures 			160#define mDecayAnalysis 			161#define mLeafStabilityDecay		162// mFile//#define cmdExecute MAKECMD (mFile, 12)#define cmdExecute MAKECMD (mFile, 15)// mEdit#define iRadConPreferences		14#define cmdRadConPreferences MAKECMD (mEdit, iRadConPreferences)// mTrees#define iInformation			1#define iTreeMeasures			3#define iShowTrees 				5#define iPrintTrees 			6#define iSaveTrees 				7#define iSelectTrees 			9#define cmdSelectTrees MAKECMD (mTrees, iSelectTrees)#define cmdInformation MAKECMD (mTrees, iInformation)#define cmdTreeMeasures MAKECMD (mTrees, iTreeMeasures)#define cmdShowTrees MAKECMD (mTrees, iShowTrees)#define cmdPrintTrees MAKECMD (mTrees, iPrintTrees)#define cmdSaveTrees MAKECMD (mTrees, iSaveTrees)// mSource#define iAddTrees					1#define iGraftOutgroupLeaf			3#define iPruneRegraftLeaves			4#define iReRoot 					6#define iRooting	 				7#define iCondenseTrees 				9#define iReweightTrees 				10#define iShowWeights 				11#define iPositionalCongruence 		13#define iLeafStabilityBootstrap	 	14#define iLeafStabilityDecay		 	15#define iDecayAnalysis				16#define iConventionalConsensus 		18#define iSuperTreeConsensus 		19#define cmdAddTrees MAKECMD (mSource, iAddTrees)#define cmdAddOutGroup MAKECMD (mSource, iGraftOutgroupLeaf)#define cmdPruneLeaves MAKECMD (mSource, iPruneRegraftLeaves)#define cmdCondenseTrees MAKECMD (mSource, iCondenseTrees)#define cmdWeightTrees MAKECMD (mSource, iReweightTrees)#define cmdShowWeights MAKECMD (mSource, iShowWeights)#define cmdReRoot MAKECMD (mSource, iReRoot)#define cmdRooting MAKECMD (mSource, iRooting)#define cmdPositionalCongruence MAKECMD (mSource, iPositionalCongruence)#define cmdLeafStabilityBootstrap MAKECMD (mSource, iLeafStabilityBootstrap)#define cmdLeafStabilityDecay MAKECMD (mSource, iLeafStabilityDecay)#define cmdDecayAnalysis MAKECMD (mSource, iDecayAnalysis)#define cmdConventionalConsensus MAKECMD (mSource, iConventionalConsensus)#define cmdSuperTreeConsensus MAKECMD (mSource, iSuperTreeConsensus)// mInformation#define iInformationLeaves 		1#define iInformationTrees		2#define cmdInformationLeaves MAKECMD (mInformation, iInformationLeaves)#define cmdInformationTrees MAKECMD (mInformation, iInformationTrees)// mTreeMeasures#define iOthers					1#define iImbalance				2#define cmdTreeMeasuresOthers MAKECMD (mTreeMeasures, iOthers)#define cmdTreeMeasuresImbalance MAKECMD (mTreeMeasures, iImbalance)// mRooting#define iRooted 			1#define iUnrooted			2#define cmdRoot MAKECMD (mRooting, iRooted)#define cmdUnroot MAKECMD (mRooting, iUnrooted)// mConventionalConsensus#define iAdams 				1#define iComponent			2#define iStrictReduced		3#define cmdAdamsConsensus MAKECMD (mConventionalConsensus, iAdams)#define cmdComponentConsensus MAKECMD (mConventionalConsensus, iComponent)#define cmdReducedConsensus MAKECMD (mConventionalConsensus, iStrictReduced)// mSuperTreeConsensus#define iMRP				1#define cmdMRP MAKECMD (mSuperTreeConsensus, iMRP)// mWeightTrees#define iEqually			1#define iBootstrap			2#define cmdWeightEqually MAKECMD (mWeightTrees, iEqually)#define cmdWeightBootstrap MAKECMD (mWeightTrees, iBootstrap)// mSelectTrees#define iAll				1#define iSubset				2#define iNone				3#define cmdSelectTreesAll MAKECMD (mSelectTrees, iAll)#define cmdSelectTreesSubset MAKECMD (mSelectTrees, iSubset)#define cmdSelectTreesNone MAKECMD (mSelectTrees, iNone)// mDecayAnalysis#define iDecayOutput		1#define iDecayInput			2#define cmdDecayOutput MAKECMD (mDecayAnalysis, iDecayOutput)#define cmdDecayInput MAKECMD (mDecayAnalysis, iDecayInput)// mLeafStabilityDecay#define iLeafStabilityDecayOutput		1#define iLeafStabilityDecayInput		2#define cmdLeafStabilityDecayOutput MAKECMD (mLeafStabilityDecay, iLeafStabilityDecayOutput)#define cmdLeafStabilityDecayInput MAKECMD (mLeafStabilityDecay, iLeafStabilityDecayInput)#endif // __MENUIDS_H