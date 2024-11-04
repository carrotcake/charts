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

    m_noteslist.clear();
    m_noteslist.emplace_back(PitchedNote(m_bassnote, Notes::Octave::A3));
    for (size_t i = 0; i < Notes::COUNT; ++i) {
        Notes::Octave oct = Notes::Octave::A4;
        if (!m_intervals[i])
            continue;
        auto val = (m_rootnote.m_value + i) % Notes::COUNT;
        switch(static_cast<Notes::interval>(i)){
        case Notes::MINSECOND:
            oct = Notes::Octave::A5;
            break;
        case Notes::MAJSECOND:
            if(!m_alts[sus2])
                oct = Notes::Octave::A5;
            break;
        case Notes::PERFOURTH:
            if(!m_alts[sus4])
                oct = Notes::Octave::A5;
            break;
        case Notes::AUGFOURTH:
            if (m_alts[sharp11])
                oct = Notes::Octave::A5;
            break;
        case Notes::AUGSECOND:
            if(m_alts[sharp9])
                oct = Notes::Octave::A5;
        case Notes::AUGFIFTH:
            if(m_alts[flat13])
                oct = Notes::Octave::A5;
        case Notes::MAJSIXTH:
            if(m_extlevel > seven && m_quality != dim)
                oct = Notes::Octave::A5;
        default:
            break;
        }
        m_noteslist.emplace_back(PitchedNote(Notes::NOTES[val], oct));
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
    if (m_rootnote.m_value != m_bassnote.m_value) {
        namestr.append("/");
        namestr.append(m_bassnote.flatName());
    }
    m_namestr.assign(namestr);
}

Chord::Chord()
    : m_rootnote(Notes::NOTES[Notes::NOTE_C])
    , m_bassnote(Notes::NOTES[Notes::NOTE_C])
    , m_quality(Chord::maj)
    , m_extlevel(Chord::triad) {
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

void Chord::setRoot(const Notes::Note root, bool rebuild) {
    m_rootnote = root;
    if (rebuild)
        constructChord();
}

void Chord::setBass(const Notes::Note bass, bool rebuild) {
    m_bassnote = bass;
    if (rebuild)
        constructChord();
}

void Chord::setQuality(const quality newqual, bool rebuild) {
    removeAllAlterations(false);
    m_quality = newqual;
    if (rebuild)
        constructChord();
}

void Chord::setExtension(const extension newlevel, bool rebuild) {
    m_extlevel = newlevel;
    if (rebuild)
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
        return m_quality != dim && !(m_alts[flat13] || m_extlevel == thirteen);
    default:
        return false;;
    }
}

void Chord::addAlteration(const alteration newalt, bool rebuild) {
    m_alts[newalt] = true;
    if (rebuild)
        constructChord();
}

void Chord::removeAlteration(const alteration alt, bool rebuild) {
    m_alts[alt] = false;
    if (rebuild)
        constructChord();
}

void Chord::removeAllAlterations(bool rebuild) {
    for (size_t i = 0; i < ALTCOUNT; ++i)
        m_alts[i] = false;
    if (rebuild)
        constructChord();
}
