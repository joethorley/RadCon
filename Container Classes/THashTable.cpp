#include "THashTable.h"void THashTable::AddItem (TObject* item){		CHECK (item);	fTable[hashItem (*item)].AddItem (item);	fItems.Incr();}void THashTable::Copy (const TObject& hashTable){	CHECK (Class () == hashTable.Class ());	DeleteAll ();	THashTableIteratorConst& iteratorConst = ((THashTableIteratorConst&)((const THashTable&)hashTable).IteratorConst ());	const TObject* item = NULL;	for (iteratorConst.FirstItem (); iteratorConst.CurItem (item); iteratorConst.NextItem ())		AddItem (*item);	delete &iteratorConst;}bool THashTable::CurItem (void) const{	TSList* list = NULL;	if (fArrayIterator->CurItem (list, true))	{		return (list->CurItem ());	}	return (false);}bool THashTable::CurItem (TObject*& item){	TSList* list = NULL;	if (fArrayIterator->CurItem (list, true))	{		return (list->CurItem (item));	}	return (false);}bool THashTable::CurItem (const TObject*& item) const{	TSList* list = NULL;	if (fArrayIterator->CurItem (list, true))	{		return (((const TSList*)list)->CurItem (item));	}	return (false);} void THashTable::DetachItem (TObject*& item){	TSList* list = NULL;	TPArrayIterator<TSList>& iterator = fTable.Iterator ();	for (iterator.FirstItem (true); iterator.CurItem (list, true); iterator.NextItem (true))	{		if (!(list->IsEmpty ()))		{			list->DetachItem (item);			break;		}	}}void THashTable::DetachCurItem (TObject*& item){	CHECK_ (0); // needs defining}bool THashTable::FirstItem (void) const{	TSList* list = NULL;	for (fArrayIterator->FirstItem (true); fArrayIterator->CurItem (list, true); fArrayIterator->NextItem (true))	{		if (!list->IsEmpty ())		{			return (((const TSList*)list)->FirstItem ());		}	}	return (false);}bool THashTable::FirstItem (TObject*& item){	TSList* list = NULL;	for (fArrayIterator->FirstItem (true); fArrayIterator->CurItem (list, true); fArrayIterator->NextItem (true))	{		if (!list->IsEmpty ())		{			return (list->FirstItem (item));		}	}	return (false);}bool THashTable::FirstItem (const TObject*& item) const{	TSList* list = NULL;	for (fArrayIterator->FirstItem (true); fArrayIterator->CurItem (list, true); fArrayIterator->NextItem (true))	{		if (!list->IsEmpty ())		{			return (((const TSList*)list)->FirstItem (item));		}	}	return (false);}bool THashTable::FindItem (const TObject& toFind) const{		return (fTable[hashItem (toFind)].FindItem (toFind));}bool THashTable::FindItem (const TObject& toFind, TObject*& item){	return (fTable[hashItem (toFind)].FindItem (toFind, item));}bool THashTable::FindItem (const TObject& toFind, const TObject*& item) const{	return (fTable[hashItem (toFind)].FindItem (toFind, item));}HashValue THashTable::hashItem (const TObject& item) const{    return (item.Hash () % fTable.Size ());}TContainerIterator& THashTable::Iterator (void){	return *((TContainerIterator*)(new THashTableIterator (*this)));}TContainerIteratorConst& THashTable::IteratorConst (void) const{	return *((TContainerIteratorConst*)(new THashTableIteratorConst (*this)));}bool THashTable::NextItem (void) const{	TSList* list = NULL;	if (fArrayIterator->CurItem (list, true))	{		if (list->NextItem ())			return (true);		for (fArrayIterator->NextItem (true);fArrayIterator->CurItem (list, true);fArrayIterator->NextItem (true))		{			if (!(list->IsEmpty ()))			{				return (list->FirstItem ());			}		}				}	return (false);}bool THashTable::NextItem (TObject*& item){	TSList* list = NULL;	if (fArrayIterator->CurItem (list, true))	{		if (list->NextItem (item))			return (true);		for (fArrayIterator->NextItem (true);fArrayIterator->CurItem (list, true);fArrayIterator->NextItem (true))		{			if (!(list->IsEmpty ()))			{				return (list->FirstItem (item));			}		}				}	return (false);}bool THashTable::NextItem (const TObject*& item) const{	TSList* list = NULL;	if (fArrayIterator->CurItem (list, true))	{		if (((const TSList*)list)->NextItem (item))			return (true);		for (fArrayIterator->NextItem (true); fArrayIterator->CurItem (list, true); fArrayIterator->NextItem (true))		{			if (!(list->IsEmpty ()))			{				return (((const TSList*)list)->FirstItem (item));			}		}				}	return (false);}THashTable::THashTable (const unsigned int sz)	: 	fTable ((unsigned int)sz),		TContainer (){	fArrayIterator = &(fTable.Iterator ());}THashTable::THashTable (const THashTable& hashTable)	: 	fTable (hashTable.fTable),		TContainer (hashTable){	fArrayIterator = &(fTable.Iterator ());}THashTable::~THashTable (void){	delete fArrayIterator;}	  bool THashTableIterator::CurItem (void) const{	return ((fListIterator == NULL) ? false : fListIterator->CurItem ());}bool THashTableIterator::CurItem (TObject*& item) const{	return ((fListIterator == NULL) ? false : fListIterator->CurItem (item));}bool THashTableIterator::FirstItem (void){	if (fListIterator != NULL)    	delete fListIterator;     fListIterator = NULL;		TSList* list = NULL;	for (fArrayIterator.FirstItem (true); fArrayIterator.CurItem (list, true); fArrayIterator.NextItem (true))	{		if (!(list->IsEmpty ()))		{			fListIterator = &((TSListIterator&)(list->Iterator ()));			return (fListIterator->FirstItem ());		}	}	return (false);}bool THashTableIterator::FirstItem (TObject*& item){	if (fListIterator != NULL)    	delete fListIterator;     fListIterator = NULL;		TSList* list = NULL;	for (fArrayIterator.FirstItem (true); fArrayIterator.CurItem (list, true); fArrayIterator.NextItem (true))	{		if (!(list->IsEmpty ()))		{			fListIterator = &((TSListIterator&)(list->Iterator ()));			return (fListIterator->FirstItem (item));		}	}	return (false);}bool THashTableIterator::NextItem (void){	TSList* list = NULL;	if (fArrayIterator.CurItem (list, true))	{		if (list->NextItem ())			return (true);		for (fArrayIterator.NextItem (true); fArrayIterator.CurItem (list, true); fArrayIterator.NextItem (true))		{			if (!(list->IsEmpty ()))			{				return (list->FirstItem ());			}		}	}	return (false);}bool THashTableIterator::NextItem (TObject*& item){	TSList* list = NULL;	if (fArrayIterator.CurItem (list, true))	{		if (list->NextItem (item))			return (true);		for (fArrayIterator.NextItem (true); fArrayIterator.CurItem (list, true); fArrayIterator.NextItem (true))		{			if (!(list->IsEmpty ()))			{				return (list->FirstItem (item));			}		}	}	return (false);}THashTableIterator::THashTableIterator (THashTable& hashTable)	: 	fArrayIterator (hashTable.fTable.Iterator ()),		fContainer (hashTable){	fListIterator = NULL;}THashTableIterator::THashTableIterator (THashTableIterator& iterator)	: 	fArrayIterator (iterator.fArrayIterator),		fContainer (iterator.fContainer){	fListIterator = NULL;}	    THashTableIterator::~THashTableIterator (void){	delete fListIterator;	delete &fArrayIterator;}	  bool THashTableIteratorConst::CurItem (void) const{	return ((fListIterator == NULL) ? false : fListIterator->CurItem ());}bool THashTableIteratorConst::CurItem (const TObject*& item) const{	return ((fListIterator == NULL) ? false : fListIterator->CurItem (item));}bool THashTableIteratorConst::FirstItem (void){	if (fListIterator != NULL)    	delete fListIterator;     fListIterator = NULL;		const TSList* list = NULL;	for (fArrayIterator.FirstItem (true); fArrayIterator.CurItem (list, true); fArrayIterator.NextItem (true))	{		if (!(list->IsEmpty ()))		{			fListIterator = &((TSListIteratorConst&)(list->IteratorConst ()));			return (fListIterator->FirstItem ());		}	}	return (false);}bool THashTableIteratorConst::FirstItem (const TObject*& item){	if (fListIterator != NULL)    	delete fListIterator;     fListIterator = NULL;		const TSList* list = NULL;	for (fArrayIterator.FirstItem (true); fArrayIterator.CurItem (list, true); fArrayIterator.NextItem (true))	{		if (!(list->IsEmpty ()))		{			fListIterator = &((TSListIteratorConst&)(list->IteratorConst ()));			return (fListIterator->FirstItem (item));		}	}	return (false);}bool THashTableIteratorConst::NextItem (void){	if (fArrayIterator.CurItem ())	{		if (fListIterator->NextItem ())			return (true);			    	delete fListIterator;     	fListIterator = NULL;					const TSList* list = NULL;			for (fArrayIterator.NextItem (true); fArrayIterator.CurItem (list, true);fArrayIterator.NextItem (true))		{			if (!(list->IsEmpty ()))			{				fListIterator = &((TSListIteratorConst&)(list->IteratorConst ()));				return (fListIterator->FirstItem ());			}		}	}	return (false);}bool THashTableIteratorConst::NextItem (const TObject*& item){	if (fArrayIterator.CurItem ())	{		if (fListIterator->NextItem (item))			return (true);			    	delete fListIterator;     	fListIterator = NULL;					const TSList* list = NULL;			for (fArrayIterator.NextItem (true); fArrayIterator.CurItem (list, true); fArrayIterator.NextItem (true))		{			if (!(list->IsEmpty ()))			{				fListIterator = &((TSListIteratorConst&)(list->IteratorConst ()));				return (fListIterator->FirstItem (item));			}		}	}	return (false);}THashTableIteratorConst::THashTableIteratorConst (const THashTable& hashTable)	: 	fArrayIterator (hashTable.fTable.IteratorConst ()),		fContainer (hashTable){	fListIterator = NULL;}THashTableIteratorConst::THashTableIteratorConst (const THashTableIterator& iterator)	:	fArrayIterator (*(new TPArrayIteratorConst<TSList> (iterator.fArrayIterator))),		fContainer (iterator.fContainer){	fListIterator = NULL;}THashTableIteratorConst::THashTableIteratorConst (const THashTableIteratorConst& iteratorConst)	:	fArrayIterator (iteratorConst.fArrayIterator),		fContainer (iteratorConst.fContainer){	fListIterator = NULL;}	    THashTableIteratorConst::~THashTableIteratorConst (void){	delete fListIterator;	delete &fArrayIterator;}