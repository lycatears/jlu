package com.snl.compiler.mylexer;

/**
 * 词法单元
 *
 */
public enum TokenType {
    ERROR("error"),
    ID("id"),               // 标识符，可以表示变量名，类型名，记录的域名，过程名等，保留字是它的子集


    /************************************************************************
     *                             保留字                                   *
     ************************************************************************/
    PROGRAM("program"), PROCEDURE("procedure"), TYPE("type"), VAR("var"),
    IF("if"), THEN("then"), ELSE("else"), FI("fi"),
    WHILE("while"), DO("do"), ENDWH("endwh"),
    BEGIN("begin"), END("end"),
    READ("read"), WRITE("write"),       // 输入输出语句
    OF("of"), RETURN("return"),

    /************************************************************************
     *                              类型                                    *
     ************************************************************************/

    /*基本类型*/
    INTEGER("integer"),     // 整型
    CHAR("char"),           // 字符类型

    /*结构类型*/ /*同时也是保留字*/
    ARRAY("array"),         // 数组类型
    RECORD("record"),       // 记录类型

    INTC("intc"),           // 无符号整数，用作数组下标和范围

    /************************************************************************
     *                             界限符                                   *
     ************************************************************************/
    /*单字符分界符*/
    EQ("="), LT("<"), EOF("."), EMPTY(""),
    PLUS("+"), MINUS("-"), TIMES("*"), DIVIDE("/"),
    LPAREN("("), RPAREN(")"), LMIDPAREN("["), RMIDPAREN("]"),
    SEMI(";"), COMMA(","), DOT("."),

    /*双字符分界符*/
    ASSIGN(":="),

    /*数组下标界限符*/
    UNDERRANGE(".."),
    ;

    private String str;

    TokenType(String str) {
        this.str = str;
    }

    public String getStr() {
        return str;
    }
}
