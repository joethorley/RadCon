#ifndef _TPARRAY_H#define _TPARRAY_H#include "TArray.h"#include "TCounter.h"template<class T>class TPArrayIterator;template<class T>class TPArrayIteratorConst;template<class T>class TPArray{    	friend class TPArrayIterator<T>;	friend class TPArrayIteratorConst<T>;	    public:    	TPArray (const unsigned int);        TPArray (const TPArray<T>&);        virtual ~TPArray (void);								virtual void 								DeleteAll (void);		virtual void								DeleteIthItem (const unsigned int);		virtual void								DetachIthItem (const unsigned int, T*&);		virtual void 								Fill (const T&);				virtual bool								IsIthFilled (const unsigned int) const;		virtual TPArrayIterator<T>&					Iterator (void);		virtual TPArrayIteratorConst<T>&			IteratorConst (void) const;		virtual T&									IthItemRef (const unsigned int);				virtual const T&							IthItemRef (const unsigned int) const;					virtual void								MemCpy (const TPArray<T>&, const unsigned int);		virtual TPArray<T>& 						operator  = (const TPArray<T>&);				        virtual T& 									operator [] (const unsigned int); 		virtual const T& 							operator [] (const unsigned int) const;		virtual void								SetIthItem (const unsigned int, T*);				virtual void								SetIthItem (const unsigned int, const T&);						virtual unsigned int						Size (const bool filled = false) const;		virtual ostream&							Write (ostream&) const;			 protected:	 	TCounter									fFilled;				 	TArray<T*>*									fArray; };template<class T>class TPArrayIterator{	friend class TPArrayIteratorConst<T>;	public:	 		TPArrayIterator (TPArray<T>&);		TPArrayIterator (const TPArrayIterator<T>&);		virtual ~TPArrayIterator (void) { };		virtual bool								CurItem (const bool filled = false) const;		virtual bool								CurItem (T*& item, const bool filled = false) const;		virtual bool								FirstItem (const bool filled = false);		virtual bool								FirstItem (T*& item, const bool filled = false);		bool										IsReversible (void) const;		virtual bool								IthItem (const unsigned int, const bool filled = false) const;				virtual bool								IthItem (const unsigned int, T*& item, const bool filled = false) const;		virtual T&									IthItemRef (const unsigned int, const bool filled = false) const;		virtual bool								LastItem (const bool filled = false);		virtual bool								LastItem (T*& item, const bool filled = false);						virtual bool								NextItem (const bool filled = false);		virtual bool								NextItem (T*& item, const bool filled = false);		virtual T& 									operator [] (const unsigned int) const;				virtual bool								PrevItem (const bool filled = false);		virtual bool								PrevItem (T*& item, const bool filled = false);	protected:		TPArray<T>&									fPArray;		unsigned int								fCurItem;};template<class T>class TPArrayIteratorConst{	public:	  		TPArrayIteratorConst (const TPArray<T>&);		TPArrayIteratorConst (const TPArrayIterator<T>&);		TPArrayIteratorConst (const TPArrayIteratorConst<T>&);		virtual ~TPArrayIteratorConst (void) { };				virtual bool								CurItem (const bool filled = false) const;		virtual bool								CurItem (const T*& item, const bool filled = false) const;		virtual bool								FirstItem (const bool filled = false);		virtual bool								FirstItem (const T*& item, const bool filled = false);		bool										IsReversible (void) const;		virtual bool								IthItem (const unsigned int, const bool filled = false) const;				virtual bool								IthItem (const unsigned int, const T*& item, const bool filled = false) const;		virtual const T&							IthItemRef (const unsigned int, const bool filled = false) const;		virtual bool								LastItem (const bool filled = false);		virtual bool								LastItem (const T*& item, const bool filled = false);						virtual bool								NextItem (const bool filled = false);		virtual bool								NextItem (const T*& item, const bool filled = false);		virtual const T& 							operator [] (const unsigned int) const;				virtual bool								PrevItem (const bool filled = false);		virtual bool								PrevItem (const T*& item, const bool filled = false);	protected:		const TPArray<T>&							fPArray;		unsigned int								fCurItem;};template<class T>void TPArray<T>::DeleteAll (void){	for (unsigned int i = 0; i < Size () ; ++i)		DeleteIthItem (i+1);}template<class T>void TPArray<T>::DeleteIthItem (const unsigned int i){	T* item = NULL;	DetachIthItem (i, item);	delete item;}template<class T>inlinevoid TPArray<T>::DetachIthItem (const unsigned int i, T*& item){	if (fArray->IthItemRef (i) != NULL)	{		item = fArray->IthItemRef (i);		fArray->IthItemRef (i) = NULL;		fFilled.Decr ();	}}template<class T>void TPArray<T>::Fill (const T& item){	DeleteAll ();	for (unsigned int i = 0; i < Size(); ++i)	{		fArray->IthItemRef (i+1) = new T (item);		fFilled.Incr ();	}}template<class T>inlinebool TPArray<T>::IsIthFilled (const unsigned int i) const{	return ((bool)(fArray->IthItemRef (i) != NULL));}template<class T>inlineTPArrayIterator<T>& TPArray<T>::Iterator (void){	return (*(new TPArrayIterator<T> (*this)));}template<class T>inlineTPArrayIteratorConst<T>& TPArray<T>::IteratorConst (void) const{	return (*(new TPArrayIteratorConst<T> (*this)));}template<class T>T& TPArray<T>::IthItemRef (const unsigned int i){	if (fArray->IthItemRef (i) == NULL)	{		fArray->IthItemRef (i) = new T;		fFilled.Incr ();	}	return (*(fArray->IthItemRef (i)));}template<class T>	const T& TPArray<T>::IthItemRef (const unsigned int i) const{	if (fArray->IthItemRef (i) == NULL)	{		fArray->IthItemRef (i) = new T;		((TPArray<T>*)this)->fFilled.Incr ();	}	return (*(fArray->IthItemRef (i)));}template<class T>void TPArray<T>::MemCpy (const TPArray<T>& pArray, const unsigned int length){	CHECK (0 < length && length <= pArray.Size ());	const unsigned int minLength = min (length, Size ());	for (unsigned int i = 0; i < minLength; ++i)	{		if (fArray->IthItemRef (i+1) != NULL)		{			delete fArray->IthItemRef (i+1);			fFilled.Decr ();			fArray->IthItemRef (i+1) = NULL;		}			if (pArray.fArray->IthItemRef (i+1) != NULL)		{			fArray->IthItemRef (i+1) = new T (pArray[i]);			fFilled.Incr ();		}	}}template<class T>TPArray<T>&	TPArray<T>::operator = (const TPArray<T>& pArray){	MemCpy (pArray, pArray.Size ());	return (*this);}template<class T>inlineT& TPArray<T>::operator [] (const unsigned int i){   	return (IthItemRef (i+1));}template<class T>inlineconst T& TPArray<T>::operator [] (const unsigned int i) const{   	return (IthItemRef (i+1));}template<class T>void TPArray<T>::SetIthItem (const unsigned int i, T* item){	if (fArray->IthItemRef (i) != NULL)	{		delete fArray->IthItemRef (i);		fFilled.Decr ();	}	if (item != NULL)		fFilled.Incr ();	fArray->IthItemRef (i) = item;}template<class T>		inlinevoid TPArray<T>::SetIthItem (const unsigned int i, const T& item){	SetIthItem (i, new T (item));}template<class T>inlineunsigned int TPArray<T>::Size (const bool filled) const{	return filled ? ((unsigned int)(fFilled.GetCount ())) : (fArray->Size ());}template<class T>inlineTPArray<T>::TPArray (const unsigned int sz)	:	fFilled (){	fArray = new TArray<T*> (sz);	fArray->Fill (NULL);}template<class T>TPArray<T>::TPArray (const TPArray<T>& pArray)	:	fFilled (pArray.fFilled){	fArray = new TArray<T*> (pArray.Size ());	MemCpy (pArray, pArray.Size ());}template<class T>inlineTPArray<T>::~TPArray (void){	DeleteAll ();	delete fArray;}template<class T>ostream& TPArray<T>::Write (ostream& o) const{	for (unsigned int i = 0; i < Size (); ++i)		o << IthItemRef (i+1) << EOLN;	return (o);}	template<class T>	inlinebool TPArrayIterator<T>::CurItem (const bool filled) const{	return (IthItem (fCurItem, filled));}template<class T>inlinebool TPArrayIterator<T>::CurItem (T*& item, const bool filled) const{	return (IthItem (fCurItem, item, filled));}template<class T>inlinebool TPArrayIterator<T>::FirstItem (const bool filled){	return (IthItem (fCurItem = 1, filled));}template<class T>inlinebool TPArrayIterator<T>::FirstItem (T*& item, const bool filled){	return (IthItem (fCurItem = 1, item, filled));}template<class T>inlinebool TPArrayIterator<T>::IsReversible (void) const{	return (true);}template<class T>inlinebool TPArrayIterator<T>::IthItem (const unsigned int i, const bool filled) const{	return ((bool)(0 < i && i <= fPArray.Size (filled)));}	template<class T>inlinebool TPArrayIterator<T>::IthItem (const unsigned int i, T*& item, const bool filled) const{	if (IthItem (i, filled))	{		if (filled)		{			TCounter count;			unsigned int element = 0;			while (count.GetCount () < i)				if (fPArray.fArray->IthItemRef (++element) != NULL)					count.Incr ();			item = &(fPArray[element-1]);		}		else			item = &(fPArray[i-1]);				return (true);	}	return (false);}template<class T>inlineT& TPArrayIterator<T>::IthItemRef (const unsigned int i, const bool filled) const{	if (filled)	{			TCounter count;			unsigned int element = 0;			while (count.GetCount () < i)				if (fPArray.fArray->IthItemRef (++element) != NULL)					count.Incr ();			return (fPArray[element-1]);	}	else		return (fPArray[i-1]);}template<class T>inlinebool TPArrayIterator<T>::LastItem (const bool filled){	return (IthItem (fCurItem = fPArray.Size (filled), filled));}template<class T>inlinebool TPArrayIterator<T>::LastItem (T*& item, const bool filled){	return (IthItem (fCurItem = fPArray.Size (filled), item, filled));}				template<class T>inlinebool TPArrayIterator<T>::NextItem (const bool filled){	if (CurItem (filled))		return (IthItem (++fCurItem, filled));	return (false);}template<class T>inlinebool TPArrayIterator<T>::NextItem (T*& item, const bool filled){	if (CurItem (filled))		return (IthItem (++fCurItem, item, filled));	return (false);}template<class T>inlineT& TPArrayIterator<T>::operator [] (const unsigned int i) const{	return (IthItemRef (i+1, false));}		template<class T>inlinebool TPArrayIterator<T>::PrevItem (const bool filled){	if (CurItem (filled))		return (IthItem (--fCurItem, filled));	return (false);}template<class T>inlinebool TPArrayIterator<T>::PrevItem (T*& item, const bool filled){	if (CurItem (filled))		return (IthItem (--fCurItem, item, filled));	return (false);}template<class T>	TPArrayIterator<T>::TPArrayIterator (TPArray<T>& pArray)	: fPArray (pArray){	fCurItem = 1;}template<class T>	TPArrayIterator<T>::TPArrayIterator (const TPArrayIterator<T>& iterator)	: fPArray (iterator.fPArray){	fCurItem = iterator.fCurItem;}template<class T>	inlinebool TPArrayIteratorConst<T>::CurItem (const bool filled) const{	return (IthItem (fCurItem, filled));}template<class T>inlinebool TPArrayIteratorConst<T>::CurItem (const T*& item, const bool filled) const{	return (IthItem (fCurItem, item, filled));}template<class T>inlinebool TPArrayIteratorConst<T>::FirstItem (const bool filled){	return (IthItem (fCurItem = 1, filled));}template<class T>inlinebool TPArrayIteratorConst<T>::FirstItem (const T*& item, const bool filled){	return (IthItem (fCurItem = 1, item, filled));}template<class T>inlinebool TPArrayIteratorConst<T>::IsReversible (void) const{	return (true);}template<class T>inlinebool TPArrayIteratorConst<T>::IthItem (const unsigned int i, const bool filled) const{	return ((bool)(0 < i && i <= fPArray.Size (filled)));}	template<class T>inlinebool TPArrayIteratorConst<T>::IthItem (const unsigned int i, const T*& item, const bool filled) const{	if (IthItem (i, filled))	{		if (filled)		{			TCounter count;			unsigned int element = 0;			while (count.GetCount () < i)				if (fPArray.fArray->IthItemRef (++element) != NULL)					count.Incr ();			item = &(fPArray[element-1]);		}		else			item = &(fPArray[i-1]);				return (true);	}	return (false);}template<class T>inlineconst T& TPArrayIteratorConst<T>::IthItemRef (const unsigned int i, const bool filled) const{	if (filled)	{			TCounter count;			unsigned int element = 0;			while (count.GetCount () < i)				if (fPArray.fArray->IthItemRef (++element) != NULL)					count.Incr ();			return (fPArray[element-1]);	}	else		return (fPArray[i-1]);}template<class T>inlinebool TPArrayIteratorConst<T>::LastItem (const bool filled){	return (IthItem (fCurItem = fPArray.Size (), filled));}template<class T>inlinebool TPArrayIteratorConst<T>::LastItem (const T*& item, const bool filled){	return (IthItem (fCurItem = fPArray.Size (), item, filled));}				template<class T>inlinebool TPArrayIteratorConst<T>::NextItem (const bool filled){	if (CurItem (filled))		return (IthItem (++fCurItem, filled));	return (false);}template<class T>inlinebool TPArrayIteratorConst<T>::NextItem (const T*& item, const bool filled){	if (CurItem (filled))		return (IthItem (++fCurItem, item, filled));	return (false);}template<class T>inlineconst T& TPArrayIteratorConst<T>::operator [] (const unsigned int i) const{	return (IthItemRef (i+1, false));}		template<class T>inlinebool TPArrayIteratorConst<T>::PrevItem (const bool filled){	if (CurItem (filled))		return (IthItem (--fCurItem, filled));	return (false);}template<class T>inlinebool TPArrayIteratorConst<T>::PrevItem (const T*& item, const bool filled){	if (CurItem (filled))		return (IthItem (--fCurItem, item, filled));	return (false);}template<class T>	TPArrayIteratorConst<T>::TPArrayIteratorConst (const TPArray<T>& pArray)	: fPArray (pArray){	fCurItem = 1;}template<class T>	TPArrayIteratorConst<T>::TPArrayIteratorConst (const TPArrayIterator<T>& iterator)	: fPArray (iterator.fPArray){	fCurItem = iterator.fCurItem;}template<class T>	TPArrayIteratorConst<T>::TPArrayIteratorConst (const TPArrayIteratorConst<T>& iterator)	: fPArray (iterator.fPArray){	fCurItem = iterator.fCurItem;}#endif // _TPARRAY_H