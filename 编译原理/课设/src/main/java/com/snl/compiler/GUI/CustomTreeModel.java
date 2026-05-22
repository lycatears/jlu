package com.snl.compiler.GUI;
//package com.mytlx.compiler.GUI;
//
//import com.mytlx.compiler.mysyntax.tree.TreeNode;
//
//import javax.swing.tree.TreeModel;
//
//import javax.swing.event.TreeModelListener;
//import java.util.ArrayList;
//import java.util.List;
//
//public class CustomTreeModel implements TreeModel {
//    private final TreeNode root;
//
//    public CustomTreeModel(TreeNode root) {
//        this.root = root;
//    }
//
//    @Override
//    public Object getRoot() {
//        return root;
//    }
//
//    @Override
//    public Object getChild(Object parent, int index) {
//        TreeNode node = (TreeNode) parent;
//        if (index == 0) {
//            return node.getChildren(); // 第一个子节点是children
//        } else {
//            // 后续的子节点需要通过siblings链获取
//            TreeNode sibling = node.getChildren();
//            for (int i = 1; i <= index; i++) {
//                if (sibling == null) break;
//                if (i == index) return sibling;
//                sibling = sibling.getSiblings();
//            }
//        }
//        return null;
//    }
//
//    @Override
//    public int getChildCount(Object parent) {
//        TreeNode node = (TreeNode) parent;
//        if (node.getChildren() == null) {
//            return 0;
//        }
//        int count = 1; // 至少有children
//        TreeNode sibling = node.getChildren().getSiblings();
//        while (sibling != null) {
//            count++;
//            sibling = sibling.getSiblings();
//        }
//        return count;
//    }
//
//    @Override
//    public boolean isLeaf(Object node) {
//        return getChildCount(node) == 0 && ((TreeNode) node).getSiblings() == null;
//    }
//
//    @Override
//    public void valueForPathChanged(javax.swing.tree.TreePath path, Object newValue) {
//        // 实现如果需要编辑功能
//    }
//
//    @Override
//    public int getIndexOfChild(Object parent, Object child) {
//        TreeNode node = (TreeNode) parent;
//        TreeNode childNode = (TreeNode) child;
//
//        if (node.getChildren() == null) {
//            return -1;
//        }
//
//        if (node.getChildren() == childNode) {
//            return 0;
//        }
//
//        int index = 1;
//        TreeNode sibling = node.getChildren().getSiblings();
//        while (sibling != null) {
//            if (sibling == childNode) {
//                return index;
//            }
//            index++;
//            sibling = sibling.getSiblings();
//        }
//
//        return -1;
//    }
//
//    // 以下方法用于监听器管理，如果不需要可以留空
//    private List<TreeModelListener> listeners = new ArrayList<>();
//
//    @Override
//    public void addTreeModelListener(TreeModelListener l) {
//        listeners.add(l);
//    }
//
//    @Override
//    public void removeTreeModelListener(TreeModelListener l) {
//        listeners.remove(l);
//    }
//}

import com.snl.compiler.mysyntax.tree.TreeNode;
import javax.swing.event.TreeModelEvent;
import javax.swing.event.TreeModelListener;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;
import java.util.ArrayList;
import java.util.List;

public class CustomTreeModel implements TreeModel {

    private TreeNode root;
    private final List<TreeModelListener> treeModelListeners = new ArrayList<>();

    public CustomTreeModel(TreeNode root) {
        this.root = root;
    }

    @Override
    public Object getRoot() {
        return root;
    }

    @Override
    public Object getChild(Object parent, int index) {
        if (parent instanceof TreeNode) {
            TreeNode parentNode = (TreeNode) parent;
            if (index == 0) { // 第一个子节点是 children
                return parentNode.getChildren();
            } else { // 后续子节点是 siblings
                TreeNode currentChild = parentNode.getChildren();
                for (int i = 0; i < index; i++) {
                    if (currentChild != null) {
                        currentChild = currentChild.getSiblings();
                    } else {
                        return null; // 越界
                    }
                }
                return currentChild;
            }
        }
        return null;
    }

    @Override
    public int getChildCount(Object parent) {
        if (parent instanceof TreeNode) {
            TreeNode parentNode = (TreeNode) parent;
            int count = 0;
            if (parentNode.getChildren() != null) {
                count++; // children 算一个子节点
                TreeNode currentSibling = parentNode.getChildren().getSiblings();
                while (currentSibling != null) {
                    count++;
                    currentSibling = currentSibling.getSiblings();
                }
            }
            return count;
        }
        return 0;
    }

    @Override
    public boolean isLeaf(Object node) {
        if (node instanceof TreeNode) {
            TreeNode treeNode = (TreeNode) node;
            // 如果一个节点没有 children 也没有 siblings，那么它就是叶子节点
            return treeNode.getChildren() == null;
        }
        return true; // 默认情况下，非 TreeNode 对象认为是叶子
    }


    @Override
    public void valueForPathChanged(TreePath path, Object newValue) {
        // 这个方法在用户编辑树节点时调用。如果你的树是只读的，可以留空。
        // 如果允许编辑，你需要更新你的底层数据结构并通知监听器。
        System.out.println("Path changed: " + path + ", New Value: " + newValue);
        // 通常，你需要找到 path 对应的 TreeNode，更新其 text 属性，然后 fireTreeNodesChanged
        // 为了简化，这里暂时不实现编辑功能
    }

    @Override
    public int getIndexOfChild(Object parent, Object child) {
        if (parent instanceof TreeNode && child instanceof TreeNode) {
            TreeNode parentNode = (TreeNode) parent;
            TreeNode childNode = (TreeNode) child;
            if (parentNode.getChildren() == childNode) {
                return 0; // 第一个子节点
            }
            TreeNode currentSibling = parentNode.getChildren();
            int index = 0;
            while (currentSibling != null) {
                if (currentSibling == childNode) {
                    return index;
                }
                currentSibling = currentSibling.getSiblings();
                index++;
            }
        }
        return -1;
    }

    @Override
    public void addTreeModelListener(TreeModelListener l) {
        treeModelListeners.add(l);
    }

    @Override
    public void removeTreeModelListener(TreeModelListener l) {
        treeModelListeners.remove(l);
    }

    // 辅助方法，用于通知 JTree 数据已更改
    protected void fireTreeNodesChanged(Object source, Object[] path, int[] childIndices, Object[] children) {
        TreeModelEvent event = new TreeModelEvent(source, path, childIndices, children);
        for (TreeModelListener listener : treeModelListeners) {
            listener.treeNodesChanged(event);
        }
    }

    protected void fireTreeNodesInserted(Object source, Object[] path, int[] childIndices, Object[] children) {
        TreeModelEvent event = new TreeModelEvent(source, path, childIndices, children);
        for (TreeModelListener listener : treeModelListeners) {
            listener.treeNodesInserted(event);
        }
    }

    protected void fireTreeNodesRemoved(Object source, Object[] path, int[] childIndices, Object[] children) {
        TreeModelEvent event = new TreeModelEvent(source, path, childIndices, children);
        for (TreeModelListener listener : treeModelListeners) {
            listener.treeNodesRemoved(event);
        }
    }

    protected void fireTreeStructureChanged(Object source, Object[] path) {
        TreeModelEvent event = new TreeModelEvent(source, path);
        for (TreeModelListener listener : treeModelListeners) {
            listener.treeStructureChanged(event);
        }
    }
}