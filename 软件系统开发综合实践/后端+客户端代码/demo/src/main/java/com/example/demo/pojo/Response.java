package com.example.demo.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class Response {
    private Integer code;
    private String message;
    private Object data;

    public Response() {
        code = 0;
        message = null;
        data = null;
    }
}
