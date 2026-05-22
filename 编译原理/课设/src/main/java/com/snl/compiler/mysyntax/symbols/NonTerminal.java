package com.snl.compiler.mysyntax.symbols;

import com.snl.compiler.mysyntax.tree.TreeNode;

public class NonTerminal extends Symbol {
    private TreeNode node;
    private String value;

    public NonTerminal(String value) {
        this.value = value;
        node = new TreeNode(value);
    }

    @Override
    public TreeNode getNode() {
        return node;
    }

    public String getValue() {
        return value;
    }

    public static NonTerminal createNonTerminal(String value) {
        return new NonTerminal(value);
    }

    public boolean isBlank(){
        return value == null || value.trim().isEmpty() || value.equals("blank");
    }
}
