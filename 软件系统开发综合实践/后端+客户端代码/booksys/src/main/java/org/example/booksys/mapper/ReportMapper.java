package org.example.booksys.mapper;

import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.example.booksys.entities.reportDTO.BookTagCountDTO;
import org.example.booksys.entities.reportDTO.BookYearDTO;

import java.util.List;

@Mapper
public interface ReportMapper {

    List<BookTagCountDTO> getBookTagCounts();

    List<BookYearDTO> getBookYears();

    @Select("SELECT \"description\" FROM BOOKMAN.\"book\" WHERE \"description\" IS NOT NULL")
    List<String> getAllDescriptions();

}
