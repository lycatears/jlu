package org.example.booksys.entities;

public class Result {
    public Integer code;
    public String message;
    public Object data;

    public static Result success(){
        Result result = new Result();
        result.code = 0;
        result.message = "success";
        return result;
    }

    public static Result error(){
        Result result = new Result();
        result.code = 1;
        result.message = "error";
        return result;
    }

    public static Result success(Object data){
        Result result = new Result();
        result.code = 0;
        result.data = data;
        result.message = "success";
        return result;
    }

    public static Result error(Object data){
        Result result = new Result();
        result.code = 1;
        result.data = data;
        result.message = "error";
        return result;
    }

    public static Result info(String message){
        Result result = new Result();
        result.code = 2;
        result.message = message;
        return result;
    }
}
