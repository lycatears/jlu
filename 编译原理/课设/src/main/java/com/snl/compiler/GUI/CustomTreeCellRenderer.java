package com.snl.compiler.GUI;

import com.snl.compiler.mysyntax.tree.TreeNode;

import javax.swing.JTree;
import javax.swing.tree.DefaultTreeCellRenderer;
import java.awt.Component;

public class CustomTreeCellRenderer extends DefaultTreeCellRenderer {
    @Override
    public Component getTreeCellRendererComponent(JTree tree, Object value,
                                                  boolean sel, boolean expanded, boolean leaf, int row, boolean hasFocus) {
        super.getTreeCellRendererComponent(tree, value, sel, expanded, leaf, row, hasFocus);

        TreeNode node = (TreeNode) value;
        setText(node.getText()); // 显示节点的text属性

        return this;
    }
}