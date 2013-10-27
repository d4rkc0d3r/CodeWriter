#include "Convert.h"

UCHAR* Convert::RC4DeEncrypt(const UCHAR* data, size_t dataLength, const UCHAR* code, size_t codeLength)
{
    UCHAR* s = new UCHAR[256];
    UCHAR* nData = new UCHAR[dataLength];
    for(int i = 0; i < 256; ++i)
        s[i] = i;
    int j = 0;
    for(int i = 0; i < 256; ++i)
    {
        j = (j + s[i] + code[i % codeLength] + 128) % 256;
        int tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    int i = 0;
    j = 0;
    for(UINT n = 0; n < dataLength; ++n)
    {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        int tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        UCHAR rnd = s[(s[i] + s[j]) % 256];
        nData[n] = rnd ^ data[n];
    }
    delete [] s;
    return nData;
}

wxString Convert::MakeLiteral(wxString s)
{
    wxString ret;
    for(UINT i = 0; i < s.Length(); ++i)
    {
        wxChar c = s.GetChar(i);
        switch(c)
        {
            case '\\': ret.append(_("\\\\")); break;
            case '\"': ret.append(_("\\\"")); break;
            case '\n': ret.append(_("\\n")); break;
            case '\r': ret.append(_("\\r")); break;
            case '\t': ret.append(_("\\t")); break;
            default: ret.append(c);
        }
    }
    return ret;
}

wxString Convert::ParseLiteral(wxString s)
{
    wxString ret;
    bool isEscaped = false;
    for(UINT i = 0; i < s.Length(); ++i)
    {
        wxChar c = s.GetChar(i);
        if(isEscaped)
        {
            switch(c)
            {
                case 'n': ret.append(_("\n")); break;
                case 'r': ret.append(_("\r")); break;
                case 't': ret.append(_("\t")); break;
                case '\\': ret.append(_("\\")); break;
                case '\"': ret.append(_("\"")); break;
                default: ret.append(_("[ERROR:\"\\") + wxString(c) + _("]")); break;
            }
            isEscaped = false;
        }
        else
        {
            if(c == '\\')
            {
                isEscaped = true;
            }
            else
            {
                ret.append(c);
            }
        }
    }
    return ret;
}

wxString Convert::DeleteSpacing(wxString s)
{
    wxString ret;
    bool wasEmpty = false;
    for(UINT i = 0; i < s.Length(); ++i)
    {
        wxChar c = s.GetChar(i);
        if(wasEmpty)
        {
            wasEmpty = false;
            if(c == ' ')
            {
                continue;
            }
            ret.append(_(" "));
        }
        switch(c)
        {
            case ' ': wasEmpty = true; break;
            case '\n': case '\r': case '\t': break;
            default: ret.append(c); break;
        }
    }
    return ret;
}

wxString Convert::ToFullLeet(wxString s)
{
    s.Replace(wxT("0"),wxT("$0"));
    s.Replace(wxT("1"),wxT("$1"));
    s.Replace(wxT("2"),wxT("$2"));
    s.Replace(wxT("3"),wxT("$3"));
    s.Replace(wxT("4"),wxT("$4"));
    s.Replace(wxT("5"),wxT("$5"));
    s.Replace(wxT("6"),wxT("$6"));
    s.Replace(wxT("7"),wxT("$7"));
    s.Replace(wxT("8"),wxT("$8"));
    s.Replace(wxT("9"),wxT("$9"));
    s.Replace(wxT("!"),wxT("#'"));
    s.Replace(wxT("("),wxT("('"));
    s.Replace(wxT(")"),wxT("')"));

    s.Replace(wxT("a"),wxT("4"));
    s.Replace(wxT("A"),wxT("4"));
    s.Replace(wxT("i"),wxT("!"));
    s.Replace(wxT("I"),wxT("!"));
    s.Replace(wxT("l"),wxT("1"));
    s.Replace(wxT("L"),wxT("1"));
    s.Replace(wxT("z"),wxT("2"));
    s.Replace(wxT("Z"),wxT("2"));
    s.Replace(wxT("o"),wxT("0"));
    s.Replace(wxT("O"),wxT("0"));
    s.Replace(wxT("t"),wxT("7"));
    s.Replace(wxT("T"),wxT("7"));
    s.Replace(wxT("g"),wxT("9"));
    s.Replace(wxT("G"),wxT("9"));
    s.Replace(wxT("s"),wxT("5"));
    s.Replace(wxT("S"),wxT("5"));
    s.Replace(wxT("e"),wxT("3"));
    s.Replace(wxT("E"),wxT("3"));
    s.Replace(wxT("y"),wxT("`/"));
    s.Replace(wxT("Y"),wxT("`/"));
    s.Replace(wxT("b"),wxT("|3"));
    s.Replace(wxT("B"),wxT("|3"));
    s.Replace(wxT("c"),wxT("("));
    s.Replace(wxT("C"),wxT("("));
    s.Replace(wxT("d"),wxT("|)"));
    s.Replace(wxT("D"),wxT("|)"));
    s.Replace(wxT("f"),wxT("|="));
    s.Replace(wxT("F"),wxT("|="));
    s.Replace(wxT("h"),wxT("|-|"));
    s.Replace(wxT("H"),wxT("|-|"));
    s.Replace(wxT("k"),wxT("|<"));
    s.Replace(wxT("K"),wxT("|<"));
    s.Replace(wxT("m"),wxT("|\\/|"));
    s.Replace(wxT("M"),wxT("|\\/|"));
    s.Replace(wxT("n"),wxT("|\\|"));
    s.Replace(wxT("N"),wxT("|\\|"));
    s.Replace(wxT("p"),wxT("|*"));
    s.Replace(wxT("P"),wxT("|*"));
    s.Replace(wxT("r"),wxT("|2"));
    s.Replace(wxT("R"),wxT("|2"));
    s.Replace(wxT("u"),wxT("|_|"));
    s.Replace(wxT("U"),wxT("|_|"));
    s.Replace(wxT("v"),wxT("\\/"));
    s.Replace(wxT("V"),wxT("\\/"));
    s.Replace(wxT("w"),wxT("|/\\|"));
    s.Replace(wxT("W"),wxT("|/\\|"));
    s.Replace(wxT("x"),wxT("><"));
    s.Replace(wxT("X"),wxT("><"));

    s.Replace(wxT("#'"),wxT("i"));

    return s;
}

wxString Convert::ToEasyLeet(wxString s)
{
    s.Replace(wxT("0"),wxT("$0"));
    s.Replace(wxT("1"),wxT("$1"));
    s.Replace(wxT("2"),wxT("$2"));
    s.Replace(wxT("3"),wxT("$3"));
    s.Replace(wxT("4"),wxT("$4"));
    s.Replace(wxT("5"),wxT("$5"));
    s.Replace(wxT("6"),wxT("$6"));
    s.Replace(wxT("7"),wxT("$7"));
    s.Replace(wxT("8"),wxT("$8"));
    s.Replace(wxT("9"),wxT("$9"));
    s.Replace(wxT("!"),wxT("#'"));

    s.Replace(wxT("a"),wxT("4"));
    s.Replace(wxT("A"),wxT("4"));
    s.Replace(wxT("i"),wxT("!"));
    s.Replace(wxT("I"),wxT("!"));
    s.Replace(wxT("l"),wxT("1"));
    s.Replace(wxT("L"),wxT("1"));
    s.Replace(wxT("z"),wxT("2"));
    s.Replace(wxT("Z"),wxT("2"));
    s.Replace(wxT("o"),wxT("0"));
    s.Replace(wxT("O"),wxT("0"));
    s.Replace(wxT("t"),wxT("7"));
    s.Replace(wxT("T"),wxT("7"));
    s.Replace(wxT("g"),wxT("9"));
    s.Replace(wxT("G"),wxT("9"));
    s.Replace(wxT("s"),wxT("5"));
    s.Replace(wxT("S"),wxT("5"));
    s.Replace(wxT("e"),wxT("3"));
    s.Replace(wxT("E"),wxT("3"));

    s.Replace(wxT("#'"),wxT("i"));

    return s;
}

wxString Convert::FromFullLeet(wxString s)
{
    s.Replace(wxT("$0"),wxT("#NULL"));
    s.Replace(wxT("$1"),wxT("#EINS"));
    s.Replace(wxT("$2"),wxT("#ZWEI"));
    s.Replace(wxT("$3"),wxT("#DREI"));
    s.Replace(wxT("$4"),wxT("#VIER"));
    s.Replace(wxT("$5"),wxT("#FUENF"));
    s.Replace(wxT("$6"),wxT("#SECHS"));
    s.Replace(wxT("$7"),wxT("#SIEBEN"));
    s.Replace(wxT("$8"),wxT("#ACHT"));
    s.Replace(wxT("$9"),wxT("#NEUN"));
    s.Replace(wxT("i"),wxT("#AUSRUF"));
    s.Replace(wxT("('"),wxT("#AUF"));
    s.Replace(wxT("')"),wxT("#ZU"));

    s.Replace(wxT("|-|"),wxT("h"));
    s.Replace(wxT("|\\|"),wxT("n"));
    s.Replace(wxT("|/\\|"),wxT("w"));
    s.Replace(wxT("|_|"),wxT("u"));
    s.Replace(wxT("|\\/|"),wxT("m"));
    s.Replace(wxT("\\/"),wxT("v"));
    s.Replace(wxT("|3"),wxT("b"));
    s.Replace(wxT("|2"),wxT("r"));

    s.Replace(wxT("4"),wxT("a"));
    s.Replace(wxT("!"),wxT("i"));
    s.Replace(wxT("1"),wxT("l"));
    s.Replace(wxT("2"),wxT("z"));
    s.Replace(wxT("0"),wxT("o"));
    s.Replace(wxT("7"),wxT("t"));
    s.Replace(wxT("9"),wxT("g"));
    s.Replace(wxT("5"),wxT("s"));
    s.Replace(wxT("3"),wxT("e"));

    s.Replace(wxT("`/"),wxT("y"));
    s.Replace(wxT("("),wxT("c"));
    s.Replace(wxT("|)"),wxT("d"));
    s.Replace(wxT("|="),wxT("f"));
    s.Replace(wxT("|<"),wxT("k"));
    s.Replace(wxT("|*"),wxT("p"));
    s.Replace(wxT("\\/"),wxT("v"));
    s.Replace(wxT("><"),wxT("x"));

    s.Replace(wxT("#NULL"),wxT("0"));
    s.Replace(wxT("#EINS"),wxT("1"));
    s.Replace(wxT("#ZWEI"),wxT("2"));
    s.Replace(wxT("#DREI"),wxT("3"));
    s.Replace(wxT("#VIER"),wxT("4"));
    s.Replace(wxT("#FUENF"),wxT("5"));
    s.Replace(wxT("#SECHS"),wxT("6"));
    s.Replace(wxT("#SIEBEN"),wxT("7"));
    s.Replace(wxT("#ACHT"),wxT("8"));
    s.Replace(wxT("#NEUN"),wxT("9"));
    s.Replace(wxT("#AUSRUF"),wxT("!"));
    s.Replace(wxT("#AUF"),wxT("("));
    s.Replace(wxT("#ZU"),wxT(")"));

    return s;
}

wxString Convert::FromEasyLeet(wxString s)
{
    s.Replace(wxT("$0"),wxT("#NULL"));
    s.Replace(wxT("$1"),wxT("#EINS"));
    s.Replace(wxT("$2"),wxT("#ZWEI"));
    s.Replace(wxT("$3"),wxT("#DREI"));
    s.Replace(wxT("$4"),wxT("#VIER"));
    s.Replace(wxT("$5"),wxT("#FUENF"));
    s.Replace(wxT("$6"),wxT("#SECHS"));
    s.Replace(wxT("$7"),wxT("#SIEBEN"));
    s.Replace(wxT("$8"),wxT("#ACHT"));
    s.Replace(wxT("$9"),wxT("#NEUN"));
    s.Replace(wxT("i"),wxT("#AUSRUF"));

    s.Replace(wxT("4"),wxT("a"));
    s.Replace(wxT("!"),wxT("i"));
    s.Replace(wxT("1"),wxT("l"));
    s.Replace(wxT("2"),wxT("z"));
    s.Replace(wxT("0"),wxT("o"));
    s.Replace(wxT("7"),wxT("t"));
    s.Replace(wxT("9"),wxT("g"));
    s.Replace(wxT("5"),wxT("s"));
    s.Replace(wxT("3"),wxT("e"));

    s.Replace(wxT("#NULL"),wxT("0"));
    s.Replace(wxT("#EINS"),wxT("1"));
    s.Replace(wxT("#ZWEI"),wxT("2"));
    s.Replace(wxT("#DREI"),wxT("3"));
    s.Replace(wxT("#VIER"),wxT("4"));
    s.Replace(wxT("#FUENF"),wxT("5"));
    s.Replace(wxT("#SECHS"),wxT("6"));
    s.Replace(wxT("#SIEBEN"),wxT("7"));
    s.Replace(wxT("#ACHT"),wxT("8"));
    s.Replace(wxT("#NEUN"),wxT("9"));
    s.Replace(wxT("#AUSRUF"),wxT("!"));

    return s;
}
