#ifndef NOTE_H
#define NOTE_H

#include "notes.h"



struct Note {
public:
    Note(Notes::Letter let, Notes::Value v)
        : m_let(let),
        m_val(v){}
    Notes::Letter const letter(){return m_let;}
    Notes::Value const value(){return m_val;}
    bool const accidental(){
        switch(m_val){
        case Notes::Value::A:
        case Notes::Value::B:
        case Notes::Value::D:
        case Notes::Value::E:
        case Notes::Value::G:
            return false;
        default:
            break;
        }
        return true;
    }

private:

    Notes::Letter m_let;
    Notes::Value m_val;
};

#endif // NOTE_H
