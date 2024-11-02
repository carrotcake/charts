#include "chord.h"

void Chord::constructChord(){
    auto& qualintervals = QUALSETS[m_quality];
    auto& extintervals = EXTSETS[m_extlevel];
    for (size_t i = 0; i < Notes::COUNT; ++i) {
        m_intervals[i] = qualintervals[i] && extintervals[i];
    }
    if(m_quality == dim && m_extlevel > triad){
        m_intervals[Notes::MAJSIXTH] = true;
    }
    for(int altidx = 0; altidx < ALTCOUNT; ++altidx){
        if(!m_alts[altidx])
            continue;
        auto& actions = ALTSETS[altidx];
        for(int intidx = 0; intidx < Notes::COUNT; ++intidx){
            switch(actions[intidx]){
            case R:
                m_intervals[intidx] = false;
                break;
            case A:
                m_intervals[intidx] = true;
                break;
            case N:
                break;
            }
        }
    }

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


