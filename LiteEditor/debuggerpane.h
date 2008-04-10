#ifndef DEBUGGERPANE_H
#define DEBUGGERPANE_H

#include "wx/panel.h"
#include "custom_notebook.h"
#include <wx/imaglist.h>

class ListCtrlPanel;
class LocalVarsTree;
class SimpleTable;
class BreakpointDlg;
class ThreadListPanel;

class DebuggerPane : public wxPanel
{
public:
	static const wxString LOCALS;
	static const wxString WATCHES;
	static const wxString FRAMES;
	static const wxString BREAKPOINTS;
	static const wxString THREADS;

private:
	Notebook *m_book;
	LocalVarsTree *m_localsTree;
	wxString m_caption;
	SimpleTable *m_watchesTable;
	ListCtrlPanel *m_frameList;
	BreakpointDlg *m_breakpoints;
	ThreadListPanel *m_threads;
	
private:
	void CreateGUIControls();
	void OnPageChanged(NotebookEvent &event);

public:
	DebuggerPane(wxWindow *parent, const wxString &caption);
	virtual ~DebuggerPane();

	//setters/getters
	const wxString &GetCaption() const{return m_caption;}
	LocalVarsTree *GetLocalsTree() {return m_localsTree;}
	SimpleTable *GetWatchesTable(){return m_watchesTable;}
	ListCtrlPanel *GetFrameListView(){return m_frameList;}
	BreakpointDlg *GetBreakpointView(){return m_breakpoints;}
	ThreadListPanel *GetThreadsView(){return m_threads;}
	Notebook *GetNotebook(){return m_book;}
	void SelectTab(const wxString &tabName);
	void Clear();
	
	DECLARE_EVENT_TABLE()
	void OnEraseBg(wxEraseEvent &e);
	void OnPaint(wxPaintEvent &e);
	void OnSize(wxSizeEvent &e);
};
#endif //DEBUGGERPANE_H

