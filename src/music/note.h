#ifndef NOTE_H
#define NOTE_H

#include "notes.h"

class Note {
public:
    Note(Notes::Letter let, Notes::Value v)
        : m_name(let),
        m_val(v){}
    Notes::Letter const name(){return m_name;}
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
    Notes::Letter m_name;
    Notes::Value m_val;
};

#endif // NOTE_H
