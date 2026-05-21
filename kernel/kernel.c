void main(){
    char* video_memory = (char*)(0xb8000 + 1600);
    char* message =  "Kernel Loaded Sucessfully";
    int i = 0;
   while(*(message + i) != '\0'){
    *(video_memory + (i*2)) = *(message + i);
    *(video_memory + i*2 + 1) = 0x0a;
    i++;
   }
}