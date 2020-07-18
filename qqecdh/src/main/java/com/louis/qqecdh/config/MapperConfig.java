package com.louis.qqecdh.config;

import com.fasterxml.jackson.databind.MapperFeature;
import org.springframework.boot.autoconfigure.jackson.Jackson2ObjectMapperBuilderCustomizer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

//JSON忽略KEY的大小写
@Configuration
public class MapperConfig {
    @Bean
    public Jackson2ObjectMapperBuilderCustomizer initJackson(){
        Jackson2ObjectMapperBuilderCustomizer c = buidler -> buidler.featuresToEnable(MapperFeature.ACCEPT_CASE_INSENSITIVE_PROPERTIES);
        return c;
    }
}
