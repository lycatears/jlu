package com.snl.compiler.mylexer;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.TimeZone;

public class SNLLexer {
    private Integer line = 1;
    private Integer column = 0;
    private final List<String> log = new ArrayList<>();
    private int backtrack = -1;
    private Reader reader;
    private boolean lf = false;
    private boolean terminated = false;

    public LexerResult getLexerResult(Reader reader) throws IOException {
        LexerResult lexerResult = new LexerResult();
        List<Token> tokens = new ArrayList<>();
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        dateFormat.setTimeZone(TimeZone.getTimeZone("GMT+8"));

        // 无法读取，提示错误
        if (reader == null) {
            log.add('[' + dateFormat.format(new Date()) + "] cannot read target SNL file");
            lexerResult.setTokenList(tokens);
            return lexerResult;
        }

        // 循环读取可能的token，直到文件结束
        this.reader = reader;
        Token token = getToken();
        while (!terminated && token != null) {
            tokens.add(token);
            token = getToken();
        }

        lexerResult.setTokenList(tokens);
        return lexerResult;
    }

    private Token getToken() throws IOException {
        LexerState state = LexerState.NORMAL;
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        dateFormat.setTimeZone(TimeZone.getTimeZone("GMT+8"));
        log.add('[' + dateFormat.format(new Date()) + "] Lexer starting... set to NORMAL state.");

        StringBuilder sb = new StringBuilder();
        log.add('[' + dateFormat.format(new Date()) + "] Get ready for read tokens.");
        int cur = getChar();

        while (cur != -1) {
            sb.append((char) cur);
            Token token;
            log.add('[' + dateFormat.format(new Date()) + "] Current state is: " + state);

            switch (state) {
                // <editor-fold desc="switch NORMAL">
                case NORMAL:
                    // 初始状态下的转换
                    if (isAlpha(cur)) {
                        // 遇到英文字母，先假设是标识符，稍后处理可能遇到的关键字
                        state = LexerState.INID;
                    } else if (isDigit(cur)) {
                        // 单词的第一个字符是数字，那肯定是数字常量
                        state = LexerState.INNUM;
                    } else if (isBlank(cur)) {
                        // 空字符，跳过
                        sb.deleteCharAt(sb.length() - 1);
                    } else if (cur == '+') {
                        // 四则运算区域
                        token = new Token(line, column, TokenType.PLUS, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == '-') {
                        token = new Token(line, column, TokenType.MINUS, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == '*') {
                        token = new Token(line, column, TokenType.TIMES, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == '/') {
                        token = new Token(line, column, TokenType.DIVIDE, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == '(') {
                        token = new Token(line, column, TokenType.LPAREN, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == ')') {
                        token = new Token(line, column, TokenType.RPAREN, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == ',') {
                        token = new Token(line, column, TokenType.COMMA, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == ';') {
                        token = new Token(line, column, TokenType.SEMI, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == '[') {
                        token = new Token(line, column, TokenType.LMIDPAREN, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == ']') {
                        token = new Token(line, column, TokenType.RMIDPAREN, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == '=') {
                        token = new Token(line, column, TokenType.EQ, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == '<') {
                        // 词法未定义大于号，无需实现，只考虑小于号即可
                        token = new Token(line, column, TokenType.LT, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else if (cur == ':') {
                        // 进入赋值操作符，需要两个字符
                        state = LexerState.INASSIGN;
                    } else if (cur == '{') {
                        // 注释起始符号
                        state = LexerState.INCOMMENT;
                        sb.deleteCharAt(sb.length() - 1);
                    } else if (cur == '}') {
                        log.add('[' + dateFormat.format(new Date()) + "] Illegal comment terminator at [" + line + ':' + column + "] T_T" + sb);
                        state = LexerState.ERROR;
                    } else if (cur == '.') {
                        state = LexerState.INDOT;
                    } else if (cur == '\'') {
                        // 字符常量表达式
                        state = LexerState.INCHAR;
                        sb.deleteCharAt(sb.length() - 1);
                    } else {
                        log.add('[' + dateFormat.format(new Date()) + "] Illegal char at [" + line + ':' + column + "] T_T" + sb);
                        state = LexerState.ERROR;
                    }
                    break;
                // </editor-fold>
                // <editor-fold desc="case INID 识别标识符">
                case INID:
                    // 若为数字、英语字母，则无需转换状态。读入字符时即已经插入到当前字符，无需任何操作。
                    if (!isAlpha(cur) && !isDigit(cur)) {
                        // 不需要检测当前字符是否合法，先回溯到上一个字符，下次执行该函数时检查
                        log.add('[' + dateFormat.format(new Date()) + "] Identifier end at [" + line + ':' + column + "] ^_^");
                        log.add('[' + dateFormat.format(new Date()) + "] Backtracking for next token...");
                        backTrackChar(sb.charAt(sb.length() - 1));
                        token = new Token(line, column, TokenType.ID, sb.substring(0, sb.length() - 1));
                        token.checkKeyWords();
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + token);
                        return token;
                    }
                    break;
                // </editor-fold>
                // <editor-fold desc="case INNUM 识别数字">
                case INNUM:
                    // 若仍为数字字符，则保持数字状态
                    if (!isDigit(cur)) {
                        // 不需要检测当前字符是否合法，先回溯到上一个字符，保存当前数字token，下次执行该函数时检查
                        log.add('[' + dateFormat.format(new Date()) + "] Number end at [" + line + ':' + column + "] ^_^");
                        log.add('[' + dateFormat.format(new Date()) + "] Backtracking for next token...");
                        backTrackChar(sb.charAt(sb.length() - 1));
                        token = new Token(line, column, TokenType.INTC, sb.substring(0, sb.length() - 1));
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + token);
                        return token;
                    }
                    break;
                // </editor-fold>
                //<editor-fold desc="case INASSIGN">
                case INASSIGN:
                    if (cur == '=') {
                        token = new Token(line, column, TokenType.ASSIGN, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + token);
                        return token;
                    } else {
                        log.add('[' + dateFormat.format(new Date()) + "] Illegal assign operator at [" + line + ':' + column + "] T_T");
                        state = LexerState.ERROR;
                    }
                    break;
                // </editor-fold>
                //<editor-fold desc="case INCOMMENT">
                case INCOMMENT:
                    // 不需要读取注释内容，直接删除即可
                    sb.deleteCharAt(sb.length() - 1);
                    while (cur != '}' && cur != -1) {
                        cur = getChar();
                    }

                    if (cur != '}') {
                        log.add('[' + dateFormat.format(new Date()) + "] Illegal comment - not closed");
                        state = LexerState.ERROR;
                    } else {
                        state = LexerState.NORMAL;
                    }
                    break;
                // </editor-fold>
                //<editor-fold desc="case INDOT">
                case INDOT:
                    if (isAlpha(cur)) {
                        log.add('[' + dateFormat.format(new Date()) + "] The dot is part of record.");
                        log.add('[' + dateFormat.format(new Date()) + "] Backtracking for next token...");
                        backTrackChar(cur);
                        sb.deleteCharAt(sb.length() - 1);
                        token = new Token(line, column, TokenType.DOT, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + token);
                        return token;
                    } else if (cur == '.') {
                        state = LexerState.INRANGE;
                        break;
                    } else {
                        int dotLine = line;
                        int dotColumn = column - 1;
                        while (isBlank(cur)) {
                            cur = getChar();
                        }
                        if (cur == -1) {
                            token = new Token(dotLine, dotColumn, TokenType.EOF, ".");
                            log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                            log.add('[' + dateFormat.format(new Date()) + "] Found terminate sign. Bye! >_<" + sb);
                            terminated = true;
                            return token;
                        } else {
                            log.add('[' + dateFormat.format(new Date()) + "] Illegal dot found at [" + dotLine + ':' + dotColumn + "] T_T");
                            state = LexerState.ERROR;
                        }
                    }
                    break;
                //</editor-fold>
                //<editor-fold desc="case INRANGE">
                case INRANGE:
                    if (isDigit(cur)) {
                        log.add('[' + dateFormat.format(new Date()) + "] Found array index.");
                        log.add('[' + dateFormat.format(new Date()) + "] Backtracking for next token...");
                        backTrackChar(cur);
                        sb.deleteCharAt(sb.length() - 1);
                        token = new Token(line, column, TokenType.UNDERRANGE, sb.toString());
                        log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                        return token;
                    } else {
                        log.add('[' + dateFormat.format(new Date()) + "] Illegal array range found at [" + line + ':' + column + "] T_T");
                        state = LexerState.ERROR;
                    }
                    break;
                // </editor-fold>
                //<editor-fold desc="case INCHAR">
                case INCHAR:
                    if (isAlpha(cur) || isDigit(cur)) {
                        cur = getChar();
                        if (cur == '\'') {
                            token = new Token(line, column, TokenType.CHAR, sb.toString());
                            log.add('[' + dateFormat.format(new Date()) + "] Get token!!!" + sb);
                            return token;
                        }
                    } else {
                        log.add('[' + dateFormat.format(new Date()) + "] Illegal char constant found at [" + line + ':' + column + "] T_T");
                        state = LexerState.ERROR;
                    }
                    break;
                    // </editor-fold>
                case ERROR:
                    log.add('[' + dateFormat.format(new Date()) + "] Illegal token found near [" + line + ':' + column + "] T_T");
                    token = new Token(line, column, TokenType.ERROR, sb.toString());
                    return token;
                default:
                    state = LexerState.ERROR;
                    break;
            }
            cur = getChar();
        }

        return null;
    }

    private int getChar() throws IOException {
        int ch;
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        dateFormat.setTimeZone(TimeZone.getTimeZone("GMT+8"));
        // 先判断backtrack中是否存储了回溯的字符
        if (backtrack != -1 && backtrack != ' ' && backtrack != '\r' && backtrack != '\n') {
            ch = backtrack;
            backtrack = -1;
        } else if (backtrack == ' ' || backtrack == '\r') {
            column++;
            backtrack = -1;
            ch = reader.read();
        } else {
            ch = reader.read();
        }

        if (lf) {
            column = 0;
            line++;
        }

        if (ch == '\n') {
            lf = true;
            column++;
        } else if (ch != -1) {
            column++;
            lf = false;
        }

        log.add('[' + dateFormat.format(new Date()) + "] Get char at" + '[' + line + ':' + column + ']' + ": " + showChar(ch));
        return ch;
    }

    private String showChar(int ch) {
        if (ch == '\n')
            return "\\n";
        else if (ch == '\r')
            return "\\r";
        else return "" + (char) ch;
    }

    private boolean isAlpha(int ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    private boolean isDigit(int ch) {
        return (ch >= '0' && ch <= '9');
    }

    private boolean isBlank(int ch) {
        return ((char) ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
    }

    private void backTrackChar(int ch) {
        backtrack = ch;
        column--;
    }

    public List<String> getLog(){
        return this.log;
    }

    private enum LexerState {
        NORMAL,
        INID,
        INNUM,
        INASSIGN,
        INCOMMENT,
        INDOT,
        INRANGE,
        INCHAR,
        ERROR
    }

    public static void main(String[] args) {
        InputStream in = SNLLexer.class.getClassLoader().getResourceAsStream("p.snl");
        SNLLexer lexer = new SNLLexer();
        try {
            LexerResult result = lexer.getLexerResult(new InputStreamReader(in));
            List<Token> list = result.getTokenList();
            System.out.println();
            if (!list.isEmpty()) {
                System.out.print("[ 行:列 ]| 词素信息 | 词法单元 \n");
                System.out.print("---------+----------+----------\n");
            }
            for (Token t : list) {
                System.out.printf("[%3d:%-3d]| %8s | %8s\n", t.getLine(), t.getColumn(), t.getValue(), t.getType());
            }
            for(String l: lexer.log){
                System.out.println(l);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
