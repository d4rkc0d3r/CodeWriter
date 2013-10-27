/***************************************************************
 * Name:      CodeWriterMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Max Heller (max.heller94@web.de)
 * Created:   2010-12-14
 * Copyright: Max Heller ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "CodeWriterMain.h"
#include "SizeofFile.h"
#include "NewCode.h"
#include "Replace.h"
#include "Convert.h"
#include <wx/msgdlg.h>
#include <wx/fontdlg.h>

//(*InternalHeaders(CodeWriterFrame)
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/wfstream.h>
//*)
#include <wx/txtstrm.h>


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(CodeWriterFrame)
const long CodeWriterFrame::idMenuOpen = wxNewId();
const long CodeWriterFrame::idMenuSave = wxNewId();
const long CodeWriterFrame::idMenuSaveAs = wxNewId();
const long CodeWriterFrame::idMenuQuit = wxNewId();
const long CodeWriterFrame::idMenuCode = wxNewId();
const long CodeWriterFrame::idMenuAbout = wxNewId();
const long CodeWriterFrame::ID_TIMER1 = wxNewId();
const long CodeWriterFrame::ID_PANEL1 = wxNewId();
const long CodeWriterFrame::ID_TEXTCTRL1 = wxNewId();
const long CodeWriterFrame::ID_UNEASYLEET = wxNewId();
const long CodeWriterFrame::ID_UNFULLLEET = wxNewId();
const long CodeWriterFrame::ID_EASYLEET = wxNewId();
const long CodeWriterFrame::ID_FULLLEET = wxNewId();
const long CodeWriterFrame::ID_NONE = wxNewId();
const long CodeWriterFrame::ID_REPLACE = wxNewId();
const long CodeWriterFrame::ID_LOWER = wxNewId();
const long CodeWriterFrame::ID_UPPER = wxNewId();
const long CodeWriterFrame::ID_DELSPACING = wxNewId();
const long CodeWriterFrame::ID_MAKELITERAL = wxNewId();
const long CodeWriterFrame::ID_PARSELITERAL = wxNewId();
//*)

BEGIN_EVENT_TABLE(CodeWriterFrame,wxFrame)
    //(*EventTable(CodeWriterFrame)
    //*)
END_EVENT_TABLE()

CodeWriterFrame::CodeWriterFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(CodeWriterFrame)
    wxMenuBar* MenuBar;
    wxMenu* MenuFile;
    wxMenu* MenuHelp;
    wxMenu* MenuLeet;
    wxMenu* MenuEdit;

    Create(parent, id, _("Code::Writer 3.1.2"), wxDefaultPosition, wxSize(816,636), wxDEFAULT_FRAME_STYLE, _T("id"));

    MenuBar = new wxMenuBar();

    MenuFile = new wxMenu();
    MenuFile->Append(idMenuOpen,_("Open file\tCtrl-O"));
    MenuFile->Append(idMenuSave,_("Save file\tCtrl-S"));
    MenuFile->Append(idMenuSaveAs,_("Save file as..."));
    MenuFile->AppendSeparator();
    MenuFile->Append(idMenuCode,_("Change code\tCtrl-K"));
    MenuFile->AppendSeparator();
    MenuFile->Append(idMenuQuit,_("Quit\tAlt-F4"));
    MenuBar->Append(MenuFile,_("&File"));

    MenuEdit = new wxMenu();
    MenuEdit->Append(ID_UPPER,_("Upper Case\tCtrl-U"));
    MenuEdit->Append(ID_LOWER,_("Lower Case\tCtrl-L"));
    MenuEdit->AppendSeparator();
    MenuEdit->Append(ID_DELSPACING,_("Delete Spacing\tCtrl-D"));
    MenuEdit->Append(ID_MAKELITERAL,_("Make Literal\tCtrl-M"));
    MenuEdit->Append(ID_PARSELITERAL,_("Parse Literal\tCtrl-P"));
    MenuEdit->AppendSeparator();
    MenuEdit->Append(ID_REPLACE,_("Replace\tCtrl-R"));
    MenuBar->Append(MenuEdit,_("&Edit"));

    MenuLeet = new wxMenu();
    MenuLeet->Append(ID_FULLLEET,_("Full Leet\tF1"));
    MenuLeet->Append(ID_UNFULLLEET,_("Un-Full Leet\tF2"));
    MenuLeet->AppendSeparator();
    MenuLeet->Append(ID_EASYLEET,_("Easy Leet\tF3"));
    MenuLeet->Append(ID_UNEASYLEET,_("Un-Easy Leet\tF4"));
    MenuBar->Append(MenuLeet,_("&Leet"));

    MenuHelp = new wxMenu();
    MenuHelp->Append(idMenuAbout,_("About\tAlt-F1"));
    MenuBar->Append(MenuHelp,_("&Help"));

    SetMenuBar(MenuBar);

    TimerResize = new wxTimer;
    TimerResize->SetOwner(this, ID_TIMER1);
    Panel = new wxPanel(this,ID_PANEL1,wxPoint(96,312),wxDefaultSize,wxTAB_TRAVERSAL,_T("ID_PANEL1"));
    TextFeld = new wxTextCtrl(Panel, ID_TEXTCTRL1, wxEmptyString, wxPoint(1,0), this->GetClientSize()-wxSize(2,1), wxTE_MULTILINE|wxTE_RICH, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    wxFont TextOutFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    TextFeld->SetFont(TextOutFont);
    TimerResize->Start(20,false);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnAbout);
    Connect(idMenuOpen,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnOpen);
    Connect(idMenuSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnSave);
    Connect(idMenuSaveAs,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnSaveAs);
    Connect(idMenuCode,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnCode);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&CodeWriterFrame::OnTimerResize);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CodeWriterFrame::OnTextChange);
    Connect(ID_EASYLEET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnEasyLeet);
    Connect(ID_FULLLEET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnFullLeet);
    Connect(ID_UNEASYLEET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnUnEasyLeet);
    Connect(ID_UNFULLLEET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnUnFullLeet);
    Connect(ID_REPLACE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnReplace);
    Connect(ID_UPPER,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnUpper);
    Connect(ID_LOWER,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnLower);
    Connect(ID_DELSPACING,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnDelSpacing);
    Connect(ID_MAKELITERAL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnMakeLiteral);
    Connect(ID_PARSELITERAL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CodeWriterFrame::OnParseLiteral);

    LogLevel=5;
    currentPW = NULL;
    old=this->GetClientSize();
    code=wxT("28061994");
    title=this->GetTitle();
    this->SetSizeHints(wxSize(300,200));
    CurrentFile=wxT("new.txt");
    wxString tmp(GetCommandLine(),wxConvUTF8);
    CmdLine=tmp;
    CurrentDir=tmp.SubString(tmp.Find(wxT(":\\")-1),tmp.Find(wxT("CodeWriter.exe")-1));
    Log(CmdLine,2);
    if(tmp.Find(wxT(".exe"))!=wxNOT_FOUND)
    {
        if(tmp.Find(wxT(".exe\" "))!=wxNOT_FOUND)
            tmp=tmp.Mid(tmp.Find(wxT(".exe\" "))+6);
        else
            tmp=tmp.Mid(tmp.Find(wxT(".exe "))+5);
        Open(tmp);
    }
    LastSave=TextFeld->GetValue();
    RefreshTitle();
    this->Center();
    //this->WarpPointer(this->GetClientSize().x/2,this->GetClientSize().y/2);
    //*)
}

CodeWriterFrame::~CodeWriterFrame()
{
    //(*Destroy(CodeWriterFrame)
    //*)
}

void CodeWriterFrame::OnQuit(wxCommandEvent& event)
{
    //if(wxMessageBox(wxT("Moechten sie das Programm wirklich beenden?"),wxT("Frage"),wxYES_NO)==wxYES)
        Close();
}

void CodeWriterFrame::Log(wxString line,int level)
{
    if (level<LogLevel)
        return;
    FILE* pLog = fopen(WX_TO_C(CurrentDir+wxT("CodeWriter.log")),"a");
    fprintf(pLog, "%s\n", line.ToUTF8().data());
    fclose(pLog);
}

void CodeWriterFrame::OnCode(wxCommandEvent& event)
{
    NewCode* dlg = new NewCode(this);
    dlg->SetCode(code);
    if(dlg->ShowModal()==ACCEPT)
    {
        code=dlg->GetCode();
        dlg->Destroy();
        delete dlg;
        this->RefreshTitle();
    }
}

void CodeWriterFrame::OnTextChange(wxCommandEvent& event)
{
    TextFeld->SetModified(LastSave != TextFeld->GetValue());
    RefreshTitle();
}

void CodeWriterFrame::OnReplace(wxCommandEvent& event)
{
    Replace* dlg = new Replace(this);
    if(dlg->ShowModal()!=EXIT_SUCCESS)
        return;
    wxString data=TextFeld->GetValue();
    data.Replace(dlg->GetOld(),dlg->GetNew());
    TextFeld->SetValue(data);
    dlg->Destroy();
}

void CodeWriterFrame::RefreshTitle()
{
    wxString buf=CurrentFile;
    if(!buf.IsEmpty())
        buf=buf.AfterLast('\\')+wxT(" - ");
    if(TextFeld->IsModified())
        buf=EDITED+buf;
    if(code!=wxT("28061994"))
        this->SetTitle(buf+title+wxT(" - ")+code);
    else
        this->SetTitle(buf+title);
}

void CodeWriterFrame::OnSaveAs(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save your data"), wxT(""), wxT(""),
                     wxT(""), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    dlg.SetPath(CurrentFile);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    CurrentFile=dlg.GetPath();
    OnSave(event);
    wxMessageBox(wxT("Die Datei\n")+CurrentFile+wxT("\nwurde gespeichert."));
}

void CodeWriterFrame::OnSave(wxCommandEvent& event)
{
    if(CurrentFile.IsEmpty())
        return;
    if(CurrentFile==wxT("new.txt"))
    {
        OnSaveAs(event);
        return;
    }
    wxString filename=CurrentFile;
    wxString data=TextFeld->GetValue();
    if((filename.EndsWith(wxT(".bmp")))||(filename.EndsWith(wxT(".png"))))
    {
        wxDELETE(currentPW);
        data.Replace(wxT("\n"),wxT("\\n"));
        unsigned char rawdata[data.Length()+2];
        for(int i=0;i<(int)data.Length()+2;i++)
            rawdata[i] = ((int)data[i] >= 128) ? '?' : (int)data[i];
        int width=data.Length()/3+1,height=1;
        for(int i=data.Length()/3+1;i>0;i--)
            for(int j=1;j<i;j++)
                if(i*j==(int)data.Length()/3+1)
                {
                    width=i;
                    height=j;
                }
        wxImage bmp(width,height,rawdata);
        bmp.SaveFile(filename);
    }
    else
    {
        if(filename.EndsWith(_(".rc4")))
        {
            wxPasswordEntryDialog dlg(this, _("Please enter your RC4 code"));
            if(currentPW != NULL)
                dlg.SetValue(*currentPW);
            if(dlg.ShowModal() == wxID_CANCEL)
                return;
            wxDELETE(currentPW);
            currentPW = new wxString(dlg.GetValue());
            wxCharBuffer bufKey = currentPW->ToUTF8();
            const char* key = bufKey.data();
            wxCharBuffer bufData = data.ToUTF8();
            const char* aData = bufData.data();
            UINT dataLen = strlen(aData);
            UCHAR* code = Convert::RC4DeEncrypt((const UCHAR*)(const void*)aData, dataLen,
                                                (const UCHAR*)(const void*)key, strlen(key));
            wxFileOutputStream output(filename);
            output.Write(code, dataLen);
            output.Close();
            delete [] code;
        }
        else
        {
            wxDELETE(currentPW);
            wxFileOutputStream output(filename);
            output.Write((const void*)data.mb_str(wxConvUTF8),data.Length());
            output.Close();
            if(filename.EndsWith(wxT(".code")))
                wxExecute(wxT("encode \"")+filename+wxT("\" ")+code);
        }

    }
    CurrentFile=filename;
    TextFeld->SetModified(false);
    LastSave=TextFeld->GetValue();
    this->RefreshTitle();
    this->Log(wxT("Save(\"")+CurrentFile+wxT("\");"));
}

void CodeWriterFrame::OnOpen(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Choose your file"), wxT(""), wxT(""),
                     wxT(""), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    Open(dlg.GetPath());
    wxMessageBox(wxT("Die Datei\n")+CurrentFile+wxT("\nwurde geoeffnet."));
}

void CodeWriterFrame::Open(wxString filename)
{
    if(filename.Find('\"')!=wxNOT_FOUND)
        filename.Replace(wxT("\""),wxT(""),true);
    if(filename.IsEmpty())
        return;
    this->Log(wxT("Open(\"")+filename+wxT("\");"));
    wxDELETE(currentPW);
    if((filename.EndsWith(wxT(".bmp")))||(filename.EndsWith(wxT(".png"))))
    {
        wxImage bmp(filename,wxBITMAP_TYPE_ANY);
        char rawdata[bmp.GetWidth()*bmp.GetHeight()*3+1];
        unsigned char* data=bmp.GetData();
        for(int i=0;i<bmp.GetWidth()*bmp.GetHeight()*3+1;i++)
            rawdata[i]=(int)data[i];
        wxString buf((const char*)rawdata,wxConvUTF8);
        buf.Replace(wxT("\\n"),wxT("\n"));
        TextFeld->SetValue(buf);
    }
    else if(filename.EndsWith(wxT(".code")))
    {
        wxArrayString array;
        wxExecute(wxT("viewcode \"")+filename+wxT("\" ")+code,array);
        wxString output = wxEmptyString;
        for(unsigned int i=0;i<array.GetCount();i++)
            output+=array[i]+wxT("\n");
        TextFeld->SetValue(output);
    }
    else if(filename.EndsWith(wxT(".rc4")))
    {
        wxPasswordEntryDialog dlg(this, _("Please enter your RC4 code"));
        if(dlg.ShowModal() == wxID_CANCEL)
            return;
        currentPW = new wxString(dlg.GetValue());
        wxCharBuffer bufKey = currentPW->ToUTF8();
        const UCHAR* key = (const UCHAR*)(bufKey.data());
        wxFileInputStream input(filename);
        size_t dataLen = SizeOfFile(filename.ToUTF8());
        UCHAR* data = new UCHAR[dataLen];
        input.Read((void*)data, dataLen);
        char* decryptData = (char*)Convert::RC4DeEncrypt(data, dataLen, key, strlen(bufKey.data()));
        TextFeld->SetValue(wxString::FromUTF8(decryptData));
        delete [] decryptData;
        delete [] data;
    }
    else
    {
        wxFileInputStream input(filename);
        char data[SizeOfFile(filename.mb_str(wxConvUTF8))];
        input.Read((void*)data,SizeOfFile(filename.mb_str(wxConvUTF8)));
        wxString buf(data,wxConvUTF8);
        TextFeld->SetValue(buf);
    }
    CurrentFile=filename;
    LastSave=TextFeld->GetValue();
    TextFeld->SetModified(false);
    this->RefreshTitle();
}

void CodeWriterFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void CodeWriterFrame::OnClose(wxCloseEvent& event)
{
    //if(wxMessageBox(wxT("Moechten sie das Programm wirklich beenden?"),wxT("Frage"),wxYES_NO)==wxYES)
        Close();
}

void CodeWriterFrame::OnTimerResize(wxTimerEvent& event)
{
    if(old!=this->GetClientSize())
    {
        TextFeld->SetSize(this->GetClientSize()-wxSize(2,1));
        old=this->GetClientSize();
    }
}

wxString CodeWriterFrame::GetSelectedString()
{
    wxString sel = TextFeld->GetStringSelection();
    return (sel == wxEmptyString) ? TextFeld->GetValue() : sel;
}

void CodeWriterFrame::SetSelectedString(const wxString& string)
{
    long from, to;
    TextFeld->GetSelection(&from, &to);
    if(from == to)
    {
        TextFeld->SetValue(string);
    }
    else
    {
        TextFeld->Replace(from, to, string);
        to = from + string.Len();
    }
    TextFeld->SetSelection(from, to);
    TextFeld->SendTextUpdatedEvent();
}

void CodeWriterFrame::OnDelSpacing(wxCommandEvent& event)
{
    this->SetSelectedString(Convert::DeleteSpacing(this->GetSelectedString()));
}

void CodeWriterFrame::OnMakeLiteral(wxCommandEvent& event)
{
    this->SetSelectedString(Convert::MakeLiteral(this->GetSelectedString()));
}

void CodeWriterFrame::OnParseLiteral(wxCommandEvent& event)
{
    this->SetSelectedString(Convert::ParseLiteral(this->GetSelectedString()));
}

void CodeWriterFrame::OnUpper(wxCommandEvent& event)
{
    this->SetSelectedString(this->GetSelectedString().Upper());
}

void CodeWriterFrame::OnLower(wxCommandEvent& event)
{
    this->SetSelectedString(this->GetSelectedString().Lower());
}

void CodeWriterFrame::OnFullLeet(wxCommandEvent& event)
{
    this->SetSelectedString(Convert::ToFullLeet(this->GetSelectedString()));
}

void CodeWriterFrame::OnEasyLeet(wxCommandEvent& event)
{
    this->SetSelectedString(Convert::ToEasyLeet(this->GetSelectedString()));
}

void CodeWriterFrame::OnUnFullLeet(wxCommandEvent& event)
{
    this->SetSelectedString(Convert::FromFullLeet(this->GetSelectedString()));
}

void CodeWriterFrame::OnUnEasyLeet(wxCommandEvent& event)
{
    this->SetSelectedString(Convert::FromEasyLeet(this->GetSelectedString()));
}
