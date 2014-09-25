#include "CP2List.h"//-----------------------------------------------------------------------------CPTwoListDialog::~CPTwoListDialog (){	// delete LeftList; // JLT 010417	// delete RightList; // JLT 010417}//-----------------------------------------------------------------------------void CPTwoListDialog::Setup (){#ifdef Macintosh	LeftList = new VListBox (this, id_LeftList);#else	LeftList = new VListBox;   this->Associate (LeftList, id_LeftList);#endif	LeftList->Append ("alpha");	LeftList->Append ("beta");	LeftList->Append ("gamma");	LeftList->Append ("delta");#ifdef Macintosh	RightList = new VListBox (this, id_RightList);#else	RightList = new VListBox;   this->Associate (RightList, id_RightList);#endif	RightList->Append ("aus");	RightList->Append ("bus b");	RightList->Append ("cus");	RightList->Append ("dus");}//-----------------------------------------------------------------------------BOOL CPTwoListDialog::DoItem (int item){	BOOL processed = TRUE;		int n;		switch (item)	{			case id_LeftList:#ifdef Macintosh			switch (LeftList->GetStatus ())#else			switch (GetItemMsg ())#endif			{				case VLIST_SELECTION_CHANGE:					EnableItem (id_Left_To_Right, (BOOL) (LeftList->GetNumSelections () > 0));						break;									case VLIST_DOUBLE_CLICK:					// Move selection to other list					LeftList->MoveSelection (RightList);					// Move Button					EnableItem (id_Left_To_Right, 						(BOOL)((LeftList->GetNumItems () > MinInLeftList) && 						(LeftList->GetNumSelections () > 0)));						// All buttons							EnableItem (id_All_Left, (BOOL)(LeftList->GetNumItems () > 0));					EnableItem (id_All_Right, (BOOL)(RightList->GetNumItems () > 0));					break;					default:					EnableItem (id_Left_To_Right, (BOOL) (LeftList->GetNumSelections () > 0));						break;			}			break;					case id_RightList:#ifdef Macintosh			switch (RightList->GetStatus ())#else			switch (GetItemMsg ())#endif			{				case VLIST_SELECTION_CHANGE:					EnableItem (id_Right_To_Left, (BOOL) (RightList->GetNumSelections () > 0));						break;									case VLIST_DOUBLE_CLICK:					// Move selection to other list					RightList->MoveSelection (LeftList);					// Move Button					EnableItem (id_Right_To_Left, 						(BOOL)((RightList->GetNumItems () > 0) && 						(RightList->GetNumSelections () > 0)));						// All buttons							EnableItem (id_All_Left, (BOOL)(LeftList->GetNumItems () > 0));					EnableItem (id_All_Right, (BOOL)(RightList->GetNumItems () > 0));					break;										default:					EnableItem (id_Right_To_Left, (BOOL) (RightList->GetNumSelections () > 0));						break;			}			break;								case id_Left_To_Right:			n = LeftList->MoveSelection (RightList);			EnableItem (item, (BOOL)((LeftList->GetNumItems () > MinInLeftList) 				&& (LeftList->GetNumSelections () > 0)));						EnableItem (id_All_Left, (BOOL)(LeftList->GetNumItems () > 0));			EnableItem (id_All_Right, (BOOL)(RightList->GetNumItems () > 0));			break;				case id_Right_To_Left:			n = RightList->MoveSelection (LeftList);			EnableItem (item, (BOOL)((RightList->GetNumItems () > 0) && (RightList->GetNumSelections () > 0)));						EnableItem (id_All_Left, (BOOL)(LeftList->GetNumItems () > 0));			EnableItem (id_All_Right, (BOOL)(RightList->GetNumItems () > 0));			break;					case id_All_Left:			LeftList->SelectAll ();			EnableItem (id_Left_To_Right, TRUE);			break;               		case id_All_Right:			RightList->SelectAll ();			EnableItem (id_Right_To_Left, TRUE);			break;               									default:			processed = FALSE;			break;	}		// Left list needs a minimum of elements	EnableItem (ok, (BOOL)(LeftList->GetNumItems () >= MinInLeftList)); 	return processed;}