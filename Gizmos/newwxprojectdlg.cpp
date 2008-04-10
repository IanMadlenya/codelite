#include "wx/xrc/xmlres.h"
#include "imanager.h"
#include "newwxprojectdlg.h"
#include "wx/msgdlg.h"
#include "workspace.h"

NewWxProjectDlg::NewWxProjectDlg( wxWindow* parent, IManager *mgr  )
: NewWxProjectBaseDlg( parent )
, m_mgr(mgr)
{
	m_bitmap1->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("wx_project_header")));
	m_choiceApplicationType->SetSelection(wxProjectTypeGUI);
	m_dirPicker->SetPath(m_mgr->GetWorkspace()->GetWorkspaceFileName().GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR));

#if defined (__WXMSW__)	
	m_checkBoxMWindows->SetValue(true);
#else
	m_checkBoxMWindows->SetValue(false);
	m_checkBoxMWindows->Enable(false);
#endif

}

void NewWxProjectDlg::OnButtonCancel(wxCommandEvent &e)
{
	EndModal(wxID_CANCEL);
}

void NewWxProjectDlg::OnButtonOK(wxCommandEvent &e)
{
	wxUnusedVar(e);
	if(ValidateInput()){
		EndModal(wxID_OK);
	}
}

bool NewWxProjectDlg::ValidateInput()
{
	if(m_textCtrlName->GetValue().IsEmpty()){
		wxString msg;
		msg << wxT("Invalid project name '") << m_textCtrlName->GetValue() << wxT("'\n");
		msg << wxT("Valid characters for project name are [0-9A-Za-z_]");
		wxMessageBox(msg, wxT("CodeLite"), wxICON_WARNING|wxOK);
		return false;
	}
	
	if(m_textCtrlName->GetValue().find_first_not_of(wxT("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_")) != wxString::npos){
		wxString msg;
		msg << wxT("Invalid project name '") << m_textCtrlName->GetValue() << wxT("'\n");
		msg << wxT("Valid characters for project name are [0-9A-Za-z_]");
		wxMessageBox(msg, wxT("CodeLite"), wxICON_WARNING|wxOK);
		return false;
	}
	return true;
}

void NewWxProjectDlg::GetProjectInfo(NewWxProjectInfo &info)
{
	size_t flag = 0;
	
	if(m_checkBoxMWindows->IsChecked()){
		flag |= wxWidgetsSetMWindows;
	}

	if(m_checkBoxUnicode->IsChecked()){
		flag |= wxWidgetsUnicode;
	}
	
	info.SetFlags(flag);
	info.SetType(m_choiceApplicationType->GetSelection());
	info.SetName(m_textCtrlName->GetValue());
	info.SetPath(m_dirPicker->GetPath());
}

void NewWxProjectDlg::OnChoiceChanged(wxCommandEvent &e)
{
#ifdef __WXMSW__
	if(e.GetSelection() == 1) {	//Simple main with wxWidgets enabled
		m_checkBoxMWindows->SetValue(false);
		m_checkBoxMWindows->Enable(false);
	} else {
		m_checkBoxMWindows->Enable(true);
	}
#else
	wxUnusedVar(e);
#endif
}
