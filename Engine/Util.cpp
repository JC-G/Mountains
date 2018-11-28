#include "Util.h"

namespace Util
{
GLuint LoadComputeShader(const char* file_path,bool includeSDF)
{
    GLuint ComputeID = glCreateShader(GL_COMPUTE_SHADER);

    std::string SDFstring="";
    if (includeSDF)
    {
        SDFstring= ReadShaderFile("sdf.txt");
    }
    std::string ComputeString = ReadShaderFile(file_path);
    std::string FinalString = SDFstring+ComputeString;

    char const* ComputePointer = FinalString.c_str();

    glShaderSource(ComputeID,1,&ComputePointer,NULL);

    glCompileShader(ComputeID);


    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetShaderiv(ComputeID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(ComputeID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(ComputeID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }


    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID,ComputeID);
    glLinkProgram(ProgramID);
    return ProgramID;



}

GLuint LoadShaders(const char* vertex_file_path, const char* frag_file_path)
{
    GLuint VertID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string FragString = ReadShaderFile(frag_file_path);
    std::string VertString = ReadShaderFile(vertex_file_path);
    char const* FragPointer = FragString.c_str();
    char const* VertPointer = VertString.c_str();

    glShaderSource(VertID,1,&VertPointer,NULL);
    glCompileShader(VertID);


    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetShaderiv(VertID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }


    glShaderSource(FragID,1,&FragPointer,NULL);
    glCompileShader(FragID);
    glGetShaderiv(FragID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }



    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID,VertID);
    glAttachShader(ProgramID,FragID);
    glLinkProgram(ProgramID);


    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    return ProgramID;
}

std::string ReadShaderFile(const char* path)
{
    std::string ShaderCode;
    std::ifstream ShaderStream(path,std::ios::in);


    if(ShaderStream.is_open())
    {
        std::string line = "";
        while (std::getline(ShaderStream,line))
        {
            ShaderCode += "\n" + line;
        }
        ShaderStream.close();
        return ShaderCode;
    }
    else
    {

        return "";
    }
}

GLuint loadBMP(const char* file_path, bool is2D)
{
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * data;
    FILE* file = fopen(file_path,"rb");
    if (!file)
    {
        printf("File was not opened");
        return 0;
    }
    if (fread(header,1,54,file)!= 54)
    {
        printf("File is not a BMP");
        return 0;
    }
    if (header[0]!='B' || header[1] !='M')
    {
        printf("File is not a BMP 2");
        return 0;
    }

    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)
        imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)
        dataPos=54; // The BMP header is done that way

    // Create a buffer
    data = new unsigned char [imageSize];

    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

    //Everything is in memory now, the file can be closed
    fclose(file);
    GLuint Texture;
    glGenTextures(1,&Texture);
    if (is2D)
    {
        glBindTexture(GL_TEXTURE_2D,Texture);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGR,GL_UNSIGNED_BYTE,data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else
    {
        glBindTexture(GL_TEXTURE_1D,Texture);
        glTexImage1D(GL_TEXTURE_1D,0,GL_RGB,width,0,GL_BGR,GL_UNSIGNED_BYTE,data);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    }

    return Texture;

}
}
