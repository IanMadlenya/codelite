#ifndef __new_quick_watch_dlg__
#define __new_quick_watch_dlg__

/**
@file
Subclass of NewQuickWatch, which is generated by wxFormBuilder.
*/

#include "newquickwatch.h"
#include <wx/timer.h>
#include "debugger.h"
#include <map>

class wxTimer;

/** Implementing NewQuickWatch */
class DisplayVariableDlg : public NewQuickWatch
{
public:
	IDebugger*                       m_debugger;
	std::map<wxString, wxTreeItemId> m_gdbId2Item;
	std::map<wxString, wxTreeItemId> m_gdbId2ItemLeaf;
	wxString                         m_mainVariableObject;
	wxString                         m_variableName;
	wxTimer*                         m_timer;
	wxTimer*                         m_timer2;
	bool                             m_leftWindow;
	wxString                         m_fullpath;
	wxTreeItemId                     m_hoveredItem;
	long                             m_showExtraFormats;
	wxCursor                         m_cursor;

protected:
	bool     IsFakeItem(const wxTreeItemId &item);
	wxString DoGetItemPath(const wxTreeItemId &item);
	void     DoAdjustPosition();

protected:
	// Handlers for NewQuickWatch events.
	void OnExpandItem  ( wxTreeEvent& event );
	void OnItemExpanded( wxTreeEvent& event );
	void OnBtnCancel(wxCommandEvent &e);
	void OnCloseEvent(wxCloseEvent &e);
	void DoAddChildren(wxTreeItemId &item, const VariableObjChildren &children);
	void OnKeyDown(wxKeyEvent &event);
	void DoCleanUp();
	void OnLeftDown(wxMouseEvent &e);
	void OnMouseLeaveWindow(wxMouseEvent &e);
	void OnMouseEnterWindow(wxMouseEvent &e);
	void OnTimer(wxTimerEvent &e);
	void OnTimer2(wxTimerEvent &e);
	void OnItemMenu(wxTreeEvent& event);
	void OnMenuSelection(wxCommandEvent &e);
	void OnMouseMove( wxMouseEvent& event );
	void OnShowHexAndBinFormat(wxCommandEvent& event);

public:
	/** Constructor */
	DisplayVariableDlg( wxWindow* parent);
	virtual ~DisplayVariableDlg();

	void AddItems   ( const wxString &varname, const VariableObjChildren &children);
	void UpdateValue( const wxString &varname, const wxString &value, DisplayFormat displayFormat);
	void BuildTree  (const VariableObjChildren &children, IDebugger *debugger);
	void HideDialog ();
	void ShowDialog (bool center);

};

#endif // __new_quick_watch_dlg__
