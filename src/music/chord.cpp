#include "chord.h"

void Chord::constructChord(){
    auto& qualintervals = QUALSETS[m_quality];
    auto& extintervals = EXTSETS[m_extlevel];
    for (size_t i = 0; i < Notes::COUNT; ++i) {
        m_intervals[i] = qualintervals[i] && extintervals[i];
    }
    if(m_quality == dim && m_extlevel > triad){
        m_intervals[Notes::MAJSIXTH] = true; // diminished seventh
    }
    for(int altidx = 0; altidx < ALTCOUNT; ++altidx){
        if(!m_alts[altidx])
            continue;
        const auto& actions = ALTSETS[altidx];
        for(int intidx = 0; intidx < Notes::COUNT; ++intidx){
            switch(actions[intidx]){
            case R:
                m_intervals[intidx] = false;
                break;
            case A:
                m_intervals[intidx] = true;
                break;
            default:
                break;
            }
        }
    }

}

void Chord::nameChord(){

}

Chord::Chord() : m_rootnote(Notes::C),
    m_bassnote(Notes::C),
    m_quality(Chord::maj),
    m_extlevel(Chord::triad){
    constructChord();
}

Chord::Chord(const Notes::Note root, const quality qual, const extension ext) :
    m_rootnote(root), m_bassnote(root), m_quality(qual), m_extlevel(ext)
{
    constructChord();
}

Chord::Chord(const Notes::Note root, const quality qual, const extension ext,
             const Alterations& alts, const Notes::Note bass) :
    m_rootnote(root), m_bassnote(bass), m_quality(qual), m_extlevel(ext)
{
   // std::copy(alts.begin(), alts.end(), m_alts);
    constructChord();
}

void Chord::setRoot(const Notes::Note root){
    m_rootnote = root;
    nameChord();
}

void Chord::setBass(const Notes::Note bass){
    m_bassnote = bass;
    nameChord();
}

void Chord::setQuality(const quality newqual){
    m_quality = newqual;
    constructChord();
}

void Chord::setExtension(const extension newlevel){
    m_extlevel = newlevel;
    constructChord();
}

bool Chord::canAddAlteration(const alteration alt) const {
    switch(alt){
    case no3:
        return !(m_alts[sus2] || m_alts[sus4]);
    case no5:
        return !(m_alts[flat5] || m_alts[sharp5]);
    case flat5:
        return !(m_alts[no5] || m_alts[sharp5] || (m_quality == dim));
    case sharp5:
        return !(m_alts[no5] || m_alts[flat5]);
    case sus2:
        return !(m_alts[sus4] || m_alts[flat9] || m_alts[sharp9] || m_alts[add9]);
    case sus4:
        return !(m_alts[sus2] || m_alts[sharp11] || m_alts[add11]);
    case flat9:
        return !(m_alts[sus2] || m_alts[sharp9]);
    case sharp9:
        return !(m_alts[sus2] || m_alts[flat9]);
    case add9:
        return !(m_alts[sus2]);
    case sharp11:
        return !(m_alts[sus4] || m_alts[flat5]);
    case add11:
        return !(m_alts[sus4]);
    case flat13:
        return !(m_alts[sharp5]);
    case add13:
        return (m_quality != dim || m_alts[flat13]);
    default:
        return false;;
    }
}

void Chord::addAlteration(const alteration newalt){
    m_alts[newalt] = true;
    constructChord();
}

void Chord::removeAlteration(const alteration alt){
    m_alts[alt] = false;
    constructChord();
}



