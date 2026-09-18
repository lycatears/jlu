package org.example.booksys.service;

import com.huaban.analysis.jieba.JiebaSegmenter;
import org.example.booksys.entities.reportDTO.WordCloudItemDTO;
import org.example.booksys.mapper.ReportMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

@Service
public class WordCloudGenerator {
    @Autowired
    ReportMapper reportMapper;

    @Cacheable("descriptionWordCloud")
    public List<WordCloudItemDTO> generate() {
        // 词频统计逻辑
        List<String> descriptions = reportMapper.getAllDescriptions();
        String allText = String.join(" ", descriptions);

        JiebaSegmenter segmenter = new JiebaSegmenter();
        List<String> words = segmenter.sentenceProcess(allText);

        // 停用词过滤
        Set<String> stopWords = Set.of("）》", "的", "了", "是", "在", "和", "有", "与", "以及", "我们", "他们", "它", "这", "那", "一个", "本书", "。", "，", "基于", "， ", "。 ", "； ");

        Map<String, Integer> freqMap = new HashMap<>();
        for (String word : words) {
            if (word.length() < 2 || stopWords.contains(word)) continue;
            freqMap.put(word, freqMap.getOrDefault(word, 0) + 1);
        }

        return freqMap.entrySet().stream()
                .sorted((a, b) -> b.getValue() - a.getValue())
                .limit(100)
                .map(e -> new WordCloudItemDTO(e.getKey(), e.getValue()))
                .collect(Collectors.toList());
    }
}