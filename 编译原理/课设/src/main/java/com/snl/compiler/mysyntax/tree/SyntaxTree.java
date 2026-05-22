package com.snl.compiler.mysyntax.tree;

import java.io.FileNotFoundException;

public class SyntaxTree {
    public TreeNode root;

    public SyntaxTree() {
    }

    public SyntaxTree(TreeNode root) {
        this.root = root;
    }

    public void preOrderRecursive() throws FileNotFoundException {
        preOrderRecursiveCore(root, 0, 0, new int[100]);
    }

    public void preOrderRecursiveCore(TreeNode node, int level, int cnt, int[] b) throws FileNotFoundException {
        if (node == null) {
            return;
        }

        for (int i = 0; i < level - 1; i++) {
            if (b[i] == 1) {
                System.out.print("|  ");
            } else {
                System.out.print("   ");
            }
        }

        if (node == root) {
            System.out.println(node.getText());
        } else {
            System.out.println("|__" + node.getText());
        }
        if (node.hasChild()) {
            if (node.hasSiblings()) {
                if (level > 0)
                    b[level - 1] = 1;
                preOrderRecursiveCore(node.getChildren(), level + 1, cnt + 1, b);
            } else {
                if (level > 0)
                    b[level - 1] = 0;
                preOrderRecursiveCore(node.getChildren(), level + 1, cnt, b);
            }
        }

        if (node.hasSiblings()) {

            preOrderRecursiveCore(node.getSiblings(), level, cnt, b);
        }
    }
}
