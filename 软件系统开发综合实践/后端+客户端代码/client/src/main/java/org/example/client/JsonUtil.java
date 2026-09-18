package org.example.client;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.util.List;

public class JsonUtil {
    private static final ObjectMapper mapper = new ObjectMapper();

    // 解析登录返回的 User 对象
    public static User parseLoginUser(String json) throws Exception {
        JsonNode root = mapper.readTree(json);
        JsonNode data = root.path("data");
        return mapper.treeToValue(data, User.class);
    }

    // 解析借阅记录列表
    public static List<BorrowRecord> parseBorrowRecords(String json) throws Exception {
        JsonNode root = mapper.readTree(json);
        JsonNode rows = root.path("data").path("rows");
        return mapper.readValue(rows.traverse(), new TypeReference<>() {
        });
    }

    public static List<Book> parseBooks(String json) throws Exception {
        JsonNode root = mapper.readTree(json);
        JsonNode rows = root.path("data").path("rows");
        return mapper.readValue(rows.traverse(), new TypeReference<List<Book>>() {});
    }

}
