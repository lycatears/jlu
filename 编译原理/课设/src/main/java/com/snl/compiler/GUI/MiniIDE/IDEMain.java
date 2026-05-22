package com.snl.compiler.GUI.MiniIDE;

import com.snl.compiler.GUI.CustomTreeCellRenderer;
import com.snl.compiler.GUI.CustomTreeModel;
import com.snl.compiler.mylexer.LexerResult;
import com.snl.compiler.mylexer.SNLLexer;
import com.snl.compiler.mylexer.Token;
import com.snl.compiler.mysyntax.Parser;
import com.snl.compiler.mysyntax.tree.TreeNode;
import com.snl.compiler.semantic.SemanticAnalyzer;

import javax.swing.*;
import javax.swing.JPanel;
import javax.swing.table.DefaultTableModel;
import javax.swing.text.*;
import java.awt.event.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.List;

public class IDEMain {
    private JButton newSnlFIle;
    private JButton openSnlFIle;
    private JButton compileButton;
    private JPanel IDEPanel;
    private JPanel sourceCodePanel;
    private JTabbedPane tabbedPane1;
    private JTable lexTable;
    private JTextArea compileLog;
    private JTextPane code;
    private JButton save;
    private JScrollPane codeScrollPane;
    private JTree grammarTree;
    private JTextPane semanticResult;
    private JTextPane syntaxError;
    private SNLLexer lexer = new SNLLexer();
    private List<Token> list;

    public IDEMain() {
        LineNumberHeaderView lineNumber = new LineNumberHeaderView();
        lineNumber.setLineHeight(18);
        codeScrollPane.setRowHeaderView(lineNumber);
        StyledDocument doc = code.getStyledDocument();
        SimpleAttributeSet attrs = new SimpleAttributeSet();
        StyleConstants.setLineSpacing(attrs, 20.0f);

        compileButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                InputStream in = new ByteArrayInputStream(code.getText().getBytes(StandardCharsets.UTF_8));
                try {
                    // 清空日志
                    lexer.getLog().clear();
                    DefaultTableModel dtm = (DefaultTableModel) lexTable.getModel();
                    compileLog.setText("");
                    syntaxError.setText("");
                    semanticResult.setText("");

                    for(int i = 0; i < dtm.getRowCount(); i++){
                        dtm.removeRow(0);
                    }

                    //词法分析
                    LexerResult result = lexer.getLexerResult(new InputStreamReader(in));
                    Parser parser = new Parser();
                    parser.lexParse(code.getText());

                    //语法分析
                    TreeNode root = parser.parse().root;
                    CustomTreeModel ctm = new CustomTreeModel(root);
                    grammarTree.setModel(ctm);
                    grammarTree.setCellRenderer(new CustomTreeCellRenderer());

                    //语义分析
                    SemanticAnalyzer sa = new SemanticAnalyzer();
                    sa.analyze(root);

                    list = result.getTokenList();
                    for (Token token : list) {
                        String[] columnNames = {"行号", "列号", "内容", "类型"};
                        dtm.setColumnIdentifiers(columnNames);
                        dtm.addRow(new Object[]{token.getLine(), token.getColumn(), token.getValue(), token.getType()});
                    }

                    for (String log : lexer.getLog()) {
                        compileLog.append(log + "\n");
                    }

                    for(String log: parser.getLog()){
                        compileLog.append(log + "\n");
                    }

                    for(String log: parser.getError()){
                        StyledDocument sd = (StyledDocument) syntaxError.getDocument();
                        AttributeSet as = sd.addStyle("error", null);
                        sd.insertString(sd.getLength(),log+'\n',as);
                    }

                    for(String log: sa.getLog()){
                        compileLog.append(log + "\n");
                        if(log.contains("ERROR")){
                            StyledDocument sd = (StyledDocument) semanticResult.getDocument();
                            AttributeSet as = sd.addStyle("error", null);
                            sd.insertString(sd.getLength(),log+'\n',as);
                        }
                    }
                } catch (IOException | BadLocationException ex) {
                    throw new RuntimeException(ex);
                }
            }
        });

        save.addActionListener(new SaveButtonListener(code));
        openSnlFIle.addActionListener(new OpenButtonListener(code));
        newSnlFIle.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                int choice = JOptionPane.showOptionDialog(code,"是否清空代码？","提示",JOptionPane.DEFAULT_OPTION,JOptionPane.WARNING_MESSAGE,null,null,null);
                if(choice == JOptionPane.OK_OPTION){
                    code.setText("");
                }
            }
        });
    }

    public static void main(String[] args) {
        try {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
        } catch (Exception e) {
            e.printStackTrace();
        }
        JFrame frame = new JFrame("IDEMain");
        frame.setSize(1440, 900);
        frame.setContentPane(new IDEMain().IDEPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }

    private class SaveButtonListener implements ActionListener {
        private JTextComponent textComponent;

        public SaveButtonListener(JTextComponent textComponent) {
            this.textComponent = textComponent;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            // 创建文件选择对话框
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setDialogTitle("保存文件");

            // 设置默认文件名（可选）
            fileChooser.setSelectedFile(new File("untitled.snl"));

            // 显示保存对话框
            int userSelection = fileChooser.showSaveDialog(save);

            if (userSelection == JFileChooser.APPROVE_OPTION) {
                File fileToSave = fileChooser.getSelectedFile();
                try {
                    // 写入文件
                    BufferedWriter writer = new BufferedWriter(new FileWriter(fileToSave));
                    writer.write(textComponent.getText());
                    writer.close();

                    // 显示成功消息
                    JOptionPane.showMessageDialog(save,
                            "文件已保存到: " + fileToSave.getAbsolutePath(),
                            "保存成功",
                            JOptionPane.INFORMATION_MESSAGE);
                } catch (IOException ex) {
                    // 显示错误消息
                    JOptionPane.showMessageDialog(save,
                            "保存文件时出错: " + ex.getMessage(),
                            "错误",
                            JOptionPane.ERROR_MESSAGE);
                    ex.printStackTrace();
                }
            }
        }
    }

    private class OpenButtonListener implements ActionListener {
        private JTextComponent textComponent;

        public OpenButtonListener(JTextComponent textComponent) {
            this.textComponent = textComponent;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            // 创建文件选择对话框
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setDialogTitle("打开文件");

            // 设置文件过滤器（可选）
            fileChooser.setFileFilter(new javax.swing.filechooser.FileNameExtensionFilter(
                    "SNL source Files (*.txt)", "snl"));

            // 显示打开对话框
            int userSelection = fileChooser.showOpenDialog(openSnlFIle);

            if (userSelection == JFileChooser.APPROVE_OPTION) {
                File fileToOpen = fileChooser.getSelectedFile();
                try {
                    // 读取文件内容
                    StringBuilder content = new StringBuilder();
                    BufferedReader reader = new BufferedReader(new FileReader(fileToOpen));

                    String line;
                    while ((line = reader.readLine()) != null) {
                        content.append(line).append("\n");
                    }
                    reader.close();

                    // 设置文本到编辑器
                    textComponent.setText(content.toString());
                } catch (IOException ex) {
                    // 显示错误消息
                    JOptionPane.showMessageDialog(openSnlFIle,
                            "打开文件时出错: " + ex.getMessage(),
                            "错误",
                            JOptionPane.ERROR_MESSAGE);
                    ex.printStackTrace();
                }
            }
        }
    }

}

