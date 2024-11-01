#ifndef CHORD_H
#define CHORD_H

#include <QList>
#include "note.h"

/*
	CHORD:
        - Root
        - Quality - 3rd & 5th (maj, min, aug, dim, sus, no3?, no5?)
        - Bass Note (mu?)
        - Extension
          - add3 for sus?
          - 2 (ive seen it?)
          - 6 (flat? / nat)
          - 6/9
          - add9
          - add11
          - 5 (sharp / flat)
          - 7 (maj / min / dim)
          - 9 (sharp / nat / flat)
          - 11 (sharp / nat)
          - 13 (nat / flat)
        - Voicing...
	
	<Chord> ::= <LetterName> <Quality> <Extension> <Slash>
	
		<Quality> ::= <Major> | <Minor> | <Aug> | <Dim> | <Sus> | <NoX>
			<Major> ::= M | Maj | Δ | <null>
			<Minor> ::= m | min | - 
   			<Aug> 	::= aug | +
            <Dim>   ::= dim | o | °
			<Sus> 	::= sus2 | sus4 | sus
			<NoX> 	::= no3 | no5 | 5

		<Extension> ::= <BasicExt> <JazzExt>
    		<BasicExt> ::= 2 | 6 | 6/9 | add9 | add11 | <null>
			<JazzExt> ::=  <ValidExt> | <ValidExt> <JazzExt> | <null>
            <ValidExt> ::= <Ext5> | <Ext7> | <Ext9> | <Ext11> | <Ext13>
				<Ext5> ::= b5
                <Ext7> ::= 7 | 7alt
				<Ext9> ::= b9 | 9 | #9
				<Ext11> ::= 11 | #11
				<Ext13> ::= b13 | 13

		<Slash> ::= / <LetterName> | <null>
		<LetterName> ::= A | A# | Bb | B | C | C# | Db | D | D# | Eb | E | F | F# | Gb | G | G# | Ab
		<null> ::= 

*/

class Chord {

    enum Quality {
        maj,
        dom,
        min,
        dim
    };
    enum Extension {
        triad,
        seven,
        nine,
        eleven,
        thirteen
    };
    enum Alteration {
        no3,
        no5,
        flat5,
        sharp5,
        sus2,
        sus4,
        flat9,
        sharp9,
        add9,
        sharp11,
        add11,
        flat13,
        add13,
        ALTCOUNT
    };

    enum IntervalAction{ R=-1,N=0,A=1}; //remove, no action, add

    const static size_t NOTECOUNT = 12;

    typedef bool IntervalSet[NOTECOUNT];
    typedef IntervalAction IntActionSet[NOTECOUNT];
                                            //          #9      #11     #5
                                            //  1 b9  9 b3  3 11 b5  5 b13 13 b7 7
    static constexpr IntervalSet QUALSETS[] = {{1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1}, //maj
                                               {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0}, //dom
                                               {1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0}, //min
                                               {1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0}};//dim

    static constexpr IntervalSet EXTSETS[] =  {{1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0}, //triad
                                               {1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1}, //7
                                               {1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1}, //9
                                               {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1}, //11
                                               {1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1}};//13

    static constexpr IntActionSet ALTSETS[] = {{N, N, N, R, R, N, N, N, N, N, N, N}, //no3 / 5
                                               {N, N, N, N, N, N, R, R, N, N, N, N}, //no5
                                               {N, N, N, N, N, N, A, R, N, N, N, N}, //b5
                                               {N, N, N, N, N, N, R, R, A, N, N, N}, //#5
                                               {N, N, A, R, R, N, N, N, N, N, N, N}, //sus2
                                               {N, N, N, R, R, A, N, N, N, N, N, N}, //sus4 / sus
                                               {N, A, R, N, N, N, N, N, N, N, N, N}, //b9
                                               {N, N, R, A, N, N, N, N, N, N, N, N}, //#9
                                               {N, N, A, N, N, N, N, N, N, N, N, N}, //add9
                                               {N, N, N, N, N, R, A, N, N, N, N, N}, //#11
                                               {N, N, N, N, N, A, N, N, N, N, N, N}, //add11
                                               {N, N, N, N, N, N, N, N, A, R, N, N}, //b13
                                               {N, N, N, N, N, N, N, N, N, A, N, N}};//add13
public:
    Chord();
    Chord(const Note root, const Quality qual, const Extension ext);
    Chord(const Note root, const Quality qual, const Extension ext, const bool alts[ALTCOUNT], const Note bass);
    const std::string& name() const {return m_namestr;}
    Note root() const {return m_rootnote;}
    Note bass() const {return m_bassnote;}
    Quality quality() const {return m_quality;}
    Extension extension() const {return m_extlevel;}
    bool hasAlteration(const Alteration alt) const {return m_alts[alt];}
    void setRoot(const Note root);
    void setBass(const Note bass);
    void setQuality(const Quality newqual);
    void setExtension(const Extension newlevel);
    bool canAddAlteration(const Alteration alt);
    bool addAlteration(const Alteration alt);
    bool removeAlteration(const Alteration alt);

    private:
    void constructChord();
    std::string m_namestr;
    std::vector<Note> m_noteslist;
    Note m_rootnote;
    Note m_bassnote;
    Quality m_quality;
    Extension m_extlevel;
    bool m_alts[ALTCOUNT];

};

#endif // CHORD_H
