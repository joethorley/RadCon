#include "TBTree.h"#if PRAGMA_MARK_SUPPORTED#pragma mark -#endifTCounter TBTreeBlockInitializer::fCount;TMemBlocks* TBTree::TBTreeElement::fMgr = NULL;void TBTree::AddItem (TObject* item){		CHECK_ (item->IsSortable ());	if (IsEmpty ()) 	{		fRoot = new TBTreeElement (item);		fItems.Incr ();		return;	}		TBTreeElement* node = fRoot;	TSortable& sortable = (TSortable&)(*item);		while (1) 	{		if (sortable < *((TSortable*)(node->fData))) 		{			if (node->fLeftChild)				node = node->fLeftChild;			else 			{				node->fLeftChild = new TBTreeElement (item, node);				fItems.Incr ();				return;			}			continue;		}		if (*((TSortable*)(node->fData)) <  sortable) 		{			if (node->fRightChild) 				node = node->fRightChild;			else 			{				node->fRightChild = new TBTreeElement (item, node);				fItems.Incr ();				return;			}			continue;		}		delete item;		return;	}}void TBTree::Copy (const TObject& obj){	CHECK (Class () == obj.Class ());	const TBTree& bTree = (const TBTree&) obj;	DeleteAll ();	const TObject* item = NULL;	for (bTree.FirstItem (); bTree.CurItem (item); bTree.NextItem ())		AddItem (*item);}bool TBTree::CurItem (TObject*& item){	if (CurItem ())	{		item = fCurItem->fData;		return (true);	}	return (false);}bool TBTree::CurItem (const TObject*& item) const{	if (CurItem ())	{		item = fCurItem->fData;		return (true);	}	return (false);}void TBTree::DeleteAll (void){	deleteTraverse (fRoot);	fCurItem = fRoot = NULL;	fItems.Reset ();}void TBTree::DeleteCurItem (void){	TObject* item = NULL;	DetachCurItem (item);	delete item;}void TBTree::DeleteItem (const TObject& toDelete){	TObject* item = NULL;	DetachItem (toDelete, item);	delete (item);}void TBTree::deleteTraverse (TBTreeElement* node){	if (node)	{    		deleteTraverse (node->fLeftChild);		deleteTraverse (node->fRightChild);		delete node->fData;		delete node;	}}void TBTree::DetachItem (const TObject& toDetach, TObject*& item){	TBTreeElement* node = NULL;	if (search (fRoot, toDetach, node))		detachItem (item, node);}void TBTree::detachItem (TObject*& item, TBTreeElement* node){	if (node)	{		fCurItem = NULL;				bool leftChild = node->fLeftChild;		bool rightChild = node->fRightChild;		if ((leftChild && !rightChild) || (rightChild && !leftChild)) // has only one child		{ 			TBTreeElement* child;			if (leftChild)				child = node->fLeftChild;			else				child = node->fRightChild;						item = node->fData;			node->fData = child->fData; 			node->fLeftChild  = child->fLeftChild;			node->fRightChild = child->fRightChild;			if (child->fLeftChild)  				child->fLeftChild->fParent = node;			if (child->fRightChild)  				child->fRightChild->fParent = node;			delete (child);		}		else if (leftChild && rightChild) // has both left and right children		{					TBTreeElement* child = node->fRightChild;			if (child->fLeftChild) 			{				while (child->fLeftChild)					child = child->fLeftChild;				item = node->fData;				node->fData = child->fData; 				child->fParent->fLeftChild = child->fRightChild;				if (child->fRightChild)					child->fRightChild->fParent = child->fParent;			}			else 			{ // no leftchild				item = node->fData;				node->fData = child->fData; 				node->fRightChild = child->fRightChild;				if (child->fRightChild) 					child->fRightChild->fParent = node;			}			delete (child);		}		else // has no children		{			if (node->fParent) // i.e. NOT root			{ 				if (node->fParent->fLeftChild == node)					node->fParent->fLeftChild = NULL;				else					node->fParent->fRightChild = NULL;			}			else // root				fRoot = NULL;			item = node->fData;			delete (node);		}		fItems.Decr ();	}}bool TBTree::FirstItem (void) const{	((TBTree*)this)->fCurItem = ((TBTree*)this)->leftMost (fRoot);	return (CurItem ());}bool TBTree::FirstItem (TObject*& item){	fCurItem = leftMost (fRoot);	return (CurItem (item));}bool TBTree::FirstItem (const TObject*& item) const{	((TBTree*)this)->fCurItem = ((TBTree*)this)->leftMost (fRoot);	return (CurItem (item));}bool TBTree::LastItem (void) const{	((TBTree*)this)->fCurItem = ((TBTree*)this)->rightMost (fRoot);	return (CurItem ());}bool TBTree::LastItem (TObject*& item){	fCurItem = rightMost (fRoot);	return (CurItem (item));}bool TBTree::LastItem (const TObject*& item) const{	((TBTree*)this)->fCurItem = ((TBTree*)this)->rightMost (fRoot);	return (CurItem (item));}TBTree::TBTreeElement* TBTree::leftMost (TBTreeElement* node){	if (node)	{		while (node->fLeftChild)			node = node->fLeftChild;	}	return (node);}TBTree::TBTreeElement* TBTree::nextItem (TBTreeElement* node){	if (node)	{		if (node->fRightChild) 			node = leftMost (node->fRightChild);		else 		{			for (;node->fParent; node = node->fParent)				if (node->fParent->fLeftChild == node)					break;			node = node->fParent;		}	}	return (node);}bool TBTree::NextItem (void) const{	((TBTree*)this)->fCurItem = ((TBTree*)this)->nextItem (fCurItem);	return (CurItem ());}bool TBTree::NextItem (TObject*& item){	fCurItem = nextItem (fCurItem);	return (CurItem (item));}bool TBTree::NextItem (const TObject*& item) const{	((TBTree*)this)->fCurItem = ((TBTree*)this)->nextItem (fCurItem);	return (CurItem (item));}TBTree& TBTree::operator = (const TBTree& bTree){	DeleteAll ();	const TObject* item = NULL;	for (bTree.FirstItem (); bTree.CurItem (item); bTree.NextItem ())		AddItem (*item);	return (*this);}bool TBTree::PrevItem (void) const{	((TBTree*)this)->fCurItem = ((TBTree*)this)->prevItem (fCurItem);	return (CurItem ());}bool TBTree::PrevItem (TObject*& item){	fCurItem = prevItem (fCurItem);	return (CurItem (item));}bool TBTree::PrevItem (const TObject*& item) const{	((TBTree*)this)->fCurItem = ((TBTree*)this)->prevItem (fCurItem);	return (CurItem (item));}TBTree::TBTreeElement* TBTree::prevItem (TBTreeElement* node){	if (node)	{		if (node->fLeftChild) 			node = rightMost (node->fLeftChild);		else		{				for (;node->fParent; node = node->fParent)				if (node->fParent->fRightChild == node)					break;			node = node->fParent;		}	}	return (node);}TBTree::TBTreeElement* TBTree::rightMost (TBTreeElement* node){	if (node)	{		while (node->fRightChild)			node = node->fRightChild;	}	return (node);}bool TBTree::search (const TBTreeElement* node, const TObject& toFind) const{	CHECK_ (toFind.IsSortable ());		if (node)	{		if (*(node->fData) == toFind)			return (true);		if (((TSortable&)toFind) < *((TSortable*)(node->fData)))			return (search (node->fLeftChild, toFind));		return (search (node->fRightChild, toFind));	}	return (false);}bool TBTree::search (const TBTreeElement* node, const TObject& toFind, TObject*& item){	CHECK_ (toFind.IsSortable ());	if (node)	{		if (*(node->fData) == toFind)		{			item = node->fData;			return (true);		}		if (((TSortable&)toFind) < *((TSortable*)(node->fData)))			return (search (node->fLeftChild, toFind, item));		return (search (node->fRightChild, toFind, item));	}	return (false);}bool TBTree::search (const TBTreeElement* node, const TObject& toFind, const TObject*& item) const{	CHECK_ (toFind.IsSortable ());	if (node)	{		if (*(node->fData) == toFind)		{			item = node->fData;			return (true);		}		if (((TSortable&)toFind) < *((TSortable*)(node->fData)))			return (search (node->fLeftChild, toFind, item));		return (search (node->fRightChild, toFind, item));	}	return (false);}bool TBTree::search (const TBTreeElement* node, const TObject& toFind, TBTreeElement*& element){	CHECK_ (toFind.IsSortable ());	if (node)	{		if (*(node->fData) == toFind)		{			element = (TBTreeElement*)node; // JLT 010412 added cast			return (true);		}		if (((TSortable&)toFind) < *((TSortable*)(node->fData)))			return (search (node->fLeftChild, toFind, element));		return (search (node->fRightChild, toFind, element));	}	return (false);}TBTree::TBTree (void){	fCurItem = fRoot = NULL; }     TBTree::TBTree (const TBTree& bTree) {	fCurItem = fRoot = NULL;	const TObject* item = NULL;	for (bTree.FirstItem (); bTree.CurItem (item); bTree.NextItem ())		AddItem (*item); }TBTree::~TBTree (void){	deleteTraverse (fRoot);}     #if PRAGMA_MARK_SUPPORTED#pragma mark -#endifTBTreeBlockInitializer::TBTreeBlockInitializer (void){	if (fCount.GetCount () == 0)		TBTree::TBTreeElement::fMgr = new TMemBlocks (sizeof(TBTree::TBTreeElement), 20);	fCount.Incr ();}TBTreeBlockInitializer::~TBTreeBlockInitializer (void){    fCount.Decr();    if (fCount.GetCount () == 0)    {        delete TBTree::TBTreeElement::fMgr;        TBTree::TBTreeElement::fMgr = NULL;    }}#if PRAGMA_MARK_SUPPORTED#pragma mark -#endifvoid* TBTree::TBTreeElement::operator new (size_t sz){	return (fMgr->Allocate (sz));}void TBTree::TBTreeElement::operator delete (void* b){	fMgr->Free (b);}	            TBTree::TBTreeElement::TBTreeElement (TObject* data, TBTree::TBTreeElement* parent){	fData = data;  	fParent = parent;  	fLeftChild = fRightChild = NULL;}#if PRAGMA_MARK_SUPPORTED#pragma mark -#endifbool TBTreeIterator::CurItem (TObject*& item) const{	if (CurItem ())	{		item = fCurItem->fData;		return (true);	}	return (false);}bool TBTreeIterator::FirstItem (void){	fCurItem = fContainer.leftMost (fContainer.fRoot);	return (CurItem ());}bool TBTreeIterator::FirstItem (TObject*& item){	fCurItem = fContainer.leftMost (fContainer.fRoot);	return (CurItem (item));}bool TBTreeIterator::LastItem (void){	fCurItem = fContainer.rightMost (fContainer.fRoot);	return (CurItem ());}bool TBTreeIterator::LastItem (TObject*& item){	fCurItem = fContainer.rightMost (fContainer.fRoot);	return (CurItem (item));}bool TBTreeIterator::NextItem (void){	fCurItem = fContainer.nextItem (fCurItem);	return (CurItem ());}bool TBTreeIterator::NextItem (TObject*& item){	fCurItem = fContainer.nextItem (fCurItem);	return (CurItem ());}bool TBTreeIterator::PrevItem (void){	fCurItem = fContainer.prevItem (fCurItem);	return (CurItem ());}bool TBTreeIterator::PrevItem (TObject*& item){	fCurItem = fContainer.prevItem (fCurItem);	return (CurItem ());}TBTreeIterator::TBTreeIterator (TBTree& bTree)	: fContainer (bTree){	fCurItem = bTree.fCurItem;}TBTreeIterator::TBTreeIterator (const TBTreeIterator& iterator)	: fContainer (iterator.fContainer){	fCurItem = iterator.fCurItem;}TBTreeIterator::~TBTreeIterator (void){}#if PRAGMA_MARK_SUPPORTED#pragma mark -#endifbool TBTreeIteratorConst::CurItem (const TObject*& item) const{	if (CurItem ())	{		item = fCurItem->fData;		return (true);	}	return (false);}bool TBTreeIteratorConst::FirstItem (void){	fCurItem = ((TBTree&)fContainer).leftMost (fContainer.fRoot);	return (CurItem ());}bool TBTreeIteratorConst::FirstItem (const TObject*& item){	fCurItem = ((TBTree&)fContainer).leftMost (fContainer.fRoot);	return (CurItem (item));}bool TBTreeIteratorConst::LastItem (void){	fCurItem = ((TBTree&)fContainer).rightMost (fContainer.fRoot);	return (CurItem ());}bool TBTreeIteratorConst::LastItem (const TObject*& item){	fCurItem = ((TBTree&)fContainer).rightMost (fContainer.fRoot);	return (CurItem (item));}bool TBTreeIteratorConst::NextItem (void){	fCurItem = ((TBTree&)fContainer).nextItem (fCurItem);	return (CurItem ());}bool TBTreeIteratorConst::NextItem (const TObject*& item){	fCurItem = ((TBTree&)fContainer).nextItem (fCurItem);	return (CurItem (item));}bool TBTreeIteratorConst::PrevItem (void){	fCurItem = ((TBTree&)fContainer).prevItem (fCurItem);	return (CurItem ());}bool TBTreeIteratorConst::PrevItem (const TObject*& item){	fCurItem = ((TBTree&)fContainer).prevItem (fCurItem);	return (CurItem (item));}TBTreeIteratorConst::TBTreeIteratorConst (const TBTree& bTree)	: fContainer (bTree){	fCurItem = bTree.fCurItem;}TBTreeIteratorConst::TBTreeIteratorConst (const TBTreeIterator& iterator)	: fContainer (iterator.fContainer){	fCurItem = iterator.fCurItem;}TBTreeIteratorConst::TBTreeIteratorConst (const TBTreeIteratorConst& iterator)	: fContainer (iterator.fContainer){	fCurItem = iterator.fCurItem;}TBTreeIteratorConst::~TBTreeIteratorConst (void){}#if PRAGMA_MARK_SUPPORTED#pragma mark -#endif