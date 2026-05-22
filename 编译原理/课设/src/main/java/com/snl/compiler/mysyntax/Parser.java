package com.snl.compiler.mysyntax;

import com.snl.compiler.mylexer.SNLLexer;
import com.snl.compiler.mylexer.Token;
import com.snl.compiler.mylexer.TokenType;
import com.snl.compiler.mysyntax.symbols.NON_TERMINAL;
import com.snl.compiler.mysyntax.symbols.NonTerminal;
import com.snl.compiler.mysyntax.symbols.Symbol;
import com.snl.compiler.mysyntax.symbols.Terminal;
import com.snl.compiler.mysyntax.tree.SyntaxTree;
import com.snl.compiler.mysyntax.tree.TreeNode;


import java.io.*;
import java.nio.charset.StandardCharsets;
import java.text.SimpleDateFormat;
import java.util.*;

public class Parser {
    private final SNLLexer lexer = new SNLLexer();
    private final List<String> log = new ArrayList<String>();
    private final List<String> error = new ArrayList<String>();
    private List<Token> tokens;
    private int index = 0;
    private SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    private SyntaxTree tree;

    public Parser() {
        dateFormat.setTimeZone(TimeZone.getTimeZone("GMT+8"));
    }

    public List<String> getLog() {
        return log;
    }

    public List<String> getError() {
        return error;
    }

    public SyntaxTree parse() {
        log.add('[' + dateFormat.format(new Date()) + "] Starting Grammar Parser...");

        Stack<Symbol> stack = new Stack<Symbol>();
        NonTerminal startSymbol = NonTerminal.createNonTerminal("Program");
        TreeNode root = startSymbol.getNode();
        stack.push(startSymbol);

        Symbol symbol = null;
        while (!stack.isEmpty()) {
            symbol = stack.pop();
            if (symbol instanceof Terminal) {
                log.add('[' + dateFormat.format(new Date()) + "] Found Terminal - " + ((Terminal) symbol).getToken().getType());
                TreeNode non = match(((Terminal) symbol).getToken().getType());
                if (non != null) {
                    symbol.getNode().setText(non.getText());
                    log.add('[' + dateFormat.format(new Date()) + "] Matched Terminal - " + ((Terminal) symbol).getNode().getText());
                } else {
                    log.add('[' + dateFormat.format(new Date()) + "] Failed to Match Terminal.");
//                    return null;
                    break;
                }
            } else if (symbol instanceof NonTerminal) {
                log.add('[' + dateFormat.format(new Date()) + "] Found NonTerminal - " + ((NonTerminal) symbol).getValue());
                List<Symbol> preds = find((NonTerminal) symbol);
                log.add('[' + dateFormat.format(new Date()) + "] Predicts: " + preds);

                // 以二叉树表示一般树
                if (preds != null) {
                    int size = preds.size();
                    for (int i = 0; i < size - 1; i++) {
                        preds.get(i).getNode().setSiblings(preds.get(i + 1).getNode());
                    }
                    symbol.getNode().setChildren(preds.get(0).getNode());
                    log.add('[' + dateFormat.format(new Date()) + "] Subtree built.");

                    // 子树入栈
                    for (int i = size - 1; i >= 0; i--) {
                        Symbol item = preds.get(i);
                        if (item instanceof Terminal || !((NonTerminal) item).isBlank())
                            stack.push(item);
                    }
                } else {
                    log.add('[' + dateFormat.format(new Date()) + "] Failed to Match NonTerminal.");
                    error.add('[' + dateFormat.format(new Date()) + "] Failed to Match NonTerminal near" + getPeekToken());
//                    return null;
                    break;
                }
            } else {
                log.add('[' + dateFormat.format(new Date()) + "] Illegal token: " + symbol.getNode().getText());
                error.add('[' + dateFormat.format(new Date()) + "] Illegal token: " + symbol.getNode().getText());
//                return null;
                break;
            }
        }
        tree = new SyntaxTree(root);
        return tree;
    }

    public void lexParse(String srcCode) throws IOException {
        log.add('[' + dateFormat.format(new Date()) + "] Starting parsing. Loading lexer... ");
        InputStream in = new ByteArrayInputStream(srcCode.getBytes(StandardCharsets.UTF_8));
        tokens = lexer.getLexerResult(new InputStreamReader(in)).getTokenList();
        log.add('[' + dateFormat.format(new Date()) + "] Lexer terminated.");
    }

    TreeNode match(TokenType type) {
        Token t = getNextToken();
        TreeNode node = null;
        if (t != null) {
            if (t.getType().equals(type)) {
                node = new TreeNode(t);
                log.add('[' + dateFormat.format(new Date()) + "] Match token with type " + type + ": " + t);
            } else {
                log.add('[' + dateFormat.format(new Date()) + "] Not match: " + type + ": " + t);
            }
        } else {
            log.add('[' + dateFormat.format(new Date()) + "] Finished match.");
        }
        return node;
    }

    List<Symbol> find(NonTerminal symbol) {
        Token token = getPeekToken();
        String value = symbol.getValue();
        log.add('[' + dateFormat.format(new Date()) + "] Checking non-terminal: " + value + " Input token: " + token.getValue());
        NON_TERMINAL nt = NON_TERMINAL.valueOf(value);
        log.add('[' + dateFormat.format(new Date()) + "] FOUND non-terminal: " + nt);
        return nt.predict(token);
    }

    private Token getNextToken() {
        Token token = null;
        if (index < tokens.size()) {
            token = tokens.get(index++);
            log.add('[' + dateFormat.format(new Date()) + "] Read next token - " + token);
        } else {
            log.add('[' + dateFormat.format(new Date()) + "] Finished reading tokens.");
        }

        return token;
    }

    private Token getPeekToken() {
        Token token = null;
        if (index < tokens.size()) {
            token = tokens.get(index);
            log.add('[' + dateFormat.format(new Date()) + "] Read current token - " + token);
        } else {
            log.add('[' + dateFormat.format(new Date()) + "] Finished reading tokens.");
        }

        return token;
    }

    public static void main(String[] args) throws IOException {
        String src = "{传说中的注释}\n" +
                "program p\n" +
                "type t = integer;\n" +
                "    var t v1;\n" +
                "    char v2,v114514;\n" +
                "begin\n" +
                "    read(v1);\n" +
                "    v1 := v1 + 10;\n" +
                "    v114514 := 7;\n" +
                "    {write('a')}\n" +
                "    write(v1)\n" +
                "end.\n" +
                "\n" +
                "\n";
        Parser p = new Parser();
        p.lexParse(src);
        SyntaxTree result = p.parse();
        // result.setOut(new PrintStream(new File("")));
        if (result != null)
            result.preOrderRecursive();
    }
}
