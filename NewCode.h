#ifndef NEWCODE_H
#define NEWCODE_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(NewCode)
	#include <wx/sizer.h>
	#include <wx/textctrl.h>
	#include <wx/button.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(NewCode)
//*)

#define ACCEPT 227

class NewCode: public wxDialog
{
	public:

		NewCode(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewCode();

		void SetCode(const wxString& newcode);
		wxString GetCode();

	protected:

		//(*Identifiers(NewCode)
		static const long ID_TEXTCTRL;
		static const long ID_BUTTON;
		//*)

	private:

		//(*Handlers(NewCode)
		void OnButtonAcceptClick(wxCommandEvent& event);
		//*)

		//(*Declarations(NewCode)
		wxButton* ButtonAccept;
		wxTextCtrl* TextCode;
		//*)

		wxString Code;

		DECLARE_EVENT_TABLE()
};

#endif
