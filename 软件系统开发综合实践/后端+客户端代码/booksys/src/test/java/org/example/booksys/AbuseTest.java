package org.example.booksys;

import org.example.booksys.entities.AbuseDetectionRequest;
import org.example.booksys.entities.AbuseDetectionResponse;
import org.example.booksys.service.AbuseDetectionService;
import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class AbuseTest {
    @Test
    public void testAbuse(){
        List<String> ls = new ArrayList<>();
        ls.add("傻逼");
        ls.add("你好");
        ls.add("河南人偷井盖");
        AbuseDetectionRequest adr = new AbuseDetectionRequest(ls);
        AbuseDetectionService ads = new AbuseDetectionService();
        AbuseDetectionResponse adrs = ads.detectAbuse(ls);
        for(Integer pred: adrs.getPredictions()){
            System.out.println(pred);
        }
        for(List<Double> prob : adrs.getProbabilities()){
            System.out.println(prob);
        }
    }

    @Test
    public void testTime(){
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        System.out.println(formatter.format(LocalDateTime.now()));
    }
}
