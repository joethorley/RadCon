// FileName: Flags.h/****************************************************************************  	COMPONENT C++ translation                                             	*  	(c) 1993, Roderic D. M. Page                                          	*      All rights reserved  *		File: flags.h                                             	*	 Purpose: bitmask flags                                               	*     History: 15 June 1993                                               	***************************************************************************//***************************************************************************	MODIFICATIONS	(c) 1998, Joseph L. Thorley		All rights reserved	File:	Purpose:	History: 24/4/98****************************************************************************/#ifndef _TFLAGS_H#define _TFLAGS_Htypedef int Flags;class TFlags {	public:		TFlags (void);		virtual ~TFlags (void);				virtual bool 			IsFlag (const Flags f) const;		virtual void 			SetFlag (const Flags f, const bool on = true) const;			private:		Flags 					fFlags;};#endif // _TFLAGS_H