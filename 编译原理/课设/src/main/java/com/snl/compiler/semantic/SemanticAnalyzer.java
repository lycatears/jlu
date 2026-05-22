package com.snl.compiler.semantic;

import com.snl.compiler.mylexer.TokenType;
import com.snl.compiler.mysyntax.Parser;
import com.snl.compiler.mysyntax.symbols.Terminal;
import com.snl.compiler.mysyntax.tree.SyntaxTree;
import com.snl.compiler.mysyntax.tree.TreeNode;

import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.*;

public class SemanticAnalyzer {
    private List<String> log = new ArrayList<String>();
    private Parser parser = new Parser();
    private DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    private SymbolTable globalTable = new SymbolTable(null); // 全局符号表

    public SemanticAnalyzer() {
        dateFormat.setTimeZone(TimeZone.getTimeZone("GMT+8"));
    }

    public static void main(String[] args) throws IOException {
        String src = "{冒泡排序}\n" +
                "{输入m,表示要排序的数的个数；接着输入m个整数；\n" +
                " 输出从小到大排序后的结果}\n" +
                "\n" +
                "program  p\n" +
                "var  integer  i,j,num;\n" +
                "      array[1..20] of  integer a;\n" +
                "\n" +
                "procedure  q(integer num);\n" +
                "var  integer i,j,k;\n" +
                "     integer t;\n" +
                "begin\n" +
                "  i:=1;\n" +
                "  j:=1;\n" +
                "  while i < num do\n" +
                "     j:=num-i+1;\n" +
                "     k:=1;\n" +
                "     while k<j  do\n" +
                "    \t if a[k+1] < a[k]  \n" +
                "         then  t:=a[k];\n" +
                "\t       a[k]:=a[k+1];\n" +
                "\t       a[k+1]:=t\n" +
                "         else  t:=0\n" +
                "         fi;   \n" +
                "     k:=k+1\n" +
                "     endwh;\n" +
                "  i:=i+1\n" +
                "  endwh\n" +
                "end\n" +
                "\n" +
                "begin\n" +
                "   read(num);\n" +
                "   i:=1;\n" +
                "   while i<(num+1)  do\n" +
                "     read(j);\n" +
                "     a[i]:=j;\n" +
                "     i:=i+1\n" +
                "   endwh;\n" +
                "   q(num);\n" +
                "   i:=1;\n" +
                "   while  i<(num+1) do \n" +
                "       write(a[i]);\n" +
                "       i:=i+1\n" +
                "   endwh\n" +
                "end.\n" +
                "  ";
        Parser p = new Parser();
        p.lexParse(src);
        SyntaxTree result = p.parse();

        SemanticAnalyzer sa = new SemanticAnalyzer();
        sa.analyze(result.root);
    }

    public List<String> getLog() {
        return log;
    }

    public void analyze(TreeNode root) {
        traverse(root, globalTable);
    }

    private void traverse(TreeNode node, SymbolTable currentScope) {
        while (node != null) {
            log.add('[' + dateFormat.format(new Date()) + "] Current Node: " + node.getText());
            switch (node.getText()) {
                case "Program":
                    traverse(node.getChildren(), currentScope);
                    break;
                case "VarIdList":
                case "FormList":
                    List<String> varNames = extractIdentifier(node, null); // 从子节点中提取变量名
                    for (String varName : varNames) {
                        if (currentScope.contains(varName)) {
                            reportError("重复定义变量: " + varName, node);
                            log.add('[' + dateFormat.format(new Date()) + "] [ERROR] Duplicate variable definition: " + varName);
                        } else {
                            currentScope.put(varName, new Terminal(node.getToken())); // 简化处理类型为 int
                        }
                    }
                    break;
                case "ProcName":
                    List<String> procNames = extractIdentifier(node, null);
                    for (String procName : procNames) {
                        if (currentScope.parent.contains(procName)) {
                            reportError("重复定义变量: " + procName, node);
                            log.add('[' + dateFormat.format(new Date()) + "] [ERROR] Duplicate proc definition: " + procName);
                        } else {
                            currentScope.parent.put(procName, new Terminal(node.getToken()));
                        }
                    }
                    break;
                case "ProcDec":
                    // 创建新的作用域
                    SymbolTable newScope = new SymbolTable(currentScope);
                    traverse(node.getChildren(), newScope);
                    log.add('[' + dateFormat.format(new Date()) + "] New scope created: " + node.getText());
                    break;
                case "Stm":
                    // 出现表达式，需要检查变量是否存在
                    List<String> vars = extractIdentifier(node, null);
                    for (String var : vars) {
                        if (!currentScope.containsRecursive(var)) {
                            reportError("未定义变量" + var, node);
                            log.add('[' + dateFormat.format(new Date()) + "] [ERROR] Undefined variable: " + var);
                        }
                    }
                default:
                    traverse(node.getChildren(), currentScope);
                    break;
            }
            node = node.getSiblings();
        }
    }

    private void reportError(String message, TreeNode node) {
        System.err.println("语义错误: " + message + " at " + node.getToken());
    }

    private List<String> extractIdentifier(TreeNode node, List<String> ids) {
        // 递归查找 IDENTIFIER 类型子节点
        if (node == null) {
            return ids;
        }

        // 如果是作用域根节点，则无需查找语法树兄弟结点
        boolean isRoot = ids == null;
        if (ids == null) {
            ids = new ArrayList<>();
        }
        if (node.getToken() != null && node.getToken().getType() == TokenType.ID) {
            ids.add(node.getToken().getValue());
        }
        if (isRoot) {
            extractIdentifier(node.getChildren(), ids);
        } else {
            TreeNode sibling = node.getSiblings();
            while (sibling != null) {
                extractIdentifier(sibling, ids);
                sibling = sibling.getSiblings();
            }
            extractIdentifier(node.getChildren(), ids);
        }
        return ids;
    }

    private String extractLeft(TreeNode node) {
        return node.getToken().getValue();
    }
}
