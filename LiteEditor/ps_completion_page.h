#ifndef __ps_completion_page__
#define __ps_completion_page__

/**
@file
Subclass of PSCompletionBase, which is generated by wxFormBuilder.
*/

#include "project_settings_base_dlg.h"
#include "project_settings_dlg.h"

class ProjectSettingsDlg;

//// end generated include

/** Implementing PSCompletionBase */
class PSCompletionPage : public PSCompletionBase, public IProjectSettingsPage
{
protected:
	ProjectSettingsDlg* m_dlg;
	bool                m_ccSettingsModified;
	
protected:
	// Handlers for PSCompletionBase events.
	void OnCmdEvtVModified( wxCommandEvent& event );
public:
	/** Constructor */
	PSCompletionPage( wxWindow* parent, ProjectSettingsDlg* dlg );
	//// end generated class members

	virtual void Clear();
	virtual void Load(BuildConfigPtr buildConf);
	virtual void Save(BuildConfigPtr buildConf, ProjectSettingsPtr projSettingsPtr);

};

#endif // __ps_completion_page__
