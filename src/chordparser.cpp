#include "chordparser.h"

ChordParser::ChordParser() {}

using namespace Notes;

static Value valueFromLetter(Letter let){
    switch(let){
    case Letter::A:return Value::A;
    case Letter::B:return Value::B;
    case Letter::C:return Value::C;
    case Letter::D:return Value::D;
    case Letter::E:return Value::E;
    case Letter::F:return Value::F;
    case Letter::G:return Value::G;
    }
}


static Note rootFromChordString(const QString& str, qsizetype &idx){
    QChar c = str.at(idx);
    if(!c.isLetter())
        return Note(Letter::A,Value::ERRNOTE);
    c = c.toUpper();
    const Letter let = static_cast<Letter>(c.toLatin1() - 'A');
    Value val = valueFromLetter(let);
    if(str.length() > idx + 1){
        switch(str.at(idx + 1).toLatin1()){
        case 'b':
            val = let == Letter::A ? Value::Aflat : static_cast<Value>(static_cast<int>(val) - 1);
            ++idx;
            break;
        case '#':
            val = static_cast<Value>(static_cast<int>(val) + 1);
            ++idx;
            break;
        default:
            break;
        }
    }
    return Note(let,val);
}

static void replaceChordTokens(QString& str){
    //major symbols
    str.replace("Maj", "M");
    str.replace("maj", "M");
    str.replace("Major", "M");
    str.replace("major", "M");
    str.replace("Δ","M7");
    //minor
    str.replace("-","m");
    str.replace("min","m");
    str.replace("Min","m");
    str.replace("minor","m");
    str.replace("Minor","m");
    //aug
    str.replace("aug", "+");
    //dim
    str.replace("dim", "o");
    //sus
    str.replace("sus","s");
    //nox
    str.replace("no3", "5");
    str.replace("no5", "n");
    str.replace("add", "a");
}

static TriadQuality qualityFromChordString(const QString& str, qsizetype &idx){
    if(str.isEmpty()) return TriadQuality::maj;
    QChar ch = str.at(idx);
    switch(ch.toLatin1()){
    case 'M':
        return TriadQuality::maj;
    case 'm':
        return TriadQuality::min;
    case '+':
        return TriadQuality::aug;
    case 'o':
        return TriadQuality::dim;
    case 's':
        if(str.length() > idx + 1 && str.at(++idx) == '2')
            return TriadQuality::sus2;
        else
            return TriadQuality::sus4;
    case 'n':
        return TriadQuality::maj;
    case '5':
        return TriadQuality::no3;
    default:
        return TriadQuality::dommaj;
    }
}

Chord ChordParser::parseChordFromString(const QString& str){
    qsizetype idx = 0;
    ChordExtension ext;
    TriadQuality qual;
    Chord c;
    //root from chord string
    Note root = rootFromChordString(str, idx);
    //quality
    QString tempstr(str);
    replaceChordTokens(tempstr);
    qual = qualityFromChordString(tempstr, idx);
    idx++;
    //build extension
    bool addedExt       = false;
    ExtQuality defQual  = ExtQuality::nat;
    ExtQuality lastQual = ExtQuality::nat;
    while (idx < tempstr.length()) {
        switch (tempstr.at(idx).toLatin1()) {
            case 'b':
                lastQual = ExtQuality::flat;
                break;
            case '#':
                lastQual = ExtQuality::sharp;
                break;
            case '2':
                ext.qualities[ExtType::two] = lastQual;
                addedExt                    = true;
                break;
            case '6':
                {
                    if (idx + 1 < tempstr.length()) {
                        switch (tempstr.at(idx + 1).toLatin1()) {
                            case '/':
                                if (idx + 2 >= tempstr.length() || tempstr.at(idx + 2) != '9')
                                    break;
                                else
                                    idx++;
                            case '9':
                                ext.qualities[ExtType::sixnine] = lastQual;
                                addedExt                        = true;
                                idx++;
                                break;
                            default:
                                ext.qualities[ExtType::six] = lastQual;
                                addedExt                    = true;
                                break;
                        }
                    } else {
                        ext.qualities[ExtType::six] = lastQual;
                        addedExt                    = true;
                    }
                    break;
                }
            case 'a':
                {
                    if (idx + 1 >= tempstr.length())
                        return c; //ERROR
                    switch (tempstr.at(idx + 1).toLatin1()) {
                        case '9':
                            ext.qualities[ExtType::addnine] = lastQual;
                            addedExt                        = true;
                            break;
                        case '1':
                            if (idx + 2 < tempstr.length() && tempstr.at(idx + 2) == '1') {
                                ext.qualities[ExtType::addeleven] = lastQual;
                                addedExt                          = true;
                            } else {
                                return c; //ERROR
                            }
                            break;
                    }
                    break;
                }
            case '5':
                if (lastQual == ExtQuality::flat) {
                    ext.qualities[ExtType::five] = lastQual;
                    addedExt                     = true;
                } else {
                    return c; //ERROR
                }
                break;
            case '7':
                switch (qual) {
                    case TriadQuality::maj:
                        ext.qualities[seven] = ExtQuality::maj;
                        break;
                    case TriadQuality::min:
                    case TriadQuality::aug:
                    case TriadQuality::dommaj:
                    case TriadQuality::sus2:
                    case TriadQuality::sus4:
                    case TriadQuality::no3:
                        ext.qualities[seven] = ExtQuality::min;
                        break;
                    case TriadQuality::dim:
                        ext.qualities[seven] = ExtQuality::dim;
                        break;
                }
                addedExt = true;
                break;
            case '9':
                break;
            case '1':
                break;
        }
        if (addedExt) {
            lastQual = defQual;
            addedExt = false;
        }
        idx++;
    }

    c.root    = root.value();
    c.quality = qual;

    return c;
}
