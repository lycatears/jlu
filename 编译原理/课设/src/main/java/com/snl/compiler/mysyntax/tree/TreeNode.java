package com.snl.compiler.mysyntax.tree;

import com.snl.compiler.mylexer.Token;

public class TreeNode {
    private TreeNode siblings;
    private TreeNode children;
    private String text;
    private Token token = null;

    public TreeNode() {

    }

    public TreeNode(String value) {
        this.text = value;
    }

    public TreeNode(Token token){
        if(token != null){
            this.text = token.toString();
        }
        this.token = token;
    }

    public boolean hasChild() {
        return children != null;
    }

    public boolean hasSiblings() {
        return siblings != null;
    }

    public int siblingsSize() {
        TreeNode temp = siblings;
        int cnt = 0;
        while (temp != null) {
            cnt++;
            temp = temp.siblings;
        }
        return cnt;
    }

    public TreeNode getSiblings() {
        return siblings;
    }

    public void setSiblings(TreeNode siblings) {
        this.siblings = siblings;
    }

    public TreeNode getChildren() {
        return children;
    }

    public void setChildren(TreeNode children) {
        this.children = children;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public Token getToken() {
        return token;
    }

    @Override
    public String toString() {
        return text + " " + (siblings != null ? siblings : "");
    }
}
