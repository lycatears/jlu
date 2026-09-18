package org.example.booksys.service.impl;

import org.example.booksys.entities.reportDTO.BookTagCountDTO;
import org.example.booksys.entities.reportDTO.BookYearDTO;
import org.example.booksys.entities.reportDTO.WordCloudItemDTO;
import org.example.booksys.mapper.ReportMapper;
import org.example.booksys.service.ReportService;
import org.example.booksys.service.WordCloudGenerator;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ReportServiceImpl implements ReportService {
    @Autowired
    ReportMapper reportMapper;

    @Autowired
    WordCloudGenerator wordCloudGenerator;

    @Override
    public List<BookTagCountDTO> getBookTagCount() {
        return reportMapper.getBookTagCounts();
    }

    @Override
    public List<BookYearDTO> getBookYearCount() {
        return reportMapper.getBookYears();
    }

    // 清除缓存
    @CacheEvict("descriptionWordCloud")
    public void clearCache() {
        System.out.println("清空词云缓存");
    }

    public List<WordCloudItemDTO> generateBookDescWordCloud() {
        return wordCloudGenerator.generate();
    }

    // 每小时刷新缓存
    @Scheduled(cron = "0 0 * * * ?")  // 每小时整点执行
    public void refreshCache() {
        clearCache();                      // 先清除
        wordCloudGenerator.generate();       // 再重新缓存
    }
}
