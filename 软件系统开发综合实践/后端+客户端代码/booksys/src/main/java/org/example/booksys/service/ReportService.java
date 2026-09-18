package org.example.booksys.service;

import org.example.booksys.entities.reportDTO.BookTagCountDTO;
import org.example.booksys.entities.reportDTO.BookYearDTO;
import org.example.booksys.entities.reportDTO.WordCloudItemDTO;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public interface ReportService {
    List<BookTagCountDTO> getBookTagCount();

    List<BookYearDTO> getBookYearCount();

    List<WordCloudItemDTO> generateBookDescWordCloud();
}
