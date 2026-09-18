package org.example.booksys.controller;

import org.example.booksys.entities.Result;
import org.example.booksys.entities.reportDTO.BookTagCountDTO;
import org.example.booksys.entities.reportDTO.BookYearDTO;
import org.example.booksys.entities.reportDTO.WordCloudItemDTO;
import org.example.booksys.service.ReportService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@CrossOrigin
public class ReportController {
    @Autowired
    ReportService reportService;

    @GetMapping("/api/chart/book-year")
    public Result getBookYearCount() {
        List<BookYearDTO> list = reportService.getBookYearCount();
        return Result.success(list);
    }

    @GetMapping("/api/chart/tag-count")
    public Result getBookTagCount() {
        List<BookTagCountDTO> list = reportService.getBookTagCount();
        return Result.success(list);
    }


    @GetMapping("/api/chart/word-cloud-description")
    public Result getDescriptionWordCloud() {
        return Result.success(reportService.generateBookDescWordCloud());
    }


}
