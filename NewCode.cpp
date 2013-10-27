#include "wx_pch.h"
#include "NewCode.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(NewCode)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(NewCode)
//*)

//(*IdInit(NewCode)
const long NewCode::ID_TEXTCTRL = wxNewId();
const long NewCode::ID_BUTTON = wxNewId();
//*)

BEGIN_EVENT_TABLE(NewCode,wxDialog)
	//(*EventTable(NewCode)
	//*)
END_EVENT_TABLE()

NewCode::NewCode(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NewCode)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Enter new code"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(505,374));
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	TextCode = new wxTextCtrl(this, ID_TEXTCTRL, _("default"), wxDefaultPosition, wxSize(88,21), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL"));
	FlexGridSizer1->Add(TextCode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonAccept = new wxButton(this, ID_BUTTON, _("Accept"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON"));
	FlexGridSizer1->Add(ButtonAccept, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewCode::OnButtonAcceptClick);
	//*)

	Code=wxT("28061994");
}

NewCode::~NewCode()
{
	//(*Destroy(NewCode)
	//*)
}

void NewCode::SetCode(const wxString& newcode)
{
    Code=newcode;
    if(Code!=wxT("28061994"))
        TextCode->SetValue(Code);
}

wxString NewCode::GetCode()
{
    if(!Code.IsNumber()||Code.IsEmpty())
        Code=wxT("28061994");
    return Code;
}

void NewCode::OnButtonAcceptClick(wxCommandEvent& event)
{
    if(TextCode->GetValue()!=wxT("default"))
        Code=TextCode->GetValue();
    else
        Code=wxT("28061994");
    EndModal(ACCEPT);
}
