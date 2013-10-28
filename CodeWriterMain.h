/***************************************************************
 * Name:      CodeWriterMain.h
 * Purpose:   Defines Application Frame
 * Author:    Max Heller (max.heller94@web.de)
 * Created:   2010-12-14
 * Copyright: Max Heller ()
 * License:
 **************************************************************/

#ifndef CODEWRITERMAIN_H
#define CODEWRITERMAIN_H

//(*Headers(CodeWriterFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/statusbr.h>
//*)

#define EDITED wxT("*")

#define WX_TO_C(s) ((const char*)(s).ToUTF8().data())
#define SYS(s) system(WX_TO_C((s)))

class CodeWriterFrame: public wxFrame
{
    public:

        CodeWriterFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~CodeWriterFrame();

    private:

        wxTimer* TimerResize;
        wxPanel* Panel;
        wxTextCtrl* TextFeld;
        wxSize old;
        wxString code;
        wxString title;
        wxString CurrentFile;
        wxString CmdLine;
        wxString LastSave;
        wxString CurrentDir;
        wxString* currentPW;
        int LogLevel;

        void Log(wxString line, int level = 3);
        void Open(wxString filename);
        void RefreshTitle();

        wxString GetSelectedString();
        void SetSelectedString(const wxString& string);

        //(*Handlers(CodeWriterFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnSaveAs(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnCode(wxCommandEvent& event);
        void OnTimerResize(wxTimerEvent& event);
        void OnTextChange(wxCommandEvent& event);
        void OnFullLeet(wxCommandEvent& event);
        void OnEasyLeet(wxCommandEvent& event);
        void OnUnFullLeet(wxCommandEvent& event);
        void OnUnEasyLeet(wxCommandEvent& event);
        void OnReplace(wxCommandEvent& event);
        void OnLower(wxCommandEvent& event);
        void OnUpper(wxCommandEvent& event);
        void OnDelSpacing(wxCommandEvent& event);
        void OnMakeLiteral(wxCommandEvent& event);
        void OnParseLiteral(wxCommandEvent& event);
        //*)

        //(*Identifiers(CodeWriterFrame)
        static const long idMenuOpen;
        static const long idMenuSave;
        static const long idMenuSaveAs;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long idMenuCode;
        static const long ID_UNEASYLEET;
        static const long ID_UNFULLLEET;
        static const long ID_EASYLEET;
        static const long ID_FULLLEET;
        static const long ID_REPLACE;
        static const long ID_TIMER1;
        static const long ID_PANEL1;
        static const long ID_TEXTCTRL1;
        static const long ID_NONE;
        static const long ID_LOWER;
        static const long ID_UPPER;
        static const long ID_DELSPACING;
        static const long ID_MAKELITERAL;
        static const long ID_PARSELITERAL;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // CODEWRITERMAIN_H
