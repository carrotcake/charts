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

Chord ChordParser::parseChordFromString(const QString& str){
    qsizetype idx = 0;
    Chord c;
    //root from chord string
    Note root = rootFromChordString(str, idx);
    //quality
    QString tempstr(str);
    replaceChordTokens(tempstr);
    idx++;
    //build extension


    return c;
}
