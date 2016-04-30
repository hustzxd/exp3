    #include <stdio.h>  
      
    #define BUFFER_SIZE  1024  
      
    int main(int argc, char *argv[])  
    {  
        FILE *from_fp, *to_fp;  
        int bytes_read, bytes_write;  
        char *ptr;  
        char buffer[BUFFER_SIZE];  
      
        if(argc != 3)       //参数包括源文件名与目标文件名  
        {  
            printf("Input failed!\n");  
            return 1;  
        }  
      
        if( (from_fp = fopen(argv[1],"r")) == NULL )    //以只读方式打开源文件名  
        {  
            printf("File is not exist\n");  
            return 1;  
        }  
          
        if((to_fp = fopen(argv[2],"w+")) == NULL)      //打开第二个文件  
        {  
            printf("Open file failed!\n");    
            return 1;  
        }  
      
        while(bytes_read = fread(buffer, 1, BUFFER_SIZE, from_fp))  //读取BUFFSIZE大小字节  
        {  
            printf("%d\n", bytes_read);
            if(bytes_read > 0)           //读取有效数据  
            {  
                ptr = buffer;  
                while(bytes_write = fwrite(ptr, 1, bytes_read, to_fp))  //写数据到目标文件  
                {  
                    if(bytes_write == bytes_read)           //写完      
                        break;  
                    else if(bytes_write > 0)         //未写完  
                    {  
                        ptr += bytes_write;  
                        bytes_read -= bytes_write;  
                    }  
                }  
                if(bytes_write == 0)            //写错误  
                    break;  
            }  
        }  
          
        fclose(from_fp);  
        fclose(to_fp);  
      
        return 0;  
    }  