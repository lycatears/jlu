package org.example.booksys.service;

import org.example.booksys.entities.AbuseDetectionRequest;
import org.example.booksys.entities.AbuseDetectionResponse;
import org.springframework.http.*;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import java.util.List;

@Service
public class AbuseDetectionService {

    private static final String API_URL = "http://localhost:8000/predict"; // 根据实际API端点调整

    private final RestTemplate restTemplate = new RestTemplate();

    /**
     * 检测文本是否包含辱骂内容
     * @param texts 待检测的文本列表
     * @return 检测结果
     */
    public AbuseDetectionResponse detectAbuse(List<String> texts) {
        // 创建请求体
        AbuseDetectionRequest request = new AbuseDetectionRequest(texts);

        // 设置请求头
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_JSON);

        // 创建HTTP实体
        HttpEntity<AbuseDetectionRequest> entity = new HttpEntity<>(request, headers);

        // 发送POST请求
        ResponseEntity<AbuseDetectionResponse> response = restTemplate.exchange(
                API_URL,
                HttpMethod.POST,
                entity,
                AbuseDetectionResponse.class);

        return response.getBody();
    }

    /**
     * 简化方法 - 只获取预测结果
     * @param texts 待检测的文本列表
     * @return 预测结果列表 (1=辱骂, 0=正常)
     */
    public List<Integer> detectAbuseSimple(List<String> texts) {
        AbuseDetectionResponse response = detectAbuse(texts);
        return response.getPredictions();
    }

    /**
     * 检测单个文本是否包含辱骂内容
     * @param text 待检测的文本
     * @return 是否是辱骂内容 (true=辱骂, false=正常)
     */
    public boolean isAbusive(String text) {
        List<String> texts = List.of(text);
        AbuseDetectionResponse response = detectAbuse(texts);
        return response.getPredictions().get(0) == 1;
    }

    /**
     * 获取辱骂内容的概率
     * @param text 待检测的文本
     * @return 辱骂概率 (0.0-1.0)
     */
    public double getAbuseProbability(String text) {
        List<String> texts = List.of(text);
        AbuseDetectionResponse response = detectAbuse(texts);
        // probabilities数组中第二个值是辱骂概率
        return response.getProbabilities().get(0).get(1);
    }
}