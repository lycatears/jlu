package com.snl.compiler.GUI.MiniIDE;

import java.awt.*;

/**
 *
 */
public class LineNumberHeaderView extends javax.swing.JComponent {
    private final Font DEFAULT_FONT = new Font(Font.MONOSPACED, Font.PLAIN, 14);
    public final Color DEFAULT_BACKGROUND = new Color(228, 228, 228);
    public final Color DEFAULT_FOREGROUND = Color.BLACK;
    public final int nHEIGHT = Integer.MAX_VALUE - 1000000;
    public final int MARGIN = 5;
    private int lineHeight;
    private int fontLineHeight;
    private int currentRowWidth;
    private FontMetrics fontMetrics;

    /**
     * 行号属性设置
     */
    public LineNumberHeaderView() {
        setFont(DEFAULT_FONT);
        setForeground(DEFAULT_FOREGROUND);
        setBackground(DEFAULT_BACKGROUND);
        setPreferredSize(9999);
    }

    /**
     * 设置大小
     * @param row
     */
    public void setPreferredSize(int row) {
        int width = fontMetrics.stringWidth(String.valueOf(row));
        if (currentRowWidth < width) {
            currentRowWidth = width;
            setPreferredSize(new Dimension(2 * MARGIN + width + 1, nHEIGHT));
        }
    }

    /**
     * 设置字体
     * @param font
     */
    @Override
    public void setFont(Font font) {
        super.setFont(font);
        fontMetrics = getFontMetrics(getFont());
        fontLineHeight = fontMetrics.getHeight();
    }

    public int getLineHeight() {
        if (lineHeight == 0) {
            return fontLineHeight;
        }
        return lineHeight;
    }

    public void setLineHeight(int lineHeight) {
        if (lineHeight > 0) {
            this.lineHeight = lineHeight;
        }
    }

    public int getStartOffset() {
        return 2;
    }

    /**
     * 画行号区域
     * @param g
     */
    @Override
    protected void paintComponent(Graphics g) {
        int nLineHeight = getLineHeight();
        int startOffset = getStartOffset();
        Rectangle drawHere = g.getClipBounds();
        g.setColor(getBackground());
        g.fillRect(drawHere.x, drawHere.y, drawHere.width, drawHere.height);
        g.setColor(getForeground());
        int startLineNum = (drawHere.y / nLineHeight) + 1;
        int endLineNum = startLineNum + (drawHere.height / nLineHeight);
        int start = (drawHere.y / nLineHeight) * nLineHeight + nLineHeight - startOffset;
        for (int i = startLineNum; i <= endLineNum; ++i) {
            String lineNum = String.valueOf(i);
            int width = fontMetrics.stringWidth(lineNum);
            g.drawString(lineNum + " ", MARGIN + currentRowWidth - width - 1, start);
            start += nLineHeight;
        }
        setPreferredSize(endLineNum);
    }
}

