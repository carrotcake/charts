
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class OperatorPrec {
    static String in = """
<Chord> ::= <LetterName> <Quality> <Extension> <Slash>
<Quality> ::= <Major> | <Minor> | <Aug> | <Dim> | <Sus> | <NoX>
<Major> ::= M | Maj | Δ | <null>
<Minor> ::= m | min | -
<Aug> ::= aug | +
<Dim> ::= dim | o | ° | ø
<Sus> ::= sus2 | sus4 | sus
<NoX> ::= no3 | no5 | 5
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
<null>  ::= """;

    private static final ArrayList<Term> terms = new ArrayList<>();
    private static final ArrayList<Nonterm> nonterms = new ArrayList<>();
    private static ArrayList<Symbol> syms;

    private static void readSymbols() {
        Scanner sc = new Scanner(in);
        while (sc.hasNext()) {
            String line[] = sc.nextLine().trim().split("(::=)|\\|");
            Nonterm current = new Nonterm(line[0].trim());
            nonterms.add(current);
            for (int i = 1; i < line.length; i++) {
                String rule[] = line[i].trim().split(" +");
                for (int j = 0; j < rule.length; j++) {
                    String str = rule[j].trim();
                    if (!str.isEmpty() && !str.matches("<.+>") && !termsContains(str)) {
                        terms.add(new Term(str));
                    }
                }
            }
        }
        sc.close();
        syms = new ArrayList<>();
        syms.addAll(terms);
        syms.addAll(nonterms);
    }

    static void processRule(String[] rule, Nonterm lefthand, int left, Matrices m) {
        boolean foundFirstTerm = false;
        boolean foundLastTerm = false;
        Symbol first = getSym(rule[0].trim()), last = getSym(rule[rule.length - 1].trim());
        int f = syms.indexOf(first), l = syms.indexOf(last);
        m.FIRST[left][f] = true;
        m.LAST[left][l] = true;
        // System.out.println("\t" + line[j]);
        // System.out.println("\t\t" + current.ident + " FIRST " + rule[0]);
        // System.out.println("\t\t" + current.ident + " LAST " + rule[rule.length -
        // 1]);
        for (int i = 0; i < rule.length; i++) {
            String str = rule[i].trim();
            String checkLast = rule[rule.length - 1 - i].trim();

            Symbol righthand = getSym(str), lastTerm = getSym(checkLast);
            int right = syms.indexOf(righthand), lt = syms.indexOf(lastTerm);

            if (!foundLastTerm && lastTerm instanceof Term) {
                foundLastTerm = true;
                m.LASTTERM[left][lt] = true;
                // System.out.println("\t\t" + current.ident + " LASTTERM " + lastT);
            }
            if (i < rule.length - 1) {
                Symbol nextSym = getSym(rule[i + 1].trim());
                int next = syms.indexOf(nextSym);
                m.EQ[right][next] = true;
                // System.out.println("\t\t" + temp.ident + " = " + rule[i + 1]);
            }
            if (righthand instanceof Term) {
                boolean foundTerm = false;
                if (!foundFirstTerm) {
                    foundFirstTerm = true;
                    m.FIRSTTERM[left][right] = true;
                    // System.out.println("\t\t" + current.ident + " FIRSTTERM " + str);
                }
                m.GRD[left][right] = true;
                for (int k = i + 2; !foundTerm && k < rule.length; k++) {
                    Symbol next = getSym(rule[k]);
                    int nextTerm = syms.indexOf(next);
                    if (next instanceof Term) {
                        foundTerm = true;
                        m.EQ[right][nextTerm] = true;
                        // System.out.println("\t\t" + t.ident + " = " + possible);
                    }
                }
            } else {
                m.CON[left][right] = true;
            }
        }
    }

    static void processLine(String line, Matrices m) {
        String rules[] = line.trim().split("(::=)|\\|");
        Nonterm current = getNonterm(rules[0].trim());
        int cur = syms.indexOf(current);
        // System.out.println(current.ident + "::=");
        for (int j = 1; j < rules.length; j++) {
            String rule[] = rules[j].trim().split(" +");
            processRule(rule, current, cur, m);
        }
    }

    static Matrices generateMatrices() {
        int count = syms.size();
        Matrices m = new Matrices(count);
        Scanner sc = new Scanner(in);
        while (sc.hasNextLine()) {
            processLine(sc.nextLine(), m);
        }
        sc.close();
        return m;
    }

    static void printSymbols() {
        System.out.println("Terms: " + terms.size() + ", Nonterms: " + nonterms.size());
        for (Term t : terms) {
            System.out.print("\"" + t.ident + "\", ");
        }
        System.out.println("");
        System.out.println(syms.toString());

    }

    public static void main(String[] args) {

        readSymbols();
        printSymbols();

        Matrices m = generateMatrices();

        checkConnectedGrounded(m.CON, m.GRD);

        // get reflexive transitive closure of first
        transitiveClosure(m.FIRST);
        addIdentity(m.FIRST);
        // multiply to get <
        boolean[][] eqfirst = logicalProduct(m.EQ, m.FIRST);
        boolean[][] YIELDS = logicalProduct(eqfirst, m.FIRSTTERM);
        // get reflexive transitive closure of last
        transitiveClosure(m.LAST);
        addIdentity(m.LAST);
        // multiply to get >
        boolean[][] lastlasttermT = transpose(logicalProduct(m.LAST, m.LASTTERM));
        boolean[][] TAKES = logicalProduct(lastlasttermT, m.EQ);

        Prec[][] prec_table = calcPrec(YIELDS, TAKES, m.EQ);
        printPrecedenceTable(prec_table);
        int[][] prec_func = calcPrecedenceFunction(prec_table);
        printPrecedenceFunction(prec_func);
        try {
            outputPrecedenceTable(prec_table, "prectable.dat");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void outputPrecedenceTable(Prec[][] mat, String filename) throws IOException {
        FileWriter fw = new FileWriter(filename);
        System.out.println();
        System.out.print("{");
        for (int i = 0; i < mat.length; i++) {
            System.out.print("{");
            for (int j = 0; j < mat.length; j++) {
                switch (mat[i][j]) {
                    case EQUAL:
                        fw.append("1 ");
                        System.out.print("EQUALS, ");
                        break;
                    case NO_RELATION:
                        fw.append("3 ");
                        System.out.print("NO_REL, ");
                        break;
                    case TAKES:
                        fw.append("2 ");
                        System.out.print("TAKES, ");
                        break;
                    case YIELDS:
                        fw.append("0 ");
                        System.out.print("YIELDS, ");
                        break;
                    default:
                        break;

                }
            }
            fw.append("\n");
            System.out.print("\b\b},");
            if (i != mat.length - 1)
                System.out.println();
        }
        System.out.println("\b}");
        System.out.flush();
        fw.flush();
        fw.close();
    }

    private static void printPrecedenceFunction(int[][] fg) {
        int n = fg[0].length;
        System.out.printf("\n\n\t");
        for (int i = 0; i < n; i++) {
            System.out.printf("%s\t", syms.get(i));
        }
        System.out.printf("\nf:\t");
        for (int i = 0; i < n; i++) {
            System.out.printf("%d\t", fg[0][i]);
        }
        System.out.printf("\ng:\t");
        for (int i = 0; i < n; i++) {
            System.out.printf("%d\t", fg[1][i]);
        }
        System.out.printf("\n");
    }

    private static int[][] calcPrecedenceFunction(Prec[][] prec_table) {
        int n = prec_table.length;
        boolean bmat[][] = new boolean[n * 2][n * 2];
        boolean[][] takes_eq = new boolean[n][n], yields_eqT = new boolean[n][n];
        int fg[][] = new int[2][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                switch (prec_table[i][j]) {
                    case YIELDS:
                        yields_eqT[j][i] = true;
                        takes_eq[i][j] = false;
                        break;
                    case TAKES:
                        yields_eqT[j][i] = false;
                        takes_eq[i][j] = true;
                        break;
                    case EQUAL:
                        yields_eqT[j][i] = true;
                        takes_eq[i][j] = true;
                        break;
                    default:
                        yields_eqT[j][i] = false;
                        takes_eq[i][j] = false;
                        break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                bmat[i][n + j] = takes_eq[i][j];
                bmat[n + i][j] = yields_eqT[i][j];
            }
        }

        transitiveClosure(bmat);
        addIdentity(bmat);

        for (int i = 0; i < n; i++) {
            fg[0][i] = 0;
            fg[1][i] = 0;
            for (int j = 0; j < n * 2; j++) {
                fg[0][i] += bmat[i][j] ? 1 : 0;
                fg[1][i] += bmat[n + i][j] ? 1 : 0;
            }
        }
        return fg;
    }

    private static void checkConnectedGrounded(boolean[][] CON, boolean[][] GRD) {
        int count = syms.size();
        transitiveClosure(CON);
        for (int i = 0; i < count; i++) {
            if (syms.get(i) instanceof Nonterm) {
                int sum = 0;
                for (int j = 0; j < count; j++) {
                    if (CON[j][i]) {
                        sum++;
                    }
                }
                if (sum == 0) {
                    System.out.println(syms.get(i).ident + " IS NOT CONNECTED");
                }
            }
        }
        addIdentity(CON);
        boolean[][] congrd = logicalProduct(CON, GRD);
        for (int i = 0; i < count; i++) {
            if (syms.get(i) instanceof Nonterm) {
                int sum = 0;
                for (int j = 0; j < count; j++) {
                    if (congrd[i][j]) {
                        sum++;
                    }
                }
                if (sum == 0) {
                    System.out.println(syms.get(i).ident + " IS NOT GROUNDED");
                }
            }
        }
    }

    private static void printPrecedenceTable(Prec mat[][]) {
        int OPS = 0;
        for (int i = 0; i < syms.size(); i++) {
            if (syms.get(i) instanceof Nonterm) {
                OPS = i;
                break;
            }
        }
        for (int i = 0; i < OPS; i++) {
            System.out.printf("\t| %s", syms.get(i));
        }
        System.out.printf("\n");
        for (int i = 0; i < OPS; i++) {
            for (int j = 0; j < OPS * 9 - 1; j++) {
                System.out.printf("-");
            }
            System.out.printf("\n%s\t| ", syms.get(i));
            for (int j = 0; j < OPS; j++) {
                System.out.printf("%s\t| ", PRECEDENCE[mat[i][j].ordinal()]);
            }
            System.out.printf("\b\b \n");
        }
    }

    private static Prec[][] calcPrec(boolean[][] yields, boolean[][] takes, boolean[][] eq) {
        assert (yields.length == yields[0].length && takes.length == takes[0].length && eq.length == eq[0].length);
        assert (yields.length == takes.length && takes.length == eq.length);
        int N = terms.size();
        Prec[][] mat = new Prec[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (yields[i][j]) {
                    mat[i][j] = eq[i][j] ? Prec.YIELDSEQ : Prec.YIELDS;
                } else if (takes[i][j]) {
                    mat[i][j] = eq[i][j] ? Prec.TAKESEQ : Prec.TAKES;
                } else if (eq[i][j]) {
                    mat[i][j] = Prec.EQUAL;
                } else {
                    mat[i][j] = Prec.NO_RELATION;
                }
            }
        }
        return mat;
    }

    private static boolean[][] transpose(boolean[][] mat) {
        assert (mat.length == mat[0].length);
        int N = mat.length;
        boolean[][] matT = new boolean[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matT[j][i] = mat[i][j];
            }
        }
        return matT;
    }

    private static void transitiveClosure(boolean[][] mat) {
        assert (mat.length == mat[0].length);
        int N = mat.length;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (mat[j][i]) {
                    for (int k = 0; k < N; k++) {
                        mat[j][k] = mat[j][k] || mat[i][k];
                    }
                }
            }
        }
    }

    private static void addIdentity(boolean[][] mat) {
        assert (mat.length == mat[0].length);
        int N = mat.length;
        for (int i = 0; i < N; i++) {
            mat[i][i] = true;
        }
    }

    private static boolean[][] logicalProduct(boolean[][] a, boolean[][] b) {
        assert (a.length == a[0].length && a.length == b.length && a[0].length == b[0].length);
        int N = a.length;
        boolean[][] r = new boolean[N][N];
        for (int i = 0; i < N; i++) {
            boolean sum = false;
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    sum = sum || (a[i][k] && b[k][j]);
                }
                r[i][j] = sum;
                sum = false;
            }
        }
        return r;
    }

    @SuppressWarnings("unused")
    private static void printBoolArr(boolean[][] mat) {
        for (int i = 0; i < mat.length; i++) {
            for (int j = 0; j < mat[i].length; j++) {
                System.out.printf("%d ", mat[i][j] ? 1 : 0);
            }
            System.out.println("");
        }
    }

    private static Symbol getSym(String s) {
        if (s.matches("<.+>")) {
            return getNonterm(s);
        } else {
            return getTerm(s);
        }
    }

    private static Nonterm getNonterm(String s) {
        for (Nonterm nt : nonterms) {
            if (nt.ident.equals(s)) {
                return nt;
            }
        }
        return null;
    }

    private static Term getTerm(String s) {
        for (Term t : terms) {
            if (t.ident.equals(s)) {
                return t;
            }
        }
        return null;
    }

    private static boolean termsContains(String s) {
        for (Term t : terms) {
            if (t.ident.equals(s)) {
                return true;
            }
        }
        return false;
    }

    private static class Symbol {

        String ident;

        public Symbol(String str) {
            ident = str;
        }

        @Override
        public String toString() {
            return ident;
        }

    }

    private static class Term extends Symbol {

        public Term(String str) {
            super(str);
        }

    }

    private static class Nonterm extends Symbol {

        public Nonterm(String str) {
            super(str);
        }

    }

    enum Prec {
        NO_RELATION,
        TAKES,
        YIELDS,
        TAKESEQ,
        YIELDSEQ,
        EQUAL
    };

    static String[] PRECEDENCE = { " ", ">", "<", "EE", "EE", "=" };

    private static class Matrices {

        boolean[][] FIRST, FIRSTTERM, LAST, LASTTERM, EQ, CON, GRD;

        public Matrices(int count) {
            FIRST = new boolean[count][count];
            LAST = new boolean[count][count];
            EQ = new boolean[count][count];
            FIRSTTERM = new boolean[count][count];
            LASTTERM = new boolean[count][count];
            CON = new boolean[count][count];
            GRD = new boolean[count][count];
        }

    }
}
