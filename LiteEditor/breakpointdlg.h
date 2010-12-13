//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : breakpointdlg.h
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
 #ifndef __breakpointdlg__
#define __breakpointdlg__

/**
@file
Subclass of BreakpointDlgBase, which is generated by wxFormBuilder.
@todo Add your event handlers directly to this file.
*/

#include "breakpoint_dlg_base.h"
#include "breakpointsmgr.h"

// Since a breakpoint will always have an internal id, but a valid debugger one only when the debugger's running, store both here
struct bpd_IDs
{
	int debugger_id;
	int internal_id;
	bpd_IDs(const BreakpointInfo& bp) { debugger_id = bp.debugger_id; internal_id = bp.internal_id; }
	// If the debugger is running, debugger_id will (should) be >0. Otherwise use the internal_id
	int GetBestId() { return debugger_id == -1 ? internal_id : debugger_id; }
	wxString GetIdAsString()	// Internal IDs start at FIRST_INTERNAL_ID + 1, == 10001
		{	int id = (GetBestId() > FIRST_INTERNAL_ID ? GetBestId()-FIRST_INTERNAL_ID : GetBestId());
			wxString idstr; idstr << id; return idstr;
		}
};

class BreakpointsListctrl : public wxListCtrl
{
	enum column_ids { col_id, col_type, col_enabled, col_file, col_lineno, col_functionname, col_at, col_memory, col_what, col_ignorecount, col_extras };
public:
	BreakpointsListctrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxLC_REPORT | wxLC_SINGLE_SEL)
		: wxListCtrl(parent, id, pos, size, style)
		{
			const wxChar* column_headers[] =
			{
				_("ID"),
				_("Type"),
				_("Enabled"),
				_("File"),
				_("Line"),
				_("Function"),
				_("At"),
				_("Memory"),
				_("What"),
				_("Ignored"),
				_("Extras")
			};

			for (int n=col_id; n <= col_extras;++n) {
				InsertColumn(n, column_headers[n]);
			}

			SetColumnWidth(col_id  ,         50);
			SetColumnWidth(col_type,         100);
			SetColumnWidth(col_enabled,      100);
			SetColumnWidth(col_file,         300);
			SetColumnWidth(col_lineno,       100);
			SetColumnWidth(col_functionname, 100);
			SetColumnWidth(col_at,           100);
			SetColumnWidth(col_memory,       100);
			SetColumnWidth(col_what,         100);
			SetColumnWidth(col_ignorecount,  50);
			SetColumnWidth(col_extras,       50);
		}

	void Initialise(std::vector<BreakpointInfo>& bps);
	int GetSelection();
	int GetLinenoColumn() {
		return col_lineno;
	}
	int GetFileColumn() {
		return col_file;
	}
};

/** Implementing BreakpointDlgBase */
class BreakpointDlg : public BreakpointTab
{
	long m_selectedItem;
protected:
	void OnAdd(wxCommandEvent &e);
	void OnEdit(wxCommandEvent &e);
	void OnDelete(wxCommandEvent &e);
	void OnDeleteAll(wxCommandEvent &e);
	void OnApplyPending(wxCommandEvent &e);
	void OnItemActivated(wxListEvent &e);
	void OnItemSelected(wxListEvent &e);
	void OnItemDeselected(wxListEvent &e);
	void OnItemRightClick(wxListEvent& e);

	std::vector<bpd_IDs> m_ids;

public:
	/** Constructor */
	BreakpointDlg( wxWindow* parent );
	void Initialize();
};

#endif // __breakpointdlg__
