#ifndef _RADPRINT_H#define _RADPRINT_H#include "VPort.h"#include "VApp.h"#include "VPrevDlg.h"#include "TTreesFile.h"//#include "Tree.h"//#include "Profile.h"// Dialogs#define id_preview_dialog 	300#define id_layout_dialog 	301//#define id_fonts_dialog 	302// Preview dialog/*#define id_radialtree 		12#define id_cladogram 		13#define id_rectangle 		14#define id_phylogram 		15#define id_1pt 				16#define id_2pt 				17#define id_3pt 				18#define id_internals 		19#define id_order 			20*/#define id_leaf_font 		id_preview_font/*#define id_edge_font 	21*/// Layout dialog#define id_shownames 		12#define id_rows 			4#define id_cols 			5#define id_total 			7#define id_left_right 		10#define id_top_bottom 		11#define id_grid 			14// Order dialog//#define id_default_order	4 //#define id_left_order 		5//#define id_right_order 		6//------------------------------------------------------------------------------// Print preview to display >= 1 tree per page (i.e., we can print the whole profile)class VPrintTreeDialog : public VPreviewDialog{public:	VPrintTreeDialog ();	virtual ~VPrintTreeDialog ();	virtual BOOL DoTreesPerPage ();//	virtual BOOL DoTreeStyle (int item);	//	virtual BOOL DoLineStyle (int item);	virtual BOOL DoFont (int item);//	virtual BOOL DoOrder () ;//	virtual BOOL DoInternals ();////	virtual void Setup (TTreesFile*, const TTreeStyle& treeStyle); // pass your pointer	virtual int GetNumRows () { return rows; };	virtual int GetNumCols () { return cols; };//	virtual unsigned int GetTreeStyle () { return TreeStyle; };	virtual BOOL GetArrangement () { return (BOOL) (arrangementItem = id_left_right); };	virtual VFontPtr GetLeafFont () { return font; };//	virtual VFontPtr GetEdgeFont () { return edgeFont; };//	virtual int GetLineWidth () { return lineWidth; };	virtual void Print ();	virtual void GetPicture (PictureTool &pic);protected:	int rows;	int cols;	int pages;	bool fDrawTreeNames;//	BOOL ShowNames;		TTreeStyle 		fTreeStyle;//	unsigned int TreeStyle;//	int treeItem;//	int numtrees;	//	ProfilePtr P;		VFontPtr font;//   	VFontPtr edgeFont; // 	LadderType ladder;//	LadderType SavedLadder;//	int lineWidth;//	int lineItem;	int arrangementItem;		// Fonts//	MenuHandle menu;	// Your stuff	TTreesFile*			fTreesFile;private:	BOOL Changed;};typedef VPrintTreeDialog *VPrintTreeDialogPtr;#endif // _RADPRINT_H