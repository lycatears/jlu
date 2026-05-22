package com.snl.compiler.mylexer;

import java.util.HashSet;
import java.util.Set;

public class Token {
    private static final Set<String> keywords = new HashSet<>();
    private Integer line;
    private Integer column;
    private TokenType type;
    private String value;

    public Token() {
        this(TokenType.EMPTY);
        if (keywords.isEmpty()) {
            initKeywordSet();
        }
    }

    public Token(TokenType type) {
        this(0, 0, type, type.getStr());
        if (keywords.isEmpty()) {
            initKeywordSet();
        }
    }

    Token(int line, int column, TokenType type, String value) {
        this.line = line;
        this.column = column;
        this.type = type;
        this.value = value;
        if (keywords.isEmpty()) {
            initKeywordSet();
        }
    }

    private void initKeywordSet() {
        for (int i = 2; i <= 23; i++) {
            String keystr = TokenType.values()[i].getStr();
            keywords.add(keystr);
        }
    }

    @Override
    public String toString() {
        return "< [" + line + ":" + column + "], " + type + ", " + value + " >";
    }

    public int getLine() {
        return line;
    }

    public int getColumn() {
        return column;
    }

    public TokenType getType() {
        return type;
    }

    public String getValue() {
        return value;
    }

    public void checkKeyWords() {
        if (type == TokenType.ID) {
            if (keywords.contains(value)) {
                type = TokenType.valueOf(value.toUpperCase());
            }
        }
    }
}
