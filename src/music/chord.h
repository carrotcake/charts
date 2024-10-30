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
			<Dim>   ::= dim | o | ° | ø 
			<Sus> 	::= sus2 | sus4 | sus
			<NoX> 	::= no3 | no5 | 5

		<Extension> ::= <BasicExt> <JazzExt>
    		<BasicExt> ::= 2 | 6 | 6/9 | add9 | add11 | <null>
			<JazzExt> ::=  <ValidExt> | <ValidExt> <JazzExt> | <null>
			<ValidExt> ::= <Ext5> | <Ext7> | <Ext9> | <Ext11> | <Ext13>
				<Ext5> ::= b5
				<Ext7> ::= 7 | Maj7 | M7 | dim7 | °7 | o7 | ø7
				<Ext9> ::= b9 | 9 | #9
				<Ext11> ::= 11 | #11
				<Ext13> ::= b13 | 13

		<Slash> ::= / <LetterName> | <null>
		<LetterName> ::= A | A# | Bb | B | C | C# | Db | D | D# | Eb | E | F | F# | Gb | G | G# | Ab
		<null> ::= 

*/

enum class TriadQuality { maj, min, aug, dim, sus2, sus4 };

enum class ExtQuality { none = 0, sharp, nat, flat, maj, min, dim };

enum ExtIntervalType {
    two = 0,
    six,
    sixnine,
    addnine,
    addeleven,
    five,
    seven,
    nine,
    eleven,
    thirteen,
    INTVLTYPECOUNT
};

struct ChordExtension {
    ExtQuality qualities[ExtIntervalType::INTVLTYPECOUNT] = {ExtQuality::none};
};

class Chord {
public:
    Chord();

private:
    QString name;
    QList<Note> notes;
    //Notes::NoteName root;
    Notes::NoteValue root;
    Notes::NoteValue bass;
    TriadQuality quality;
    ChordExtension ext;
};

#endif // CHORD_H
