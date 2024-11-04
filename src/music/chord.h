#ifndef CHORD_H
#define CHORD_H

#include "note.h"
#include <array>
#include <string>
#include <vector>
/*
	CHORD:
        - Root
        - Quality - 3rd 5th 7th (maj, min, dim, dim, sus, no3?, no5?)
        - Extension
          - 5 (sharp / flat)
          - 7 (maj / min / dim)
          - 9 (sharp / nat / flat)
          - 11 (sharp / nat)
          - 13 (nat / flat)
        - Alterations
        - Bass Note
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
public:
    typedef std::array<bool, Notes::COUNT> interval_set;
    enum quality { maj = 0, dom, min, dim };
    const std::array<const std::string, 4> str_QUALITY = {"Maj", "", "min", "dim"};
    enum extension { triad = 0, seven, nine, eleven, thirteen };
    const std::array<const std::string, 5> str_EXTENSION = {"", "7", "9", "11", "13"};
    enum alteration {
        no3 = 0,
        no5,
        flat5,
        sharp5,
        sus2,
        sus4,
        flat9,
        sharp9,
        add13,
        add9,
        sharp11,
        add11,
        flat13,
        ALTCOUNT
    };
    const std::array<const std::string, ALTCOUNT> str_ALTERATION = {
        "no3", "no5", "b5", "#5", "sus2", "sus4", "b9", "#9", "add13", "add9", "#11", "add11", "b13"};
    typedef std::array<bool, ALTCOUNT> Alterations;
    Chord();
    Chord(const Notes::Note root, const quality qual, const extension ext);
    Chord(const Notes::Note root, const quality qual, const extension ext,
          const Alterations& alts, const Notes::Note bass);
    const auto& notes() const { return m_noteslist; }
    const std::string& name() const { return m_namestr; }
    Notes::Note root() const {return m_rootnote;}
    Notes::Note bass() const {return m_bassnote;}
    quality qual() const {return m_quality;}
    extension extensionLevel() const {return m_extlevel;}
    bool hasAlteration(const alteration alt) const {return m_alts[alt];}
    void setRoot(const Notes::Note root);
    void setBass(const Notes::Note bass);
    void setQuality(const quality newqual);
    void setExtension(const extension newlevel);
    bool canAddAlteration(const alteration alt) const;
    void addAlteration(const alteration newalt);
    void removeAlteration(const alteration alt);

private:
    void constructChord();
    void nameChord();
    enum action{R=-1,N=0,A=1}; //remove, no action, add

    typedef const std::array<action, Notes::COUNT> action_set;
    //                                                   #9      #11     #5
    //                                           1 b9  9 b3  3 11 b5  5 b13 13 b7 7
    static constexpr interval_set QUALSETS[] = {{1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1},  //maj
                                                {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0},  //dom
                                                {1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0},  //min
                                                {1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0}}; //dim

    static constexpr interval_set EXTSETS[] = {{1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0},  //triad
                                               {1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1},  //7
                                               {1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1},  //9
                                               {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1},  //11
                                               {1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1}}; //13

    static constexpr action_set ALTSETS[] = {
        {N, N, N, R, R, N, N, N, N, N, N, N}, //no3 / 5
        {N, N, N, N, N, N, R, R, N, N, N, N}, //no5
        {N, N, N, N, N, N, A, R, N, N, N, N}, //b5
        {N, N, N, N, N, N, R, R, A, N, N, N}, //#5
        {N, N, A, R, R, N, N, N, N, N, N, N}, //sus2
        {N, N, N, R, R, A, N, N, N, N, N, N}, //sus4 / sus
        {N, A, R, N, N, N, N, N, N, N, N, N}, //b9
        {N, N, R, A, N, N, N, N, N, N, N, N}, //#9
        {N, N, N, N, N, N, N, N, N, A, N, N}, //add13
        {N, N, A, N, N, N, N, N, N, N, N, N}, //add9
        {N, N, N, N, N, R, A, N, N, N, N, N}, //#11
        {N, N, N, N, N, A, N, N, N, N, N, N}, //add11
        {N, N, N, N, N, N, N, N, A, R, N, N}, //b13
    }; //add13
    std::string m_namestr;
    std::vector<PitchedNote> m_noteslist;
    Notes::Note m_rootnote;
    Notes::Note m_bassnote;
    quality m_quality;
    extension m_extlevel;
    Alterations m_alts = {0};
    interval_set m_intervals;
};

#endif // CHORD_H
