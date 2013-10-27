#ifndef CONVERT_H
#define CONVERT_H

#include <wx/string.h>

namespace Convert
{
    wxString ToFullLeet(wxString s);
    wxString ToEasyLeet(wxString s);
    wxString FromFullLeet(wxString s);
    wxString FromEasyLeet(wxString s);
    wxString MakeLiteral(wxString s);
    wxString ParseLiteral(wxString s);
    wxString DeleteSpacing(wxString s);

    UCHAR* RC4DeEncrypt(const UCHAR* data, size_t dataLength, const UCHAR* code, size_t codeLength);
}

#endif // CONVERT_H
