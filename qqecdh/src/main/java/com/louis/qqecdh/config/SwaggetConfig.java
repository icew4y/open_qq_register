package com.louis.qqecdh.config;

import org.springframework.boot.autoconfigure.condition.ConditionalOnProperty;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Profile;
import springfox.documentation.builders.RequestHandlerSelectors;
import springfox.documentation.spi.DocumentationType;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2;

@Configuration
@EnableSwagger2
//@ConditionalOnProperty(name = "swagger.enable", havingValue = "true")
public class SwaggetConfig {

    @Bean
    public Docket api(){
        return new Docket(DocumentationType.SWAGGER_2)
                .useDefaultResponseMessages(false)
                .select()
                .apis(RequestHandlerSelectors.any())
                .build();
    }
}


//        - @Api()用于类；
//        表示标识这个类是swagger的资源
//        - @ApiOperation()用于方法；
//        表示一个http请求的操作
//        - @ApiParam()用于方法，参数，字段说明；
//        表示对参数的添加元数据（说明或是否必填等）
//        - @ApiModel()用于类
//        表示对类进行说明，用于参数用实体类接收
//        - @ApiModelProperty()用于方法，字段
//        表示对model属性的说明或者数据操作更改
//        - @ApiIgnore()用于类，方法，方法参数
//        表示这个方法或者类被忽略
//        - @ApiImplicitParam() 用于方法
//        表示单独的请求参数
//