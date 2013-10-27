#ifndef REPLACE_H
#define REPLACE_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(Replace)
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	#include <wx/panel.h>
	#include <wx/button.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(Replace)
//*)

class Replace: public wxDialog
{
	public:

		Replace(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~Replace();

		wxString GetOld();
		wxString GetNew();

		//(*Declarations(Replace)
		wxButton* ButtonReplace;
		wxStaticText* StaticText2;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxTextCtrl* TextToReplace;
		wxButton* Button2;
		wxTextCtrl* TextReplaceWith;
		//*)

	protected:

		//(*Identifiers(Replace)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(Replace)
		void OnButtonReplaceClick(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
