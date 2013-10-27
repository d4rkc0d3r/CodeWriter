#include "wx_pch.h"
#include "Replace.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(Replace)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(Replace)
//*)

//(*IdInit(Replace)
const long Replace::ID_STATICTEXT1 = wxNewId();
const long Replace::ID_TEXTCTRL1 = wxNewId();
const long Replace::ID_STATICTEXT2 = wxNewId();
const long Replace::ID_TEXTCTRL2 = wxNewId();
const long Replace::ID_BUTTON1 = wxNewId();
const long Replace::ID_BUTTON2 = wxNewId();
const long Replace::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Replace,wxDialog)
	//(*EventTable(Replace)
	//*)
END_EVENT_TABLE()

Replace::Replace(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(Replace)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Text to Replace"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextToReplace = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(TextToReplace, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Replace with"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextReplaceWith = new wxTextCtrl(Panel1, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer1->Add(TextReplaceWith, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonReplace = new wxButton(Panel1, ID_BUTTON1, _("Replace"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	ButtonReplace->SetDefault();
	FlexGridSizer1->Add(ButtonReplace, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(Panel1, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer1->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(Panel1);
	FlexGridSizer1->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Replace::OnButtonReplaceClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Replace::OnButton2Click);
	//*)
	this->SetTitle(wxT("Replace..."));
}

Replace::~Replace()
{
	//(*Destroy(Replace)
	//*)
}

void Replace::OnButtonReplaceClick(wxCommandEvent& event)
{
    wxString tmp=GetOld();
    if(tmp.IsEmpty())
        EndModal(EXIT_FAILURE);
    EndModal(EXIT_SUCCESS);
}

void Replace::OnButton2Click(wxCommandEvent& event)
{
    EndModal(EXIT_FAILURE);
}

wxString Replace::GetOld()
{
    return TextToReplace->GetValue();
}

wxString Replace::GetNew()
{
    return TextReplaceWith->GetValue();
}
