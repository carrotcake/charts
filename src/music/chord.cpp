#include "chord.h"

void Chord::constructChord(){
    auto& qualintervals = QUALSETS[m_quality];
    auto& extintervals = EXTSETS[m_extlevel];
    for (size_t i = 0; i < Notes::COUNT; ++i)
        m_intervals[i] = qualintervals[i] && extintervals[i];
    if (m_quality == dim && m_extlevel > triad)
        m_intervals[Notes::MAJSIXTH] = true; // diminished seventh
    for (size_t altidx = 0; altidx < ALTCOUNT; ++altidx) {
        if(!m_alts[altidx])
            continue;
        const auto& actions = ALTSETS[altidx];
        for (size_t intidx = 0; intidx < Notes::COUNT; ++intidx) {
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
    Notes::Octave oct = Notes::Octave::A4;
    for (size_t i = 0; i < Notes::COUNT; ++i) {
        if (m_intervals[i]) {
            m_noteslist.emplace_back(PitchedNote(Notes::Note{static_cast<Notes::value>(i)}, oct));
        }
    }
    nameChord();
}

void Chord::nameChord(){
    if (m_rootnote.m_value == Notes::ERRNOTE) {
        m_namestr.assign("N.C.");
        return;
    }
    std::string namestr(m_rootnote.flatName());
    if (!(m_quality == maj && m_extlevel == triad))
        namestr.append(str_QUALITY[m_quality]);
    namestr.append(str_EXTENSION[m_extlevel]);
    for (size_t i = 0; i < ALTCOUNT; ++i) {
        if (!m_alts[i])
            continue;
        if (i == add13 && m_extlevel == triad) {
            namestr.append("6");
        } else if (i == add9 && m_extlevel == triad && m_alts[add13]) {
            namestr.append("/9");
        } else {
            namestr.append(str_ALTERATION[i]);
        }
    }
    m_namestr.assign(namestr);
}

Chord::Chord() : m_rootnote(Notes::C),
    m_bassnote(Notes::C),
    m_quality(Chord::maj),
    m_extlevel(Chord::triad){
    constructChord();
}

Chord::Chord(const Notes::Note root, const quality qual, const extension ext)
    : m_rootnote(root)
    , m_bassnote(root)
    , m_quality(qual)
    , m_extlevel(ext) {
    constructChord();
}

Chord::Chord(const Notes::Note root, const quality qual, const extension ext,
             const Alterations& alts, const Notes::Note bass) :
    m_rootnote(root), m_bassnote(bass), m_quality(qual), m_extlevel(ext)
{
    for (size_t i = 0; i < ALTCOUNT; ++i) {
        m_alts[i] = alts[i];
    }
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
        return !(m_alts[sus2] || m_alts[sharp9] || m_extlevel == nine);
    case sharp9:
        return !(m_alts[sus2] || m_alts[flat9] || m_extlevel == nine);
    case add9:
        return !(m_alts[sus2] || m_extlevel >= nine);
    case sharp11:
        return !(m_alts[sus4] || m_alts[flat5] || m_extlevel == eleven);
    case add11:
        return !(m_alts[sus4] || m_extlevel == eleven);
    case flat13:
        return !(m_alts[sharp5] || m_extlevel == thirteen);
    case add13:
        return (m_quality != dim || m_alts[flat13] || m_extlevel == thirteen);
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



