package com.snl.compiler.mysyntax.symbols;

import com.snl.compiler.mylexer.Token;
import com.snl.compiler.mylexer.TokenType;

import java.util.List;

import static com.snl.compiler.mysyntax.symbols.NonTerminal.createNonTerminal;
import static com.snl.compiler.mysyntax.symbols.Terminal.terminalFactory;
import static java.util.Arrays.asList;
import static java.util.Collections.singletonList;

/**
 * 所有非终结符，根据预测分析表返回产生式右侧
 *
 */
public enum NON_TERMINAL {
    // ======================总程序===============================
    // (1)
    Program(new NonTerminal("Program")) {
        @Override
        public List<Symbol> predict(Token token) {
            if (token.getType() == TokenType.PROGRAM) {
                return asList(createNonTerminal("ProgramHead"), createNonTerminal("DeclarePart"),
                        createNonTerminal("ProgramBody"), terminalFactory(TokenType.EOF));
            }
            return null;
        }
    },
    // ======================程序头===============================
    // (2)
    ProgramHead(new NonTerminal("ProgramHead")) {
        @Override
        public List<Symbol> predict(Token token) {
            if (token.getType() == TokenType.PROGRAM) {
                return asList(terminalFactory(TokenType.PROGRAM), createNonTerminal("ProgramName"));
            }
            return null;
        }
    },
    // (3)
    ProgramName(new NonTerminal("ProgramName")) {
        @Override
        public List<Symbol> predict(Token token) {
            if (token.getType() == TokenType.ID) {
                return singletonList(terminalFactory(TokenType.ID));
            }
            return null;
        }
    },
    // ======================程序声明===============================
    // (4)
    DeclarePart(new NonTerminal("DeclarePar")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.TYPE || type == TokenType.VAR || type == TokenType.PROCEDURE || type == TokenType.BEGIN) {
                return asList(createNonTerminal("TypeDecpart"), createNonTerminal("VarDecpart"), createNonTerminal("ProcDecpart"));
            }
            return null;
        }
    },
    // ======================类型声明===============================
    // (5),(6)
    TypeDecpart(new NonTerminal("TypeDecpart")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.VAR || type == TokenType.PROCEDURE || type == TokenType.BEGIN) {
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.TYPE) {
                return singletonList(createNonTerminal("TypeDec"));
            }
            return null;
        }
    },
    // (7)
    TypeDec(new NonTerminal("TypeDec")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.TYPE) {
                return asList(terminalFactory(TokenType.TYPE), createNonTerminal("TypeDecList"));
            }
            return null;
        }
    },
    // (8)
    TypeDecList(new NonTerminal("TypeDecList")) {
        @Override
        public List<Symbol> predict(Token token) {
            if (token.getType() == TokenType.ID) {
                return asList(createNonTerminal("TypeId"), terminalFactory(TokenType.EQ), createNonTerminal("TypeDef"),
                        terminalFactory(TokenType.SEMI), createNonTerminal("TypeDecMore"));
            }
            return null;
        }
    },
    // (9),(10)
    TypeDecMore(new NonTerminal("TypeDecMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.VAR || type == TokenType.PROCEDURE || type == TokenType.BEGIN) {
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.ID) {
                return singletonList(createNonTerminal("TypeDecList"));
            }
            return null;
        }
    },
    // (11)
    TypeId(new NonTerminal("TypeId")) {
        @Override
        public List<Symbol> predict(Token token) {
            if (token.getType() == TokenType.ID) {
                return singletonList(terminalFactory(TokenType.ID));
            }
            return null;
        }
    },
    // ======================类型===============================
    // (12), (13), (14)
    TypeDef(new NonTerminal("TypeDef")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.INTEGER || type == TokenType.CHAR) {
                return singletonList(createNonTerminal("BaseType"));
            } else if (type == TokenType.ARRAY || type == TokenType.RECORD) {
                return singletonList(createNonTerminal("StructureType"));
            } else if (type == TokenType.ID) {
                return singletonList(terminalFactory(token));
            }
            return null;
        }
    },
    // (15), (16)
    BaseType(new NonTerminal("BaseType")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.INTEGER) {
                return singletonList(terminalFactory(TokenType.INTEGER));
            } else if (type == TokenType.CHAR) {
                return singletonList(terminalFactory(TokenType.CHAR));
            }
            return null;
        }
    },
    // (17), (18)
    StructureType(new NonTerminal("StructureType")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.ARRAY) {
                return singletonList(createNonTerminal("ArrayType"));
            } else if (type == TokenType.RECORD) {
                return singletonList(createNonTerminal("RecType"));
            }
            return null;
        }
    },
    // (19)
    ArrayType(new NonTerminal("ArrayType")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.ARRAY) {
                return asList(terminalFactory(TokenType.ARRAY), terminalFactory(TokenType.LMIDPAREN), createNonTerminal("Low"), terminalFactory(TokenType.UNDERRANGE),
                        createNonTerminal("Top"),terminalFactory(TokenType.RMIDPAREN) ,terminalFactory(TokenType.OF), createNonTerminal("BaseType"));
            }
            return null;
        }
    },
    // (20)
    Low(new NonTerminal("Low")) {
        @Override
        public List<Symbol> predict(Token token) {
            if (token.getType() == TokenType.INTC) {
                return singletonList(terminalFactory(TokenType.INTC));
            }
            return null;
        }
    },
    // (21)
    Top(new NonTerminal("Top")) {
        @Override
        public List<Symbol> predict(Token token) {
            if (token.getType() == TokenType.INTC) {
                return singletonList(terminalFactory(TokenType.INTC));
            }
            return null;
        }
    },
    // (22)
    RecType(new NonTerminal("RecType")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.RECORD) {
                return asList(terminalFactory(TokenType.RECORD), createNonTerminal("FieldDecList"), terminalFactory(TokenType.END));
            }
            return null;
        }
    },
    // (23), (24)
    FieldDecList(new NonTerminal("FieldDecList")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.INTEGER || type == TokenType.CHAR) {
                return asList(createNonTerminal("BaseType"), createNonTerminal("IdList"), terminalFactory(TokenType.SEMI), createNonTerminal("FieldDecMore"));
            } else if (type == TokenType.ARRAY) {
                return asList(createNonTerminal("ArrayType"), createNonTerminal("IdList"), terminalFactory(TokenType.SEMI), createNonTerminal("FieldDecMore"));
            }
            return null;
        }
    },
    // (25), (26)
    FieldDecMore(new NonTerminal("FieldDecMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.END) {
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.INTEGER || type == TokenType.CHAR || type == TokenType.ARRAY) {
                return singletonList(createNonTerminal("FieldDecList"));
            }
            return null;
        }
    },
    // (27)
    IdList(new NonTerminal("IdList")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.ID) {
                return asList(terminalFactory(token), createNonTerminal("IdMore"));
            }
            return null;
        }
    },
    // (28), (29)
    IdMore(new NonTerminal("IdMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.SEMI) {
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.COMMA) {
                return asList(terminalFactory(TokenType.COMMA), createNonTerminal("IdList"));
            }
            return null;
        }
    },
    // ======================变量声明===============================
    // (30), (31)
    VarDecpart(new NonTerminal("VarDecpart")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.PROCEDURE || type == TokenType.BEGIN) {
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.VAR) {
                return singletonList(createNonTerminal("VarDec"));
            }
            return null;
        }
    },
    // (32)
    VarDec(new NonTerminal("VarDec")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.VAR) {
                return asList(terminalFactory(TokenType.VAR), createNonTerminal("VarDecList"));
            }
            return null;
        }
    },
    // (33)
    VarDecList(new NonTerminal("VarDecList")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.INTEGER || type == TokenType.CHAR || type == TokenType.ARRAY || type == TokenType.RECORD || type == TokenType.ID) {
                return asList(createNonTerminal("TypeDef"), createNonTerminal("VarIdList"), terminalFactory(TokenType.SEMI), createNonTerminal("VarDecMore"));
            }
            return null;
        }
    },
    // (34), (35)
    VarDecMore(new NonTerminal("VarDecMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.PROCEDURE || type == TokenType.BEGIN) {
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.INTEGER || type == TokenType.CHAR || type == TokenType.ARRAY || type == TokenType.RECORD || type == TokenType.ID) {
                return singletonList(createNonTerminal("VarDecList"));
            }
            return null;
        }
    },
    // (36)
    VarIdList(new NonTerminal("VarIdList")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.ID) {
                return asList(terminalFactory(token), createNonTerminal("VarIdMore"));
            }
            return null;
        }
    },
    // (37), (38)
    VarIdMore(new NonTerminal("VarIdMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.SEMI) {
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.COMMA) {
                return asList(terminalFactory(TokenType.COMMA), createNonTerminal("VarIdList"));
            }
            return null;
        }
    },
    // ======================过程声明===============================
    // (39), (40)
    ProcDecpart(new NonTerminal("ProcDecpart")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.BEGIN) {
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.PROCEDURE) {
                return singletonList(createNonTerminal("ProcDec"));
            }
            return null;
        }
    },
    // (41)
    ProcDec(new NonTerminal("ProcDec")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.PROCEDURE) {
                return asList(terminalFactory(TokenType.PROCEDURE), createNonTerminal("ProcName"), terminalFactory(TokenType.LPAREN),
                        createNonTerminal("ParamList"), terminalFactory(TokenType.RPAREN), terminalFactory(TokenType.SEMI), createNonTerminal("ProcDecPart"),
                        createNonTerminal("ProcBody"), createNonTerminal("ProcDecMore"));
            }
            return null;
        }
    },
    // (42), (43)
    ProcDecMore(new NonTerminal("ProcDecMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.BEGIN) {
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.PROCEDURE) {
                return singletonList(createNonTerminal("ProcDec"));  // correction: 应该是ProcDec而不是ProcDeclaration
            }
            return null;
        }
    },
    // (44)
    ProcName(new NonTerminal("ProcName")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.ID) {
                return singletonList(terminalFactory(token));
            }
            return null;
        }
    },
    // ======================参数声明===============================
    // (45), (46)
    ParamList(new NonTerminal("ParamList")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case RPAREN:
                    return singletonList(createNonTerminal("blank"));
                case INTEGER:
                case CHAR:
                case ARRAY:
                case RECORD:
                case ID:
                case VAR:
                    return singletonList(createNonTerminal("ParamDecList"));
            }

            return null;
        }
    },
    // (47)
    ParamDecList(new NonTerminal("ParamDecList")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.INTEGER || type == TokenType.CHAR || type == TokenType.ARRAY || type == TokenType.RECORD || type == TokenType.ID
                    || type == TokenType.VAR) {
                return asList(createNonTerminal("Param"), createNonTerminal("ParamMore"));
            }
            return null;
        }
    },
    // (48), (49)
    ParamMore(new NonTerminal("ParamMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.RPAREN) {       // correction: 书上为左括号，有错误
                return singletonList(createNonTerminal("blank"));
            } else if (type == TokenType.SEMI) {
                return asList(terminalFactory(TokenType.SEMI), createNonTerminal("ParamDecList"));
            }
            return null;
        }
    },
    // (50), (51)
    Param(new NonTerminal("Param")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.INTEGER || type == TokenType.CHAR || type == TokenType.ARRAY || type == TokenType.RECORD || type == TokenType.ID) {
                return asList(createNonTerminal("TypeDef"), createNonTerminal("FormList"));
            } else if (type == TokenType.VAR) {
                return asList(terminalFactory(TokenType.VAR), createNonTerminal("TypeDef"), createNonTerminal("FormList"));
            }
            return null;
        }
    },
    // (52)
    FormList(new NonTerminal("FormList")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.ID) {
                return asList(terminalFactory(token), createNonTerminal("FidMore"));
            }
            return null;
        }
    },
    // (53), (54)
    FidMore(new NonTerminal("FidMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case SEMI:
                case RPAREN:
                    return singletonList(createNonTerminal("blank"));
                case COMMA:
                    return asList(terminalFactory(TokenType.COMMA), createNonTerminal("FormList"));
            }
            return null;
        }
    },
    // ======================过程中的声明部分===============================
    // (55)
    ProcDecPart(new NonTerminal("ProcDecPart")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case TYPE:
                case VAR:
                case PROCEDURE:
                case BEGIN:
                    return singletonList(createNonTerminal("DeclarePart"));
            }
            return null;
        }
    },
    // ======================过程体===============================
    // (56)
    ProcBody(new NonTerminal("ProcBody")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.BEGIN) {
                return singletonList(createNonTerminal("ProgramBody"));
            }
            return null;
        }
    },
    // ======================主程序体===============================
    // (57)
    ProgramBody(new NonTerminal("ProgramBody")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.BEGIN) {
                return asList(terminalFactory(TokenType.BEGIN), createNonTerminal("StmList"), terminalFactory(TokenType.END));
            }
            return null;
        }
    },
    // ======================语句序列===============================
    // (58)
    StmList(new NonTerminal("StmList")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case ID:
                case IF:
                case WHILE:
                case RETURN:
                case READ:
                case WRITE:
                    return asList(createNonTerminal("Stm"), createNonTerminal("StmMore"));
            }
            return null;
        }
    },
    // (59), (60)
    StmMore(new NonTerminal("StmMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case ELSE:
                case FI:
                case END:
                case ENDWH:
                    return singletonList(createNonTerminal("blank"));
                case SEMI:
                    return asList(terminalFactory(TokenType.SEMI), createNonTerminal("StmList"));
            }
            return null;
        }
    },
    // ======================语句===============================
    // (61), (62), (63), (64), (65), (66)
    Stm(new NonTerminal("Stm")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case IF:
                    return singletonList(createNonTerminal("ConditionalStm"));
                case WHILE:
                    return singletonList(createNonTerminal("LoopStm"));
                case READ:
                    return singletonList(createNonTerminal("InputStm"));
                case WRITE:
                    return singletonList(createNonTerminal("OutputStm"));
                case RETURN:
                    return singletonList(createNonTerminal("ReturnStm"));
                case ID:
                    return asList(terminalFactory(token), createNonTerminal("AssCall"));
            }
            return null;
        }
    },
    // (67), (68)
    AssCall(new NonTerminal("AssCall")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case LMIDPAREN:     // correction: 应该有个左方括号的情况
                case DOT:           // correction: 应该有个点号的情况
                case ASSIGN:
                    return singletonList(createNonTerminal("AssignmentRest"));
                case LPAREN:
                    return singletonList(createNonTerminal("CallStmRest"));
            }
            return null;
        }
    },
    // ======================赋值语句===============================
    // (69)
    AssignmentRest(new NonTerminal("AssignmentRest")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case LMIDPAREN:
                case DOT:
                case ASSIGN:
                    return asList(createNonTerminal("VariMore"), terminalFactory(TokenType.ASSIGN), createNonTerminal("Exp"));
            }
            return null;
        }
    },
    // ======================条件语句===============================
    // (70)
    ConditionalStm(new NonTerminal("ConditionalStm")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.IF) {
                return asList(terminalFactory(TokenType.IF), createNonTerminal("RelExp"), terminalFactory(TokenType.THEN), createNonTerminal("StmList"),
                        terminalFactory(TokenType.ELSE), createNonTerminal("StmList"), terminalFactory(TokenType.FI));
            }
            return null;
        }
    },
    // ======================循环语句===============================
    // (71)
    LoopStm(new NonTerminal("LoopStm")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.WHILE) {
                return asList(terminalFactory(TokenType.WHILE), createNonTerminal("RelExp"), terminalFactory(TokenType.DO),
                        createNonTerminal("StmList"), terminalFactory(TokenType.ENDWH));
            }
            return null;
        }
    },
    // ======================循环语句===============================
    // (72)
    InputStm(new NonTerminal("InputStm")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.READ) {
                return asList(terminalFactory(TokenType.READ), terminalFactory(TokenType.LPAREN),
                        createNonTerminal("Invar"), terminalFactory(TokenType.RPAREN));
            }
            return null;
        }
    },
    // (73)
    Invar(new NonTerminal("Invar")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.ID) {
                return singletonList(terminalFactory(token));
            }
            return null;
        }
    },
    // ======================输出语句===============================
    // (74)
    OutputStm(new NonTerminal("OutputStm")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.WRITE) {
                return asList(terminalFactory(TokenType.WRITE), terminalFactory(TokenType.LPAREN),
                        createNonTerminal("Exp"), terminalFactory(TokenType.RPAREN));
            }
            return null;
        }
    },
    // ======================返回语句===============================
    // (75)
    ReturnStm(new NonTerminal("ReturnStm")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.RETURN) {
                return singletonList(terminalFactory(TokenType.RETURN));
            }
            return null;
        }
    },
    // ======================过程调用语句===============================
    // (76)
    CallStmRest(new NonTerminal("CallStmRest")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.LPAREN) {
                return asList(terminalFactory(TokenType.LPAREN), createNonTerminal("ActParamList"), terminalFactory(TokenType.RPAREN));
            }
            return null;
        }
    },
    // (77), (78)
    ActParamList(new NonTerminal("ActParamList")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case RPAREN:
                    return singletonList(createNonTerminal("blank"));
                case LPAREN:
                case INTC:
                case ID:
                    return asList(createNonTerminal("Exp"), createNonTerminal("ActParamMore"));
            }
            return null;
        }
    },
    // (79), (80)
    ActParamMore(new NonTerminal("ActParamMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case RPAREN:
                    return singletonList(createNonTerminal("blank"));
                case COMMA:
                    return asList(terminalFactory(TokenType.COMMA), createNonTerminal("ActParamList"));
            }
            return null;
        }
    },
    // ======================条件表达式===============================
    // (81)
    RelExp(new NonTerminal("RelExp")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case LPAREN:
                case INTC:
                case ID:
                    return asList(createNonTerminal("Exp"), createNonTerminal("OtherRelE"));
            }
            return null;
        }
    },
    // (82)
    OtherRelE(new NonTerminal("OtherRelE")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.EQ || type == TokenType.LT) {
                return asList(createNonTerminal("CmpOp"), createNonTerminal("Exp"));
            }
            return null;
        }
    },
    // ======================算术表达式===============================
    // (83)
    Exp(new NonTerminal("Exp")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case LPAREN:
                case INTC:
                case ID:
                    return asList(createNonTerminal("Term"), createNonTerminal("OtherTerm"));
            }
            return null;
        }
    },
    // (84), (85)
    OtherTerm(new NonTerminal("OtherTerm")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case LT:
                case EQ:
                case RMIDPAREN:
                case THEN:
                case ELSE:
                case FI:
                case DO:
                case ENDWH:
                case RPAREN:
                case END:
                case SEMI:
                case COMMA:
                    return singletonList(createNonTerminal("blank"));
                case PLUS:
                case MINUS:
                    return asList(createNonTerminal("AddOp"), createNonTerminal("Exp"));
            }
            return null;
        }
    },
    // ======================项===============================
    // (86)
    Term(new NonTerminal("Term")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case LPAREN:
                case INTC:
                case ID:
                    return asList(createNonTerminal("Factor"), createNonTerminal("OtherFactor"));
            }
            return null;
        }
    },
    // (87), (88)
    OtherFactor(new NonTerminal("OtherFactor")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case PLUS:
                case MINUS:
                case LT:
                case EQ:
                case RMIDPAREN:
                case THEN:
                case ELSE:
                case FI:
                case DO:
                case ENDWH:
                case RPAREN:
                case END:
                case SEMI:
                case COMMA:
                    return singletonList(createNonTerminal("blank"));
                case TIMES:
                case DIVIDE:
                    return asList(createNonTerminal("MultOp"), createNonTerminal("Term"));
            }
            return null;
        }
    },
    // ======================因子===============================
    // (89), (90), (91)
    Factor(new NonTerminal("Factor")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case LPAREN:
                    return asList(terminalFactory(TokenType.LPAREN), createNonTerminal("Exp"), terminalFactory(TokenType.RPAREN));
                case INTC:
                    return singletonList(terminalFactory(TokenType.INTC));
                case ID:
                    return singletonList(createNonTerminal("Variable"));
            }
            return null;
        }
    },
    // (92)
    Variable(new NonTerminal("Variable")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.ID) {
                return asList(terminalFactory(token), createNonTerminal("VariMore"));
            }
            return null;
        }
    },
    // (93), (94), (95)
    VariMore(new NonTerminal("VariMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case RMIDPAREN:     // correction: 应添加右方括号
                case ASSIGN:
                case TIMES:
                case DIVIDE:
                case PLUS:
                case MINUS:
                case LT:
                case EQ:
                case THEN:
                case ELSE:
                case FI:
                case DO:
                case ENDWH:
                case RPAREN:
                case END:
                case SEMI:
                case COMMA:
                    return singletonList(createNonTerminal("blank"));
                case LMIDPAREN:
                    return asList(terminalFactory(TokenType.LMIDPAREN), createNonTerminal("Exp"), terminalFactory(TokenType.RMIDPAREN));
                case DOT:
                    return asList(terminalFactory(TokenType.DOT), createNonTerminal("FieldVar"));
            }
            return null;
        }
    },
    // (96)
    FieldVar(new NonTerminal("FieldVar")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.ID) {
                return asList(terminalFactory(token), createNonTerminal("FieldVarMore"));
            }
            return null;
        }
    },
    // (97), (98)
    FieldVarMore(new NonTerminal("FieldVarMore")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            switch (type) {
                case ASSIGN:
                case TIMES:
                case DIVIDE:
                case PLUS:
                case MINUS:
                case LT:
                case EQ:
                case THEN:
                case ELSE:
                case FI:
                case DO:
                case ENDWH:
                case RPAREN:
                case END:
                case SEMI:
                case COMMA:
                    return singletonList(createNonTerminal("blank"));
                case LMIDPAREN:
                    return asList(terminalFactory(TokenType.LMIDPAREN), createNonTerminal("Exp"), terminalFactory(TokenType.RMIDPAREN));
            }
            return null;
        }
    },
    // (99), (100)
    CmpOp(new NonTerminal("CmpOp")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.LT) {
                return singletonList(terminalFactory(TokenType.LT));
            } else if (type == TokenType.EQ) {
                return singletonList(terminalFactory(TokenType.EQ));
            }
            return null;
        }
    },
    // (101), (102)
    AddOp(new NonTerminal("AddOp")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.PLUS) {
                return singletonList(terminalFactory(TokenType.PLUS));
            } else if (type == TokenType.MINUS) {
                return singletonList(terminalFactory(TokenType.MINUS));
            }
            return null;
        }
    },
    // (103), (104)
    MultOp(new NonTerminal("MultOp")) {
        @Override
        public List<Symbol> predict(Token token) {
            TokenType type = token.getType();
            if (type == TokenType.TIMES) {
                return singletonList(terminalFactory(TokenType.TIMES));
            } else if (type == TokenType.DIVIDE) {
                return singletonList(terminalFactory(TokenType.DIVIDE));
            }
            return null;
        }
    };


    NON_TERMINAL(NonTerminal nonTerminal) {
        this.nonTerminal = nonTerminal;
    }

    public NonTerminal nonTerminal;

    /**
     * 用所给的token类型查预测分析表，返回产生式右部
     *
     * @param token 要查的token
     * @return 产生式右部，列表
     */
    public abstract List<Symbol> predict(Token token);
}
