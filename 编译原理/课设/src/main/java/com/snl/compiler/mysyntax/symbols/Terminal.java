package com.snl.compiler.mysyntax.symbols;


import com.snl.compiler.mylexer.Token;
import com.snl.compiler.mylexer.TokenType;
import com.snl.compiler.mysyntax.tree.TreeNode;

public class Terminal extends Symbol{
    private final TreeNode node;
    private Token token;

    public Terminal(Token token) {
        this.token = token;
        this.node = new TreeNode(token);
    }

    @Override
    public TreeNode getNode() {
        return node;
    }

    public Token getToken() {
        return token;
    }

    public static Terminal terminalFactory(TokenType tokenType) {
        return new Terminal(new Token(tokenType));
    }

    public static Terminal terminalFactory(Token token) {
        return new Terminal(token);
    }
}
