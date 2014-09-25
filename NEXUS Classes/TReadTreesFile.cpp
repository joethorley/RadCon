#include "TReadTreesFile.h"#include "DialogIDs.h"#include "TWrapString.h"#include "VMsg.h"char TReadTreesFile::fSErrorMsg [128];#if PRAGMA_MARK_SUPPORTED#pragma mark -#endifvoid TReadTreesFile::addLeafOnTheFly (const TString& leafName){//	if (leafName.IsInteger ())//	{//		sprintf (fSErrorMsg, "'%s' is an invalid leaf name", leafName.Array ());//		throw EInputError (fSErrorMsg);//	}	// some shit with reading in names with ' ' and illegal characters !!!!	// also lengths of taxlabels	CHECK_ (!fCurTranslationTable->IsLeaf (leafName));	if (fCurTranslationTable->GetLeaves () == kMaxLeaves)	{		sprintf (fSErrorMsg, "The number of leaves cannot exceed %i", kMaxLeaves);		throw EInputError (fSErrorMsg);	}	fCurTranslationTable->AddLeaf (leafName);}void TReadTreesFile::addLeaf (const TString& leafName){//	if (leafName.IsInteger ())//	{//		sprintf (fSErrorMsg, "'%s' is an invalid leaf name", leafName.Array ());//		throw EInputError (fSErrorMsg);//	}	// some shit with reading in names with ' ' and illegal characters !!!!	// also lengths of taxlabels	CHECK_ (!fCurTaxaBlock->IsLeaf (leafName));	if (fCurTaxaBlock->GetLeaves () == kMaxLeaves)	{		sprintf (fSErrorMsg, "The number of leaves cannot exceed %i", kMaxLeaves);		throw EInputError (fSErrorMsg);	}	fCurTaxaBlock->AddLeaf (leafName);}void TReadTreesFile::addTree (void){	if (fCurTreesBlock->IsEmpty ()) 	{	// because TTreesBlock created by default as rooted		if (!fCurTree.IsRooted ())			fCurTreesBlock->UnRoot ();	}	if (fCurTreesBlock->IsRooted () && !fCurTree.IsRooted ())		fCurTree.Root ();	else if (!fCurTreesBlock->IsRooted () && fCurTree.IsRooted ())		fCurTree.UnRoot ();	if (fCurTree.IsRooted () ? fCurTree.GetLeaves () < 3 : fCurTree.GetLeaves () < 4)	{		sprintf (fSErrorMsg, "A tree contains too few leaves");		throw EInputError (fSErrorMsg);	}	fCurTreesBlock->AddTree (fCurTree);			}void TReadTreesFile::addTreesToList (void){	TTaxaBlock* taxaBlock = new TTaxaBlock (*fCurTaxaBlock);	TSourceTreesBlock* treesBlock = fCurTreesBlock;	fCurTreesBlock = new TSourceTreesBlock ();		CHECK_ (treesBlock->GetLeafSet (false, false).IsSubset (taxaBlock->GetLeafSet ()));	if (taxaBlock->GetLeafSet () != treesBlock->GetLeafSet (false, false))	{		TLeafSet leafSet = (taxaBlock->GetLeafSet () - treesBlock->GetLeafSet (false, false));				*Log << EOLN << (int)leafSet.GetLeaves () << ' ' << ((leafSet.GetLeaves () == 1) ? "leaf is " : "leaves are ") << "absent from all the trees:" << EOLN;		TWrapString wrapString (kFileWidth) ;		for (leafSet.FirstLeaf (); leafSet.CurLeaf (); leafSet.NextLeaf ())			wrapString.AddToThis (taxaBlock->GetLeafName (leafSet.CurLeaf ()));		*Log << wrapString.GetString ().Array () << EOLN;				taxaBlock->PruneLeaves (leafSet);		*Log << EOLN << ((leafSet.GetLeaves () == 1) ? "It has " : "They have ") << "been deleted from memory" << EOLN;				CHECK_ (taxaBlock->GetLeafSet () == treesBlock->GetLeafSet (false, false));				TLeafSet newLeafSet (taxaBlock->GetLeaves ());		TLeafMap leafMap (taxaBlock->GetLeafSet (), newLeafSet);				taxaBlock->MapLeaves (leafMap);		treesBlock->MapLeaves (leafMap);				CHECK_ (taxaBlock->GetLeafSet () == treesBlock->GetLeafSet (false, false));	}	TString name = fFileName;	if (!fTreesFiles.IsEmpty ())		name.AddToThis (fTreesFiles.GetItems () + 1);	fTreesFiles.AddItem (new TSourceTreesFile (taxaBlock, treesBlock, name.Array ()));}NexusBlockType TReadTreesFile::getBlockType (const TString& string){	if (string == "TAXA")		return (kTaxaBlock);	else if (string == "TREES")		return (kTreesBlock);		return (kUnknownBlock);}bool TReadTreesFile::isNexusFile (void){	fIStream.seekg (0, ios::beg);	fCurBlockType = kNoBlock;	return (nextToken ().ToUpper () == "#NEXUS");}bool TReadTreesFile::isPhylipFile (void){//	fIStream.seekg (0, ios::beg); why the hell is this no resetting!!!//	fCurBlockType = kNoBlock;		return (fCurToken == "(");}NexusBlockType TReadTreesFile::nextBlockType (void){	try 	{	// at this point where actually expecting eof could test for it but what it lots of white space and comments!!			if (nextToken ().ToUpper () != "BEGIN") 		{			sprintf (fSErrorMsg, "Expecting a BEGIN command");			throw EInputError (fSErrorMsg);		}	}	catch (EReadChar) 	{		// do we need to delete...assume not??		return (fCurBlockType = kNoBlock);	}		return (fCurBlockType = getBlockType (nextToken ().ToUpper ()));}void TReadTreesFile::nextFileCharacter (void){	if (!fIStream.get (fCurFileChar)) 		throw EReadChar ();}void TReadTreesFile::readNexusFile (void){	while (nextBlockType () != kNoBlock)	{		switch (curBlockType ())		{			case kTaxaBlock:				*Log << EOLN << "Reading Taxa Block" << EOLN;				readTaxaBlock ();				break;						case kTreesBlock:							if (fCurTreesBlock->GetTrees () < kMaxTrees)				{									*Log << EOLN << "Reading Trees Block" << EOLN;					readTreesBlock ();					if (fCurTreesBlock->GetTrees () == kMaxTrees)					{						*Log << EOLN << "The Upper Limit on the number of Trees Was Reached" << EOLN;					}					if (IsFlag (kMultipleSetsTrees))					{							*Log << EOLN << (int)fCurTreesBlock->GetTrees () << ' ' << (fCurTreesBlock->IsRooted ()? "Rooted " : "Unrooted ") << (fCurTreesBlock->GetTrees () == 1 ? "Tree " : "Trees ") << "read into memory" << EOLN;						addTreesToList ();					}				}				else				{					*Log << EOLN << "Skipping Trees Block" << EOLN;					skipBlock ();				}				break;								default:				*Log << EOLN << "Skipping " << fCurToken.Array () << ' ' << "Block" << EOLN;								skipBlock ();								break;		}		try		{			nextToken ();		}		catch (EReadChar)		{			// do we need to delete here??		}		if (fCurToken != ";")		{			sprintf (fSErrorMsg, "Expecting a semicolon ';'");			throw EInputError (fSErrorMsg);			}			}	if (!IsFlag (kMultipleSetsTrees))	{		if (fCurTreesBlock->IsEmpty ())		{			sprintf (fSErrorMsg, "Nexus file contains no trees block");			throw EInputError (fSErrorMsg);		}		*Log << EOLN << (int)fCurTreesBlock->GetTrees () << ' ' << (fCurTreesBlock->IsRooted ()? "Rooted " : "Unrooted ") << (fCurTreesBlock->GetTrees () == 1 ? "Tree " : "Trees ") << "read into memory" << EOLN;		addTreesToList ();	}}void TReadTreesFile::readNexusTree (void){			if (fCurToken == "=")	{		sprintf (fSErrorMsg, "Expecting a tree name");		throw EInputError (fSErrorMsg);	}	if (kMaxNameLength < fCurToken.Length ())		fCurToken.SetLength (kMaxNameLength);	fCurTree.SetName (fCurToken);			if (nextToken () != "=")	{		sprintf (fSErrorMsg, "Expecting an equals '='");		throw EInputError (fSErrorMsg);	}		readTreeCommandComments ();	readTreeDescription ();}void TReadTreesFile::readPhylipFile (void){	try 	{		fCurTranslationTable = new TTranslationTable (*fCurTaxaBlock);		bool firstPass = true;		const bool predefineLeaves = IsFlag (kPredefineLeaves);				MonitorDialog = TheApp->CreateMonitor (dlgProgressText);		MonitorDialog->SetItemText (3, "1");		MonitorDialog->SetItemText (4, "Reading Trees");		MonitorDialog->Show ();		while (1)		{						if (firstPass)				SetFlag (kPredefineLeaves, false);						readPhylipTree ();												if (fCurTreesBlock->GetTrees () == kMaxTrees)			{				CHECK_ (fCurTreesBlock->GetTrees () == fCurTreesBlock->GetTotalTrees ());				Message (MSG_INFO, "The Upper Limit on the number of Trees Has Been Reached");				break;			}			addTree ();				if (firstPass)			{				SetFlag (kPredefineLeaves, predefineLeaves);				firstPass = false;				fCurTreesBlock->SetCurTreeNumber (1); // added 29/09/99 4.08pm j. thorley			}			if (nextToken () != ";")			{				sprintf (fSErrorMsg, "Expecting a semicolon ';'");				throw EInputError (fSErrorMsg);				}												try			{				nextToken ();			}			catch (EReadChar)			{				break;			}		}	}	catch (...)	{		delete (fCurTranslationTable);		fCurTranslationTable = NULL;		TheApp->DestroyDialog ();		throw;	}	addTreesToList ();	delete (fCurTranslationTable);	fCurTranslationTable = NULL;	TheApp->DestroyDialog ();}void TReadTreesFile::readPhylipTree (void){		// how to get name ?? what if none!!	TString name ("tree");	name.AddToThis (fCurTreesBlock->GetTrees () + 1);	fCurTree.SetName (name);		fCurTree.SetWeight (kDefaultWeight);	// how to get weighting ?? what if none!!	// how to get rooting ?? what if none!!	// assuming that all rooted ?? how to determine	readTreeDescription ();}void TReadTreesFile::ReadFile (void){		try	{		if (!isNexusFile ())			{			if (!isPhylipFile ())			{				sprintf (fSErrorMsg, "Unrecognised file format");				throw EInputError (fSErrorMsg);			}			readPhylipFile ();		}		else			readNexusFile ();	}	catch (EReadChar)	{		sprintf (fSErrorMsg, "Unexpected end of file");		throw EInputError (fSErrorMsg);	}}void TReadTreesFile::readTaxaBlock (void){//	CHECK_ (IsFlag (kPredefineLeaves)); // JLT 010310 commented out		TTaxaBlock* curTaxaBlock = NULL;		if (IsFlag (kMultipleSetsTrees))		resetTaxaBlock ();	else	{		curTaxaBlock = new TTaxaBlock ();		swap (fCurTaxaBlock, curTaxaBlock);	}		if (nextToken () != ";")	{		sprintf (fSErrorMsg, "Expecting a semicolon ';'");		throw EInputError (fSErrorMsg);		}			readTaxaBlockLabels (readTaxaBlockDimensions ());		if (nextToken ().ToUpper () != "END" && fCurToken.ToUpper () != "ENDBLOCK")	{		sprintf (fSErrorMsg, "Expecting a ENDBLOCK command");		throw EInputError (fSErrorMsg);		}	if (curTaxaBlock)	{		swap (fCurTaxaBlock, curTaxaBlock);		fCurTaxaBlock->AddLeaves (*curTaxaBlock);		delete (curTaxaBlock);	}}unsigned int TReadTreesFile::readTaxaBlockDimensions (void){	if (nextToken ().ToUpper () != "DIMENSIONS")	{		sprintf (fSErrorMsg, "Expecting a DIMENSIONS command");		throw EInputError (fSErrorMsg);	}	if (nextToken ().ToUpper () != "NTAX")	{		sprintf (fSErrorMsg, "Expecting a NTAX command");		throw EInputError (fSErrorMsg);	}	if (nextToken () != "=") 	{		sprintf (fSErrorMsg, "Expecting an equals '='");		throw EInputError (fSErrorMsg);	}	if (!nextToken ().IsInteger ())	{		sprintf (fSErrorMsg, "Expecting an integer not '%s'", fCurToken.Array ());		throw EInputError (fSErrorMsg);	}	unsigned int ntax = atoi (fCurToken.Array ());	if (ntax > kMaxLeaves) 	{		sprintf (fSErrorMsg, "The number of leaves cannot exceed %i", kMaxLeaves);		throw EInputError (fSErrorMsg);	}	if (nextToken () != ";")	{		sprintf (fSErrorMsg, "Expecting a semicolon ';'");		throw EInputError (fSErrorMsg);		}			return (ntax);}void TReadTreesFile::readTaxaBlockLabels (const unsigned int ntax){	CHECK_ (fCurTaxaBlock);		if (nextToken ().ToUpper () != "TAXLABELS")	{		sprintf (fSErrorMsg, "Expecting a TAXLABELS command");		throw EInputError (fSErrorMsg);	}	while (nextToken () != ";") 	{		if (kMaxNameLength < fCurToken.Length ())			fCurToken.SetLength (kMaxNameLength);			if (ntax <= fCurTaxaBlock->GetLeaves ())		{			sprintf (fSErrorMsg, "Taxa block contains more leaves than specified by its DIMENSIONS command");			throw EInputError (fSErrorMsg);		}		if (fCurTaxaBlock->IsLeaf (fCurToken))		{			sprintf (fSErrorMsg, "Leaf '%s'occurs more than once in the taxa block", fCurToken.Array ());			throw EInputError (fSErrorMsg);		}		addLeaf (fCurToken);	}	if (fCurTaxaBlock->GetLeaves () < ntax)	{		sprintf (fSErrorMsg, "Taxa block contains less leaves than specified by its DIMENSIONS command");		throw EInputError (fSErrorMsg);		}}void TReadTreesFile::readTranslationTable (void){	CHECK_ (fCurTranslationTable);		while (fCurToken != ";")	{		TString token = nextToken ();		TString leafName = nextToken ();				if (!fCurTranslationTable->IsLeaf (leafName))		{			if (!IsFlag (kPredefineLeaves))			{							if (fCurTranslationTable->IsToken (leafName))				{					sprintf (fSErrorMsg, "Leaf '%s' is also a translation token", leafName.Array ());					throw EInputError (fSErrorMsg);				}				addLeafOnTheFly (leafName);			}			else			{				sprintf (fSErrorMsg, "Translation table contains undefined leaf '%s'", leafName.Array ());				throw EInputError (fSErrorMsg);			}		}					if (fCurTranslationTable->IsLeaf (token)) 		{			sprintf (fSErrorMsg, "Translation token '%s' is also a leaf", token.Array ());			throw EInputError (fSErrorMsg);		}		if (fCurTranslationTable->IsToken (token))		{			sprintf (fSErrorMsg, "Translation token '%s' occurs more than once in the translation table", token.Array ());			throw EInputError (fSErrorMsg);		}				fCurTranslationTable->AddToken (token, leafName);				if (nextToken () != "," && fCurToken != ";")		{			sprintf (fSErrorMsg, "Expecting a comma ','");			throw EInputError (fSErrorMsg);		}	}}void TReadTreesFile::readTreeDescription (void){	CHECK_ (fCurTranslationTable);								if (fCurToken != "(") 	{		sprintf (fSErrorMsg, "Expecting a parenthesis '(' at start of tree description");		throw EInputError (fSErrorMsg);	}	fTreeString.SetNull ();	fLeafSet.SetEmpty ();	readTreeDescriptionComponent ();		if (((!fCurTreesBlock->IsEmpty () && fCurTreesBlock->IsRooted ()) || fCurTree.IsRooted ()) ? fLeafSet.GetLeaves () < 3 : fLeafSet.GetLeaves () < 4)	{		sprintf (fSErrorMsg, "A tree contains too few leaves to be informative");		throw EInputError (fSErrorMsg);	}		fCurTree.FromTreeString (fTreeString);	}void TReadTreesFile::readTreesBlock (void){// JLT 010311 turned off resetting taxabloack because i prefer to get leaves in order from taxablock even if adding on the fly//	if (IsFlag (kMultipleSetsTrees) && !IsFlag (kPredefineLeaves))//		resetTaxaBlock ();			fCurTranslationTable = new TTranslationTable (*fCurTaxaBlock);	if (nextToken () != ";")	{		sprintf (fSErrorMsg, "Expecting a semicolon ';'");		throw EInputError (fSErrorMsg);		}			if (nextToken ().ToUpper () == "TRANSLATE")	{		readTranslationTable ();		nextToken ().ToUpper ();	}	MonitorDialog = TheApp->CreateMonitor (dlgProgressText);	MonitorDialog->SetItemText (3, "1");	MonitorDialog->SetItemText (4, "Reading Trees");	MonitorDialog->Show ();		try	{		while (fCurToken != "ENDBLOCK" && fCurToken != "END")		{			if (fCurToken != "TREE" && fCurToken != "UTREE" )			{				sprintf (fSErrorMsg, "Expecting a TREE command");				throw EInputError (fSErrorMsg);			}						if (fCurTreesBlock->GetTrees () == kMaxTrees)			{				CHECK_ (fCurTreesBlock->GetTrees () == fCurTreesBlock->GetTotalTrees ());				Message (MSG_INFO, "The Upper Limit on the number of Trees Has Been Reached");				skipBlock ();				break;			}						if (fCurToken == "TREE")				fCurTree.Root ();			else				fCurTree.UnRoot ();						bool defalt = false;						if (!fCurTreesBlock->GetTrees ())				defalt = true;			if (nextToken () == "*")			{				defalt = true;				nextToken ();			}			readNexusTree ();						if (nextToken () != ";")			{				sprintf (fSErrorMsg, "Expecting a semicolon ';'");				throw EInputError (fSErrorMsg);				}								addTree ();			if (defalt)				fCurTreesBlock->SetCurTreeNumber (fCurTreesBlock->GetTrees ());						TString string;			string.AddToThis (fCurTreesBlock->GetTrees ());			MonitorDialog->SetItemText (3, string.Array ());			MonitorDialog->ProcessExternal ();						if (MonitorDialog->HasAborted ())			{				skipBlock ();				break;			}				nextToken ().ToUpper ();		}	}	catch (...)	{		if (fCurTranslationTable)			delete (fCurTranslationTable);		TheApp->DestroyDialog ();		throw;	}	if (fCurTranslationTable)		delete (fCurTranslationTable);	TheApp->DestroyDialog ();}void TReadTreesFile::readTreeCommandComments (void){	setReadCommandComments (true);		if (nextToken () == "&")	{		if (nextToken () == "U")		{			if (fCurTree.IsRooted ())				fCurTree.UnRoot ();		}		else if (fCurToken == "R")		{			if (!fCurTree.IsRooted ())				fCurTree.Root ();		}		else if (fCurToken == "W")		{			nextToken ();			double weight;			if (fCurToken.IsFraction ())				weight = fCurToken.FractionToDouble ();			else if (fCurToken.IsFloat ())				weight = fCurToken.ToDouble (); 			else			{				sprintf (fSErrorMsg, "Invalid tree weight '%s'", fCurToken.Array ());				throw EInputError (fSErrorMsg);							}			if ((double)kMaxWeight < weight)			{				sprintf (fSErrorMsg, "The weight of a tree cannot exceed %.0f", (float)kMaxWeight);				throw EInputError (fSErrorMsg);							}			if (weight < (double)kMinWeight)			{				sprintf (fSErrorMsg, "The weight of a tree cannot be less than %.5f", (float)kMinWeight);				throw EInputError (fSErrorMsg);									}			fCurTree.SetWeight (weight);		}		if (nextToken () != "]")		{			sprintf (fSErrorMsg, "Expecting an end of command comment ']'");			throw EInputError (fSErrorMsg);						}		readTreeCommandComments ();	}	setReadCommandComments (false);}void TReadTreesFile::readTreeDescriptionComponent (void){	fTreeString += "(";		TCounter degree;	bool isNodeExpected = true;			nextToken ();	while (fCurToken != ")")	{		if (fCurToken == ";")		{			sprintf (fSErrorMsg, "Expecting a parenthesis ')' at end of tree description");			throw EInputError (fSErrorMsg);		}		if (!isNodeExpected)		{			if (fCurToken != ",")			{				sprintf (fSErrorMsg, "Expecting a comma ',' in tree description");				throw EInputError (fSErrorMsg);			}			fTreeString += ",";								nextToken ();				isNodeExpected = true;		}		else		{			if (fCurToken == "(")				readTreeDescriptionComponent ();			else			{				if (kMaxNameLength < fCurToken.Length ())					fCurToken.SetLength (kMaxNameLength);									const unsigned int leaf = fCurTranslationTable->GetLeafNumber (fCurToken);				if (!leaf)					{					if (!IsFlag (kPredefineLeaves))					{						addLeafOnTheFly (fCurToken);						fLeafSet.AddToThis (fCurTranslationTable->GetLeafNumber (fCurToken)); // JLT 010308 fixed bug					}					else					{						sprintf (fSErrorMsg, "Undefined leaf '%s' in tree description", fCurToken.Array ());						throw EInputError (fSErrorMsg);					}				}				else if (fLeafSet.IsLeaf (leaf))				{					sprintf (fSErrorMsg, "Multiple occurrences of leaf '%s' in tree description", fCurToken.Array ());					throw EInputError (fSErrorMsg);				}				else					fLeafSet.AddToThis (leaf); 								fTreeString.AddToThis (fCurTranslationTable->GetLeafNumber (fCurToken));			}			if (nextToken () == ":")			{				nextToken();				nextToken();			}			degree.Incr ();			isNodeExpected = false;				}	}	fTreeString += ")";		if (degree.GetCount () < 2)	{		sprintf (fSErrorMsg, "Extra pair of parentheses '()' in tree description");		throw EInputError (fSErrorMsg);	}}void TReadTreesFile::resetTaxaBlock (void){	CHECK_ (fCurTreesBlock->IsEmpty ());		delete (fCurTaxaBlock);	fCurTaxaBlock = new TTaxaBlock ();}TReadTreesFile::TReadTreesFile (istream& i, const TString name, TSourceTreesFileList& treesFiles, const bool predefineLeaves, const bool multipleSetsTrees)	:	fIStream (i)	,	fTreesFiles (treesFiles)	,	fTreeString (100, 100)	, 	fFileName (name){	CHECK_ (treesFiles.IsEmpty ());		fCurBlockType = kNoBlock;		SetFlag (kPredefineLeaves, predefineLeaves);	SetFlag (kMultipleSetsTrees, multipleSetsTrees);	fCurTaxaBlock = new TTaxaBlock ();	fCurTranslationTable = NULL;	fCurTreesBlock = new TSourceTreesBlock ();}TReadTreesFile::~TReadTreesFile (void){//	if (fCurTaxaBlock)//		delete (fCurTaxaBlock);//	if (fCurTranslationTable)//		delete (fCurTranslationTable);//	if (fCurTreesBlock)//		delete (fCurTreesBlock);}#if PRAGMA_MARK_SUPPORTED#pragma mark -#endif